/*        Generated by TAPENADE     (INRIA, Ecuador team)
    Tapenade 3.13 (r6666M) -  1 Mar 2018 15:30
*/
#include <stdio.h>
#include <math.h>

/*
  Differentiation of sqsum in forward (tangent) mode:
   variations   of useful results: sqsum
   with respect to varying inputs: *x
   Plus diff mem management of: x:in
*/
double sqsum_d(int n, double *x, double *xd, double *sqsum) {
    int i;
    double res;
    double resd;
    res = 0;
    resd = 0.0;
    for (i = 0; i < n; ++i) {
        resd = resd + xd[i]*x[i] + x[i]*xd[i];
        res = res + x[i]*x[i];
    }
    *sqsum = res;
    return resd;
}

/*
  Differentiation of cross in forward (tangent) mode:
   variations   of useful results: *out
   with respect to varying inputs: *out *a *b
   Plus diff mem management of: out:in a:in b:in
*/
void cross_d0(double *a, double *ad, double *b, double *bd, double *out, 
        double *outd) {
    outd[0] = ad[1]*b[2] + a[1]*bd[2] - ad[2]*b[1] - a[2]*bd[1];
    out[0] = a[1]*b[2] - a[2]*b[1];
    outd[1] = ad[2]*b[0] + a[2]*bd[0] - ad[0]*b[2] - a[0]*bd[2];
    out[1] = a[2]*b[0] - a[0]*b[2];
    outd[2] = ad[0]*b[1] + a[0]*bd[1] - ad[1]*b[0] - a[1]*bd[0];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

/*
  Differentiation of dot_prod in forward (tangent) mode:
   variations   of useful results: dot_prod
   with respect to varying inputs: *x *y
   Plus diff mem management of: x:in y:in
*/
double dot_prod_d(int n, double *x, double *xd, double *y, double *yd, double 
        *dot_prod) {
    double res = 0;
    double resd;
    resd = 0.0;
    for (int i = 0; i < n; ++i) {
        resd = resd + xd[i]*y[i] + x[i]*yd[i];
        res += x[i]*y[i];
    }
    *dot_prod = res;
    return resd;
}

/*
  Differentiation of ba_rod_single in forward (tangent) mode:
   variations   of useful results: alloc(*cross_) alloc(*w) *rotatedPt
   with respect to varying inputs: alloc(*cross_) alloc(*w) *rot
                *rotatedPt *pt
   Plus diff mem management of: rot:in rotatedPt:in pt:in
*/
void ba_rod_single_d(double *rot, double *rotd, double *pt, double *ptd, 
        double *rotatedPt, double *rotatedPtd) {
    int i;
    double sqtheta, theta, costheta, sintheta, theta_inverse, tmp;
    double sqthetad, thetad, costhetad, sinthetad, theta_inversed, tmpd;
    double *w;
    double *wd;
    double result1;
    double result1d;
    int ii1;
    wd = (double *)malloc(sizeof(double)*3);
    for (ii1 = 0; ii1 < 3; ++ii1)
        wd[ii1] = 0.0;
    w = (double *)malloc(sizeof(double)*3);
    double *cross_;
    double *cross_d;
    cross_d = (double *)malloc(sizeof(double)*3);
    for (ii1 = 0; ii1 < 3; ++ii1)
        cross_d[ii1] = 0.0;
    cross_ = (double *)malloc(sizeof(double)*3);
    sqthetad = sqsum_d(3, rot, rotd, &sqtheta);
    thetad = (sqtheta == 0.0 ? 0.0 : sqthetad/(2.0*sqrt(sqtheta)));
    theta = sqrt(sqtheta);
    costhetad = -(thetad*sin(theta));
    costheta = cos(theta);
    sinthetad = thetad*cos(theta);
    sintheta = sin(theta);
    theta_inversed = -(thetad/(theta*theta));
    theta_inverse = 1.0/theta;
    for (i = 0; i < 3; ++i) {
        wd[i] = rotd[i]*theta_inverse + rot[i]*theta_inversed;
        w[i] = rot[i]*theta_inverse;
    }
    cross_d0(w, wd, pt, ptd, cross_, cross_d);
    result1d = dot_prod_d(3, w, wd, pt, ptd, &result1);
    tmpd = result1d*(1.-costheta) - result1*costhetad;
    tmp = result1*(1.-costheta);
    for (i = 0; i < 3; ++i) {
        rotatedPtd[i] = ptd[i]*costheta + pt[i]*costhetad + cross_d[i]*
            sintheta + cross_[i]*sinthetad + wd[i]*tmp + w[i]*tmpd;
        rotatedPt[i] = pt[i]*costheta + cross_[i]*sintheta + w[i]*tmp;
    }
    free(wd);
    free(w);
    free(cross_d);
    free(cross_);
}

/*
  Differentiation of ba_rod_native in forward (tangent) mode:
   variations   of useful results: alloc(*cross_) alloc(*w) **res
   with respect to varying inputs: alloc(*cross_) alloc(*w) **res
                *xs
   RW status of diff variables: alloc(*cross_):in-out alloc(*w):in-out
                **res:in-out *xs:in
   Plus diff mem management of: res:in *res:in xs:in
*/
void ba_rod_native_d(int d, double *xs, double *xsd, int n, double **res, 
        double **resd) {
    for (int idx = 0; idx < n; ++idx) {
        int offset = 11 + d*idx;
        ba_rod_single_d(xs, xsd, &xs[offset], &xsd[offset], res[idx], resd[idx
                        ]);
    }
}
