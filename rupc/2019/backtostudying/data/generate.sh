#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki_greedy.cpp

# Compile generators
compile gen_many_small.py # Arguments: num-small len-small len-last seed
compile gen_random.py # Arguments: n max-len bounded seed
compile gen_unique.py # Arguments: n
compile gen_unique_offset.py # Arguments: n offset
compile gen_back.py # Arguments: n sum

# Generate answers to sample cases (optional)
sample 1
sample 2
sample 3
sample 4

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc one-large-00 gen_many_small 0 0 1
tc one-large-01 gen_many_small 0 0 12345
tc one-large-02 gen_many_small 0 0 1000000000

tc one-small-one-large-00 gen_many_small 1 1 1000000000
tc one-small-one-large-01 gen_many_small 1 1 999999999
tc one-small-one-large-02 gen_many_small 1 1 999999998
tc one-small-one-large-03 gen_many_small 1 1 999999997
tc one-small-one-large-04 gen_many_small 1 1 999999996

tc many-small-00 gen_many_small 100 1000000 899999900
tc many-small-01 gen_many_small 100 999999 899999900
tc many-small-02 gen_many_small 100 1000001 899999900
tc many-small-03 gen_many_small 99 1000000 899999900
tc many-small-04 gen_many_small 101 1000000 899999900
tc many-small-05 gen_many_small 100 1000000 899999901
tc many-small-06 gen_many_small 100 1000000 899999899

tc many-small-07 gen_many_small 199999 100 100000000
tc many-small-08 gen_many_small 199999 100 1000000000
tc many-small-09 gen_many_small 199999 100 500000000
tc many-small-10 gen_many_small 199999 100 979800000
tc many-small-11 gen_many_small 199999 100 979800001
tc many-small-12 gen_many_small 199999 100 979799999

tc unique-00 gen_unique 200000
tc unique-01 gen_unique 200000
tc unique-02 gen_unique 200000
tc unique-offset-00 gen_unique_offset 200000 1
tc unique-offset-01 gen_unique_offset 200000 2
tc unique-offset-02 gen_unique_offset 200000 -1
tc unique-offset-03 gen_unique_offset 200000 -2

tc random-00 gen_random 200000 100 false
tc random-01 gen_random 200000 1000 false
tc random-02 gen_random 200000 5000 false

tc random-bounded-00 gen_random 200000 1000 true
tc random-bounded-01 gen_random 200000 2000 true
tc random-bounded-02 gen_random 200000 4000 true
tc random-bounded-03 gen_random 200000 5000 true
tc random-bounded-04 gen_random 200000 4500 true
tc random-bounded-05 gen_random 200000 4800 true
tc random-bounded-06 gen_random 200000 8000 true
tc random-bounded-07 gen_random 200000 10000 true

tc back-00 gen_back 200000 1000000000
tc back-01 gen_back 200000 200000
tc back-02 gen_back 200000 999999999
tc back-03 gen_back 200000 200000000000000
tc back-04 gen_back 200000 2147483647
tc back-05 gen_back 200000 3000000000
tc back-06 gen_back 200000 4000000000
tc back-07 gen_back 200000 5000000000
tc back-08 gen_back 200000 6000000000

