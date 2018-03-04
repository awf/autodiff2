CC=clang
CPP=clang++
OPTFLAG=-O3 -g
CFLAGS=-std=c++14 -stdlib=libc++
LIBS=-I /usr/local/include/eigen3 
FILES_ADEPT=../adept-1.1/adept/adept.cpp adept-main.cpp
FILES_TAP=tapanade-main.cpp
FILES_ALL=all-main.cpp
C_FILES=diffsmooth/ba.c

compile:
	# $(CPP) $(OPTFLAG) $(CFLAGS) -DDO_BA $(LIBS) $(FILES_ADEPT) -o ba_adept.exe;
	# $(CPP) $(OPTFLAG) $(CFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_ADEPT) -o micro_dot_adept.exe;
	# $(CPP) $(OPTFLAG) $(CFLAGS) -DDO_BA $(LIBS) $(FILES_TAP) -o ba_tap.exe;
	# $(CPP) $(OPTFLAG) $(CFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_TAP) -o micro_dot_tap.exe;
	# $(CPP) $(OPTFLAG) $(CFLAGS) -DDO_GMM $(LIBS) $(FILES_TAP) -o gmm_tap.exe;
	$(CPP) $(OPTFLAG) $(CFLAGS) -DTAPENADE -DDO_GMM $(LIBS) $(FILES_ALL) -o gmm_tap_all.exe;
	$(CPP) $(OPTFLAG) $(CFLAGS) -DTAPENADE -DDO_BA $(LIBS) $(FILES_ALL) -o ba_tap_all.exe;
	$(CPP) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DFUSED -DDO_BA $(LIBS) ba_diff_fused.o $(FILES_ALL) -o ba_diff_fused.exe;
	$(CPP) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DFUSED -DDPS -DDO_BA $(LIBS) ba_diff_fused_dps.o $(FILES_ALL) -o ba_diff_fused_dps.exe;


c:
	$(CC) $(OPTFLAG) -DDIFFSMOOTH -DBUMP -DFUSED -DDO_BA $(C_FILES) -c -o ba_diff_fused.o;
	$(CC) $(OPTFLAG) -DDIFFSMOOTH -DBUMP -DFUSED -DDPS -DDO_BA $(C_FILES) -c -o ba_diff_fused_dps.o;