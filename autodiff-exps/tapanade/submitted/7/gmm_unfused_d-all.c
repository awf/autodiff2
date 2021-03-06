#ifdef __cplusplus
extern "C" {
#endif
/*        Generated by TAPENADE     (INRIA, Ecuador team)
    Tapenade 3.13 (r6666M) -  1 Mar 2018 15:30
*/
#include <stdlib.h>
#include <math.h>
#include "gmm_unfused_d-all.h"

/*
  Differentiation of arr_max in forward (tangent) mode:
   variations   of useful results: arr_max
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
double arr_max_d(array_number_t_struct *arr, array_number_t_struct *arrd, 
        double *arr_max) {
    double *x = arr->arr;
    double *xd = arrd->arr;
    int n = arr->length;
    double m;
    double md;
    int i;
    md = xd[0];
    m = x[0];
    for (i = 1; i < n; ++i)
        if (x[i] > m) {
            md = xd[i];
            m = x[i];
        }
    *arr_max = m;
    return md;
}

/*
  Differentiation of logsumexp in forward (tangent) mode:
   variations   of useful results: logsumexp
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
double logsumexp_d(array_number_t_struct *arr, array_number_t_struct *arrd, 
        double *logsumexp) {
    double *x = arr->arr;
    double *xd = arrd->arr;
    int n = arr->length;
    int i;
    double mx, semx;
    double mxd, semxd;
    mxd = arr_max_d(arr, arrd, &mx);
    semx = 0.;
    semxd = 0.0;
    for (i = 0; i < n; ++i) {
        semxd = semxd + (xd[i]-mxd)*exp(x[i]-mx);
        semx += exp(x[i] - mx);
    }
    *logsumexp = log(semx) + mx;
    return semxd/semx + mxd;
}

/*
  Differentiation of sqnorm in forward (tangent) mode:
   variations   of useful results: sqnorm
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
double sqnorm_d(array_number_t_struct *arr, array_number_t_struct *arrd, 
        double *sqnorm) {
    double *x = arr->arr;
    double *xd = arrd->arr;
    int d = arr->length;
    int i;
    double out;
    double outd;
    out = 0;
    outd = 0.0;
    for (i = 0; i < d; ++i) {
        outd = outd + xd[i]*x[i] + x[i]*xd[i];
        out += x[i]*x[i];
    }
    *sqnorm = out;
    return outd;
}

/*
  Differentiation of vectorSum in forward (tangent) mode:
   variations   of useful results: vectorSum
   with respect to varying inputs: *(*arr.arr)
   Plus diff mem management of: arr:in *arr.arr:in
*/
double vectorSum_d(array_number_t_struct *arr, array_number_t_struct *arrd, 
        double *vectorSum) {
    double *x = arr->arr;
    double *xd = arrd->arr;
    int d = arr->length;
    int i;
    double out;
    double outd;
    out = 0;
    outd = 0.0;
    for (i = 0; i < d; ++i) {
        outd = outd + xd[i];
        out += x[i];
    }
    *vectorSum = out;
    return outd;
}

/*
  Differentiation of subtract in forward (tangent) mode:
   variations   of useful results: *(*out.arr)
   with respect to varying inputs: *(*out.arr) *(*x.arr) *(*y.arr)
   Plus diff mem management of: subtract:in-out out:in *out.arr:in
                x:in *x.arr:in y:in *y.arr:in
*/
array_number_t subtract_d(array_number_t_struct *x, array_number_t_struct *xd,
        array_number_t_struct *y, array_number_t_struct *yd, 
        array_number_t_struct *out, array_number_t_struct *outd, 
        array_number_t *subtract) {
    int id;
    for (id = 0; id < x->length; ++id) {
        outd->arr[id] = xd->arr[id] - yd->arr[id];
        out->arr[id] = x->arr[id] - y->arr[id];
    }
    *subtract = out;
    return outd;
}

/*
  Differentiation of vectorExp in forward (tangent) mode:
   variations   of useful results: *(*out.arr)
   with respect to varying inputs: *(*out.arr) *(*arr.arr)
   Plus diff mem management of: out:in *out.arr:in vectorExp:in-out
                arr:in *arr.arr:in
*/
array_number_t vectorExp_d(array_number_t_struct *arr, array_number_t_struct *
        arrd, array_number_t_struct *out, array_number_t_struct *outd, 
        array_number_t *vectorExp) {
    int id;
    for (id = 0; id < arr->length; ++id) {
        outd->arr[id] = arrd->arr[id]*exp(arr->arr[id]);
        out->arr[id] = exp(arr->arr[id]);
    }
    *vectorExp = out;
    return outd;
}

/*
  Differentiation of Qtimesv in forward (tangent) mode:
   variations   of useful results: *(*result.arr)
   with respect to varying inputs: *(*result.arr) *(*l.arr) *(*q.arr)
                *(*v.arr)
   Plus diff mem management of: result:in *result.arr:in l:in
                *l.arr:in q:in *q.arr:in Qtimesv:in-out v:in *v.arr:in
*/
array_number_t Qtimesv_d(array_number_t_struct *q, array_number_t_struct *qd, 
        array_number_t_struct *l, array_number_t_struct *ld, 
        array_number_t_struct *v, array_number_t_struct *vd, 
        array_number_t_struct *result, array_number_t_struct *resultd, 
        array_number_t *Qtimesv) {
    card_t macroDef294 = v->length;
    for (int i = 0; i < result->length; ++i) {
        index_t tis;
        tis = tri(i - 1);
        card_t macroDef295 = l->length;
        number_t macroDef296 = 0;
        number_t macroDef296d;
        macroDef296d = 0.0;
        for (int idx = 0; idx < macroDef295; ++idx) {
            index_t j = idx - tis;
            bool_t isInRange = 0;
            if (j >= 0)
                isInRange = j < i;
            else
                isInRange = 0;
            number_t ite298 = 0;
            number_t ite298d;
            if (isInRange) {
                ite298d = macroDef296d + ld->arr[idx]*v->arr[j] + l->arr[idx]*
                    vd->arr[j];
                ite298 = macroDef296 + l->arr[idx]*v->arr[j];
            } else {
                ite298d = macroDef296d;
                ite298 = macroDef296;
            }
            macroDef296d = ite298d;
            macroDef296 = ite298;
        }
        number_t sum = macroDef296;
        number_t sumd = macroDef296d;
        resultd->arr[i] = sumd + qd->arr[i]*exp(q->arr[i])*v->arr[i] + exp(q->
            arr[i])*vd->arr[i];
        result->arr[i] = sum + exp(q->arr[i])*v->arr[i];
    }
    *Qtimesv = result;
    return resultd;
}

/*
  Differentiation of gmm_objective in forward (tangent) mode:
   variations   of useful results: alloc(*(*expRes.arr)) *(alloc(*expRes).arr)
                alloc(*(*macroDef305.arr)) *(alloc(*macroDef305).arr)
                alloc(*(*QtimesvRes.arr)) *(alloc(*QtimesvRes).arr)
                alloc(*(*subRes.arr)) *(alloc(*subRes).arr) alloc(*(*macroDef300.arr))
                *(alloc(*macroDef300).arr) alloc(*(*macroDef301.arr))
                *(alloc(*macroDef301).arr) gmm_objective
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
                *(**(*qs.arr).arr):in *(**(*x.arr).arr):in *(**(*means.arr).arr):in
                *(**(*ls.arr).arr):in gmm_objective:out *(*alphas.arr):in
   Plus diff mem management of: alloc(*expRes).arr:in-out alloc(*macroDef305).arr:in-out
                alloc(*QtimesvRes).arr:in-out alloc(*subRes).arr:in-out
                alloc(*macroDef300).arr:in-out alloc(*macroDef301).arr:in-out
                qs:in *qs.arr:in *(*qs.arr):in **(*qs.arr).arr:in
                x:in *x.arr:in *(*x.arr):in **(*x.arr).arr:in
                means:in *means.arr:in *(*means.arr):in **(*means.arr).arr:in
                ls:in *ls.arr:in *(*ls.arr):in **(*ls.arr).arr:in
                alphas:in *alphas.arr:in
*/
number_t gmm_objective_d(array_array_number_t_struct *x, 
        array_array_number_t_struct *xd, array_number_t_struct *alphas, 
        array_number_t_struct *alphasd, array_array_number_t_struct *means, 
        array_array_number_t_struct *meansd, array_array_number_t_struct *qs, 
        array_array_number_t_struct *qsd, array_array_number_t_struct *ls, 
        array_array_number_t_struct *lsd, number_t wishart_gamma, number_t 
        wishart_m, number_t *gmm_objective) {
    card_t n = x->length;
    card_t d = x->arr[0]->length;
    card_t macroDef299 = alphas->length;
    card_t K = macroDef299;
    array_number_t macroDef301;
    array_number_t macroDef301d;
    double result1;
    double result1d;
    int ii1;
    macroDef301d = (array_number_t_struct *)malloc(sizeof(int)*2);
    macroDef301 = (array_number_t_struct *)malloc(sizeof(int)*2);
    macroDef301->length = n;
    macroDef301d->arr = (number_t *)malloc(sizeof(number_t)*n);
    for (ii1 = 0; ii1 < n; ++ii1)
        macroDef301d->arr[ii1] = 0.0;
    macroDef301->arr = (number_t *)malloc(sizeof(number_t)*n);
    for (int i = 0; i < macroDef301->length; ++i) {
        array_number_t macroDef300;
        array_number_t macroDef300d;
        macroDef300d = (array_number_t_struct *)malloc(sizeof(int)*2);
        macroDef300 = (array_number_t_struct *)malloc(sizeof(int)*2);
        macroDef300->length = K;
        macroDef300d->arr = (number_t *)malloc(sizeof(number_t)*K);
        for (ii1 = 0; ii1 < K; ++ii1)
            macroDef300d->arr[ii1] = 0.0;
        macroDef300->arr = (number_t *)malloc(sizeof(number_t)*K);
        for (int k = 0; k < macroDef300->length; ++k) {
            array_number_t subRes;
            array_number_t subResd;
            double result1;
            double result1d;
            array_number_t_struct *result2;
            array_number_t result2d;
            array_number_t_struct *result3;
            array_number_t result3d;
            double result4;
            double result4d;
            subResd = (array_number_t_struct *)malloc(sizeof(int)*2);
            subRes = (array_number_t_struct *)malloc(sizeof(int)*2);
            subRes->length = d;
            subResd->arr = (number_t *)malloc(sizeof(number_t)*d);
            for (ii1 = 0; ii1 < d; ++ii1)
                subResd->arr[ii1] = 0.0;
            subRes->arr = (number_t *)malloc(sizeof(number_t)*d);
            array_number_t QtimesvRes;
            array_number_t QtimesvResd;
            QtimesvResd = (array_number_t_struct *)malloc(sizeof(int)*2);
            QtimesvRes = (array_number_t_struct *)malloc(sizeof(int)*2);
            QtimesvRes->length = d;
            QtimesvResd->arr = (number_t *)malloc(sizeof(number_t)*d);
            for (ii1 = 0; ii1 < d; ++ii1)
                QtimesvResd->arr[ii1] = 0.0;
            QtimesvRes->arr = (number_t *)malloc(sizeof(number_t)*d);
            result1d = vectorSum_d(qs->arr[k], qsd->arr[k], &result1);
            result2d = subtract_d(x->arr[i], xd->arr[i], means->arr[k], meansd
                                  ->arr[k], subRes, subResd, &result2);
            result3d = Qtimesv_d(qs->arr[k], qsd->arr[k], ls->arr[k], lsd->arr
                                 [k], result2, result2d, QtimesvRes, 
                                 QtimesvResd, &result3);
            result4d = sqnorm_d(result3, result3d, &result4);
            macroDef300d->arr[k] = alphasd->arr[k] + result1d - 0.5*result4d;
            macroDef300->arr[k] = alphas->arr[k] + result1 - 0.5*result4;
            free(QtimesvResd->arr);
            free(QtimesvRes->arr);
            free(QtimesvResd);
            free(QtimesvRes);
            free(subResd->arr);
            free(subRes->arr);
            free(subResd);
            free(subRes);
        }
        macroDef301d->arr[i] = logsumexp_d(macroDef300, macroDef300d, &
                                           macroDef301->arr[i]);
        free(macroDef300d->arr);
        free(macroDef300->arr);
        free(macroDef300d);
        free(macroDef300);
    }
    array_number_t macroDef305;
    array_number_t macroDef305d;
    macroDef305d = (array_number_t_struct *)malloc(sizeof(int)*2);
    macroDef305 = (array_number_t_struct *)malloc(sizeof(int)*2);
    macroDef305->length = K;
    macroDef305d->arr = (number_t *)malloc(sizeof(number_t)*K);
    for (ii1 = 0; ii1 < K; ++ii1)
        macroDef305d->arr[ii1] = 0.0;
    macroDef305->arr = (number_t *)malloc(sizeof(number_t)*K);
    for (int k = 0; k < macroDef305->length; ++k) {
        array_number_t expRes;
        array_number_t expResd;
        array_number_t_struct *result1;
        array_number_t result1d;
        double result2;
        double result2d;
        double result3;
        double result3d;
        expResd = (array_number_t_struct *)malloc(sizeof(int)*2);
        expRes = (array_number_t_struct *)malloc(sizeof(int)*2);
        expRes->length = qs->arr[k]->length;
        expResd->arr = (number_t *)malloc(sizeof(number_t)*qs->arr[k]->length)
        ;
        for (ii1 = 0; ii1 < qs->arr[k]->length; ++ii1)
            expResd->arr[ii1] = 0.0;
        expRes->arr = (number_t *)malloc(sizeof(number_t)*qs->arr[k]->length);
        result1d = vectorExp_d(qs->arr[k], qsd->arr[k], expRes, expResd, &
                               result1);
        result2d = sqnorm_d(result1, result1d, &result2);
        result3d = sqnorm_d(ls->arr[k], lsd->arr[k], &result3);
        macroDef305d->arr[k] = result2d + result3d;
        macroDef305->arr[k] = result2 + result3;
        free(expResd->arr);
        free(expRes->arr);
        free(expResd);
        free(expRes);
    }
    double resVectorSum1;
    double resVectorSum1d;
    resVectorSum1d = vectorSum_d(macroDef301, macroDef301d, &resVectorSum1);
    double resVectorSum2;
    double resVectorSum2d;
    resVectorSum2d = vectorSum_d(macroDef305, macroDef305d, &resVectorSum2);
    free(macroDef301d->arr);
    free(macroDef301->arr);
    free(macroDef301d);
    free(macroDef301);
    free(macroDef305d->arr);
    free(macroDef305->arr);
    free(macroDef305d);
    free(macroDef305);
    result1d = logsumexp_d(alphas, alphasd, &result1);
    *gmm_objective = resVectorSum1 - (double)n*result1 + 0.5*resVectorSum2;
    return resVectorSum1d - (double)n*result1d + 0.5*resVectorSum2d;
}

#ifdef __cplusplus
}
#endif