#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
#use_solution bjarki_greedy.cpp
use_solution bjarki_loop_simplify.cpp

# Compile generators
compile gen_random.py # Arguments: left-length right-length seed
compile gen_fixed.py # Arguments: left-sum right-sum seed

# Generate answers to sample cases (optional)
sample 1
sample 2
sample 3

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc edge gen_fixed 2 0

tc random-00 gen_random
tc random-01 gen_random
tc random-02 gen_random
tc random-03 gen_random
tc random-04 gen_random
tc random-05 gen_random
tc random-06 gen_random
tc random-07 gen_random
tc random-08 gen_random
tc random-09 gen_random
tc random-10 gen_random
tc random-11 gen_random
tc random-12 gen_random
tc random-13 gen_random
tc random-14 gen_random
tc random-15 gen_random
tc random-16 gen_random
tc random-17 gen_random
tc random-18 gen_random
tc random-19 gen_random

tc fixed-00 gen_fixed 0 0
tc fixed-01 gen_fixed 0 1
tc fixed-02 gen_fixed 0 5
tc fixed-03 gen_fixed 0 10
tc fixed-04 gen_fixed 0 499
tc fixed-05 gen_fixed 0 500
tc fixed-06 gen_fixed 1 0
tc fixed-07 gen_fixed 1 1
tc fixed-08 gen_fixed 1 5
tc fixed-09 gen_fixed 1 10
tc fixed-10 gen_fixed 1 499
tc fixed-11 gen_fixed 1 500
tc fixed-12 gen_fixed 5 0
tc fixed-13 gen_fixed 5 1
tc fixed-14 gen_fixed 5 5
tc fixed-15 gen_fixed 5 10
tc fixed-16 gen_fixed 5 499
tc fixed-17 gen_fixed 5 500
tc fixed-18 gen_fixed 10 0
tc fixed-19 gen_fixed 10 1
tc fixed-20 gen_fixed 10 5
tc fixed-21 gen_fixed 10 10
tc fixed-22 gen_fixed 10 499
tc fixed-23 gen_fixed 10 500
tc fixed-24 gen_fixed 499 0
tc fixed-25 gen_fixed 499 1
tc fixed-26 gen_fixed 499 5
tc fixed-27 gen_fixed 499 10
tc fixed-28 gen_fixed 499 499
tc fixed-29 gen_fixed 499 500
tc fixed-30 gen_fixed 500 0
tc fixed-31 gen_fixed 500 1
tc fixed-32 gen_fixed 500 5
tc fixed-33 gen_fixed 500 10
tc fixed-34 gen_fixed 500 499
tc fixed-35 gen_fixed 500 500

