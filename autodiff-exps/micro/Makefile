REV_FOLDER=../tapanade/ADFirstAidKit
FLIB=-L /usr/local/lib/gcc/7/ -lgfortran $(REV_FOLDER)/adBuffer.c $(REV_FOLDER)/adStack.c

all : 
	clang -O3 micro-main.c -DBUMP -DMULTS -o mults_diff.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DTAPENADE -o mults_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DTAPENADE -DREV_MODE $(FLIB) -o mults_tap_rev.exe
	clang -O3 micro-main.c -DBUMP -DADD -o add_diff.exe
	clang -O3 micro-main.c -DBUMP -DADD -DDPS -o add_diff_dps.exe
	clang -O3 micro-main.c -DBUMP -DADD -DTAPENADE -o add_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DADD -DTAPENADE -DREV_MODE $(FLIB) -o add_tap_rev.exe
