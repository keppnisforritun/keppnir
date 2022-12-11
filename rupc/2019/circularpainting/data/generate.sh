#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki_fraction.cpp

# Compile generators
compile gen_random.py # Arguments: n m seed

# Generate answers to sample cases (optional)
sample 1
sample 2
sample 3

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc random-00 gen_random 1 0
tc random-01 gen_random 1 1
tc random-02 gen_random 2 0
tc random-03 gen_random 2 1
tc random-04 gen_random 2 2
tc random-05 gen_random 5 0
tc random-06 gen_random 5 2
tc random-07 gen_random 10 2
tc random-08 gen_random 20 2
tc random-09 gen_random 30 2
tc random-10 gen_random 60 2
tc random-11 gen_random 180 2
tc random-12 gen_random 360 0
tc random-13 gen_random 360 2
tc random-14 gen_random 360 180
tc random-15 gen_random 360 360

