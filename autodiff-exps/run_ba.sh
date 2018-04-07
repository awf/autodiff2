declare -a files=(
	"./ba_tap_for_all.exe" "./ba_tap_rev_all.exe" 
	"./ba_diff.exe" "./ba_diff_old_fused.exe" "./ba_diff_old_fused_dps.exe"
	"./ba_diff_fused_aos.exe" "./ba_diff_fused_soa.exe"
	)

declare -a params=(
	"ba1" "ba2" "ba3" "ba4"
	)

for p in "${params[@]}"
do
	echo "$p"
	for f in "${files[@]}"
	do
		echo "$f"
		eval "$f ../ba_instances/ ../results_ad/ $p 1 5"
	done
done
