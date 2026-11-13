#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// Structre Definition According to file
typedef struct
{
    int roll_no;
    int subj1,subj2,subj3,subj4,subj5;
    
}Student;


// Main method
int main(int argc, char *argv[])
{

    // File Initialization
    FILE *file;
    file = fopen("small.csv","r");


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
        free(file);
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
    if(!database)
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

            if(!temp)
            {
                printf("Reallocation Failed");
                free(temp);
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
            return -1;
        }

        

    }while(!feof(file));
    
    double end = omp_get_wtime();
    printf("The Total Records in small.csv file is: %d\n",record);
    printf("Time taken: %lf\n",end - start);
    return 0;
}