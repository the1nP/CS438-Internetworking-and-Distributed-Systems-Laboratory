/* @(#)sort_proc.c	2.1 88/08/11 4.0 RPCSRC */
#include <stdlib.h>
#include <rpc/rpc.h>
#include "sort.h"

static int
compareobj(sp1, sp2)
    mytype *sp1, *sp2;
{
    if(*sp1 == *sp2) return(0);
    else if(*sp1 > *sp2) return(1);
    else return(-1);
}

returntype *
sort_1_svc(ssp,c)
    parameter *ssp;
    struct svc_req *c;
{
    static returntype ss_res;

    if (ss_res.ss.ss_val != (mytype *)NULL)
        free(ss_res.ss.ss_val);

    qsort(ssp->ss.ss_val, ssp->ss.ss_len, sizeof (mytype), compareobj);
    ss_res.ss.ss_len = ssp->ss.ss_len;
    ss_res.ss.ss_val = (mytype *)malloc((ssp->ss.ss_len) * sizeof(mytype));
    bcopy(ssp->ss.ss_val, ss_res.ss.ss_val,
        ssp->ss.ss_len * sizeof(mytype));
    return(&ss_res);
}
