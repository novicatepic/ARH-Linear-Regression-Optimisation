echo "20 runs of Normal with file that contains 100 000 000 elements"
time for i in {1..20}; do ./Normal entry_fileDOUBLE o; done

echo "20 runs of AVX with file that contains 150 000 000 elements"
time for i in {1..20}; do ./AVX entry_fileDOUBLE o1; done

echo "20 runs of OpenMP with file that contains 150 000 000 elements"
time for i in {1..20}; do ./OpenMP entry_fileDOUBLE o2; done

