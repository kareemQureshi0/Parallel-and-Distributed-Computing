#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// Structre Definition According to file
typedef struct
{
    int roll_no;
    int subj1,subj2,subj3,subj4,subj5;
    
}Student;

int benchSequential(char *filename)
{
    // File Initialization
    FILE *file;
    file = fopen(filename,"r");


    // 1st Edge case of file
    if (file == NULL)
    {
        printf("File not Found ");
        
        return -1;
    }

    // Shifting 23 bytes ahead to not include the header of each file
    if((fseek(file,23,SEEK_SET))!=0)
    {
        printf("Header is not skipped! Operation Failed");
        fclose(file);
        return -1;
    }


    double start = omp_get_wtime();

    // Declaration for Our Structure for reading the file
    int read = 0;
    int record = 0;
    int capacity = 5000;


    // Allocation of database on heap
    Student *database = (Student *)malloc(sizeof(Student)*capacity);

    // Edge Case for checking database failed
    if(database==NULL)
    {
        printf("Allocation Failed");
        free(database);
        fclose(file);
        return 0;
    }

    // Reading of file
    do{
        read = fscanf(file,"%d,%d,%d,%d,%d,%d\n",
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
            capacity*=2;
            Student *temp = (Student *)realloc(database,sizeof(Student)*capacity);

            if(temp==NULL)
            {
                printf("Reallocation Failed");
                fclose(file);
                return 0;    
            }
            database = temp;
        }

        if(ferror(file))
        {
            printf("Error Reading File\n");
        }

        if(read!=6 && !feof(file))
        {
            printf("Incorrect Formatted String");
            free(database);
            fclose(file);
            return -1;
        }

    }while(!feof(file));

    

    // for(int i = 0; i<5;i++)
    // {
    //     printf("Record %d:\n",i+1);
    //     printf("Roll no: %d\n",database[i].roll_no);
    //     printf("Subject 1 Marks: %d\n",database[i].subj1);
    //     printf("Subject 2 Marks: %d\n",database[i].subj2);
    //     printf("Subject 3 Marks: %d\n",database[i].subj3);
    //     printf("Subject 4 Marks: %d\n",database[i].subj4);
    //     printf("Subject 5 Marks: %d\n",database[i].subj5);
    // }

    long total = 0;
    float average;


    // Overall Average of the students
    for (int i = 0; i<record;i++)
    {
        total+=database[i].subj1+database[i].subj2+database[i].subj3+database[i].subj4+database[i].subj5;
    }

    average = total/(record*5.0);

    double end = omp_get_wtime();

    printf("Students: %d\n",record);
    printf("Overall Average: %.4f\n",average);
    printf("Time taken: %lf\n",end - start);
    return 0;
}

// Main method
int main(int argc, char *argv[])
{

    benchSequential("small.csv");
    // benchSequential("medium.csv");
    // benchSequential("large.csv");

    return 0;
}