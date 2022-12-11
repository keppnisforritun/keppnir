#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki_topsort.cpp

# Compile generators
compile gen_random.py # Arguments: n m k seed
compile gen_star.py # Arguments: n k seed
compile gen_star_directed.py # Arguments: n k seed
compile gen_star_directed_one.py # Arguments: n k seed
compile gen_star_directed_two.py # Arguments: n k seed
compile gen_cycle.py # Arguments: n m k seed
compile gen_cycle_bad.py # Arguments: n m k seed
compile gen_cycle_bad_start.py # Arguments: n m k seed
compile gen_path.py # Arguments: n m k seed
compile gen_path_short.py # Arguments: n m k seed

# Generate answers to sample cases (optional)
sample 1
# sample 2
sample 3

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc random-00 gen_random 3 2 1
tc random-01 gen_random 5 5 1
tc random-02 gen_random 5 10 1
tc random-03 gen_random 5 10 2
tc random-04 gen_random 5 20 1
tc random-05 gen_random 5 20 2
tc random-06 gen_random 10 20 1
tc random-07 gen_random 10 20 3
tc random-08 gen_random 10 50 3
tc random-09 gen_random 10 90 3
tc random-10 gen_random 10 90 5
tc random-11 gen_random 500 1000 10
tc random-12 gen_random 500 5000 10
tc random-13 gen_random 500 5000 10
tc random-14 gen_random 500 10000 10
tc random-15 gen_random 500 20000 10
tc random-16 gen_random 500 40000 10
tc random-17 gen_random 500 60000 10
tc random-18 gen_random 500 80000 10
tc random-19 gen_random 500 90000 10
tc random-20 gen_random 500 100000 10
tc random-21 gen_random 500 1000 30
tc random-22 gen_random 500 5000 30
tc random-23 gen_random 500 5000 30
tc random-24 gen_random 500 10000 30
tc random-25 gen_random 500 20000 30
tc random-26 gen_random 500 40000 30
tc random-27 gen_random 500 60000 30
tc random-28 gen_random 500 80000 30
tc random-29 gen_random 500 90000 30
tc random-30 gen_random 500 100000 30
tc random-31 gen_random 5000 5000 30
tc random-32 gen_random 5000 10000 30
tc random-33 gen_random 5000 20000 30
tc random-34 gen_random 5000 40000 30
tc random-35 gen_random 5000 60000 30
tc random-36 gen_random 5000 80000 30
tc random-37 gen_random 5000 90000 30
tc random-38 gen_random 5000 100000 30

tc star-00 gen_star 5000 1
tc star-01 gen_star 5000 2
tc star-02 gen_star 5000 20
tc star-03 gen_star 5000 29
tc star-04 gen_star 5000 30
tc star-d-00 gen_star_directed 5000 1
tc star-d-01 gen_star_directed 5000 2
tc star-d-02 gen_star_directed 5000 20
tc star-d-03 gen_star_directed 5000 29
tc star-d-04 gen_star_directed 5000 30
tc star-d1-00 gen_star_directed_one 5000 1
tc star-d1-01 gen_star_directed_one 5000 2
tc star-d1-02 gen_star_directed_one 5000 20
tc star-d1-03 gen_star_directed_one 5000 29
tc star-d1-04 gen_star_directed_one 5000 30
tc star-d2-00 gen_star_directed_two 5000 2
tc star-d2-01 gen_star_directed_two 5000 20
tc star-d2-02 gen_star_directed_two 5000 29
tc star-d2-03 gen_star_directed_two 5000 30

tc cycle-00 gen_cycle 5000 0 1
tc cycle-01 gen_cycle 5000 0 15
tc cycle-02 gen_cycle 5000 0 30
tc cycle-03 gen_cycle 5000 10000 1
tc cycle-04 gen_cycle 5000 10000 15
tc cycle-05 gen_cycle 5000 10000 30
tc cycle-06 gen_cycle 5000 40000 1
tc cycle-07 gen_cycle 5000 40000 15
tc cycle-08 gen_cycle 5000 40000 30
tc cycle-09 gen_cycle 5000 100000 1
tc cycle-10 gen_cycle 5000 100000 15
tc cycle-11 gen_cycle 5000 100000 30
tc cycle-bad-00 gen_cycle_bad 5000 0 2
tc cycle-bad-01 gen_cycle_bad 5000 0 3
tc cycle-bad-02 gen_cycle_bad 5000 0 15
tc cycle-bad-03 gen_cycle_bad 5000 0 30
tc cycle-bad-04 gen_cycle_bad 5000 5100 2
tc cycle-bad-05 gen_cycle_bad 5000 5100 3
tc cycle-bad-06 gen_cycle_bad 5000 5100 15
tc cycle-bad-07 gen_cycle_bad 5000 5100 30
tc cycle-bad-08 gen_cycle_bad 5000 10000 2
tc cycle-bad-09 gen_cycle_bad 5000 10000 3
tc cycle-bad-10 gen_cycle_bad 5000 10000 15
tc cycle-bad-11 gen_cycle_bad 5000 10000 30
tc cycle-bad-12 gen_cycle_bad 5000 100000 2
tc cycle-bad-13 gen_cycle_bad 5000 100000 3
tc cycle-bad-14 gen_cycle_bad 5000 100000 15
tc cycle-bad-15 gen_cycle_bad 5000 100000 30
tc cycle-bad-start-00 gen_cycle_bad_start 5000 0 2
tc cycle-bad-start-01 gen_cycle_bad_start 5000 0 3
tc cycle-bad-start-02 gen_cycle_bad_start 5000 0 15
tc cycle-bad-start-03 gen_cycle_bad_start 5000 0 30
tc cycle-bad-start-04 gen_cycle_bad_start 5000 5100 2
tc cycle-bad-start-05 gen_cycle_bad_start 5000 5100 3
tc cycle-bad-start-06 gen_cycle_bad_start 5000 5100 15
tc cycle-bad-start-07 gen_cycle_bad_start 5000 5100 30
tc cycle-bad-start-08 gen_cycle_bad_start 5000 10000 2
tc cycle-bad-start-09 gen_cycle_bad_start 5000 10000 3
tc cycle-bad-start-10 gen_cycle_bad_start 5000 10000 15
tc cycle-bad-start-11 gen_cycle_bad_start 5000 10000 30
tc cycle-bad-start-12 gen_cycle_bad_start 5000 100000 2
tc cycle-bad-start-13 gen_cycle_bad_start 5000 100000 3
tc cycle-bad-start-14 gen_cycle_bad_start 5000 100000 15
tc cycle-bad-start-15 gen_cycle_bad_start 5000 100000 30

tc path-00 gen_path 5000 0 30
tc path-01 gen_path 5000 5500 30
tc path-02 gen_path 5000 10000 30
tc path-03 gen_path 5000 100000 30
tc path-short-00 gen_path_short 5000 0 30
tc path-short-01 gen_path_short 5000 5500 30
tc path-short-02 gen_path_short 5000 10000 30
tc path-short-03 gen_path_short 5000 100000 30

tc_manual ../manual-tests/hard-impossible.in
tc_manual ../manual-tests/minimal.in
tc_manual ../manual-tests/minimal-open.in
tc_manual ../manual-tests/disconnected.in

