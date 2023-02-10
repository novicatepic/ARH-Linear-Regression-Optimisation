#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef union {
    __m256d m256d;
    double d[4];
} m256d_union;

int main(int argc, char *argv[])
{
    /*clock_t start, end;
    start = clock();*/

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

        m256d_union rX, rY, rXtimesX, rXtimesY;
        m256d_union tmp1, tmp2, tmp3, tmp4, tmp5;

        //printf("NUM ELEMENTS = %d\n", numElements);


        clock_t start, end;
        start = clock();

        //WAS UNCOMMENTED
        rX.m256d = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rY.m256d = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rXtimesX.m256d = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
        rXtimesY.m256d = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);
		
	//printf("NUM PARTIAL = %d\n", partialIterations);
        int tempCounter = 0;
        for(int i = 0; i < partialIterations; i++) {
            tmp1.m256d = _mm256_loadu_pd(xValues+i*4);
            rX.m256d = _mm256_add_pd(rX.m256d, tmp1.m256d);
            tmp2.m256d = _mm256_loadu_pd(yValues+i*4);
            rY.m256d = _mm256_add_pd(rY.m256d, tmp2.m256d);
            tmp1.m256d = _mm256_mul_pd(tmp1.m256d, tmp1.m256d);
            rXtimesX.m256d = _mm256_add_pd(rXtimesX.m256d, tmp1.m256d);
            tmp4.m256d = _mm256_loadu_pd(xValues+i*4);
            tmp4.m256d = _mm256_mul_pd(tmp4.m256d, tmp2.m256d);
            rXtimesY.m256d = _mm256_add_pd(rXtimesY.m256d, tmp4.m256d);
        }

        for(int i = 0; i < leftoverIterations; i++) {
            rX.d[0] += xValues[numElements-i-1];
            rY.d[0] += yValues[numElements-i-1];
            rXtimesX.d[0] += (xValues[numElements-i-1]*xValues[numElements-i-1]);
            rXtimesY.d[0] += (xValues[numElements-i-1]*yValues[numElements-i-1]);
        }

        sumX = rX.d[0] + rX.d[1] + rX.d[2] + rX.d[3];
        sumY = rY.d[0] + rY.d[1] + rY.d[2] + rY.d[3];
        sumXSquare = rXtimesX.d[0] + rXtimesX.d[1] + rXtimesX.d[2] + rXtimesX.d[3];
        sumXmultiplY = rXtimesY.d[0] + rXtimesY.d[1] +rXtimesY.d[2] +rXtimesY.d[3];

        b = (sumXmultiplY - (sumY / sumX) * sumXSquare) / (sumX - (numElements / sumX) * sumXSquare);
        a = (sumY - numElements * b) / sumX;

        end = clock();
        double duration = ((double)end-start)/CLOCKS_PER_SEC;
        //printf("AVX DURATION = %lf\n", duration);  

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

    /*end = clock();
    double duration = ((double)end-start)/CLOCKS_PER_SEC;
    printf("%lf\n", duration);*/

    return 0;
}

