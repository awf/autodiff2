REV_FOLDER=../tapanade/ADFirstAidKit
FLIB=-L /usr/local/lib/gcc/7/ -lgfortran $(REV_FOLDER)/adBuffer.c $(REV_FOLDER)/adStack.c

all : ba_rod
	clang -O3 micro-main.c -DBUMP -DMULTS -o mults_diff.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DDPS -o mults_diff_dps.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DTAPENADE -o mults_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DTAPENADE -DREV_MODE $(FLIB) -o mults_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DADD -o add_diff.exe
	clang -O3 micro-main.c -DBUMP -DADD -DDPS -o add_diff_dps.exe
	clang -O3 micro-main.c -DBUMP -DADD -DTAPENADE -o add_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DADD -DTAPENADE -DREV_MODE $(FLIB) -o add_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DDOT -o dot_diff.exe
	clang -O3 micro-main.c -DBUMP -DDOT -DDPS -o dot_diff_dps.exe
	clang -O3 micro-main.c -DBUMP -DDOT -DTAPENADE -o dot_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DDOT -DTAPENADE -DREV_MODE $(FLIB) -o dot_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DVEC_MAX -o max_diff.exe
	clang -O3 micro-main.c -DBUMP -DVEC_MAX -DDPS -o max_diff_dps.exe
	clang -O3 micro-main.c -DBUMP -DVEC_MAX -DTAPENADE -o max_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DVEC_MAX -DTAPENADE -DREV_MODE $(FLIB) -o max_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DLSE -o lse_diff.exe
	clang -O3 micro-main.c -DBUMP -DLSE -DDPS -o lse_diff_dps.exe
	clang -O3 micro-main.c -DBUMP -DLSE -DTAPENADE -o lse_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DLSE -DTAPENADE -DREV_MODE $(FLIB) -o lse_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DLSE -DTAPENADE -DFUSED -o lse_tap_fused_for.exe
	clang -O3 micro-main.c -DBUMP -DLSE -DTAPENADE -DFUSED -DREV_MODE $(FLIB) -o lse_tap_fused_rev.exe

ba_rod :
	clang -O3 micro-main.c -DBUMP -DBA_ROD -DFUSED -o ba_rod_diff_fused.exe
	clang -O3 micro-main.c -DBUMP -DBA_ROD -DFUSED -DNOUNROLL -o ba_rod_diff_fused_nounroll.exe
	clang -O3 micro-main.c -DBUMP -DBA_ROD -DFUSED -DNOMOTION -o ba_rod_diff_fused_nomotion.exe
	clang -O3 micro-main.c -DBUMP -DBA_ROD -DFUSED -DDPS -o ba_rod_diff_fused_dps.exe
	clang -O3 micro-main.c -DBUMP -DBA_ROD -DTAPENADE -o ba_rod_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DBA_ROD -DTAPENADE -DREV_MODE $(FLIB) -o ba_rod_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DBA_PROJ -DFUSED -o ba_proj_diff_fused.exe
	clang -O3 micro-main.c -DBUMP -DBA_PROJ -DFUSED -DNOMOTION -o ba_proj_diff_fused_nomotion.exe
	clang -O3 micro-main.c -DBUMP -DBA_PROJ -DFUSED -DDPS -o ba_proj_diff_fused_dps.exe
	clang -O3 micro-main.c -DBUMP -DBA_PROJ -DTAPENADE -o ba_proj_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DBA_PROJ -DTAPENADE -DREV_MODE $(FLIB) -o ba_proj_tap_rev.exe