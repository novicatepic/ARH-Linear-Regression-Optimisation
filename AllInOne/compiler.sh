#!/bin/bash

gcc -o normal Normal.c
gcc -O3 -mavx2 -o avx AVX.c
gcc -O3 -fopenmp -o OpenMP OpenMP.c
gcc -O3 -fopenmp -mavx2 -o mix MIX.c
