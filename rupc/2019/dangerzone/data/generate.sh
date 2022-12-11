#!/usr/bin/env bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen-acm.sh

# For unlimited stack:
ulimit -s unlimited

# Choose your solution
use_solution bjarki.cpp

# Compile generators
compile gen_random.py # Arguments: n min_dist box seed
compile gen_maze.py # Arguments: n b seed

# Generate answers to sample cases (optional)
sample 1
sample 2
# sample 3

# Note: tc automatically adds a deterministic, pseudo-random seed argument to your generator
tc 1random-00 gen_random 12 80 290
tc 1random-01 gen_random 12 80 290
tc 1random-02 gen_random 12 80 289
tc 1random-03 gen_random 100 80 750
tc 1random-04 gen_random 100 80 851
tc 1random-05 gen_random 100 80 850
tc 1random-06 gen_random 5000 80 8000
tc 1random-07 gen_random 5000 80 8000
tc 1random-08 gen_random 500 80 1700
tc 1random-09 gen_random 500 80 1800
tc 1random-10 gen_random 500 80 2000

tc 0maze-possible-00 gen_maze 5000 4 possible
tc 0maze-possible-01 gen_maze 5000 10 possible
tc 0maze-possible-02 gen_maze 5000 20 possible
tc 0maze-possible-03 gen_maze 5000 30 possible
tc 0maze-possible-04 gen_maze 5000 40 possible
tc 0maze-possible-05 gen_maze 5000 50 possible
tc 0maze-possible-06 gen_maze 5000 70 possible
tc 0maze-possible-07 gen_maze 5000 79 possible

tc 2maze-impossible-00 gen_maze 5000 4 impossible
tc 2maze-impossible-01 gen_maze 5000 10 impossible
tc 2maze-impossible-02 gen_maze 5000 20 impossible
tc 2maze-impossible-03 gen_maze 5000 30 impossible
tc 2maze-impossible-04 gen_maze 5000 40 impossible
tc 2maze-impossible-05 gen_maze 5000 50 impossible
tc 2maze-impossible-06 gen_maze 5000 70 impossible
tc 2maze-impossible-07 gen_maze 5000 79 impossible

tc_manual ../manual-tests/00.in
tc_manual ../manual-tests/01.in
tc_manual ../manual-tests/02.in
tc_manual ../manual-tests/empty.in

