#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki.cpp

# Compile generators
compile gen_random.py # Arguments: left-length right-length seed
compile gen_fixed.py # Arguments: left-sum right-sum seed

# Generate answers to sample cases (optional)
sample 1
sample 2
sample 3

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc random-00 gen_random 1 1
tc random-01 gen_random 1 10
tc random-02 gen_random 10 1
tc random-03 gen_random 10 10
tc random-04 gen_random 100 10
tc random-05 gen_random 10 100
tc random-06 gen_random 100 100
tc random-07 gen_random 1000 100
tc random-08 gen_random 100 1000
tc random-09 gen_random 1000 1000
tc random-10 gen_random 999 1000
tc random-11 gen_random 1000 999
tc random-12 gen_random 4999 5000
tc random-13 gen_random 5000 4999
tc random-14 gen_random 5000 5000

tc fixed-00 gen_fixed 0 0
tc fixed-01 gen_fixed 0 10
tc fixed-02 gen_fixed 10 0
tc fixed-03 gen_fixed 1 1
tc fixed-04 gen_fixed 1 2
tc fixed-05 gen_fixed 2 1
tc fixed-06 gen_fixed 2 2
tc fixed-07 gen_fixed 10 5
tc fixed-08 gen_fixed 5 10
tc fixed-09 gen_fixed 5 5
tc fixed-10 gen_fixed 300000 299999
tc fixed-11 gen_fixed 299999 300000
tc fixed-12 gen_fixed 300000 300000
tc fixed-13 gen_fixed 0 300000
tc fixed-14 gen_fixed 300000 0
tc fixed-15 gen_fixed 300000 200000
tc fixed-16 gen_fixed 200000 200000
tc fixed-17 gen_fixed 200000 300000

