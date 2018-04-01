#ifdef __cplusplus
extern "C" {
#endif
/*        Generated by TAPENADE     (INRIA, Ecuador team)
    Tapenade 3.13 (r6666M) -  1 Mar 2018 15:30
*/
#include "../../ADFirstAidKit/adBuffer.h"
#include <stdlib.h>
#include <math.h>
#include "gmm_unfused_b-all.h"

/*
  Differentiation of arr_max in reverse (adjoint) mode:
   gradient     of useful results: *(*arr.arr) arr_max
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
void arr_max_b(array_number_t_struct *arr, array_number_t_struct *arrb, double
        arr_maxb) {
    double *x = arr->arr;
    double *xb = (double *)0;
    int branch;
    double arr_max;
    xb = arrb->arr;
    int n = arr->length;
    double m;
    double mb;
    int i;
    m = x[0];
    for (i = 1; i < n; ++i)
        if (x[i] > m) {
            m = x[i];
            pushcontrol1b(1);
        } else
            pushcontrol1b(0);
    mb = arr_maxb;
    for (i = n-1; i > 0; --i) {
        popcontrol1b(&branch);
        if (branch != 0) {
            xb[i] = xb[i] + mb;
            mb = 0.0;
        }
    }
    xb[0] = xb[0] + mb;
}

/*
  Differentiation of logsumexp in reverse (adjoint) mode:
   gradient     of useful results: logsumexp *(*arr.arr)
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
void logsumexp_b(array_number_t_struct *arr, array_number_t_struct *arrb, 
        double logsumexpb) {
    double *x = arr->arr;
    double *xb = (double *)0;
    double tempb;
    double logsumexp;
    xb = arrb->arr;
    int n = arr->length;
    int i;
    double mx, semx;
    double mxb, semxb;
    mx = arr_max(arr);
    semx = 0.;
    for (i = 0; i < n; ++i)
        semx = semx + exp(x[i] - mx);
    semxb = logsumexpb/semx;
    mxb = logsumexpb;
    for (i = n-1; i > -1; --i) {
        tempb = exp(x[i]-mx)*semxb;
        xb[i] = xb[i] + tempb;
        mxb = mxb - tempb;
    }
    arr_max_b(arr, arrb, mxb);
}

/*
  Differentiation of sqnorm in reverse (adjoint) mode:
   gradient     of useful results: *(*arr.arr) sqnorm
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
void sqnorm_b(array_number_t_struct *arr, array_number_t_struct *arrb, double 
        sqnormb) {
    double *x = arr->arr;
    double *xb = (double *)0;
    double sqnorm;
    xb = arrb->arr;
    int d = arr->length;
    int i;
    double out;
    double outb;
    outb = sqnormb;
    for (i = d-1; i > -1; --i)
        xb[i] = xb[i] + 2*x[i]*outb;
}

/*
  Differentiation of vectorSum in reverse (adjoint) mode:
   gradient     of useful results: *(*arr.arr) vectorSum
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
void vectorSum_b(array_number_t_struct *arr, array_number_t_struct *arrb, 
        double vectorSumb) {
    double *x = arr->arr;
    double *xb = (double *)0;
    double vectorSum;
    xb = arrb->arr;
    int d = arr->length;
    int i;
    double out;
    double outb;
    outb = vectorSumb;
    for (i = d-1; i > -1; --i)
        xb[i] = xb[i] + outb;
}

/*
  Differentiation of subtract in reverse (adjoint) mode:
   gradient     of useful results: *(*out.arr) *(*x.arr) *(*y.arr)
   with respect to varying inputs: *(*out.arr) *(*x.arr) *(*y.arr)
   Plus diff mem management of: subtract:in-out out:in *out.arr:in
                x:in *x.arr:in y:in *y.arr:in
*/
void subtract_b(array_number_t_struct *x, array_number_t_struct *xb, 
        array_number_t_struct *y, array_number_t_struct *yb, 
        array_number_t_struct *out, array_number_t_struct *outb, 
        array_number_t_struct *subtractb) {
    int id;
    array_number_t_struct *subtract;
    subtractb = outb;
    outb = subtractb;
    subtractb = (array_number_t)0;
    for (id = x->length-1; id > -1; --id) {
        xb->arr[id] = xb->arr[id] + outb->arr[id];
        yb->arr[id] = yb->arr[id] - outb->arr[id];
        outb->arr[id] = 0.0;
    }
}

/*
  Differentiation of vectorExp in reverse (adjoint) mode:
   gradient     of useful results: *(*out.arr) *(*arr.arr)
   with respect to varying inputs: *(*out.arr) *(*arr.arr)
   Plus diff mem management of: out:in *out.arr:in vectorExp:in-out
                arr:in *arr.arr:in
*/
void vectorExp_b(array_number_t_struct *arr, array_number_t_struct *arrb, 
        array_number_t_struct *out, array_number_t_struct *outb, 
        array_number_t_struct *vectorExpb) {
    int id;
    array_number_t_struct *vectorExp;
    vectorExpb = outb;
    outb = vectorExpb;
    vectorExpb = (array_number_t)0;
    for (id = arr->length-1; id > -1; --id) {
        arrb->arr[id] = arrb->arr[id] + exp(arr->arr[id])*outb->arr[id];
        outb->arr[id] = 0.0;
    }
}

/*
  Differentiation of Qtimesv in reverse (adjoint) mode:
   gradient     of useful results: *(*result.arr) *(*l.arr) *(*q.arr)
                *(*v.arr)
   with respect to varying inputs: *(*result.arr) *(*l.arr) *(*q.arr)
                *(*v.arr)
   Plus diff mem management of: result:in *result.arr:in l:in
                *l.arr:in q:in *q.arr:in Qtimesv:in-out v:in *v.arr:in
*/
void Qtimesv_b(array_number_t_struct *q, array_number_t_struct *qb, 
        array_number_t_struct *l, array_number_t_struct *lb, 
        array_number_t_struct *v, array_number_t_struct *vb, 
        array_number_t_struct *result, array_number_t_struct *resultb, 
        array_number_t_struct *Qtimesvb) {
    card_t macroDef294 = v->length;
    int branch;
    array_number_t_struct *Qtimesv;
    for (int i = 0; i < result->length; ++i) {
        index_t tis;
        tis = tri(i - 1);
        card_t macroDef295 = l->length;
        number_t macroDef296 = 0;
        for (int idx = 0; idx < macroDef295; ++idx) {
            index_t j = idx - tis;
            bool_t isInRange = 0;
            if (j >= 0)
                isInRange = j < i;
            else
                isInRange = 0;
            number_t ite298 = 0;
            if (isInRange)
                pushcontrol1b(0);
            else
                pushcontrol1b(1);
            pushinteger4(j);
        }
        number_t sum = macroDef296;
        pushinteger4(macroDef295);
    }
    Qtimesvb = resultb;
    resultb = Qtimesvb;
    Qtimesvb = (array_number_t)0;
    for (int i = result->length-1; i > -1; --i) {
        index_t tis;
        card_t macroDef295 = l->length;
        number_t macroDef296 = 0;
        number_t macroDef296b = 0.0;
        number_t sum = macroDef296;
        number_t sumb = 0.0;
        popinteger4(&macroDef295);
        sumb = resultb->arr[i];
        qb->arr[i] = qb->arr[i] + v->arr[i]*exp(q->arr[i])*resultb->arr[i];
        vb->arr[i] = vb->arr[i] + exp(q->arr[i])*resultb->arr[i];
        resultb->arr[i] = 0.0;
        macroDef296b = sumb;
        for (int idx = macroDef295-1; idx > -1; --idx) {
            index_t j = idx - tis;
            bool_t isInRange = 0;
            number_t ite298 = 0;
            number_t ite298b = 0.0;
            popinteger4(&j);
            ite298b = macroDef296b;
            popcontrol1b(&branch);
            if (branch == 0) {
                macroDef296b = ite298b;
                lb->arr[idx] = lb->arr[idx] + v->arr[j]*ite298b;
                vb->arr[j] = vb->arr[j] + l->arr[idx]*ite298b;
            } else
                macroDef296b = ite298b;
        }
    }
}

/*
  Differentiation of gmm_objective in reverse (adjoint) mode:
   gradient     of useful results: alloc(*(*expRes.arr)) *(alloc(*expRes).arr)
                alloc(*(*macroDef305.arr)) *(alloc(*macroDef305).arr)
                alloc(*(*QtimesvRes.arr)) *(alloc(*QtimesvRes).arr)
                alloc(*(*subRes.arr)) *(alloc(*subRes).arr) alloc(*(*macroDef300.arr))
                *(alloc(*macroDef300).arr) alloc(*(*macroDef301.arr))
                *(alloc(*macroDef301).arr) *(**(*qs.arr).arr)
                *(**(*x.arr).arr) *(**(*means.arr).arr) *(**(*ls.arr).arr)
                gmm_objective *(*alphas.arr)
   with respect to varying inputs: alloc(*(*expRes.arr)) *(alloc(*expRes).arr)
                alloc(*(*macroDef305.arr)) *(alloc(*macroDef305).arr)
                alloc(*(*QtimesvRes.arr)) *(alloc(*QtimesvRes).arr)
                alloc(*(*subRes.arr)) *(alloc(*subRes).arr) alloc(*(*macroDef300.arr))
                *(alloc(*macroDef300).arr) alloc(*(*macroDef301.arr))
                *(alloc(*macroDef301).arr) *(**(*qs.arr).arr)
                *(**(*x.arr).arr) *(**(*means.arr).arr) *(**(*ls.arr).arr)
                *(*alphas.arr)
   RW status of diff variables: alloc(*(*expRes.arr)):in-out *(alloc(*expRes).arr):in-out
                alloc(*(*macroDef305.arr)):in-out *(alloc(*macroDef305).arr):in-out
                alloc(*(*QtimesvRes.arr)):in-out *(alloc(*QtimesvRes).arr):in-out
                alloc(*(*subRes.arr)):in-out *(alloc(*subRes).arr):in-out
                alloc(*(*macroDef300.arr)):in-out *(alloc(*macroDef300).arr):in-out
                alloc(*(*macroDef301.arr)):in-out *(alloc(*macroDef301).arr):in-out
                *(**(*qs.arr).arr):incr *(**(*x.arr).arr):incr
                *(**(*means.arr).arr):incr *(**(*ls.arr).arr):incr
                gmm_objective:in-killed *(*alphas.arr):incr
   Plus diff mem management of: alloc(*expRes).arr:in-out alloc(*macroDef305).arr:in-out
                alloc(*QtimesvRes).arr:in-out alloc(*subRes).arr:in-out
                alloc(*macroDef300).arr:in-out alloc(*macroDef301).arr:in-out
                qs:in *qs.arr:in *(*qs.arr):in **(*qs.arr).arr:in
                x:in *x.arr:in *(*x.arr):in **(*x.arr).arr:in
                means:in *means.arr:in *(*means.arr):in **(*means.arr).arr:in
                ls:in *ls.arr:in *(*ls.arr):in **(*ls.arr).arr:in
                alphas:in *alphas.arr:in
*/
void gmm_objective_b(array_array_number_t_struct *x, 
        array_array_number_t_struct *xb, array_number_t_struct *alphas, 
        array_number_t_struct *alphasb, array_array_number_t_struct *means, 
        array_array_number_t_struct *meansb, array_array_number_t_struct *qs, 
        array_array_number_t_struct *qsb, array_array_number_t_struct *ls, 
        array_array_number_t_struct *lsb, number_t wishart_gamma, number_t 
        wishart_m, number_t gmm_objectiveb) {
    card_t n = x->length;
    card_t d = x->arr[0]->length;
    card_t macroDef299 = alphas->length;
    card_t K = macroDef299;
    array_number_t macroDef301;
    array_number_t macroDef301b;
    double result1;
    double result1b;
    int adTo;
    int adTo0;
    int adTo1;
    int ii1;
    int chunklength;
    int branch;
    void *diffchunkold;
    void *chunkold;
    number_t gmm_objective;
    macroDef301b = (array_number_t_struct *)malloc(sizeof(int)*2);
    for (ii1 = 0; ii1 < 2; ++ii1)
        macroDef301b[ii1].arr = NULL;
    macroDef301 = (array_number_t_struct *)malloc(sizeof(int)*2);
    macroDef301->length = n;
    macroDef301b->arr = (number_t *)malloc(sizeof(number_t)*n);
    for (ii1 = 0; ii1 < n; ++ii1)
        macroDef301b->arr[ii1] = 0.0;
    macroDef301->arr = (number_t *)malloc(sizeof(number_t)*n);
    int i;
    for (i = 0; i < macroDef301->length; ++i) {
        array_number_t macroDef300;
        array_number_t macroDef300b;
        macroDef300b = (array_number_t_struct *)malloc(sizeof(int)*2);
        for (ii1 = 0; ii1 < 2; ++ii1)
            macroDef300b[ii1].arr = NULL;
        macroDef300 = (array_number_t_struct *)malloc(sizeof(int)*2);
        pushinteger4(macroDef300->length);
        macroDef300->length = K;
        pushpointer8(macroDef300b->arr);
        macroDef300b->arr = (number_t *)malloc(sizeof(number_t)*K);
        for (ii1 = 0; ii1 < K; ++ii1)
            macroDef300b->arr[ii1] = 0.0;
        pushpointer8(macroDef300->arr);
        macroDef300->arr = (number_t *)malloc(sizeof(number_t)*K);
        int k;
        for (k= 0; k < macroDef300->length; ++k) {
            array_number_t subRes;
            double result1;
            array_number_t_struct *result2;
            array_number_t_struct *result3;
            double result4;
            array_number_t subResb;
            array_number_t QtimesvResb;
            array_number_t result3b;
            array_number_t result2b;
            subResb = (array_number_t_struct *)malloc(sizeof(int)*2);
            for (ii1 = 0; ii1 < 2; ++ii1)
                subResb[ii1].arr = NULL;
            subRes = (array_number_t_struct *)malloc(sizeof(int)*2);
            subRes->length = d;
            pushpointer8(subResb->arr);
            subResb->arr = (number_t *)malloc(sizeof(number_t)*d);
            for (ii1 = 0; ii1 < d; ++ii1)
                subResb->arr[ii1] = 0.0;
            pushpointer8(subRes->arr);
            subRes->arr = (number_t *)malloc(sizeof(number_t)*d);
            array_number_t QtimesvRes;
            QtimesvResb = (array_number_t_struct *)malloc(sizeof(int)*2);
            for (ii1 = 0; ii1 < 2; ++ii1)
                QtimesvResb[ii1].arr = NULL;
            QtimesvRes = (array_number_t_struct *)malloc(sizeof(int)*2);
            pushinteger4(QtimesvRes->length);
            QtimesvRes->length = d;
            pushpointer8(QtimesvResb->arr);
            QtimesvResb->arr = (number_t *)malloc(sizeof(number_t)*d);
            for (ii1 = 0; ii1 < d; ++ii1)
                QtimesvResb->arr[ii1] = 0.0;
            pushpointer8(QtimesvRes->arr);
            QtimesvRes->arr = (number_t *)malloc(sizeof(number_t)*d);
            result1 = vectorSum(qs->arr[k]);
            if (subRes->arr) {
                pushreal8(*subRes->arr);
                pushcontrol1b(1);
            } else
                pushcontrol1b(0);
            result2 = subtract(x->arr[i], means->arr[k], subRes);
            if (QtimesvRes->arr) {
                pushreal8(*QtimesvRes->arr);
                pushcontrol1b(1);
            } else
                pushcontrol1b(0);
            result3 = Qtimesv(qs->arr[k], ls->arr[k], result2, QtimesvRes);
            result4 = sqnorm(result3);
            pushreal8(macroDef300->arr[k]);
            macroDef300->arr[k] = alphas->arr[k] + result1 - 0.5*result4;
            pushpointer8(QtimesvResb->arr);
            free(QtimesvResb->arr);
            pushreal8array(QtimesvRes->arr, chunklength);
            pushpointer8(QtimesvRes->arr);
            free(QtimesvRes->arr);
            pushinteger4(chunklength);
            for (ii1 = 0; ii1 < chunklength; ++ii1)
                pushpointer8(QtimesvResb[ii1].arr);
            pushpointer8(QtimesvResb);
            free(QtimesvResb);
            for (ii1 = 0; ii1 < chunklength; ++ii1) {
                pushpointer8(QtimesvRes[ii1].arr);
                pushinteger4(QtimesvRes[ii1].length);
            }
            pushpointer8(QtimesvRes);
            free(QtimesvRes);
            pushinteger4(chunklength);
            pushpointer8(subResb->arr);
            free(subResb->arr);
            pushreal8array(subRes->arr, chunklength);
            pushpointer8(subRes->arr);
            free(subRes->arr);
            pushinteger4(chunklength);
            for (ii1 = 0; ii1 < chunklength; ++ii1)
                pushpointer8(subResb[ii1].arr);
            pushpointer8(subResb);
            free(subResb);
            for (ii1 = 0; ii1 < chunklength; ++ii1)
                pushpointer8(subRes[ii1].arr);
            pushpointer8(subRes);
            free(subRes);
            pushinteger4(chunklength);
            pushpointer8(result3b);
            pushpointer8(result3);
            pushpointer8(result2b);
            pushpointer8(result2);
        }
        pushinteger4(k - 1);
        macroDef301->arr[i] = logsumexp(macroDef300);
        pushpointer8(macroDef300b->arr);
        free(macroDef300b->arr);
        pushreal8array(macroDef300->arr, chunklength);
        pushpointer8(macroDef300->arr);
        free(macroDef300->arr);
        pushinteger4(chunklength);
        for (ii1 = 0; ii1 < chunklength; ++ii1)
            pushpointer8(macroDef300b[ii1].arr);
        pushpointer8(macroDef300b);
        free(macroDef300b);
        for (ii1 = 0; ii1 < chunklength; ++ii1) {
            pushpointer8(macroDef300[ii1].arr);
            pushinteger4(macroDef300[ii1].length);
        }
        pushpointer8(macroDef300);
        free(macroDef300);
        pushinteger4(chunklength);
    }
    pushinteger4(i - 1);
    array_number_t macroDef305;
    array_number_t macroDef305b;
    macroDef305b = (array_number_t_struct *)malloc(sizeof(int)*2);
    for (ii1 = 0; ii1 < 2; ++ii1)
        macroDef305b[ii1].arr = NULL;
    macroDef305 = (array_number_t_struct *)malloc(sizeof(int)*2);
    macroDef305->length = K;
    macroDef305b->arr = (number_t *)malloc(sizeof(number_t)*K);
    for (ii1 = 0; ii1 < K; ++ii1)
        macroDef305b->arr[ii1] = 0.0;
    macroDef305->arr = (number_t *)malloc(sizeof(number_t)*K);
    int k;
    for (k = 0; k < macroDef305->length; ++k) {
        array_number_t expRes;
        array_number_t_struct *result1;
        double result2;
        double result3;
        array_number_t expResb;
        array_number_t result1b0;
        expResb = (array_number_t_struct *)malloc(sizeof(int)*2);
        for (ii1 = 0; ii1 < 2; ++ii1)
            expResb[ii1].arr = NULL;
        expRes = (array_number_t_struct *)malloc(sizeof(int)*2);
        pushinteger4(expRes->length);
        expRes->length = qs->arr[k]->length;
        pushpointer8(expResb->arr);
        expResb->arr = (number_t *)malloc(sizeof(number_t)*qs->arr[k]->length)
        ;
        for (ii1 = 0; ii1 < qs->arr[k]->length; ++ii1)
            expResb->arr[ii1] = 0.0;
        pushpointer8(expRes->arr);
        expRes->arr = (number_t *)malloc(sizeof(number_t)*qs->arr[k]->length);
        if (expRes->arr) {
            pushreal8(*expRes->arr);
            pushcontrol1b(1);
        } else
            pushcontrol1b(0);
        result1 = vectorExp(qs->arr[k], expRes);
        result2 = sqnorm(result1);
        result3 = sqnorm(ls->arr[k]);
        macroDef305->arr[k] = result2 + result3;
        pushpointer8(expResb->arr);
        free(expResb->arr);
        pushreal8array(expRes->arr, chunklength);
        pushpointer8(expRes->arr);
        free(expRes->arr);
        pushinteger4(chunklength);
        for (ii1 = 0; ii1 < chunklength; ++ii1)
            pushpointer8(expResb[ii1].arr);
        pushpointer8(expResb);
        free(expResb);
        for (ii1 = 0; ii1 < chunklength; ++ii1) {
            pushpointer8(expRes[ii1].arr);
            pushinteger4(expRes[ii1].length);
        }
        pushpointer8(expRes);
        free(expRes);
        pushinteger4(chunklength);
        pushpointer8(result1b0);
        pushpointer8(result1);
    }
    pushinteger4(k - 1);
    double resVectorSum1;
    double resVectorSum1b;
    double resVectorSum2;
    double resVectorSum2b;
    resVectorSum1b = gmm_objectiveb;
    result1b = -((double)n*gmm_objectiveb);
    resVectorSum2b = 0.5*gmm_objectiveb;
    logsumexp_b(alphas, alphasb, result1b);
    vectorSum_b(macroDef305, macroDef305b, resVectorSum2b);
    vectorSum_b(macroDef301, macroDef301b, resVectorSum1b);
    popinteger4(&adTo);
    for (int k = adTo; k > -1; --k) {
        array_number_t expRes;
        array_number_t expResb;
        array_number_t_struct *result1;
        array_number_t result1b0;
        double result2;
        double result2b;
        double result3;
        double result3b;
        poppointer8((void **)&result1);
        poppointer8((void **)&result1b0);
        popinteger4(&chunklength);
        expRes = (array_number_t_struct *)malloc(sizeof(array_number_t_struct)
            *chunklength);
        poppointer8((void **)&chunkold);
        for (ii1 = chunklength-1; ii1 > -1; --ii1) {
            popinteger4(&expRes[ii1].length);
            poppointer8((void **)&expRes[ii1].arr);
        }
        expResb = (array_number_t_struct *)malloc(sizeof(array_number_t_struct
            )*chunklength);
        poppointer8((void **)&diffchunkold);
        for (ii1 = chunklength-1; ii1 > -1; --ii1)
            poppointer8((void **)&expResb[ii1].arr);
        popinteger4(&chunklength);
        expRes->arr = (number_t *)malloc(8*chunklength);
        poppointer8((void **)&chunkold);
        popreal8array(expRes->arr, chunklength);
        expResb->arr = (number_t *)malloc(8*chunklength);
        poppointer8((void **)&diffchunkold);
        for (ii1 = 0; ii1 < chunklength; ++ii1)
            expResb->arr[ii1] = 0.0;
        result2b = macroDef305b->arr[k];
        result3b = macroDef305b->arr[k];
        macroDef305b->arr[k] = 0.0;
        sqnorm_b(ls->arr[k], lsb->arr[k], result3b);
        sqnorm_b(result1, result1b0, result2b);
        popcontrol1b(&branch);
        if (branch == 1)
            popreal8(expRes->arr);
        vectorExp_b(qs->arr[k], qsb->arr[k], expRes, expResb, result1b0);
        free(expRes->arr);
        poppointer8((void **)&expRes->arr);
        free(expResb->arr);
        poppointer8((void **)&expResb->arr);
        popinteger4(&expRes->length);
        free(expRes);
        free(expResb);
    }
    free(macroDef305->arr);
    free(macroDef305b->arr);
    free(macroDef305);
    free(macroDef305b);
    popinteger4(&adTo0);
    for (int i = adTo0; i > -1; --i) {
        array_number_t macroDef300;
        array_number_t macroDef300b;
        popinteger4(&chunklength);
        macroDef300 = (array_number_t_struct *)malloc(sizeof(
            array_number_t_struct)*chunklength);
        poppointer8((void **)&chunkold);
        for (ii1 = chunklength-1; ii1 > -1; --ii1) {
            popinteger4(&macroDef300[ii1].length);
            poppointer8((void **)&macroDef300[ii1].arr);
        }
        macroDef300b = (array_number_t_struct *)malloc(sizeof(
            array_number_t_struct)*chunklength);
        poppointer8((void **)&diffchunkold);
        for (ii1 = chunklength-1; ii1 > -1; --ii1)
            poppointer8((void **)&macroDef300b[ii1].arr);
        popinteger4(&chunklength);
        macroDef300->arr = (number_t *)malloc(8*chunklength);
        poppointer8((void **)&chunkold);
        popreal8array(macroDef300->arr, chunklength);
        macroDef300b->arr = (number_t *)malloc(8*chunklength);
        poppointer8((void **)&diffchunkold);
        for (ii1 = 0; ii1 < chunklength; ++ii1)
            macroDef300b->arr[ii1] = 0.0;
        logsumexp_b(macroDef300, macroDef300b, macroDef301b->arr[i]);
        macroDef301b->arr[i] = 0.0;
        popinteger4(&adTo1);
        for (int k = adTo1; k > -1; --k) {
            array_number_t subRes;
            array_number_t subResb;
            double result1;
            double result1b;
            array_number_t_struct *result2;
            array_number_t result2b;
            array_number_t_struct *result3;
            array_number_t result3b;
            double result4;
            double result4b;
            array_number_t QtimesvRes;
            array_number_t QtimesvResb;
            poppointer8((void **)&result2);
            poppointer8((void **)&result2b);
            poppointer8((void **)&result3);
            poppointer8((void **)&result3b);
            popinteger4(&chunklength);
            subRes = (array_number_t_struct *)malloc(sizeof(
                array_number_t_struct)*chunklength);
            poppointer8((void **)&chunkold);
            for (ii1 = chunklength-1; ii1 > -1; --ii1)
                poppointer8((void **)&subRes[ii1].arr);
            subResb = (array_number_t_struct *)malloc(sizeof(
                array_number_t_struct)*chunklength);
            poppointer8((void **)&diffchunkold);
            for (ii1 = chunklength-1; ii1 > -1; --ii1)
                poppointer8((void **)&subResb[ii1].arr);
            popinteger4(&chunklength);
            subRes->arr = (number_t *)malloc(8*chunklength);
            poppointer8((void **)&chunkold);
            popreal8array(subRes->arr, chunklength);
            subResb->arr = (number_t *)malloc(8*chunklength);
            poppointer8((void **)&diffchunkold);
            for (ii1 = 0; ii1 < chunklength; ++ii1)
                subResb->arr[ii1] = 0.0;
            popinteger4(&chunklength);
            QtimesvRes = (array_number_t_struct *)malloc(sizeof(
                array_number_t_struct)*chunklength);
            poppointer8((void **)&chunkold);
            for (ii1 = chunklength-1; ii1 > -1; --ii1) {
                popinteger4(&QtimesvRes[ii1].length);
                poppointer8((void **)&QtimesvRes[ii1].arr);
            }
            QtimesvResb = (array_number_t_struct *)malloc(sizeof(
                array_number_t_struct)*chunklength);
            poppointer8((void **)&diffchunkold);
            for (ii1 = chunklength-1; ii1 > -1; --ii1)
                poppointer8((void **)&QtimesvResb[ii1].arr);
            popinteger4(&chunklength);
            QtimesvRes->arr = (number_t *)malloc(8*chunklength);
            poppointer8((void **)&chunkold);
            popreal8array(QtimesvRes->arr, chunklength);
            QtimesvResb->arr = (number_t *)malloc(8*chunklength);
            poppointer8((void **)&diffchunkold);
            for (ii1 = 0; ii1 < chunklength; ++ii1)
                QtimesvResb->arr[ii1] = 0.0;
            popreal8(&macroDef300->arr[k]);
            alphasb->arr[k] = alphasb->arr[k] + macroDef300b->arr[k];
            result1b = macroDef300b->arr[k];
            result4b = -(0.5*macroDef300b->arr[k]);
            macroDef300b->arr[k] = 0.0;
            sqnorm_b(result3, result3b, result4b);
            popcontrol1b(&branch);
            if (branch == 1)
                popreal8(QtimesvRes->arr);
            Qtimesv_b(qs->arr[k], qsb->arr[k], ls->arr[k], lsb->arr[k], 
                      result2, result2b, QtimesvRes, QtimesvResb, result3b);
            popcontrol1b(&branch);
            if (branch == 1)
                popreal8(subRes->arr);
            subtract_b(x->arr[i], xb->arr[i], means->arr[k], meansb->arr[k], 
                       subRes, subResb, result2b);
            vectorSum_b(qs->arr[k], qsb->arr[k], result1b);
            free(QtimesvRes->arr);
            poppointer8((void **)&QtimesvRes->arr);
            free(QtimesvResb->arr);
            poppointer8((void **)&QtimesvResb->arr);
            popinteger4(&QtimesvRes->length);
            free(QtimesvRes);
            free(QtimesvResb);
            free(subRes->arr);
            poppointer8((void **)&subRes->arr);
            free(subResb->arr);
            poppointer8((void **)&subResb->arr);
            free(subRes);
            free(subResb);
        }
        free(macroDef300->arr);
        poppointer8((void **)&macroDef300->arr);
        free(macroDef300b->arr);
        poppointer8((void **)&macroDef300b->arr);
        popinteger4(&macroDef300->length);
        free(macroDef300);
        free(macroDef300b);
    }
    free(macroDef301->arr);
    free(macroDef301b->arr);
    free(macroDef301);
    free(macroDef301b);
}
#ifdef __cplusplus
}
#endif