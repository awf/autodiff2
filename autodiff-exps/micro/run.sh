declare -a files=(
	# "./mults_diff.exe" "./mults_tap_for.exe" "./mults_tap_rev.exe"
	"./add_diff.exe" "./add_diff_dps.exe" "./add_tap_for.exe" "./add_tap_rev.exe"
	)

declare -a params=(
	# "800" "1600" "3200" "6400" "12800" "25600" "51200" "102400"  # MULTS
	"100" "200" "400" "800" "1600" "3200" "6400" "12800" # ADD
	# "204800" "409600" "819200" "1638400"
	)

for p in "${params[@]}"
do
	echo "$p"
	for f in "${files[@]}"
	do
		echo "$f"
		eval "$f $p 10"
	done
done
