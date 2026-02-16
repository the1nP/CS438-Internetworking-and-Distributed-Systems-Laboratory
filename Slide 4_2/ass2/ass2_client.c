#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "ass2.h"

int main(int argc, char **argv)
{
    CLIENT *cl;
    char *machinename;
    parameter args;
    returntype *res;
    int i, j;
    mytype arrobj[MAXSORTSIZE];

    if (argc < 3) {
        fprintf(stderr, "usage: %s machinename [n1 n2 ...]\n", argv[0]);
        exit(1);
    }

    machinename = argv[1];
    args.ss.ss_len = argc - 2; 

    for (i = 2, j = 0; i < argc; i++, j++) {
        arrobj[j] = atoi(argv[i]);
    }
    
    args.ss.ss_val = &arrobj[0];

    cl = clnt_create(machinename, EVEN_SORTPROG, EVEN_SORTVERS, "tcp");

    if (cl == NULL) {
        clnt_pcreateerror(machinename);
        exit(1);
    }

    res = even_sort_1(&args, cl);

    if (res == NULL) {
        clnt_perror(cl, machinename);
        exit(1);
    }

    printf("Sorted even numbers:\n");
    for (i = 0; i < res->ss.ss_len; i++) {
        printf("%d\n", res->ss.ss_val[i]);
    }

    exit(0);
}
