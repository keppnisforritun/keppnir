#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki.cpp

# Compile generators
compile gen_random.py # Arguments: n m k seed
compile gen_path.py # Arguments: n m k back seed

# Generate answers to sample cases (optional)
sample 1
sample 2
# sample 3

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator

tc_manual ../manual-tests/spfa-tle.in
tc_manual ../manual-tests/042-per-dijkstratest.in
tc_manual ../manual-tests/042-per-dijkstratest-2.in
tc_manual ../manual-tests/max-test.in
tc_manual ../manual-tests/max-test-2.in
tc_manual ../manual-tests/max-test-3.in
tc_manual ../manual-tests/max-test-4.in

tc path-00 gen_path 200000 0 1 false
tc path-01 gen_path 200000 0 2 false
# tc path-02 gen_path 200000 0 4 false
tc path-03 gen_path 200000 0 10 false
tc path-04 gen_path 100000 200000 1 false
tc path-05 gen_path 100000 200000 2 false
# tc path-06 gen_path 100000 200000 4 false
# tc path-07 gen_path 100000 150000 1 false
# tc path-08 gen_path 100000 150000 4 false
tc path-09 gen_path 100000 150000 10 false
# tc path-10 gen_path 100000 150000 50 false
tc path-11 gen_path 100000 150000 100 false
tc path-12 gen_path 100000 150000 5000 false
# tc path-13 gen_path 100000 150000 10000 false
tc path-14 gen_path 100000 150000 50000 false
tc path-back-00 gen_path 100000 200000 1 true
# tc path-back-01 gen_path 100000 200000 2 true
tc path-back-02 gen_path 100000 200000 4 true
# tc path-back-03 gen_path 100000 150000 1 true
tc path-back-04 gen_path 100000 150000 4 true
# tc path-back-05 gen_path 100000 150000 10 true
tc path-back-06 gen_path 100000 150000 50 true
tc path-back-07 gen_path 100000 150000 100 true
# tc path-back-08 gen_path 100000 150000 5000 true
tc path-back-09 gen_path 100000 150000 10000 true
tc path-back-10 gen_path 100000 150000 50000 true

tc random-00 gen_random 2 1 1
tc random-01 gen_random 2 1 2
tc random-02 gen_random 10 90 3
tc random-03 gen_random 10 90 10
tc random-04 gen_random 10 90 5
tc random-05 gen_random 100 1000 10
tc random-06 gen_random 100 1000 50
tc random-07 gen_random 100 1000 1
tc random-08 gen_random 200000 200000 200000
tc random-09 gen_random 200000 200000 100000
tc random-10 gen_random 100000 200000 50000
tc random-11 gen_random 100000 200000 1000
tc random-12 gen_random 10000 200000 1000
tc random-13 gen_random 1000 200000 500
tc random-14 gen_random 10000 200000 5000
tc random-15 gen_random 10000 200000 9000
tc random-16 gen_random 50000 200000 9000

tc_manual ../manual-tests/fire-00.in
tc_manual ../manual-tests/fire-01.in
tc_manual ../manual-tests/fire-02.in
tc_manual ../manual-tests/fire-03.in
tc_manual ../manual-tests/fire-04.in
tc_manual ../manual-tests/fire-06.in
tc_manual ../manual-tests/fire-07.in
tc_manual ../manual-tests/fire-08.in
tc_manual ../manual-tests/fire-09.in
tc_manual ../manual-tests/fire-10.in
tc_manual ../manual-tests/fire-12.in
tc_manual ../manual-tests/fire-13.in
tc_manual ../manual-tests/fire-14.in
tc_manual ../manual-tests/fire-15.in
tc_manual ../manual-tests/fire-16.in

