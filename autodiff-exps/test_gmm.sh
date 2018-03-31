echo "TAPENADE FORWARD"
./gmm_tap_for_test.exe 
echo "TAPENADE FUSED FORWARD"
./gmm_tap_fused_for_test.exe
echo "TAPENADE REVERSE"
./gmm_tap_rev_test.exe 
echo "TAPENADE FUSED REVERSE"
./gmm_tap_fused_rev_test.exe
echo "DIFFSMOOTH FORWARD"
./gmm_diff_for_test.exe 
echo "DIFFSMOOTH MULT -- note that it's wrong!"
./gmm_diff_mult_test.exe 
