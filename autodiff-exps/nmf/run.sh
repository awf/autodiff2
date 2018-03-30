./nmf_diff.exe 200  100  1 5
./nmf_tap_rev.exe 200  100  1 5
./nmf_tap_for.exe 200  100  1 5
python ./NMF.py exponential 200  100  1 5
./nmf_diff.exe 400  200  1 5
./nmf_tap_rev.exe 400  200  1 5
./nmf_tap_for.exe 400  200  1 5
python ./NMF.py exponential 400  200  1 5
# python ./NMF.py exponential 8000  4000  8 5
# python ./NMF.py exponential 12000 6000  8 5