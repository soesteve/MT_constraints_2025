
# Mutation testing and metamorphic testing for MiniZinc scheduling problems


## Step 1 - generation of follow_ups files

The program to generate the follow ups of the metamorphic rules are in
the folder `follow_ups`.

The programs to generate the follow ups files are in the folder
`follow_ups`. For each metamorphic rule MRx (1<=x<=8) there is
a file called `GEN_FU_MRx.cpp`.  The programs do not have special
requirements, just a standard c++ compiler (for instance g++) and the
`makefile` utilities. They have been tested in Windows and Linux. They
can be compiled with

```
make GEN_FU_MRx
```

and executed with

```
./GEN_FU_MRx
```

These programs take the original RCPSP data from the folder

```
benchmarks/data/data_psplib/j30/J30_*_*.dzn
```

and  generate the files in the folder `benchmarks/data/data_psplib_follow_ups/MRx`





An generate the data corresponding to the metamorphic rules in the
corresponding folders

```
benchmarks/data/data_psplib_follow_ups/MR1/J30_*_*_fu_all_prec.dzn
benchmarks/data/data_psplib_follow_ups/MR2/J30_*_*_fu_cycle.dzn
benchmarks/data/data_psplib_follow_ups/MR3/J30_*_*_fu_d.dzn
benchmarks/data/data_psplib_follow_ups/MR4/J30_*_*_fu_rc_1.dzn
benchmarks/data/data_psplib_follow_ups/MR5/J30_*_*_ fu_1_rc_mayor_rr.dzn
benchmarks/data/data_psplib_follow_ups/MR6/J30_*_*_ fu_rc_and_rr_0.dzn
benchmarks/data/data_psplib_follow_ups/MR7/J30_*_* _fu_rr_max.dzn
benchmarks/data/data_psplib_follow_ups/DUR_0/J30_*_*_fu_dur_0.dzn
```

## Step 2 - mutant generation

The original RCPSP problem is in the folder

```
benchmarks/models/rcpsp.mzn
```

To generate the mutants we must execute a the program `gen_mutants.py`
that is located in the benchmark folder

```
cd benchmarks
python gen_mutants.py --original ./models/rcpsp.mzn --output-dir Mutants
```

This program does not require any external dependency. It needs python 3.x.

## Step 3 - mutant execution

We first generate two files MODELS.txt and DATA.txt with the models we
want to execute (the original RCPSP and its mutants) and the DATA
files (the original J30 data with the follow ups).

There is a program called `launcher.py` that controls all the
executions in parallel. It has the obvious dependency of minizinc.

One can execute the program with

```
python launcher.py
```

If minizinc installed in other location or the files MODELS.txt and
DATA.txt are named differently, we can pass the options at the command
line

```
$ python launcher.py -h
usage: launcher.py [-h] [--model_file MODEL_FILE] [--data_file DATA_FILE] [--minizinc MINIZINC]

Run minizinc tests

options:
  -h, --help            show this help message and exit
  --model_file MODEL_FILE
                        file with list of minizinc models
  --data_file DATA_FILE
                        file with list of data files
  --minizinc MINIZINC   path to minizinc executable
```

The results of the execution is stored in the `out` directory as txt
files with name `model--data.out`. for instance
`rcpsp.mzn--J30_9_9_fu_rc_4.dzn.out` indicates the execution of the
original model of RCPSP `rcpsp.mzn` with the data file `J30_9_9_fu_rc_4.dzn`.



## Step 4 - calculate the raw results

To calculate the results of the analysis we need some programs located
at the `calc_result` folder.

The program `results` reads the results in the `out` folder and
generates a file `out.txt`.
The  executable `results` is generated with

```
make results
```

The we can execute it with the command

```
./results
```

Then we need a precalculation of some results to make the analysis, we
need the program `pre_mr1` which can be compiled with

```
make pre_mr1
```

and execute it

```
./pre_mr1
```

The program `V9_PROCESS_MRs.cpp` that calculate the csv files
with the details of which mutants are killed:

   * `V9_mutants_killed.csv`: Summary file of the mutants killed by
     two processes. The first process is represented by the first
     column and compares the result of the original model with the
     mutated model. The other columns show the results of applying the
     different MRs (1 means killed and/or alive). This information is
     obtained from the files shown below.

   * `V9_killed_different_outputs.csv`: Detailed matrix of the
      process comparing the result of the original model with the
      mutated model.

   * `V9_killed_MRx.csv` with 1 <= x <= 8: Detailed matrices show the
      results of applying the different MRs.


This program is compiled with

```
make V9_PROCESS_MR
```

and executed with

```
./V9_PROCESS_MR
```

Finally, the program `classByConstr.cpp` shows varying detection effectiveness across metamorphic rules and constraint classifications, as reported in the file `classByConstr.csv`.


This program is compiled with

```
make classByConstr
```

and executed with

```
./classByConstr
```


## Step 5 - subsuming mutants calculation

The repository includes a set of scripts to find the set of subsuming mutants, using the algorithm by [Papadakis et al.](https://doi.org/10.1145/2931037.2931040), both in its original form, and in a modified form that samples among duplicated mutants.

The algorithm is implemented in `01-subsumption.py`.
To compute the subsumption relationships across all tests using the unmodified Papadakis algorithm:

```shell
virtualenv .env
source .env/bin/activate
pip install -r requirements.txt
python 01-subsumption.py V9_killed_*.csv --output V9_killed_all.yaml
```

To use the modified algorithm (which can handle duplicated mutants via sampling), add the `--sample-duplicated` flag:

```shell
python 01-subsumption.py V9_killed_*.csv --sample-duplicated --output V9_killed_all.yaml
```

The rest of the `NN-*.py` programs extract various reports from the computed relationships:

* `02-operators.py` computes per-operator statistics for a given set of subsuming relationships (as produced by `01-subsumption.py`).
* `03-within-subsuming.py` computes how many times an operator is part of the subsuming operator set (across one or multiple runs), and what was the minimum size of the operator and subsuming mutant sets it was part of across those runs.
* `04-opstats-table.py` produces a table showing, for each operator, how many mutants survived, were killed and were subsumed, were killed and were subsuming, and were killed and discarded from Papadakis' algorithm due to duplication.
* `05-within-subsuming-table.py` produces a table based on the results from `03-within-subsuming.py`.
* `06-list-subsuming.py` lists the subsuming mutants present in one of the `V9*.yaml` files generated by the `01-subsumption.py` script.

The above scripts include on-line help, which can be shown by passing the `--help` option:

```shell
./01-subsumption.py --help
```

There is also a convenience script that automates the entire pipeline used for analysis:

```shell
./run-all.sh
```

## Distribution of the repository

```
+ README.md  ......................... This file
+ launcher.py  ....................... Program to perform the all the executions of model and data
+ (01*-06*).py ....................... Programs to study subsuming mutants
+ run_all.sh  ........................ Script to launch all subsuming mutant calculations
+ follow_ups ......................... Source programs to generate the follow ups
+ calc_results   ..................... Source programs to generate the csv files
+ benchmarks
|--+ gen_mutants.py .................. Program to generate the mutants
|--+ data
|--|--+ data_psplib   ................ original J30 data
|--|--+ data_psplib_follow_ups ....... follow ups of the metamorphic rules
|--+ models
|--|--+ rcpsp.mzn .................... Original RCPSP model
|--+ Mutants ......................... Generated mutants
+ out  ............................... Folder of the result of the execution of models and data
+ out.txt ............................ Summary of the results of folder out
