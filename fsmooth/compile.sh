echo "Compiling BA ..."
clang ba.c -O3 -o ba.exe
clang ba.c -O3 -DFUSED -o ba_opt.exe
clang ba.c -O3 -DDPS -o ba_dps.exe
clang ba.c -O3 -DDPS -DFUSED -o ba_opt_dps.exe
clang ba.c -O3 -DBUMP -DDPS -DFUSED -o ba_opt_dps_bump.exe
echo "Compiling GMM ..."
clang gmm.c -O3 -o gmm.exe
clang gmm.c -O3 -DFUSED -o gmm_opt.exe
clang gmm.c -O3 -DDPS -o gmm_dps.exe
clang gmm.c -O3 -DDPS -DFUSED -o gmm_opt_dps.exe
clang gmm.c -O3 -DBUMP -DDPS -DFUSED -o gmm_opt_dps_bump.exe
echo "Compiling Micro Benchmarks ..."
clang micro.c -O3 -o micro_add3.exe
clang micro.c -O3 -DFUSED -o micro_add3_opt.exe
clang micro.c -O3 -DDPS -o micro_add3_dps.exe
clang micro.c -O3 -DDPS -DFUSED -o micro_add3_opt_dps.exe
clang micro.c -O3 -DBUMP -DDPS -DFUSED -o micro_add3_opt_dps_bump.exe
echo "Compiling CPP files ..."
cd ..; cd benchmark_gmm; make
cd ..; cd benchmark_ba; make
cd ..; cd benchmark_micro; make
cd ..; cd fsmooth