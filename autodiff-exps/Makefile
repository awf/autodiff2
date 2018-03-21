CC=clang
CPP=clang++
OPTFLAG=-O3
CFLAGS=-std=c99
CPPFLAGS=-std=c++14 -stdlib=libc++
LIBS=-I /usr/local/include/eigen3 
FILES_ADEPT=../adept-1.1/adept/adept.cpp adept-main.cpp
FILES_TAP=tapanade-main.cpp
FILES_ALL=all-main.cpp

compile:
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_BA $(LIBS) $(FILES_ADEPT) -o ba_adept.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_ADEPT) -o micro_dot_adept.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_BA $(LIBS) $(FILES_TAP) -o ba_tap.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_TAP) -o micro_dot_tap.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM $(LIBS) gmm_tap.o $(FILES_TAP) -o gmm_tap_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DDO_GMM $(LIBS) $(FILES_TAP) -o gmm_diff_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM $(LIBS) tapanade/gmm_all.c $(FILES_ALL) -o gmm_tap_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DFUSED -DDO_GMM $(LIBS) $(FILES_ALL) -o gmm_diff_fused.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_BA $(LIBS) $(FILES_ALL) -o ba_tap_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DDO_BA $(LIBS) -lgc ba_diff.o $(FILES_ALL) -o ba_diff.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DFUSED -DDO_BA $(LIBS)  -lgc ba_diff_fused.o $(FILES_ALL) -o ba_diff_fused.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DFUSED -DDPS -DDO_BA $(LIBS) ba_diff_fused_dps.o $(FILES_ALL) -o ba_diff_fused_dps.exe;


c:
	$(CC) $(OPTFLAG) $(CFLAGS) tapanade/gmm_all.c -c -o gmm_tap.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DGC -DDO_BA diffsmooth/ba.c -c -o ba_diff.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DGC -DFUSED -DDO_BA diffsmooth/ba.c -c -o ba_diff_fused.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DBUMP -DFUSED -DDPS -DDO_BA diffsmooth/ba.c -c -o ba_diff_fused_dps.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DFUSED -DDO_GMM diffsmooth/gmm.c -c -o gmm_diff_fused.o;