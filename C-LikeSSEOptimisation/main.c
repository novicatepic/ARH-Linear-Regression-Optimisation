#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

int main(int argc, char *argv[])
{


    int numElements = 0;
    FILE *fp;
    fp = fopen(argv[1], "rb");

    if(fp != NULL) {
        double sumX = 0.0, sumY = 0.0, sumXmultiplY = 0.0, sumXSquare = 0.0;
        double a = 0.0, b = 0.0;
        int read = fread(&numElements, sizeof(int), 1, fp);

        double* xValues = (double*)calloc(numElements, sizeof(double));
        double* yValues = (double*)calloc(numElements, sizeof(double));

        read = fread(xValues, sizeof(double), numElements, fp);
        read = fread(yValues, sizeof(double), numElements, fp);

        //Was below, if there would be problems in the future
        fclose(fp);

        /*for(int i = 0; i < numElements; i++) {
            sumXmultiplY += xValues[i] * yValues[i];
            sumY += yValues[i];
            sumX += xValues[i];
            sumXSquare += xValues[i] * xValues[i];
        }

        b = (sumXmultiplY - (sumY / sumX) * sumXSquare) / (sumX - (numElements / sumX) * sumXSquare);
        a = (sumY - numElements * b) / sumX;*/

        int partialIterations = numElements / 4;
        int leftoverIterations = numElements % 4;

        __m256d rX, rY, rXplusY, rXtimesY;
        __m256d tmp1;

        rX = my_setr_pd(0.0,0.0,0.0,0.0);
        //rY = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
        /*rXplusY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rXtimesY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);*/

        for(int i = 0; i < partialIterations; i++) {

        }

        for(int i = 0; i < leftoverIterations; i++) {

        }


        fp = fopen(argv[2], "wb");
        if(fp != NULL) {
            fwrite(&a, sizeof(double), 1, fp);
            fwrite(&b, sizeof(double), 1, fp);
            fclose(fp);
        } else {
            printf("Nested error");
        }


    } else {
        printf("Outer error!");
    }


    return 0;
}

inline __m256d my_setr_pd(double d1, double d2, double d3, double d4) {
  return _mm256_set_pd((double)d1, (double)d2, (double)d3, (double)d4);
}

//PARALLELISATION CODE
/*a = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
  b = _mm256_set_pd(4.0, 3.0, 2.0, 1.0);

  // Perform the vector addition
  c = _mm256_add_pd(a, b);

  // Extract the results from the vector and print them
  double res[4];
  _mm256_store_pd(res, c);*/


