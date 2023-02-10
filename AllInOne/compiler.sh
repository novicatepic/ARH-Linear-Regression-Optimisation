#!/bin/bash

gcc -O0 -o normal Normal.c

gcc -O0 -mavx2 -o avx AVX.c

gcc -O0 -fopenmp -o OpenMP OpenMP.c

gcc -O0 -fopenmp -mavx2 -o mix MIX.c
