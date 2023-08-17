# Algorithm Optimisation

Implement a parallelizable algorithm that performs non-trivial data processing in an arbitrary programming language. Choose the algorithm from the course material.

The program should accept the following command-line arguments: path to the input file, path to the output file, and algorithm parameter values. Provide meaningful default values for all command-line arguments. Analyze, compare, document, and graphically present the acceleration possibilities of the given algorithm using compiler optimizations and at least two of the following approaches:

(a) SIMD programming or (b) cache memory optimizations.

For (a), you may use SIMD optimizations done in task 1.2 (assembly program for data processing) if the same algorithm is chosen for this task.
For (b), measurements need to be conducted (e.g., using the cachegrind tool) to demonstrate that cache optimization truly contributes to cache performance (cache hit rate).
For (b), using a variant of the algorithm with worse cache performance (without adding unnecessary code) as the initial algorithm is permitted.
Multicore processor parallelization (e.g., OpenMP or custom solution).

Distributed processing (e.g., OpenMPI or custom solution).

GPGPU programming (e.g., OpenCL or CUDA).

(10) Combine two of the mentioned approaches to achieve even greater acceleration and document the results. Properly record and graphically represent the results before and after applying optimizations and parallelization. Provide several examples or unit tests that demonstrate the functionalities outlined in the project task specification. Clearly demonstrate that the optimized algorithm variants will produce accurate results.

When measuring execution time:

Conduct measurements for input sizes 𝑁 of varying orders – e.g., 𝑁 ∈ {103, 104, 105, 106, 107, … }.
Perform a warm-up before measurements, i.e., run the algorithm multiple times without measuring.
If the computation time of the algorithm depends on the input data content, conduct measurements for different cases (e.g., random input data and edge cases).
For each input, perform multiple measurements, and document the average value and variance as the final measurement results.



