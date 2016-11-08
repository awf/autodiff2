clang ba.c -O3 -o ba.exe
clang ba.c -O3 -DBUMP -o ba_bump.exe
clang ba.c -O3 -DFUSED -o ba_opt.exe
clang ba.c -O3 -DBUMP -DFUSED -o ba_opt_bump.exe
clang ba.c -O3 -DDPS -o ba_dps.exe
clang ba.c -O3 -DBUMP -DDPS -o ba_dps_bump.exe