#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void benchmarkFile(const char *filename, const char *label)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    double start = omp_get_wtime();

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char *box = (char *)malloc(file_size + 1);
    if (box == NULL)
    {
        printf("Error: Memory allocation failed for %s\n", filename);
        fclose(fp);
        return;
    }

    fread(box, 1, file_size, fp);
    box[file_size] = '\0';

    fclose(fp);
    double end = omp_get_wtime();

    printf("%s loaded in memory in %lfs\n", label, end - start);
    free(box);
}

int main(void)
{
    benchmarkFile("Sequential/small.csv", "Small CSV");
    benchmarkFile("Sequential/medium.csv", "Medium CSV");
    benchmarkFile("Sequential/large.csv", "Large CSV");

    return 0;
}