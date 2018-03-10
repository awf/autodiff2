clang -O3 nmf-main.c -DBUMP -o nmf.exe
./nmf.exe 2000  1000  1 5
python ./NMF.py exponential 2000  1000  1 5
./nmf.exe 4000  2000  1 5
python ./NMF.py exponential 4000  2000  1 5
# python ./NMF.py exponential 8000  4000  8 5
# python ./NMF.py exponential 12000 6000  8 5