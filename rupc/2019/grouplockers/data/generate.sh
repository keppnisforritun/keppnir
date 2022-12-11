#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki_sliding_window.cpp

# Compile generators
compile gen_random.py # Arguments: n m

# Generate answers to sample cases (optional)
sample 1
sample 2
sample 3
sample 4

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc random-00 gen_random 2 500000
tc random-01 gen_random 100 500000
tc random-02 gen_random 5000 500000
tc random-03 gen_random 10000 500000
tc random-04 gen_random 50000 500000
tc random-05 gen_random 80000 500000
tc random-06 gen_random 90000 500000
tc random-07 gen_random 100000 500000
tc random-08 gen_random 200000 500000
tc random-09 gen_random 300000 500000
tc random-10 gen_random 400000 500000
tc random-11 gen_random 600000 500000
tc random-12 gen_random 800000 500000
tc random-13 gen_random 1000000 500000
tc random-14 gen_random 1400000 500000
tc random-15 gen_random 1800000 500000
tc random-16 gen_random 2000000 500000

