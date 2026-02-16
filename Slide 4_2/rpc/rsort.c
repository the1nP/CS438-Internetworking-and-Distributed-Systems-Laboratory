/* @(#)rsort.c	2.1 88/08/11 4.0 RPCSRC */
/*
 * rsort.c
 * Client side application which sorts argc, argv.
 */
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "sort.h"

int main(argc, argv)
	int argc;
	char **argv;
{
        CLIENT *cl;
	char *machinename;
	parameter args;
        returntype *res;
        returntype result;
	int i,j;
        mytype arrobj[MAXSORTSIZE];

	if (argc < 3) {
		fprintf(stderr, "usage: %s machinename [s1 ...]\n", argv[0]);
		exit(1);
	}
	machinename = argv[1];
        res = &result;
	args.ss.ss_len = argc - 2;     /* substract off progname, machinename */
        for(i=2,j=0;i < argc; i++,j++)        
          arrobj[j] = atoi(argv[i]);
	args.ss.ss_val = &arrobj[0];
	res->ss.ss_val = (mytype *)NULL;

        cl = clnt_create(machinename, SORTPROG, SORTVERS, "tcp");

       if (cl == NULL) {
        /* Couldn't establish connection with server.
         * Print error message and close up shop.
         */
          clnt_pcreateerror(machinename);
          exit(1);
        } 
        res = sort_1(&args,cl);
  
        if (res == NULL) {
            /* An error occurred while calling the server.
             * Print error message and exit.
             */
             clnt_perror(cl, machinename);
            exit(1);
        } 

	for (i = 0; i < res->ss.ss_len; i++) {
		printf("%d\n", res->ss.ss_val[i]);
	}

	/* should free res here */
	exit(0);
}


