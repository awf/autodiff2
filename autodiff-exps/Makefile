CC=clang++
OPTFLAG=-O3 -g
CFLAGS=-std=c++14 -stdlib=libc++
LIBS=-I /usr/local/include/eigen3 
FILES=../adept-1.1/adept/adept.cpp main.cpp

compile:
	$(CC) $(OPTFLAG) $(CFLAGS) -DDO_BA $(LIBS) $(FILES) -o ba.exe;