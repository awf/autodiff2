REV_FOLDER=../tapanade/ADFirstAidKit
FLIB=-L /usr/local/lib/gcc/7/ -lgfortran $(REV_FOLDER)/adBuffer.c $(REV_FOLDER)/adStack.c

all : 
	clang -O3 nmf-main.c -DBUMP -o nmf_diff.exe
	clang -O3 nmf-main.c -DBUMP -DDPS -o nmf_diff_dps.exe
	clang -O3 nmf-main.c -DBUMP -DTAPENADE ../tapanade/submitted/3/default_d-all.c -o nmf_tap_for.exe
	clang -O3 nmf-main.c -DBUMP -DTAPENADE -DREV_MODE $(FLIB) ../tapanade/submitted/3/default_b-all.c -o nmf_tap_rev.exe
	clang -O3 nmf-main.c -DBUMP -DTAPENADE ../tapanade/submitted/4/default_d-all.c -o nmf_tap_for_unf.exe
	clang -O3 nmf-main.c -DBUMP -DTAPENADE -DREV_MODE $(FLIB) ../tapanade/submitted/4/default_b-all.c -o nmf_tap_rev_unf.exe
	# clang -O3 nmf-main.c -DBUMP -DTAPENADE -DREV_MODE -o nmf_tap_rev.exe
	clang -O3 nmf-main.c -DBUMP -DPOISSON -o nmf_poisson_diff.exe
	clang -O3 nmf-main.c -DBUMP -DDPS -DPOISSON -o nmf_poisson_diff_dps.exe
	clang -O3 nmf-main.c -DBUMP -DPOISSON -DTAPENADE ../tapanade/submitted/3/default_d-all.c -o nmf_poisson_tap_for.exe
	clang -O3 nmf-main.c -DBUMP -DPOISSON -DTAPENADE -DREV_MODE $(FLIB) ../tapanade/submitted/3/default_b-all.c -o nmf_poisson_tap_rev.exe