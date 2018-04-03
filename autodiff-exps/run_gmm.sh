declare -a files=(
	"./gmm_tap_for_all.exe" "./gmm_tap_for_hoist_all.exe" "./gmm_tap_rev_all.exe" 
	"./gmm_tap_fused_for_all.exe" "./gmm_tap_fused_rev_all.exe"
	"./gmm_tap_unfused_for_all.exe"
	"./gmm_diff_fused.exe" 
	)

declare -a params=(
	"gmm_d2_K5" "gmm_d2_K10" "gmm_d2_K25" "gmm_d2_K50" "gmm_d2_K100" "gmm_d2_K200"
	"gmm_d10_K5" "gmm_d10_K10" "gmm_d10_K25" "gmm_d10_K50" "gmm_d10_K100" "gmm_d10_K200"
	"gmm_d20_K5" "gmm_d20_K10" "gmm_d20_K25" "gmm_d20_K50" "gmm_d20_K100" "gmm_d20_K200"
	"gmm_d32_K5" "gmm_d32_K10" "gmm_d32_K25" "gmm_d32_K50" "gmm_d32_K100" "gmm_d32_K200"
	"gmm_d64_K5" "gmm_d64_K10" "gmm_d64_K25" "gmm_d64_K50" "gmm_d64_K100" "gmm_d64_K200"
	)

for p in "${params[@]}"
do
	echo "$p"
	for f in "${files[@]}"
	do
		echo "$f"
		eval "gtimeout 600 $f ../gmm_instances/10k/ ../results_ad/ $p 5 5"
	done
done
