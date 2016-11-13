declare -a files=("ba.exe" "ba_opt.exe" "ba_dps.exe" "ba_opt_dps.exe" "ba_opt_dps_bump.exe" 
	"../benchmark_ba/ba_cpp.exe" "../benchmark_ba/ba_eigen_cpp.exe"
# 	)
# declare -a files=(
    "gmm.exe" "gmm_opt.exe" "gmm_dps.exe" "gmm_opt_dps.exe" "gmm_opt_dps_bump.exe" 
	"../benchmark_gmm/gmm_fixed_cpp.exe" "../benchmark_gmm/gmm_eigen_cpp.exe"
    )

echo "=== Run time Usage ==="

for i in "${files[@]}"
do
   echo "$i"
   eval "./$i"
done

echo "=== Memory Usage ==="

for i in "${files[@]}"
do
   echo "$i"
   eval "./memusg.sh ./$i"
done