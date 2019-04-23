#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define INPUTFOLDER "inputs"
#define BUFSIZE 100000
#define NUM_OF_THREADS 4

char *textData;
int textLength;

char *patternData;
int patternLength;

clock_t c0, c1;

// when it is out of memory, handle error
void outOfMemory()
{
    fprintf (stderr, "Out of memory\n");
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

/*
void findAllInstances(char buf[])
{
	int i,j,k, lastI;

	j=0;

	//lastI = textLength[textIndex] - patternLength[patternIndex];

	int found = 0;

	#pragma omp parallel for default(none) shared(found, buf) private(j, k) firstprivate(lastI, textData, patternData, patternLength) schedule(static) num_threads(8)
	for (i = 0; i <= lastI; i++)
	{
		k=i;
		j=0;

		while( textData[textIndex][k] == patternData[patternIndex][j] && j < patternLength[patternIndex] )
		{
			k++;
			j++;
		}

		if (j == patternLength[patternIndex])
		{
			#pragma omp critical(check)
			{
				found = 1;
				writeToBuffer(buf, textIndex, patternIndex, i);
			}
		}

	}

	if (!found)
		writeToBuffer(buf, textIndex, patternIndex, -1);

}
*/

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

        if (j == M){
            #pragma omp critical(check)
            found++;
        }
    }

    printf("Pattern Found match is %d",found);
}

int main()
{
    //read text data
    FILE *txt;
    txt = fopen("C:\\Users\\Thabet\\Desktop\\myproj\\files\\gene_ecoli.txt", "r");
    readFromFile(txt,&textData,&textLength);
    fclose(txt);

    //read pattern data
    FILE *pattern;
    pattern = fopen("C:\\Users\\Thabet\\Desktop\\myproj\\files\\gene_ecoli_patt.txt", "r");
    readFromFile(pattern,&patternData,&patternLength);
    fclose(pattern);

    double total_time =0;
    c0 = clock();
    findAll();
    c1 = clock();
    total_time = ((double) (c1 - c0)) / CLK_TCK;
    printf("\nTime is %f",total_time);


    return 0;
}
