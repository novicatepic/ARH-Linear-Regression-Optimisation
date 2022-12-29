#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{

    //set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1");
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

        fclose(fp);

        int partialIterations = numElements / 4;
        int leftoverIterations = numElements % 4;

        __m256d rX, rY, rXplusY, rXtimesY;
        __m256d tmp1, tmp2, tmp3, tmp4;

        printf("NUM ELEMENTS = %d\n", numElements);

        //__m128i rZ;
        //rZ = _mm_set_epi64x(1, 2);

        //rX = my_setr_pd(0.0,0.0,0.0,0.0);
        rX = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rXplusY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rXtimesY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        /*rXplusY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rXtimesY = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);*/

        for(int i = 0; i < partialIterations; i++) {
            //printf("X=%4.2lf\n", xValues[i]);
            tmp1 = _mm256_set_pd(xValues[i], xValues[i+1], xValues[i+2], xValues[i+3]);
            tmp2 = _mm256_set_pd(yValues[i], yValues[i+1], yValues[i+2], yValues[i+3]);
            tmp3 = _mm256_set_pd(xValues[i]+yValues[i], xValues[i+1]+yValues[i+1], xValues[i+2]+yValues[i+2], xValues[i+3]+yValues[i+3]);
            tmp4 = _mm256_set_pd(xValues[i]*yValues[i], xValues[i+1]*yValues[i+1], xValues[i+2]*yValues[i+2], xValues[i+3]*yValues[i+3]);
            //tmp3 = _mm256_set_pd(xValues[i], xValues[i+1], xValues[i+2], xValues[i+3]);
            rX = _mm256_add_pd(rX, tmp1);
            //__m256i b1 = _mm256_castpd_si256(rX);
            //long long c = _mm256_extract_epi64(b1, 0);
            //printf("B1 = %lld\n", c);
            //double helper1 = _mm256_extract_pd(rX, 0);
            //printf("HELPER1 = %4.2f\n", helper1);
            rY = _mm256_add_pd(rX, tmp2);
            rXplusY = _mm256_add_pd(rXplusY, tmp3);
            rXtimesY = _mm256_add_pd(rXtimesY, tmp3);
        }

        //__m256i b1 = _mm256_castpd_si256(rX);
        //long long c = _mm256_extract_epi64(b1, 0);
        //printf("%lld\n", c);

        //double helper1 = _mm256_extract_epi64(rX, 0);
        //printf("%4.2f\n", helper1);

        for(int i = 0; i < leftoverIterations; i++) {
            tmp1 = _mm256_set_pd(0.0, 0.0, 0.0, xValues[numElements-i-1]);
            tmp2 = _mm256_set_pd(0.0, 0.0, 0.0, yValues[numElements-i-1]);
            tmp3 = _mm256_set_pd(0.0, 0.0, 0.0, xValues[numElements-i-1]+yValues[numElements-i-1]);
            tmp4 = _mm256_set_pd(0.0, 0.0, 0.0, xValues[numElements-i-1]*yValues[numElements-i-1]);
            rX = _mm256_add_pd(rX, tmp1);
            rY = _mm256_add_pd(rX, tmp2);
            rXplusY = _mm256_add_pd(rXplusY, tmp3);
            rXtimesY = _mm256_add_pd(rXtimesY, tmp3);
        }

        for(int i = 0; i < 3; i++) {
            __m256d b = _mm256_shuffle_pd(rX, rX, 0b0110);
            rX = _mm256_add_pd(rX, b);
            b = _mm256_shuffle_pd(rY, rY, 0b0110);
            rY = _mm256_add_pd(rY, b);
            b = _mm256_shuffle_pd(rXplusY, rXplusY, 0b0110);
            rXplusY = _mm256_add_pd(rXplusY, b);
            b = _mm256_shuffle_pd(rXtimesY, rXtimesY, 0b0110);
            rXtimesY = _mm256_add_pd(rXtimesY, b);
        }

        //double helper = _mm256_extract_pd(rX, 0);
        //printf("%4.2f", helper);

        //__m256i b1 = _mm256_castpd_si256(rX);
        //long long c = _mm256_extract_epi64(b1, 0);
        //printf("%d\n", c);


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


