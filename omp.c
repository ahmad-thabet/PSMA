#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define INPUTFOLDER "inputs"
#define BUFSIZE 100000
#define NUM_OF_THREADS 8

char *textData;
int textLength;

char *patternData;
int patternLength;

clock_t start, end;

// when it is out of memory, handle error
void outOfMemory()
{
    fprintf (stderr, "Out of memory :(\n");
    exit (0);
}

// read from file and store data
void readFromFile(FILE *f, char **data, int *length)
{
    int ch;
    int allocatedLength;
    int resultLength = 0;
    char *result;

    allocatedLength = 0;
    result = NULL;

    ch = fgetc(f);
    while (ch >= 0)
    {
        resultLength++;
        if (resultLength > allocatedLength)
        {
            allocatedLength += 10000;
            result = (char *)realloc(result, sizeof(char) * allocatedLength);
            if (result == NULL)
                outOfMemory();
        }
        result[resultLength-1] = ch;
        ch = fgetc(f);
    }
    *data = result;
    *length = resultLength;
}

void findAll()
{
    int i, j, N, M;
    M = patternLength;
    N = textLength;
    int found;

    #pragma omp parallel for default(none) shared(found) private(i,j) firstprivate(textData, patternData, N,M) schedule(static) num_threads(NUM_OF_THREADS)
    for (i = 0; i <= N - M; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (textData[i + j] != patternData[j])
                break;
        }

        /*int tid = omp_get_thread_num();
        printf("Hello world from omp thread %d\n", tid);*/

        if (j == M){
            #pragma omp critical(check)
            found++;

        }
    }

    printf("Pattern Found match: %d",found);
}

int main()
{
    //read text data
    FILE *txt;
    txt = fopen("C:\\Users\\Thabet\\Desktop\\myproj\\files\\EnglishText.txt", "r");
    readFromFile(txt,&textData,&textLength);
    fclose(txt);

    //read pattern data
    FILE *pattern;
    pattern = fopen("C:\\Users\\Thabet\\Desktop\\myproj\\files\\gene_ecoli_patt.txt", "r");
    readFromFile(pattern,&patternData,&patternLength);
    fclose(pattern);

    double total_time =0;
    // start timer
    start = clock();

    //call function to find all patterns
    findAll();

    //print number of threads
    printf("\nNumber of Threads is %d", NUM_OF_THREADS);

    //end timer
    end = clock();

    //calculate total time
    total_time = ((double) (end - start)) / CLK_TCK;

    //print total time
    printf("\nTime is %f\n\n",total_time);

    return 0;
}
