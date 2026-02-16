/* @(#)sort.x	2.1 88/08/11 4.0 RPCSRC */
/*
 * The sort procedure receives an array of strings and returns an array
 * of strings.  This toy service handles a maximum of 64 strings.
 */
const MAXSORTSIZE  = 64;

typedef	int mytype; /* the string itself */

struct sortobject {
    mytype ss<MAXSORTSIZE>; 
};

typedef struct sortobject returntype;
typedef struct sortobject parameter;

program SORTPROG {
    version SORTVERS {
      returntype SORT(parameter) = 1;
    } = 1;
} = 22855;
