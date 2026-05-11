
# Combining mutation testing and metamorphic testing for MiniZinc scheduling problems.


## 1. Distribution of the **benchmarks** folder:


```
+ benchmarks
|--+ data
|--|--+ data_psplib
|--|--|--+ j30
|--|--|--|--+ J30_1_1.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10.dzn
|--|--+ data_psplib_follow_ups
|--|--|--+ MR1
|--|--|--|--+ J30_1_1_fu_all_prec.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_all_prec.dzn
|--|--|--+ MR2
|--|--|--|--+ J30_1_1_fu_cycle.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_cycle.dzn
|--|--|--+ MR3
|--|--|--|--+ J30_1_1_fu_d.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_d.dzn
|--|--|--+ MR4
|--|--|--|--+ J30_1_1_fu_rc_1.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_rc_1.dzn
|--|--|--+ MR5
|--|--|--|--+ J30_1_1_fu_rc_mayor_rr.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_rc_mayor_rr.dzn
|--|--|--+ MR6
|--|--|--|--+ J30_1_1_fu_rc_and_rr_0.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_rc_and_rr_0.dzn
|--|--|--+ MR7
|--|--|--|--+ J30_1_1_fu_rr_max.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_rr_max.dzn
|--|--|--+ MR8
|--|--|--|--+ J30_1_1_fu_dur_0.dzn
|--|--|--|--+ ...
|--|--|--|--+ J30_48_10_fu_dur_0.dzn
|--+ models
|--|--+ rcpsp.mzn
|--+ Mutants
|--|--+ mut-LE2NE-4.mzn
|--|--+ mut-LE2GE-4.mzn
|--|--+ mut-LT2NE-1.mzn
|--|--+ mut-A2M-4.mzn
|--|--+ mut-LE2GE-1.mzn
|--|--+ mut-A2S-5.mzn
|--|--+ mut-LE2LT-1.mzn
|--|--+ mut-GT2LT-1.mzn
|--|--+ mut-GT2NE-4.mzn
|--|--+ mut-A2DV-4.mzn
|--|--+ mut-GT2LT-4.mzn
|--|--+ mut-A2S-2.mzn
|--|--+ mut-A2DV-2.mzn
|--|--+ mut-EQ2LE-1.mzn
|--|--+ mut-S2M-1.mzn
|--|--+ mut-LE2LT-4.mzn
|--|--+ mut-LE2GT-4.mzn
|--|--+ mut-S2A-1.mzn
|--|--+ mut-GT2LT-2.mzn
|--|--+ mut-LE2EQ-3.mzn
|--|--+ mut-LE2GE-2.mzn
|--|--+ mut-GT2LE-2.mzn
|--|--+ mut-LE2GT-2.mzn
|--|--+ mut-GT2LE-4.mzn
|--|--+ mut-A2DV-1.mzn
|--|--+ mut-LE2EQ-4.mzn
|--|--+ mut-GT2EQ-2.mzn
|--|--+ mut-LE2NE-3.mzn
|--|--+ mut-F2E-1.mzn
|--|--+ mut-A2M-2.mzn
|--|--+ mut-GT2EQ-3.mzn
|--|--+ mut-LT2EQ-1.mzn
|--|--+ mut-LE2GE-3.mzn
|--|--+ mut-C2D-2.mzn
|--|--+ mut-EQ2GT-1.mzn
|--|--+ mut-A2S-4.mzn
|--|--+ mut-LE2GT-3.mzn
|--|--+ mut-NE2GT-1.mzn
|--|--+ mut-D2C-1.mzn
|--|--+ mut-F2E-3.mzn
|--|--+ mut-LE2LT-2.mzn
|--|--+ mut-A2M-5.mzn
|--|--+ mut-C2D-1.mzn
|--|--+ mut-A2S-3.mzn
|--|--+ mut-LE2GT-1.mzn
|--|--+ mut-GT2NE-1.mzn
|--|--+ mut-NE2EQ-1.mzn
|--|--+ mut-EQ2NE-1.mzn
|--|--+ mut-GT2EQ-4.mzn
|--|--+ mut-GT2EQ-1.mzn
|--|--+ mut-F2E-2.mzn
|--|--+ mut-E2F-1.mzn
|--|--+ mut-A2S-1.mzn
|--|--+ mut-LE2EQ-1.mzn
|--|--+ mut-LT2GT-1.mzn
|--|--+ mut-CSWAP-1.mzn
|--|--+ mut-A2DV-5.mzn
|--|--+ mut-A2DV-3.mzn
|--|--+ mut-NE2LE-1.mzn
|--|--+ mut-GT2LE-3.mzn
|--|--+ mut-GT2LE-1.mzn
|--|--+ mut-GT2LT-3.mzn
|--|--+ mut-NE2LT-1.mzn
|--|--+ mut-LE2NE-2.mzn
|--|--+ mut-LE2EQ-2.mzn
|--|--+ mut-LT2GE-1.mzn
|--|--+ mut-LE2NE-1.mzn
|--|--+ mut-GT2NE-3.mzn
|--|--+ mut-EQ2LT-1.mzn
|--|--+ mut-A2M-3.mzn
|--|--+ mut-S2DV-1.mzn
|--|--+ mut-LE2LT-3.mzn
|--|--+ mut-GT2NE-2.mzn
|--|--+ mut-A2M-1.mzn
|--|--+ mut-LT2LE-1.mzn
|--|--+ mut-F2E-4.mzn
```

## 2. This section details the C++ source code contained in the **Project_MT_c++** folder.

### 2.1 The main program.

**V9_PROCESS_MRs.cpp** is the main program that processes the metamorphic relations MR1, ..., MR8 and, generates all files with the 'V9_' prefix and 'csv' extension. Specifically, this program generates the file **V9_mutants_killed.csv** which shows which mutants are killed.  This program also generates the log file **V9_process_MRs_log.txt**.



* Input files of **V9_PROCESS_MRs.cpp**:

   * **sum_durations.txt**: It contains the sum of the durations of all the tasks in each dzn file.

   * **longer_durations.txt**: It contains the longest duration of all tasks in each dzn file. 

   * **out_1.txt**, **out_2.txt** and **out_3.txt**: These files contain the different makespans obtained from running the Minizinc (mzn) programs, model and mutants,
with the data (dzn), originals and follow-ups.

* Output files of **V9_PROCESS_MRs.cpp**:

   * **V9_mutants_killed.csv**: Summary file of the mutants killed by two processes. The first process is represented by the first column and compares the result of the original model with the mutated model. The other columns show the results of applying the different MRs (1 means killed and/or alive). This information is obtained from the files shown below.

    * **V9_killed_different_outputs.csv**: Detailed matrix of the process comparing the result of the original model with the mutated model.

    * **V9_killed_MRx.csv** with 1 <= x <= 8: Detailed matrices show the results of applying the different MRs (1 means dead or alive).

    * **V9_process_MRs_log.txt**: Process log.



### 2.2. Auxiliary program.
**GEN_SUM_and_GREATER_DURATIONS.cpp**: This program processes the following files to obtain, for each file, the sum of the durations of the tasks and the longest-lasting task.

``` 
     benchmarks\data\data_psplib\j30\ J30_*_*.dzn  
     benchmarks\data\data_psplib_follow_ups\MR1\ J30_*_*_fu_all_prec.dzn  
     benchmarks\data\data_psplib_follow_ups\MR2\ J30_*_*_fu_cycle.dzn   
     benchmarks\data\data_psplib_follow_ups\MR3\ J30_*_*_fu_d.dzn   
     benchmarks\data\data_psplib_follow_ups\MR4\ J30_*_*_fu_rc_1.dzn  
     benchmarks\data\data_psplib_follow_ups\MR5\ J30_*_*_ fu_1_rc_mayor_rr.dzn 
     benchmarks\data\data_psplib_follow_ups\MR6\ J30_*_*_ fu_rc_and_rr_0.dzn  
     benchmarks\data\data_psplib_follow_ups\MR7\ J30_*_* _fu_rr_max.dzn  
     benchmarks\data\data_psplib_follow_ups\DUR_0\ J30_*_*_fu_dur_0.dzn  
```

### 2.3. Optimization process.

The program **results.cpp** performs an optimization process.

First, let's clarify that the output of a program (e.g., mut-A2DV-1.mnz) running on specific data (e.g., J30_1_1.dzn) is stored in an .out file (mut-A2DV-1.mzn--J30_1_1.dzn.out).
Then, the **results.cpp** code processes the answers (.out) contained in the "out_1", "out_2", and "out_3" folders to extract the *makespan* values (or the "TIMEOUT" and "UNSATISFIABLE"). Specifically, this program uses regular expressions to find the information.
The output files, **out_1.txt**, **out_2.txt**, and **out_3.txt** contain a pair for each processed file; its first component is the name of the .out file and the second component is:


 * -2 is TIMEOUT 
 * -1 is UNSATISFIABLE 
 * A value >= 0 corresponds to the makespan 



### 2.4. La generación de los distintos ficheros follow_ups se realizan con los programas GEN_FU_MRx.cpp, con 1 <= x <= 8.  


