#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

void searchForPattern(char *pattern, char *txt) {
    int M = strlen(pattern);
    int N = strlen(txt);
    int i, j;

    for (i = 0; i <= N - M; i++) {
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == M) {
            printf("Pattern found, index --> %d \n", i);
        }
    }
}

int main() {
    // file reading components
    FILE *fp;
    long lSize;
    char *buffer;

    //open targeted file
    fp = fopen("../files/gene_ecoli.txt", "rb");
    if (!fp) perror("../files/gene_ecoli.txt"), exit(1);

    /*
    fp = fopen("path", "rb");
    if (!fp) perror("path"), exit(1);
     */

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    /* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

    /* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, fp))
        fclose(fp), free(buffer), fputs("entire read fails", stderr), exit(1);

    /*Code Goes Here*/
    // clock start
    clock_t begin = clock();
    // pattern needed
    char pattern[] = "agt";
    // call PSMA algorithm function
    searchForPattern(pattern, buffer);
    // clock end
    clock_t end = clock();
    //calculate time spent
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    //print out time spent
    printf("Time spent equals %lf", time_spent);

    /*End Of Code*/

    //close file
    fclose(fp);
    //free buffer space
    free(buffer);

    return 0;
} 

