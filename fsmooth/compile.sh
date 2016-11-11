clang ba.c -O3 -o ba.exe
# clang ba.c -O3 -DBUMP -o ba_bump.exe
clang ba.c -O3 -DFUSED -o ba_opt.exe
# clang ba.c -O3 -DBUMP -DFUSED -o ba_opt_bump.exe
clang ba.c -O3 -DDPS -o ba_dps.exe
# clang ba.c -O3 -DBUMP -DDPS -o ba_dps_bump.exe
clang ba.c -O3 -DDPS -DFUSED -o ba_opt_dps.exe
clang ba.c -O3 -DBUMP -DDPS -DFUSED -o ba_opt_dps_bump.exe
clang gmm.c -O3 -o gmm.exe
clang gmm.c -O3 -DFUSED -o gmm_opt.exe
clang gmm.c -O3 -DDPS -o gmm_dps.exe
clang gmm.c -O3 -DDPS -DFUSED -o gmm_opt_dps.exe
clang gmm.c -O3 -DBUMP -DDPS -DFUSED -o gmm_opt_dps_bump.exe