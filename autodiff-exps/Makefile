CC=clang++
OPTFLAG=-O3 -g
CFLAGS=-std=c++14 -stdlib=libc++
LIBS=-I /usr/local/include/eigen3 
FILES_ADEPT=../adept-1.1/adept/adept.cpp adept-main.cpp
FILES_TAP=tapanade-main.cpp

compile:
	$(CC) $(OPTFLAG) $(CFLAGS) -DDO_BA $(LIBS) $(FILES_ADEPT) -o ba_adept.exe;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_ADEPT) -o micro_dot_adept.exe;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_TAP) -o micro_dot_tap.exe;