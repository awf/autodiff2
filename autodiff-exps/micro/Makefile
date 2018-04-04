REV_FOLDER=../tapanade/ADFirstAidKit
FLIB=-L /usr/local/lib/gcc/7/ -lgfortran $(REV_FOLDER)/adBuffer.c $(REV_FOLDER)/adStack.c

all : 
	clang -O3 micro-main.c -DBUMP -DMULTS -o mults_diff.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DTAPENADE -o mults_tap_for.exe
	clang -O3 micro-main.c -DBUMP -DMULTS -DTAPENADE -DREV_MODE $(FLIB) -o mults_tap_rev.exe
