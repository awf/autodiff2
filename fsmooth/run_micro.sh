declare -a files=(
	"micro_add3.exe" "micro_add3_opt.exe" "micro_add3_dps.exe" "micro_add3_opt_dps.exe" "micro_add3_opt_dps_bump.exe" 
   "../benchmark_micro/micro_add3_cpp.exe" "../benchmark_micro/micro_add3_eigen_cpp.exe"
	)

echo "=== Run time Usage ==="

N=1000000;

for i in "${files[@]}"
do
   echo "$i"
   eval "./$i $N"
   # l=$(eval "./$i $N" | awk '{print $7;}')
   # echo "$i,$l"
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