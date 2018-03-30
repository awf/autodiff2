# ./nmf_diff.exe 200  100  1 5
# ./nmf_tap_rev.exe 200  100  1 5
# ./nmf_tap_for.exe 200  100  1 5
# python ./NMF.py exponential 200  100  1 5
# ./nmf_diff.exe 400  200  1 5
# ./nmf_tap_rev.exe 400  200  1 5
# ./nmf_tap_for.exe 400  200  1 5
# python ./NMF.py exponential 400  200  1 5
# python ./NMF.py exponential 8000  4000  8 5
# python ./NMF.py exponential 12000 6000  8 5

declare -a files=(
	"./nmf_diff.exe" "./nmf_tap_rev.exe" "./nmf_tap_for.exe" 
	"./nmf_tap_rev_unf.exe" "./nmf_tap_for_unf.exe"
	"python ./NMF.py exponential"
	)

declare -a params=(
	"100 100" "200 100" "400 100" "800 100" "1600 100" "3200 100"
	"100 200" "100 400" "100 800" "100 1600" "100 3200"
	)

echo "=== Run time Usage ==="

for p in "${params[@]}"
do
	echo "$p"
	for f in "${files[@]}"
	do
		echo "$f"
		eval "$f $p 1 5"
	done
done
