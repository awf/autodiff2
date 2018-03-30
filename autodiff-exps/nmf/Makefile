all : 
	clang -O3 nmf-main.c -DBUMP -o nmf_diff.exe
	clang -O3 nmf-main.c -DBUMP -DTAPENADE ../tapanade/submitted/3/default_d-all.c -o nmf_tap_for.exe
	# clang -O3 nmf-main.c -DBUMP -DTAPENADE -DREV_MODE -o nmf_tap_rev.exe