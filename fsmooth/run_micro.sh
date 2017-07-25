declare -a files=(
   "micro_add3.exe" "micro_add3_gc.exe" "micro_add3_opt.exe" "micro_add3_dps.exe" "micro_add3_opt_dps.exe" "micro_add3_opt_dps_hoist.exe" "micro_add3_opt_dps_hoist_bump.exe"
   "../benchmark_micro/micro_add3_cpp.exe" "../benchmark_micro/micro_add3_eigen_cpp.exe"
   "micro_cross.exe" "micro_cross_gc.exe" "micro_cross_opt.exe" "micro_cross_dps.exe" "micro_cross_opt_dps.exe" "micro_cross_opt_dps_hoist.exe" "micro_cross_opt_dps_hoist_bump.exe"
   "../benchmark_micro/micro_cross_cpp.exe" "../benchmark_micro/micro_cross_eigen_cpp.exe"
   # "micro_dot.exe" "micro_dot_opt.exe" "micro_dot_dps.exe" "micro_dot_opt_dps.exe" "micro_dot_opt_dps_bump.exe" 
   # "../benchmark_micro/micro_dot_cpp.exe" "../benchmark_micro/micro_dot_eigen_cpp.exe"
	)

echo "=== Run time Usage ==="

N=1000000;

for i in "${files[@]}"
do
   # echo "$i"
   # eval "./$i $N"
   l=$(eval "./$i $N" | awk '{print $7;}')
   echo "$i,$l"
done

declare -a iters=(1000 10000 100000 1000000 10000000)

echo "=== Memory Usage ==="

for i in "${files[@]}"
do
	for it in "${iters[@]}"
	do
   		#echo "$i $it"
   		l=$(eval "./memusg.sh './$i $it'" | awk '{print $1;}')
   		echo "$i,$it,$l"
   	done
done