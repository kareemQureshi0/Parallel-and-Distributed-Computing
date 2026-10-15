#include <stdio.h>
#include <stdlib.h>

static unsigned long long state = 2026ULL;
/* fixed seed */

static unsigned int next_rand(void) /* xorshift64* */
{
    state ^= state >> 12;
    state ^= state << 25;
    state ^= state >> 27;
    return (unsigned int)((state * 2685821657736338717ULL) >> 32);
}

static int mark(void)
{
    if (next_rand() % 100 == 0)
    {
        return 0;
    }
    /* about 1% absent: mark 0 */

    int m = 20;

    for (int k = 0; k < 4; k++)
    {
        m += next_rand() % 21;
    }
    /* 20..100, most marks near 60 */
   
    return m;
}

int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        fprintf(stderr, "usage: %s <num_students> <output.csv>\n", argv[0]);
        return 1;
    }

    long n = atol(argv[1]);
    FILE *f = fopen(argv[2], "w");
    if (!f) 
    {
        perror("fopen"); 
        return 1;
    }

    fprintf(f, "roll_no,S1,S2,S3,S4,S5\n");
    
    for (long i = 1; i <= n; i++)
    {
        fprintf(f, "%ld", i);
        for (int s = 0; s < 5; s++)
            fprintf(f, ",%d", mark());
        fputc('\n', f);
    }

    fclose(f);
    return 0;
}