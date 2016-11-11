# declare -a files=("ba.exe" "ba_opt.exe" "ba_dps.exe" "ba_opt_dps.exe" "ba_opt_dps_bump.exe")
declare -a files=("gmm.exe" "gmm_opt.exe" "gmm_dps.exe" "gmm_opt_dps.exe" "gmm_opt_dps_bump.exe")

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