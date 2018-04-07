CC=clang
FC=gfortran -g
CPP=clang++
OPTFLAG=-O3
CFLAGS=-std=c99
CPPFLAGS=-std=c++14 -stdlib=libc++
LIBS=-I /usr/local/include/eigen3 
REV_FOLDER=tapanade/ADFirstAidKit
TAP_SUB_FOLDER=tapanade/submitted
FLIB=-L /usr/local/lib/gcc/7/ -lgfortran $(REV_FOLDER)/adBuffer.c $(REV_FOLDER)/adStack.c
FILES_ADEPT=../adept-1.1/adept/adept.cpp adept-main.cpp
FILES_TAP=tapanade-main.cpp
FILES_ALL=all-main.cpp

all : c test compile

compile : gmm_all ba_all
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_BA $(LIBS) $(FILES_ADEPT) -o ba_adept.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_ADEPT) -o micro_dot_adept.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_BA $(LIBS) $(FILES_TAP) -o ba_tap.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DDO_MICRO -DDOT $(LIBS) $(FILES_TAP) -o micro_dot_tap.exe;
	# $(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM $(LIBS) adBuffer.o adStack.o tapanade/gmm_all.c $(FILES_ALL) -o gmm_tap_all.exe;
	

ba_all : c
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_BA $(LIBS) $(TAP_SUB_FOLDER)/6/ba_d-all.c $(FILES_ALL) -o ba_tap_for_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_BA -DREV_MODE $(LIBS) $(FLIB) $(TAP_SUB_FOLDER)/6/ba_b-all.c $(FILES_ALL) -o ba_tap_rev_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DDO_BA $(LIBS) -lgc ba_diff.o $(FILES_ALL) -o ba_diff.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DOLD_FUSED -DDO_BA $(LIBS)  -lgc ba_diff_old_fused.o $(FILES_ALL) -o ba_diff_old_fused.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DOLD_FUSED -DDPS -DDO_BA $(LIBS) ba_diff_old_fused_dps.o $(FILES_ALL) -o ba_diff_old_fused_dps.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DFUSED -DAOS -DDO_BA $(LIBS) -lgc ba_diff_fused_aos.o $(FILES_ALL) -o ba_diff_fused_aos.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DFUSED -DSOA -DDO_BA $(LIBS) -lgc ba_diff_fused_soa.o $(FILES_ALL) -o ba_diff_fused_soa.exe;

gmm_all :
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM $(LIBS) tapanade/gmm_all.c $(FILES_ALL) -o gmm_tap_for_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM -DHOIST $(LIBS) tapanade/gmm_all.c $(FILES_ALL) -o gmm_tap_for_hoist_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_FUSED -DDO_GMM $(LIBS) $(TAP_SUB_FOLDER)/5/gmm_fused.h_d-all.c $(FILES_ALL) -o gmm_tap_fused_for_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM -DREV_MODE $(LIBS) $(FLIB) tapanade/gmm_b-all.c tapanade/gmm_all.c $(FILES_ALL) -o gmm_tap_rev_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_FUSED -DDO_GMM -DREV_MODE $(LIBS) $(FLIB) $(TAP_SUB_FOLDER)/5/gmm_fused.h_b-all.c $(FILES_ALL) -o gmm_tap_fused_rev_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_UNFUSED -DDO_GMM $(LIBS) $(TAP_SUB_FOLDER)/7/gmm_unfused_d-all.c $(FILES_ALL) -o gmm_tap_unfused_for_all.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DFUSED -DDO_GMM $(LIBS) $(FILES_ALL) -o gmm_diff_fused.exe;

test :
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM $(LIBS) tapanade/gmm_all.c $(FILES_TAP) -o gmm_tap_for_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAPENADE -DDO_GMM -DREV_MODE $(LIBS) $(FLIB) $(TAP_SUB_FOLDER)/2/default_b-all.c $(FILES_TAP) -o gmm_tap_rev_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_FUSED -DDO_GMM $(LIBS) $(TAP_SUB_FOLDER)/5/gmm_fused.h_d-all.c $(FILES_TAP) -o gmm_tap_fused_for_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_FUSED -DDO_GMM -DREV_MODE $(LIBS) $(FLIB) $(TAP_SUB_FOLDER)/5/gmm_fused.h_b-all.c $(FILES_TAP) -o gmm_tap_fused_rev_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_UNFUSED -DDO_GMM $(LIBS) $(TAP_SUB_FOLDER)/7/gmm_unfused_d-all.c $(FILES_TAP) -o gmm_tap_unfused_for_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DTAP_UNFUSED -DDO_GMM -DREV_MODE $(LIBS) $(FLIB) $(TAP_SUB_FOLDER)/7/gmm_unfused_b-all.c $(FILES_TAP) -o gmm_tap_unfused_rev_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DDO_GMM $(LIBS) $(FILES_TAP) -o gmm_diff_for_test.exe;
	$(CPP) $(OPTFLAG) $(CPPFLAGS) -DDIFFSMOOTH -DDO_GMM -DMULT_MODE $(LIBS) $(FILES_TAP) -o gmm_diff_mult_test.exe;

c :
	# $(CC) $(OPTFLAG) $(CFLAGS) tapanade/gmm_all.c -c -o gmm_tap.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DBUMP -DDO_BA diffsmooth/ba.c -c -o ba_diff.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DBUMP -DOLD_FUSED -DDO_BA diffsmooth/ba.c -c -o ba_diff_old_fused.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DBUMP -DFUSED -DAOS -DDO_BA diffsmooth/ba.c -c -o ba_diff_fused_aos.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DBUMP -DFUSED -DSOA -DDO_BA diffsmooth/ba.c -c -o ba_diff_fused_soa.o;
	$(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DBUMP -DOLD_FUSED -DDPS -DDO_BA diffsmooth/ba.c -c -o ba_diff_old_fused_dps.o;
	# $(CC) $(OPTFLAG) $(CFLAGS) tapanade/gmm_b-all.c -c -o gmm_b-all.o;
	# $(CC) $(OPTFLAG) $(CFLAGS) -DDIFFSMOOTH -DFUSED -DDO_GMM diffsmooth/gmm.c -c -o gmm_diff_fused.o;

clean :
	rm *.o *.exe