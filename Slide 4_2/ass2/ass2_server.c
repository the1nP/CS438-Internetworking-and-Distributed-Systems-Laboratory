#include <stdlib.h>
#include <rpc/rpc.h>
#include "ass2.h"

static int
compareobj(const void *p1, const void *p2)
{
    mytype sp1 = *(mytype *)p1;
    mytype sp2 = *(mytype *)p2;
    if(sp1 == sp2) return(0);
    else if(sp1 > sp2) return(1);
    else return(-1);
}

returntype *
even_sort_1_svc(parameter *ssp, struct svc_req *c)
{
    static returntype ss_res;
    int i, even_count = 0;

    if (ss_res.ss.ss_val != (mytype *)NULL)
        free(ss_res.ss.ss_val);

    mytype *temp_even = (mytype *)malloc(ssp->ss.ss_len * sizeof(mytype));
    
    for (i = 0; i < ssp->ss.ss_len; i++) {
        if (ssp->ss.ss_val[i] % 2 == 0) {
            temp_even[even_count++] = ssp->ss.ss_val[i];
        }
    }

    /* Sort the even numbers */
    if (even_count > 0) {
        qsort(temp_even, even_count, sizeof(mytype), compareobj);
    }

    /* Prepare result */
    ss_res.ss.ss_len = even_count;
    ss_res.ss.ss_val = (mytype *)malloc(even_count * sizeof(mytype));
    for (i = 0; i < even_count; i++) {
        ss_res.ss.ss_val[i] = temp_even[i];
    }

    free(temp_even);
    return(&ss_res);
}
