#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 8
int NUMBER_OF_MATCHES = 0;

/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
    char *txt;
    char *pat;
} thread_data_t;

/* thread function */
void *thr_func(void *arg) {
    thread_data_t *data = (thread_data_t *) arg;

/*
    printf("hello from thr_func, thread id: %s,%s\n", data->txt, data->pat);
*/
/*    char txt[strlen(data->txt) + 1];
    strcpy(txt, data->txt);
    char pattern[strlen(data->pat) + 1];
    strcpy(pattern, data->pat);*/
    int N = 4638690;
    int M = 3;
    int i, j;
    int numberOfMatch = 0;

    for (i = 0; i <= N - M; i++) {
        for (j = 0; j < M; j++) {
            if (data->txt[i + j] != data->pat[j]) {
                break;
            }
        }

        if (j == M) {
            printf("ssss");
            numberOfMatch++;
        }
    }
    printf("Number of matches %d \n", numberOfMatch);
    NUMBER_OF_MATCHES += numberOfMatch;

    pthread_exit(NULL);
}

int main() {

    printf("Parralel Implementation For PSMA using Pthreads \n");
    printf("\n%f", 12.2);

    /* Read File */
    // file reading components
    FILE *fp;
    long lSize;
    char *buffer;

    //open targeted file
    fp = fopen("../files/gene_ecoli.txt", "rb");
    if (!fp) perror("../files/gene_ecoli.txt"), exit(1);

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    /* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer) fclose(fp), fputs("memory alloc fails", stderr), exit(1);


    /* copy the file into the buffer */

    if (1 != fread(buffer, lSize, 1, fp))
        fclose(fp), free(buffer), fputs("entire read fails", stderr), exit(1);

    char pattern[] = "agt";

    printf("%s", pattern);
/*
    printf("%d", strlen(buffer));
*/


    pthread_t thr[NUM_THREADS];
    int i, rc;

    /* create a thread_data_t argument array */
    thread_data_t thr_data[NUM_THREADS];


    /* create threads */
    for (i = 0; i < NUM_THREADS; ++i) {
        thr_data[i].txt = (char *) malloc(sizeof(char) * (lSize));
        thr_data[i].pat = (char *) malloc(sizeof(char) * (strlen(pattern) + 1));

        strcpy(thr_data[i].pat, pattern);
        strcpy(thr_data[i].txt, buffer);

        printf("%s", thr_data[i].pat);

        if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
        }
    }
    /* block until all threads complete */
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }

    printf("num of matches is %d", NUMBER_OF_MATCHES);
    fclose(fp);
    free(buffer);
    return EXIT_SUCCESS;
}

/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>
#include <pthread.h>

int NUM_OF_MATCHES = 0;

struct patob {
    char *str;
    char *pat;
    char s[999999999];
    char p[99999999];
};

void *searchForPattern(void *input) {
    */
/*
    char tempTXT = input->str;
    char txt[strlen(tempTXT) + 1];
    stpcpy(txt, &tempTXT);
    printf("s %s\n", &tempTXT);

    char tempPatt = input->pat;
    char pattern[strlen(&tempPatt) + 1];
    stpcpy(pattern, &tempPatt);
    *//*



    struct patob *data = (patob *) input;

    int M = strlen(pattern);
    int N = strlen(txt);

    int i, j;
    int numberOfMatch = 0;

    for (i = 0; i <= N - M; i++) {
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == M) {
            //printf("Pattern found, index --> %d \n", i);
            numberOfMatch++;
        }
    }
    printf("Number of matches %d \n", numberOfMatch);
    NUM_OF_MATCHES += numberOfMatch;

    return NULL;

}

int main() {
    printf("Parralel Implementation For PSMA using Pthreads \n");

    // file reading components
    FILE *fp;
    long lSize;
    char *buffer;

    //open targeted file
    fp = fopen("../files/gene_ecoli.txt", "rb");
    if (!fp) perror("../files/gene_ecoli.txt"), exit(1);

    */
/*
    fp = fopen("path", "rb");
    if (!fp) perror("path"), exit(1);
     *//*


    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    */
/* allocate memory for entire content *//*

    buffer = calloc(1, lSize + 1);
    if (!buffer) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

    */
/* copy the file into the buffer *//*

    if (1 != fread(buffer, lSize, 1, fp))
        fclose(fp), free(buffer), fputs("entire read fails", stderr), exit(1);

    // clock start
    clock_t begin = clock();

    */
/*Code Goes Here*//*


    pthread_t thread; //initilize thread

    // pattern needed
    char pattern[] = "agt";

    struct patob *Str = (struct patob *) malloc(sizeof(struct patob));
    Str->str = buffer;
    Str->pat = pattern;

    strcpy(Str->s, buffer);
    strcpy(Str->p, pattern);



    // call PSMA algorithm function
    //searchForPattern(pattern, buffer);
    pthread_create(&thread, NULL, searchForPattern, &Str);



    */
/*End Of Code*//*


    // clock end
    clock_t end = clock();
    //calculate time spent
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    //print out time spent
    printf("Time spent equals %lf \n", time_spent);



    //close file
    fclose(fp);
    //free buffer space
    free(buffer);


    printf("num of matches ALL %d", NUM_OF_MATCHES);
    pthread_join(thread, NULL);
    return 0;

}

*/
