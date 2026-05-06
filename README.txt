
Metamorphic testing of scheduling problems with constraints.


1. Distribution of 'benchmarks' folder:

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


2. The main program that processes the metamorphic relations and generates all files with the 'V9_' prefix and 'csv' extension is V9_PROCESS_MRs.cpp.


 Ficheros de entrada de V9_PROCESS_MRs.cpp:

   * Los distintos makespan que se obtienen de ejecutar un programa minizinc (mzn) con los datos  dadas en un fichero dzn. En concreto, lee los ficheros "out_x.txt" con x = 1,2 y 3.

   * "sum_durations.txt" contiene la suma de las duraciones de todas las tareas de cada fichero dzn.

   * "longer_durations.txt" contiene la mayor duración de todas las tareas de cada fichero dzn. 

 Ficheros de salida de V9_PROCESS_MRs.cpp:

   * "V9_mutants_killed_2025.csv": fichero resumen de los mutantes matados por dos procesos. El primer proceso compara el resultado o1 con o1_mutado y, el segundo proceso por la la  aplicación de las distintas MRs (1 significa muerto y o vivo). Esta información es obtenida de los siguientes ficheros:  

   * "V9_killed_different_outputs.csv" matriz detallada de la columna O1!=O1_mut
   "V9_killed_MRx.csv" con 1 <= x <= 8 

   * "V9_process_MRs_log_2025.txt": log del proceso. 


 3. Los ficheros "mayor_duration.txt" y "sum_durations.txt" se ontienen con los respectivos programas GEN_SUM_and_GREATER_DURATIONS.cpp. 

   En total se procesan 480 x 9 = 4.320 ficheros, que corresponden a  
     benchmarks\data\data_psplib\j30\ J30_*_*.dzn  
     benchmarks\data\data_psplib_follow_ups\MR1\ J30_*_*_fu_all_prec.dzn  (36960)
     benchmarks\data\data_psplib_follow_ups\MR2\ J30_*_*_fu_cycle.dzn   (36960)
     benchmarks\data\data_psplib_follow_ups\MR3\ J30_*_*_fu_d.dzn   (36960)
     benchmarks\data\data_psplib_follow_ups\MR4\ J30_*_*_fu_rc_1.dzn  (36960)
     benchmarks\data\data_psplib_follow_ups\MR5\ J30_*_*_ fu_1_rc_mayor_rr (36960)
     benchmarks\data\data_psplib_follow_ups\MR6\ J30_*_*_ fu_rc_and_rr_0  (36960)
     benchmarks\data\data_psplib_follow_ups\MR7\ J30_*_* _fu_rr_max.dzn  (36960)
     benchmarks\data\data_psplib_follow_ups\DUR_0\ J30_*_*_fu_dur_0.dzn  (36960)

4. El programa "results.cpp" hace un proceso de optimización. 
   La respuesta de la ejecución de un programa (por ejemplo mut-A2DV-1.mnz) con unos determinados datos (por ejemplo J30_1_1.dzn) se encuentra en ficheros de extensión .out (mut-A2DV-1.mzn--J30_1_1.dzn.out).
   Estos fichero .out se localizan en las carpetas "out_1", "out_2" y "out_3".  


5. La generación de los distintos ficheros follow_ups se realizan con los programas GEN_FU_MRx.cpp, con 1 <= x <= 8.  