/****************************************************************************************[Dimacs.h]
Copyright (c) 2003-2006, Niklas Een, Niklas Sorensson
Copyright (c) 2007-2010, Niklas Sorensson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/

#ifndef Glucose_Dimacs_h
#define Glucose_Dimacs_h

#include <stdio.h>
#include <string>

#include "utils/ParseUtils.h"
#include "core/SolverTypes.h"

namespace Glucose {

//=================================================================================================
// DIMACS Parser:

template<class B, class Solver>
static void readClause(B& in, Solver& S, vec<Lit>& lits) {
    int     parsed_lit, var;
    lits.clear();
    for (;;){
        parsed_lit = parseInt(in);
        if (parsed_lit == 0) break;
        var = abs(parsed_lit)-1;
        while (var >= S.nVars()) S.newVar();
        lits.push( (parsed_lit > 0) ? mkLit(var) : ~mkLit(var) );
    }
}

template<class B, class Solver>
static void parse_DIMACS_main(B& in, Solver& S, std::string clause, int nombre_clauses) {
    vec<Lit> lits;
    int clauses = nombre_clauses;
    int cnt     = 0;
  
    for (;;){
        skipWhitespace(in);
        if (*in == EOF) break;
        else if (*in == 'c' || *in == 'p')
            skipLine(in);
        else{
            cnt++;
            readClause(in, S, lits);
            S.addClause_(lits); }
    }
    if(clause != "")
    {
        cnt++;
        bool neg = false;
        int val = 0;
        int parsed_lit;
        int var;
        lits.clear();
        for (int i = 0; i < clause.length(); i++)
        {
            if      (clause[i] == '-') neg = true;
            else if (clause[i] == '+') neg = false;
            else if (clause[i] >= '0' && clause[i] <= '9')
                val = val*10 + (clause[i] - '0');
            else if (clause[i] == ' ')
            {
                parsed_lit = neg ? -val : val;
                val = 0;
                var = abs(parsed_lit) - 1;
                lits.push( (parsed_lit > 0) ? mkLit(var) : ~mkLit(var) );
            }
            else if (clause[i] < '0' || clause[i] > '9') fprintf(stderr, "PARSE ERROR! Unexpected char: %c\n", clause[i]), exit(3);
        }
        S.addClause_(lits);
        clauses++;
    }
}

// Inserts problem into solver.
//
template<class Solver>
static void parse_DIMACS(gzFile input_stream, Solver& S, std::string clause, int nombre_clauses) {
    StreamBuffer in(input_stream);
    parse_DIMACS_main(in, S, clause, nombre_clauses); }

//=================================================================================================
}

#endif
