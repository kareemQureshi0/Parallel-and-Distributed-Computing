#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    FILE *fptr;

    fptr = fopen("small.csv","r");

    double start = omp_get_wtime();

    char line[1024];
    while(fgets(line,1024,fptr))
    {
        
    }
    double end = omp_get_wtime();

    printf("The load time of small.csv is: %f \n",end-start);
    fclose(fptr);
    return 0;
}