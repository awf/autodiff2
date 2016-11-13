CC=clang++
OPTFLAG=-O3
CFLAGS=-std=c++14 -stdlib=libc++
LIBS=-std=c++14 -stdlib=libc++ 
FILES=benchmark_micro.cpp stdafx.cpp

compile:
	$(CC) $(OPTFLAG) $(CFLAGS) $(LIBS) $(FILES) -o micro_add3_cpp.exe;
	$(CC) $(OPTFLAG) $(CFLAGS) $(LIBS) $(FILES) -DEIGEN -I /usr/local/include/eigen3 -o micro_add3_eigen_cpp.exe;