declare -a files=(
	# "./mults_tap_rev.exe" "./mults_tap_for.exe" "./mults_diff.exe" "./mults_diff_dps.exe" 
	# "./add_tap_rev.exe" "./add_tap_for.exe" "./add_diff.exe" "./add_diff_dps.exe" 
	# "./dot_tap_rev.exe" "./dot_tap_for.exe" "./dot_diff.exe" "./dot_diff_dps.exe"
	"./max_tap_rev.exe" "./max_tap_for.exe" "./max_diff.exe" "./max_diff_dps.exe"
	)

declare -a params=(
	"800" "1600" "3200" "6400" "12800" "25600" "51200"  # MULTS & DOT & MAX
	# "200" "400" "800" "1600" "3200" "6400" "12800" # ADD
	# "102400" "204800" "409600" "819200" "1638400"
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
