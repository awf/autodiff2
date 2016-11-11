declare -a files=("ba.exe" "ba_opt.exe" "ba_dps.exe" "ba_opt_dps.exe" "ba_opt_dps_bump.exe" "../benchmark_ba/ba_cpp.out")
# declare -a files=("gmm.exe" "gmm_opt.exe" "gmm_dps.exe" "gmm_opt_dps.exe" "gmm_opt_dps_bump.exe" 
# 	"../benchmark_gmm/gmm_cpp.out" "../benchmark_gmm/gmm_fixed_cpp.out")

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