#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#ifndef RAND_MAX
#define RAND_MAX ((int) (unsigned)~0 >> 1)
#endif

//inclusive
double generateRandomFloat(double low, double high) {

    double result;
    result = (double)rand() / ((double) RAND_MAX + 1);
    return (low + result * (high - low));
}

int num_elements = 1000000;

int main() {
    srand((int)time(NULL));
    double *xValues, *yValues;
    xValues = (double*)calloc(num_elements, sizeof(double));
    yValues = (double*)calloc(num_elements, sizeof(double));

    //Go back a folder and then perform magic!!!
    FILE* fp = fopen("../C-LikeSSEOptimisation/entry_fileDOUBLE", "wb");

    if(fp != NULL) {
        fwrite(&num_elements, sizeof(int), 1, fp);
        for(int i = 0; i < num_elements; i++) {
            xValues[i] = (double)5.0;//(double)generateRandomFloat(1.0, 100.0);
            yValues[i] = (double)6.0;//(double)generateRandomFloat(1.0, 100.0);
        }
        fwrite(xValues, sizeof(double), num_elements, fp);
        fwrite(yValues, sizeof(double), num_elements, fp);

        fclose(fp);
    }
    return 0;
}
