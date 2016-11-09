declare -a files=("ba.exe" "ba_bump.exe" "ba_opt.exe" "ba_opt_bump.exe" "ba_dps.exe" "ba_dps_bump.exe" "ba_opt_dps.exe" "ba_opt_dps_bump.exe")

for i in "${files[@]}"
do
   echo "$i"
   eval "./$i"
done
