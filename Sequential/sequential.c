#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// Structre Definition According to file
typedef struct
{
    int roll_no;
    int subj1, subj2, subj3, subj4, subj5;

} Student;

int benchSequential(char *filename)
{
    // File Initialization
    FILE *file;
    file = fopen(filename, "r");

    // 1st Edge case of file
    if (file == NULL)
    {
        printf("File not Found ");

        return -1;
    }

    // Shifting 23 bytes ahead to not include the header of each file
    if ((fseek(file, 23, SEEK_SET)) != 0)
    {
        printf("Header is not skipped! Operation Failed");
        fclose(file);
        return -1;
    }

    double start = omp_get_wtime();

    // Declaration for Our Structure for reading the file
    int read = 0;
    int record = 0;
    int capacity = 2000;

    // Allocation of database on heap
    Student *database = (Student *)malloc(sizeof(Student) * capacity);

    // Edge Case for checking database failed
    if (database == NULL)
    {
        printf("Allocation Failed");
        free(database);
        fclose(file);
        return 0;
    }

    // Reading of file
    do
    {
        read = fscanf(file, "%d,%d,%d,%d,%d,%d\n",
                      &database[record].roll_no,
                      &database[record].subj1,
                      &database[record].subj2,
                      &database[record].subj3,
                      &database[record].subj4,
                      &database[record].subj5);

        if (read == 6)
        {
            record++;
        }

        if (record >= capacity)
        {
            capacity *= 2;
            Student *temp = (Student *)realloc(database, sizeof(Student) * capacity);

            if (temp == NULL)
            {
                printf("Reallocation Failed");
                fclose(file);
                return 0;
            }
            database = temp;
        }

        if (ferror(file))
        {
            printf("Error Reading File\n");
        }

        if (read != 6 && !feof(file))
        {
            printf("Incorrect Formatted String");
            free(database);
            fclose(file);
            return -1;
        }

    } while (!feof(file));


    double end = omp_get_wtime();

    long total = 0;
    float average;

    int subj1_total = 0;
    int subj2_total = 0;
    int subj3_total = 0;
    int subj4_total = 0;
    int subj5_total = 0;

    float avg_of_subj1;
    float avg_of_subj2;
    float avg_of_subj3;
    float avg_of_subj4;
    float avg_of_subj5;

    int pass = 0;
    int fail = 0;

    int pass1=0,pass2=0,pass3=0,pass4=0,pass5=0;


    // Overall Average of the students of each subject
    for (int i = 0; i < record; i++)
    {
        total += database[i].subj1 + database[i].subj2 + database[i].subj3 + database[i].subj4 + database[i].subj5;
        
        subj1_total += database[i].subj1;
        subj2_total += database[i].subj2;
        subj3_total += database[i].subj3;
        subj4_total += database[i].subj4;
        subj5_total += database[i].subj5;

        if ((database[i].subj1 >= 50) && (database[i].subj2 >= 50) && (database[i].subj3 >= 50) && (database[i].subj4 >= 50) && (database[i].subj5 >= 50))
        {
            pass++;
        }
        else
        {
            fail++;
        }

         if(database[i].subj1>=50)
        {
            pass1++;
        }

        if(database[i].subj2>=50)
        {
            pass2++;
        }

        if(database[i].subj3>=50)
        {
            pass3++;
        }

        if(database[i].subj4>=50)
        {
            pass4++;
        }

        if(database[i].subj5>=50)
        {
            pass5++;
        }
   
    }

    average = total / (record * 5.0);

    avg_of_subj1 = (float)subj1_total / (float)record;
    avg_of_subj2 = (float)subj2_total / (float)record;
    avg_of_subj3 = (float)subj3_total / (float)record;
    avg_of_subj4 = (float)subj4_total / (float)record;
    avg_of_subj5 = (float)subj5_total / (float)record;


    float avg_of_S1= ((float)pass1/(float)record)*100.0;
    float avg_of_S2= ((float)pass2/(float)record)*100.0;
    float avg_of_S3= ((float)pass3/(float)record)*100.0;
    float avg_of_S4= ((float)pass4/(float)record)*100.0;
    float avg_of_S5= ((float)pass5/(float)record)*100.0;


    printf("Students: %d\n", record);
    printf("Overall Average: %.4f\n", average);
    printf("Passed %d / Failed: %d\n", pass, fail);
    printf("Subject Average: S1 %.2f S2 %.2f S3 %.2f S4 %.2f S5 %.2f \n", avg_of_subj1, avg_of_subj2, avg_of_subj3, avg_of_subj4, avg_of_subj5);
    printf("Subject pass rate: S1: %.2f%% S2: %.2f%% S3: %.2f%% S4: %.2f%% S5: %.2f%% \n",avg_of_S1,avg_of_S2,avg_of_S3,avg_of_S4,avg_of_S5);
    printf("Time taken: %lf\n", end - start);

    return 0;
}

// Main method
int main(int argc, char *argv[])
{
    printf("Analysis of Small CSV file\n");
    benchSequential("small.csv");

    // printf("\nAnalysis of Medium CSV file\n");
    // benchSequential("medium.csv");
    // printf("\nAnalysis of Large CSV file\n");
    // benchSequential("large.csv");

    return 0;
}