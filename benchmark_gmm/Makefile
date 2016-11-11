CC=clang++
OPTFLAG=-O3
CFLAGS=-std=c++14 -stdlib=libc++
LIBS=-std=c++14 -stdlib=libc++ 
FILES=benchmark_gmm.cpp usecases_gmm.cpp stdafx.cpp

compile:
	$(CC) $(OPTFLAG) $(CFLAGS) $(LIBS) $(FILES) -o gmm_cpp.out;
	$(CC) $(OPTFLAG) $(CFLAGS) -DFIXED_SIZES $(LIBS) $(FILES) -o gmm_fixed_cpp.out;