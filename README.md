# Glucose

Made by `Gilles Audemard` and `Laurent Simon`
Improved version by `Stephane Branly` to solve a specific problem.
Origine : [https://www.labri.fr/perso/lsimon/glucose/](https://www.labri.fr/perso/lsimon/glucose/)

## Stdout
- `0` for `s UNSATISFIABLE`
- `1` for `s SATISFIABLE`

## Directory overview

mtl/            Minisat Template Library
core/           A core version of the solver glucose (no main here)
simp/           An extended solver with simplification capabilities
parallel/       A multicore version of glucose
README
LICENSE
Changelog

## Build
Like minisat....

cd { simp | parallel }
make rs

## Usage

in simp directory:      ./glucose --help

in parallel directory:  ./glucose-syrup --help