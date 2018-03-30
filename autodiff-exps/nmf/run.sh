./nmf_diff.exe 2000  1000  1 5
./nmf_tap_for.exe 2000  1000  1 5
python ./NMF.py exponential 2000  1000  1 5
./nmf_diff.exe 4000  2000  1 5
./nmf_tap_for.exe 4000  2000  1 5
python ./NMF.py exponential 4000  2000  1 5
# python ./NMF.py exponential 8000  4000  8 5
# python ./NMF.py exponential 12000 6000  8 5