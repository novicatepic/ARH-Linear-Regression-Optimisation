echo "20 runs of Normal with file that contains 1 000 000 elements"
time for i in {1..20}; do ./normal entry_fileDOUBLE o; done

echo "20 runs of AVX with file that contains 1 000 000 elements"
time for i in {1..20}; do ./avx entry_fileDOUBLE o1; done

echo "20 runs of OpenMP with file that contains 1 000 000 elements"
time for i in {1..20}; do ./OpenMP entry_fileDOUBLE o2; done

echo "20 runs of MIX with file that contains 1 000 000 elements"
time for i in {1..20}; do ./mix entry_fileDOUBLE o3; done

