# echo "Compiling BA ..."
# clang ba.c -O3 -o ba.exe
# clang ba.c -O3 -DFUSED -o ba_opt.exe
# clang ba.c -O3 -DDPS -o ba_dps.exe
# clang ba.c -O3 -DDPS -DFUSED -o ba_opt_dps.exe
# clang ba.c -O3 -DBUMP -DDPS -DFUSED -o ba_opt_dps_bump.exe
# echo "Compiling GMM ..."
# clang gmm.c -O3 -o gmm.exe
# clang gmm.c -O3 -DFUSED -o gmm_opt.exe
# clang gmm.c -O3 -DDPS -o gmm_dps.exe
# clang gmm.c -O3 -DDPS -DFUSED -o gmm_opt_dps.exe
# clang gmm.c -O3 -DBUMP -DDPS -DFUSED -o gmm_opt_dps_bump.exe
echo "Compiling HT ..."
clang ht.c -O3 -o ht.exe
clang ht.c -O3 -DFUSED -o ht_opt.exe
clang ht.c -O3 -DDPS -o ht_dps.exe
clang ht.c -O3 -DDPS -DFUSED -o ht_opt_dps.exe
clang ht.c -O3 -DBUMP -DDPS -o ht_dps_bump.exe
# echo "Compiling Micro Benchmarks ..."
# echo "Compiling Add3 ..."
# clang micro.c -O3 -DADD3 -o micro_add3.exe
# clang micro.c -O3 -DADD3 -DFUSED -o micro_add3_opt.exe
# clang micro.c -O3 -DADD3 -DDPS -o micro_add3_dps.exe
# clang micro.c -O3 -DADD3 -DDPS -DFUSED -o micro_add3_opt_dps.exe
# clang micro.c -O3 -DADD3 -DBUMP -DDPS -DFUSED -o micro_add3_opt_dps_bump.exe
# echo "Compiling Cross ..."
# clang micro.c -O3 -DCROSS -o micro_cross.exe
# clang micro.c -O3 -DCROSS -DFUSED -o micro_cross_opt.exe
# clang micro.c -O3 -DCROSS -DDPS -o micro_cross_dps.exe
# clang micro.c -O3 -DCROSS -DDPS -DFUSED -o micro_cross_opt_dps.exe
# clang micro.c -O3 -DCROSS -DBUMP -DDPS -DFUSED -o micro_cross_opt_dps_bump.exe
# echo "Compiling Dot ..."
# clang micro.c -O3 -DDOT -o micro_dot.exe
# clang micro.c -O3 -DDOT -DFUSED -o micro_dot_opt.exe
# clang micro.c -O3 -DDOT -DDPS -o micro_dot_dps.exe
# clang micro.c -O3 -DDOT -DDPS -DFUSED -o micro_dot_opt_dps.exe
# clang micro.c -O3 -DDOT -DBUMP -DDPS -DFUSED -o micro_dot_opt_dps_bump.exe
# echo "Compiling CPP files ..."
# cd ..; cd benchmark_gmm; make
# cd ..; cd benchmark_ba; make
cd ..; cd benchmark_ht; make
# cd ..; cd benchmark_micro; make
# cd ..; cd fsmooth