declare -a files=(
	"./gmm_tap_for_all.exe" "./gmm_tap_for_hoist_all.exe" "./gmm_tap_rev_all.exe" 
	"./gmm_tap_fused_for_all.exe"
	"./gmm_diff_fused.exe" 
	)

declare -a params=(
	"gmm_d2_K5" "gmm_d2_K10" "gmm_d2_K25" "gmm_d2_K50"
	"gmm_d10_K5" "gmm_d10_K10" "gmm_d10_K25" "gmm_d10_K50"
	)

for p in "${params[@]}"
do
	echo "$p"
	for f in "${files[@]}"
	do
		echo "$f"
		eval "$f ../gmm_instances/10k/ ../results_ad/ $p 100 5"
	done
done
