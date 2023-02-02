#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv)
{
    clock_t start, end;
    /*start = clock();*/
    //double start = omp_get_wtime(); 

    int numElements = 0;
    FILE *fp;
    fp = fopen(argv[1], "rb");

    if(fp != NULL) {
        double sumX = 0.0, sumY = 0.0, sumXmultiplY = 0.0, sumXSquare = 0.0;
        double a = 1.0, b = 1.0;
        int read = fread(&numElements, sizeof(int), 1, fp);

        double* xValues = (double*)calloc(numElements, sizeof(double));
        double* yValues = (double*)calloc(numElements, sizeof(double));

        read = fread(xValues, sizeof(double), numElements, fp);
        read = fread(yValues, sizeof(double), numElements, fp);

        
        clock_t start, end;
        start = clock();
        for(int i = 0; i < numElements; i++) {
            sumXmultiplY += xValues[i] * yValues[i];
            sumY += yValues[i];
            sumX += xValues[i];
            sumXSquare = sumXSquare + (xValues[i] * xValues[i]);
        }

	/*printf("sumX = %4.2lf\n",sumX);
        printf("sumY = %4.2lf\n",sumY);
        printf("sumX^2 = %4.2lf\n",sumXSquare);
        printf("sumX*Y = %4.2lf\n",sumXmultiplY);*/
	
        b = (sumXmultiplY - (sumY / sumX) * sumXSquare) / (sumX - (numElements / sumX) * sumXSquare);
        a = (sumY - numElements * b) / sumX;
        fclose(fp);

        end = clock();
        double duration = ((double)end-start)/CLOCKS_PER_SEC;
        //printf("NORMAL DURATION = %lf\n", duration);

	    //printf("a = %4.2f", a);
	    //printf("b = %4.2f", b);

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

    //double diff = omp_get_wtime() - start; 
	//printf("%lf\n", diff);

    /*end = clock();
    double duration = ((double)end-start)/CLOCKS_PER_SEC;
    printf("%lf\n", duration);*/

    return 0;
}
