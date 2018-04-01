#include <cstring>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>

#include "shared/defs.h"
#include "shared/utils.h"

// #define DO_GMM
// #define DO_BA


#if defined DO_GMM
  #if defined TAPENADE
    #include "tapanade/gmm_all.h"
    #if defined REV_MODE
      extern "C" {
        #include "tapanade/gmm_b-all.h"
      }
    #endif
  #elif defined DIFFSMOOTH
// extern "C"
// {
    #include "diffsmooth/gmm_compact.h"
    // #include "diffsmooth/gmm.h"
// }
  #elif defined TAP_FUSED
    extern "C"
    {
      #include "tapanade/submitted/5/gmm_fused.h"
    #if defined REV_MODE
      #include "tapanade/submitted/5/gmm_fused.h_b-all.h"
    #else
      #include "tapanade/submitted/5/gmm_fused.h_d-all.h"
    #endif
    }
  #elif defined TAP_UNFUSED
    extern "C"
    {
      #include "tapanade/submitted/7/gmm_unfused.h"
    #if defined REV_MODE
      #include "tapanade/submitted/7/gmm_unfused_b-all.h"
    #else
      #include "tapanade/submitted/7/gmm_unfused_d-all.h"
    #endif
    }
  #endif
#elif defined DO_BA
extern "C"
{
  #if defined TAPENADE
    #include "tapanade/submitted/6/ba.h"
    #if defined REV_MODE
      #include "tapanade/submitted/6/ba_b-all.h"
    #else
      #include "tapanade/submitted/6/ba_d-all.h"
    #endif
  #elif defined DIFFSMOOTH
    #include "diffsmooth/ba.h"
  #endif
}
#endif


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std::chrono;

#if defined DO_GMM
  #if defined DIFFSMOOTH || TAP_FUSED || TAP_UNFUSED


index_t TOP_LEVEL_usecases_gmm_tri(index_t n) {
  
  return ((n) * ((n) + (1))) / (2);
}

void matrix_refill(array_array_number_t mat, number_t value) {
  for(int r = 0; r < mat->length; r++){
    for(int c = 0; c < mat->arr[r]->length; c++){
      mat->arr[r]->arr[c] = value;
    }
  }
}

void vector_refill(array_number_t vec, number_t value) {
  for(int r = 0; r < vec->length; r++){
    vec->arr[r] = value;
  }
}

inline void compute_gmm_Jb(int d, int k, int n,
  array_number_t alphas_data,
  array_array_number_t means_data,
  array_array_number_t qs_data,
  array_array_number_t ls_data,
  array_array_number_t xs_data,
  array_number_t alphasd_data,
  array_array_number_t meansd_data,
  array_array_number_t qsd_data,
  array_array_number_t lsd_data,
  array_array_number_t xsd_data,
  Wishart wishart,
  double* err, double* Jb)
{
  int Jsz = (k*(d + 1)*(d + 2)) / 2;
  int td = TOP_LEVEL_usecases_gmm_tri(d);

#if defined REV_MODE
  vector_refill(alphasd_data, 0);
  matrix_refill(meansd_data, 0);
  matrix_refill(qsd_data, 0);
  matrix_refill(lsd_data, 0);
  matrix_refill(xsd_data, 0);
  double eb = 1.;

  gmm_objective_b(xs_data, xsd_data, alphas_data, alphasd_data, means_data, meansd_data, qs_data, qsd_data, ls_data, lsd_data, wishart.gamma, wishart.m, eb);
  for(int i = 0; i<Jsz; i++) {
    if(i < k) {
      Jb[i] = alphasd_data->arr[i];
    } else if (i >= k && i < k + k * d) {
      int j = i - k;
      Jb[i] = meansd_data->arr[j / d]->arr[j % d];
    } else  //if (i >= k + k * d && i < k + k * d + k * td + d) 
      {
      int j = i - k - k * d;
      int j1 = j % td;
      int j2 = j / td;
      if (j1 < d) {
        Jb[i] = qsd_data->arr[j2]->arr[j1];
      } else {
        Jb[i] = lsd_data->arr[j2]->arr[j1 - d];  
      }
      //qsd_data->arr[j / td]->arr[j % td] = 1;
    } 
  }
#else

  // double eb = 1.;
  // memset(Jb, 0, Jsz*sizeof(double));

  // alphasd_data->arr = &Jb[0];
  // for(int i = 0; i<k; i++) {
  //   meansd_data->arr[i]->arr = &Jb[k + i * d];
  //   qsd_data->arr[i]->arr = &Jb[k + k * d + i*td];
  //   lsd_data->arr[i]->arr = &Jb[k + k * d + i*td+d];
  // }
  // Jb[0] = gmm_objective_d(xs_data, alphas_data, means_data, qs_data, ls_data, wishart.gamma, wishart.m,
  //     xsd_data, alphasd_data, meansd_data, qsd_data, lsd_data, wishart.gamma, wishart.m);
  for(int i = 0; i<Jsz; i++) {
    if(i < k) {
      alphasd_data->arr[i] = 1;
    } else if (i >= k && i < k + k * d) {
      int j = i - k;
      meansd_data->arr[j / d]->arr[j % d] = 1;
    } else  //if (i >= k + k * d && i < k + k * d + k * td + d) 
      {
      int j = i - k - k * d;
      int j1 = j % td;
      int j2 = j / td;
      if (j1 < d) {
        qsd_data->arr[j2]->arr[j1] = 1;
      } else {
        lsd_data->arr[j2]->arr[j1 - d] = 1;  
      }
      //qsd_data->arr[j / td]->arr[j % td] = 1;
    } 
    // else {
    //   int j = i - k - k * d - d;
    //   lsd_data->arr[j / td]->arr[j % td] = 1;
    // }
    #if defined TAP_FUSED || TAP_UNFUSED
    double tmp;
    Jb[i] = gmm_objective_d(xs_data, xsd_data, alphas_data, alphasd_data, means_data, meansd_data, 
      qs_data, qsd_data, ls_data, lsd_data, wishart.gamma, wishart.m, &tmp);
    #else
    Jb[i] = gmm_objective_d(xs_data, alphas_data, means_data, qs_data, ls_data, wishart.gamma, wishart.m,
      xsd_data, alphasd_data, meansd_data, qsd_data, lsd_data, wishart.gamma, wishart.m);
    #endif
    if(i < k) {
      alphasd_data->arr[i] = 0;
    } else if (i >= k && i < k + k * d) {
      int j = i - k;
      meansd_data->arr[j / d]->arr[j % d] = 0;
    } else {
      int j = i - k - k * d;
      int j1 = j % td;
      int j2 = j / td;
      if (j1 < d) {
        qsd_data->arr[j2]->arr[j1] = 0;
      } else {
        lsd_data->arr[j2]->arr[j1 - d] = 0;  
      }
    } 
  }
#endif
}
  #else
void compute_gmm_Jb(int d, int k, int n,
  double* alphas, double* means,
  double* icf, double* x, Wishart wishart,
  double* err, double* Jb)
{
  int Jsz = (k*(d + 1)*(d + 2)) / 2;

  double eb = 1.;
  memset(Jb, 0, Jsz*sizeof(double));

#if defined REV_MODE

  double *alphasb = &Jb[0];
  double *meansb = &Jb[k];
  double *icfb = &Jb[k + d*k];
  gmm_objective_b(d, k, n, alphas, alphasb, means, meansb,
    icf, icfb, x, wishart, err, &eb);
#else
  double *alld = (double*)malloc(Jsz * sizeof(double));
  memset(alld, 0, Jsz*sizeof(double));
  double *alphasd = &alld[0];
  double *meansd = &alld[k];
  double *icfd = &alld[k + d*k];
  double *xd = (double*)malloc(n * sizeof(double));
  memset(xd, 0, n*sizeof(double));
  for(int i = 0; i<Jsz; i++) {
    alld[i] = 1;
    gmm_objective_d(d, k, n, alphas, alphasd, means, meansd,
      icf, icfd, x, xd, wishart.gamma, wishart.m, err, &Jb[i]);  
    alld[i] = 0;
  }
  free(alld);
#endif
}
  #endif
#endif

#if defined DO_GMM
#if defined DIFFSMOOTH || TAP_FUSED || TAP_UNFUSED
array_array_number_t TOP_LEVEL_linalg_matrixFill(card_t rows, card_t cols, number_t value) {
  array_array_number_t macroDef79 = (array_array_number_t)malloc(sizeof(int) * 2);
  macroDef79->length=rows;
  macroDef79->arr = (array_number_t*)malloc(sizeof(array_number_t) * rows);
    for(int r = 0; r < macroDef79->length; r++){
      array_number_t macroDef78 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef78->length=cols;
  macroDef78->arr = (number_t*)malloc(sizeof(number_t) * cols);
    for(int c = 0; c < macroDef78->length; c++){
      
      macroDef78->arr[c] = value;;
    }
      macroDef79->arr[r] = macroDef78;;
    }
  return macroDef79;
}

array_array_number_t matrix_fill(card_t rows, card_t cols, number_t value) {
  return TOP_LEVEL_linalg_matrixFill(rows, cols, value);
}

array_number_t vector_fill(card_t rows, number_t value) {
  return matrix_fill(1, rows, value)->arr[0];
}

#endif
void test_gmm(const string& fn_in, const string& fn_out, 
  int nruns_f, int nruns_J, bool replicate_point)
{
  int d, k, n;
  vector<double> alphas, means, icf, x;
  double* alphas_arr, *means_arr, *icf_arr, *x_arr;
  Wishart wishart;

  //read instance
  read_gmm_instance(fn_in + ".txt", &d, &k, &n,
    alphas, means, icf, x, wishart, replicate_point);

  alphas_arr = alphas.data();
  means_arr = means.data();
  icf_arr = icf.data();
  x_arr = x.data();
  #if defined DIFFSMOOTH || TAP_FUSED || TAP_UNFUSED
  int K = k;
  array_number_t alphas_data;
  array_array_number_t means_data;
  array_array_number_t qs_data;
  array_array_number_t ls_data;
  array_array_number_t xs_data;
  array_number_t alphasd_data;
  array_array_number_t meansd_data;
  array_array_number_t qsd_data;
  array_array_number_t lsd_data;
  array_array_number_t xsd_data;
  int td = TOP_LEVEL_usecases_gmm_tri(d);
  alphas_data = vector_fill(K, 0);
  means_data = matrix_fill(K, d, 0);
  qs_data = matrix_fill(K, d, 0);
  ls_data = matrix_fill(K, td, 0);
  xs_data = matrix_fill(n, d, 0);
  alphasd_data = vector_fill(K, 0);
  meansd_data = matrix_fill(K, d, 0);
  qsd_data = matrix_fill(K, d, 0);
  lsd_data = matrix_fill(K, td, 0);
  xsd_data = matrix_fill(n, d, 0);
  alphas_data->arr = alphas_arr;
  for(int i = 0; i<K; i++) {
    means_data->arr[i]->arr = &means_arr[i*d];
    qs_data->arr[i]->arr = &icf_arr[i*td];
    for (int j = 0; j < td; ++j) {
      if(j >= td - d)
        ls_data->arr[i]->arr[j] = 0;
      else 
        ls_data->arr[i]->arr[j] = icf_arr[i*td+d+j];
    }
  }
  for(int i = 0; i<n; i++) {
    xs_data->arr[i]->arr = &x_arr[i*d];
  }
  #endif

  // gmm_init(d, k, n);
  // printf("read!\n");

  int icf_sz = d*(d + 1) / 2;
  int Jsz = (k*(d + 1)*(d + 2)) / 2;

  double e1, e2, tmp;
  vector<double> J(Jsz);
  double* J_arr = J.data();

  high_resolution_clock::time_point start, end;
  double tf, tb = 0., tdv = 0.;

  start = high_resolution_clock::now();
  for (int i = 0; i < nruns_f; i++)
  {
    #if defined DIFFSMOOTH || TAP_FUSED || TAP_UNFUSED
    e1 = gmm_objective(xs_data, alphas_data, means_data, qs_data, ls_data, wishart.gamma, wishart.m);
    #else
    gmm_objective(d, k, n, alphas_arr, means_arr,
      icf_arr, x_arr, wishart.gamma, wishart.m, &e1);
    #endif
  }
  end = high_resolution_clock::now();
  tf = duration_cast<duration<double>>(end - start).count() / nruns_f;
  // cout << "err: " << e1 << endl;



  start = high_resolution_clock::now();
  for (int i = 0; i < nruns_J; i++)
  {
    // compute_gmm_Jb(d, k, n, alphas.data(),
    //   means.data(), icf.data(), x.data(), wishart, e2, J.data());
    #if defined DIFFSMOOTH || TAP_FUSED || TAP_UNFUSED
    // tmp = gmm_objective_d3(xs_data, alphas_data, means_data, qs_data, ls_data, wishart.gamma, wishart.m,
    //   xsd_data, alphasd_data, meansd_data, qsd_data, lsd_data, wishart.gamma, wishart.m);
      compute_gmm_Jb(d, k, n, alphas_data, means_data, qs_data, ls_data, xs_data,
        alphasd_data, meansd_data, qsd_data, lsd_data, xsd_data,
        wishart, &e2, J_arr);
    #else
      compute_gmm_Jb(d, k, n, alphas_arr,
        means_arr, icf_arr, x_arr, wishart, &e2, J_arr);
    #endif
  }
  end = high_resolution_clock::now();
  tb = duration_cast<duration<double>>(end - start).count() / nruns_J;
  // cout << "err: " << e2 << endl;
  cout << "time per call = " << tb << " s" << endl;

  /////////////////// results //////////////////////////
  #if defined TAPENADE
    #if defined REV_MODE
    string name("Tapenade_rev");
    #else
    string name("Tapenade_for");
    #endif
  #elif defined TAP_FUSED
    #if defined REV_MODE
    string name("Tapenade_fused_rev");
    #else
    string name("Tapenade_fused_for");
    #endif
  #elif defined TAP_UNFUSED
    #if defined REV_MODE
    string name("Tapenade_unfused_rev");
    #else
    string name("Tapenade_unfused_for");
    #endif
  #elif defined DIFFSMOOTH 
    #if defined DPS && defined FUSED
    string name = "DiffSmooth_fused_dps";
    #elif defined DPS
    string name = "DiffSmooth_dps";
    #elif defined FUSED
    string name = "DiffSmooth_fused";
    #else
    string name = "DiffSmooth";
    #endif
  #endif
  write_J(fn_out + "_J_" + name + ".txt", 1, Jsz, J.data());
  //write_times(tf, tb);
  write_times(fn_out + "_times_" + name + ".txt", tf, tb);
}

#elif defined DO_BA

void computeZachWeightError_d(double w, double *err, double *J)
{
  *err = 1 - w*w;
  *J = -2 * w;
}

#if defined TAPENADE && REV_MODE
void computeReprojError_b(double *cam, double *camb, double *X, double *Xb, 
        double *w, double *wb, double feat_x, double *feat_xb, double feat_y, 
        double *feat_yb, double *err, double *errb) {
    double proj[2];
    double projb[2];
    int ii1;
    pushreal8array(proj, 2);
    project(cam, X, proj);
    // This term is here so that tapenade correctly 
    // recognizes inputs to be the inputs
    for (ii1 = 0; ii1 < 2; ++ii1)
        projb[ii1] = 0.0;
    *wb = *wb + (proj[1]-feat_y)*errb[1];
    projb[1] = projb[1] + (*w)*errb[1];
    *feat_yb = *feat_yb - (*w)*errb[1];
    errb[1] = 0.0;
    *wb = *wb + (proj[0]-feat_x)*errb[0];
    projb[0] = projb[0] + (*w)*errb[0];
    *feat_xb = *feat_xb - (*w)*errb[0];
    errb[0] = 0.0;
    popreal8array(proj, 2);
    project_b(cam, camb, X, Xb, proj, projb);
}
#endif

void computeReprojError_d(
  double* cam,
  double* X, 
  double w, 
  double feat_x,
  double feat_y, 
  double *err, 
  double *J)
{
#if defined REV_MODE
  for (int i = 0; i < 2; i++)
  {
    double proj[2];
    double camb[BA_NCAMPARAMS] = {0};
    double Xb[3] = {0};
    double wb;
    double projb[2] = {0};
    projb[i] = 1;
    double feat_xb, feat_yb;
    double tmp;
    computeReprojError_b(cam, camb, X, Xb, &w, &wb, feat_x, &feat_xb, feat_y, &feat_yb, &tmp, projb);
    for (int j = 0; j < BA_NCAMPARAMS; j++)
      J[j * 2 + i] = camb[j];

    int off = BA_NCAMPARAMS * 2;
    for (int j = 0; j < 3; j++)
      J[j * 2 + i + off] = Xb[j];

    off += 3 * 2;
    J[i + off] = wb;
  }
#else
  double proj[2];
  double cam_d[BA_NCAMPARAMS] = {0};
  double X_d[3] = {0};
  for(int i =0; i<BA_NCAMPARAMS + 3; i++) {
    if(i < BA_NCAMPARAMS) {
      cam_d[i] = 1;
    } else {
      X_d[i - BA_NCAMPARAMS] = 1;
    }
    double proj_d[2];
    project_d(cam, cam_d, X, X_d, proj, proj_d);
    J[i * 2] = proj_d[0];
    J[i * 2 + 1] = proj_d[1];
    if(i < BA_NCAMPARAMS) {
      cam_d[i] = 0;
    } else {
      X_d[i - BA_NCAMPARAMS] = 0;
    }
  }
  int Jw_idx = 2 * (BA_NCAMPARAMS + 3);
  J[Jw_idx + 0] = (proj[0] - feat_x);
  J[Jw_idx + 1] = (proj[1] - feat_y);
  err[0] = w*J[Jw_idx + 0];
  err[1] = w*J[Jw_idx + 1];
  for (int i = 0; i < 2 * (BA_NCAMPARAMS + 3); i++)
  {
    J[i] *= w;
  }
#endif
}


void computeReprojError(
  double *cam,
  double *X, 
  double *w, 
  double feat_x, 
  double feat_y,
  double *err)
{
  double proj[2];
  project(cam, X, proj);

  err[0] = (*w)*(proj[0] - feat_x);
  err[1] = (*w)*(proj[1] - feat_y);

  // This term is here so that tapenade correctly 
  // recognizes inputs to be the inputs
  err[0] = err[0] + (cam[0] - cam[0]) + (X[0] - X[0]);
}

void computeZachWeightError(double *w, double *err)
{
  *err = 1 - (*w)*(*w);
}

void ba_objective(int n, int m, int p, 
  double *cams, 
  double *X,
  double *w, 
  int *obs, 
  double *feats,
  double *reproj_err, 
  double *w_err)
{
  int i, camIdx, ptIdx;

  for (i = 0; i < p; i++)
  {
    camIdx = obs[i * 2 + 0];
    ptIdx = obs[i * 2 + 1];
    computeReprojError(&cams[camIdx * BA_NCAMPARAMS], &X[ptIdx * 3],
      &w[i], feats[i * 2 + 0], feats[i * 2 + 1], &reproj_err[2 * i]);
  }

  for (i = 0; i < p; i++)
  {
    computeZachWeightError(&w[i], &w_err[i]);
  }

  // This term is here so that tapenade correctly 
  // recognizes inputs to be the inputs
  //reproj_err[0] = reproj_err[0] + ((cams[0] - cams[0]) +
  //  (X[0] - X[0]) + (w[0] - w[0]));
}

void compute_ba_Jbv(int n, int m, int p, double *cams, double *X,
  double *w, int *obs, double *feats, double *reproj_err,
  double *w_err, BASparseMat& J)
{
  J = BASparseMat(n, m, p);

  int n_new_cols = BA_NCAMPARAMS + 3 + 1;
  vector<double> reproj_err_d(2 * n_new_cols);
  for (int i = 0; i < p; i++)
  {
    memset(reproj_err_d.data(), 0, 2 * n_new_cols*sizeof(double));

    int camIdx = obs[2 * i + 0];
    int ptIdx = obs[2 * i + 1];
    computeReprojError_d(
      &cams[BA_NCAMPARAMS*camIdx],
      &X[ptIdx * 3],
      w[i],
      feats[2 * i + 0], feats[2 * i + 1],
      &reproj_err[2 * i],
      reproj_err_d.data());

    J.insert_reproj_err_block(i, camIdx, ptIdx, reproj_err_d.data());
  }

  for (int i = 0; i < p; i++)
  {
    double w_d = 0;
    computeZachWeightError_d(w[i], &w_err[i], &w_d);

    J.insert_w_err_block(i, w_d);
  }
}

void test_ba(const string& fn_in, const string& fn_out,
  int nruns_f, int nruns_J)
{
  int n, m, p;
  vector<double> cams, X, w, feats;
  vector<int> obs;

  //read instance
  read_ba_instance(fn_in + ".txt", n, m, p,
    cams, X, w, obs, feats);
  #if defined DIFFSMOOTH
  ba_init();
  #endif

  vector<double> reproj_err(2 * p);
  vector<double> w_err(p);
  BASparseMat J(n,m,p);

  high_resolution_clock::time_point start, end;
  double tf = 0., tJ = 0.;

  start = high_resolution_clock::now();
  for (int i = 0; i < nruns_f; i++)
  {
    ba_objective(n, m, p, cams.data(), X.data(), w.data(),
      obs.data(), feats.data(), reproj_err.data(), w_err.data());
  }
  end = high_resolution_clock::now();
  tf = duration_cast<duration<double>>(end - start).count() / nruns_f;

  start = high_resolution_clock::now();
  for (int i = 0; i < nruns_J; i++)
  {
    compute_ba_Jbv(n, m, p, cams.data(), X.data(), w.data(), 
      obs.data(), feats.data(), reproj_err.data(), w_err.data(), J);
  }
  end = high_resolution_clock::now();
  tJ = duration_cast<duration<double>>(end - start).count() / nruns_J;

  cout << "time per call = " << tJ << " s" << endl;

  #if defined TAPENADE
    #if defined REV_MODE
    string name("Tapenade_rev");
    #else
    string name("Tapenade_for");
    #endif
  #elif defined DIFFSMOOTH 
    #if defined DPS && defined FUSED
    string name = "DiffSmooth_fused_dps";
    #elif defined DPS
    string name = "DiffSmooth_dps";
    #elif defined FUSED
    string name = "DiffSmooth_fused";
    #else
    string name = "DiffSmooth";
    #endif
  #endif

  // write_J_sparse(fn_out + "_J_" + name + ".txt", J);
  write_times(fn_out + "_times_" + name + ".txt", tf, tJ);
}

#endif

int main(int argc, char *argv[])
{
  string dir_in(argv[1]);
  string dir_out(argv[2]);
  string fn(argv[3]);
  int nruns_f = std::stoi(string(argv[4]));
  int nruns_J = std::stoi(string(argv[5]));

  // printf("params %s %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4], argv[5]);
  
  // read only 1 point and replicate it?
  bool replicate_point = (argc >= 7 && string(argv[6]).compare("-rep") == 0);

#if defined DO_GMM
  test_gmm(dir_in + fn, dir_out + fn, nruns_f, nruns_J, replicate_point);
#elif defined DO_BA
  test_ba(dir_in + fn, dir_out + fn, nruns_f, nruns_J);
#endif
}