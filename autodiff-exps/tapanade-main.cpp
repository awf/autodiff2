#include <iostream>
#include <string>
#include <chrono>
#include <set>

#include "shared/utils.h"
#include "shared/defs.h"

#if defined DO_BA
#include "tapanade/ba_d-all.h"

double sqsum(int n, double *x)
{
  int i;
  double res;
  res = 0;
  for (i = 0; i < n; i++)
    res = res + x[i] * x[i];
  return res;
}


int test_ba()
{
    // auto cam = vec(
    //     0.1, 0.1, 0.1,     // ROT_IDX = 0;    
    //     0.2,0.1,0.3,       // CENTER_IDX = 3;
    //     1.2,               // FOCAL_IDX = 6;
    //     0.01, 0.03,        // X0_IDX = 7;
    //     0.009, 1.2e-4      // RAD_IDX = 9;
    //     );

    // Vec3<Real> X = vec(0.03, 0.11, -0.7);
    double cam[] = { 0.1, 0.1, 0.1,     // ROT_IDX = 0;    
        0.2,0.1,0.3,       // CENTER_IDX = 3;
        1.2,               // FOCAL_IDX = 6;
        0.01, 0.03,        // X0_IDX = 7;
        0.009, 1.2e-4      // RAD_IDX = 9;
        };
    double X[] = {0.03, 0.11, -0.7};

    // boost::timer::auto_cpu_timer t;
    timer_t t = tic();

    // Debug 150s 
    // Release 1s
    double total = 0;
    int N = 10000000;
#ifdef _DEBUG
    N = N / 100;  // Debug is roughly this much slower than release -- multiply timings.
#endif
    for (int count = 0; count < N; ++count) {
        X[0] = 1.0 / (2.0 + count);
        cam[5] = 1.0 + count * 1e-6;

        double proj[2];
        double proj_d[2];
        project_d(cam, cam , X, X, proj, proj_d);

        total += sqsum(2, proj_d);
    }

    // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall/double(N) << "ns" << std::endl;
    // std::cout << "total =" << total << std::endl;
    auto elapsed = toc(t);
    printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
    
    return 0;
}

#elif defined DO_GMM
// #include "tapanade/gmm.h"
extern "C"
{
#if defined TAPENADE
#include "tapanade/gmm_all.h"
#else 
extern "C"
{
#include "diffsmooth/gmm_compact.h"
}
#endif
}

#include "diffsmooth/types.h"
const size_t GMM_K = 5;
const size_t GMM_D = 2;

double dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

array_array_number_t matrix_fill(card_t rows, card_t cols, number_t value) {
  array_array_number_t macroDef83 = (array_array_number_t)malloc(sizeof(int) * 2);
  macroDef83->length=rows;
  macroDef83->arr = (array_number_t*)malloc(sizeof(array_number_t) * rows);
    for(int r = 0; r < macroDef83->length; r++){
      array_number_t macroDef82 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef82->length=cols;
  macroDef82->arr = (number_t*)malloc(sizeof(number_t) * cols);
    for(int c = 0; c < macroDef82->length; c++){
      
      macroDef82->arr[c] = value;;
    }
      macroDef83->arr[r] = macroDef82;;
    }
  return macroDef83;
}

array_number_t vector_fill(card_t rows, number_t value) {
  return matrix_fill(1, rows, value)->arr[0];
}

void array_print(array_number_t arr) {
  printf("[");
  for (int i = 0; i < arr->length; i++) {
    printf("%f", arr->arr[i]);
    if (i != arr->length - 1)
      printf(", ");
  }
  printf("]\n");
}

#if defined DIFFSMOOTH 
number_t gmm_objective3(array_array_number_t x, array_number_t alphas, array_array_number_t means, array_array_number_t qs, array_array_number_t ls, number_t wishart_gamma, number_t wishart_m) {
  card_t macroDef175 = x->length;
  card_t n = macroDef175;
  card_t macroDef176 = alphas->length;
  card_t K = macroDef176;
  number_t macroDef189 = 0;
  for(int idx = 0; idx < n; idx++){
    number_t acc0 = macroDef189;
    index_t i = idx;
    number_t macroDef182 = -1000;
  for(int idx0 = 0; idx0 < K; idx0++){
    number_t acc2 = macroDef182;
    index_t k = idx0;
    array_number_t v = qs->arr[k];
    number_t macroDef177 = 0;
  for(int cur_idx = 0; cur_idx < v->length; cur_idx++){
    number_t cur = v->arr[cur_idx];
    
    macroDef177 = (macroDef177) + (cur);;
  }
    array_number_t q = qs->arr[k];
    array_number_t l = ls->arr[k];
    array_number_t x0 = x->arr[i];
    array_number_t y = means->arr[k];
    card_t macroDef180 = x0->length;
    number_t macroDef181 = 0;
  for(int idx1 = 0; idx1 <= (macroDef180) - (1); idx1++){
    number_t acc4 = macroDef181;
    index_t i0 = idx1;
    index_t n0 = (i0) - (1);
    index_t tis = ((n0) * ((n0) + (1))) / (2);
    card_t s = 0;
    card_t macroDef178 = l->length;
    card_t e = macroDef178;
    number_t macroDef179 = 0;
  for(int idx2 = 0; idx2 <= (((e) - (s)) + (1)) - (1); idx2++){
    number_t acc6 = macroDef179;
    index_t i1 = idx2;
    number_t cur = (double)(((s)) + (i1));
    index_t idx3 = (int)(cur);
    index_t j = (idx3) - (tis);
    bool_t isInRange = 0;
  if((j) >= (0)) {
    
    isInRange = (j) < (i0);;
  } else {
    
    isInRange = false;;
  }
    number_t ite198 = 0;
  if(isInRange) {
    number_t x1 = x0->arr[j];
    number_t y0 = y->arr[j];
    ite198 = (acc6) + ((l->arr[idx3]) * ((x1) - (y0)));;
  } else {
    
    ite198 = acc6;;
  }
    macroDef179 = ite198;;
  }
    number_t sum = macroDef179;
    number_t x1 = x0->arr[i0];
    number_t y0 = y->arr[i0];
    number_t x10 = (sum) + ((exp(q->arr[i0])) * ((x1) - (y0)));
    number_t cur = (x10) * (x10);
    macroDef181 = (acc4) + (cur);;
  }
    number_t cur = ((alphas->arr[k]) + (macroDef177)) - ((0.5) * (macroDef181));
    number_t ite199 = 0;
  if((acc2) > (cur)) {
    
    ite199 = acc2;;
  } else {
    
    ite199 = cur;;
  }
    macroDef182 = ite199;;
  }
    number_t mx148 = macroDef182;
    number_t macroDef188 = 0;
  for(int idx0 = 0; idx0 < K; idx0++){
    number_t acc2 = macroDef188;
    index_t i0 = idx0;
    array_number_t v149 = qs->arr[i0];
    number_t macroDef183 = 0;
  for(int cur_idx = 0; cur_idx < v149->length; cur_idx++){
    number_t cur = v149->arr[cur_idx];
    
    macroDef183 = (macroDef183) + (cur);;
  }
    array_number_t q150 = qs->arr[i0];
    array_number_t l151 = ls->arr[i0];
    array_number_t x152 = x->arr[i];
    array_number_t y153 = means->arr[i0];
    card_t macroDef186 = x152->length;
    number_t macroDef187 = 0;
  for(int idx1 = 0; idx1 <= (macroDef186) - (1); idx1++){
    number_t acc4 = macroDef187;
    index_t i1 = idx1;
    index_t n154 = (i1) - (1);
    index_t tis155 = ((n154) * ((n154) + (1))) / (2);
    card_t s156 = 0;
    card_t macroDef184 = l151->length;
    card_t e157 = macroDef184;
    number_t macroDef185 = 0;
  for(int idx2 = 0; idx2 <= (((e157) - (s156)) + (1)) - (1); idx2++){
    number_t acc6 = macroDef185;
    index_t i2 = idx2;
    number_t cur = (double)(((s156)) + (i2));
    index_t idx158 = (int)(cur);
    index_t j159 = (idx158) - (tis155);
    bool_t isInRange160 = 0;
  if((j159) >= (0)) {
    
    isInRange160 = (j159) < (i1);;
  } else {
    
    isInRange160 = false;;
  }
    number_t ite200 = 0;
  if(isInRange160) {
    number_t x161 = x152->arr[j159];
    number_t y162 = y153->arr[j159];
    ite200 = (acc6) + ((l151->arr[idx158]) * ((x161) - (y162)));;
  } else {
    
    ite200 = acc6;;
  }
    macroDef185 = ite200;;
  }
    number_t sum163 = macroDef185;
    number_t x164 = x152->arr[i1];
    number_t y165 = y153->arr[i1];
    number_t x1166 = (sum163) + ((exp(q150->arr[i1])) * ((x164) - (y165)));
    number_t cur = (x1166) * (x1166);
    macroDef187 = (acc4) + (cur);;
  }
    number_t x168 = ((alphas->arr[i0]) + (macroDef183)) - ((0.5) * (macroDef187));
    number_t cur = exp((x168) - (mx148));
    macroDef188 = (acc2) + (cur);;
  }
    number_t semx170172 = macroDef188;
    number_t cur = (log(semx170172)) + (mx148);
    macroDef189 = (acc0) + (cur);;
  }
  number_t macroDef190 = -1000;
  for(int cur_idx = 0; cur_idx < alphas->length; cur_idx++){
    number_t cur = alphas->arr[cur_idx];
    number_t ite201 = 0;
  if((macroDef190) > (cur)) {
    
    ite201 = macroDef190;;
  } else {
    
    ite201 = cur;;
  }
    macroDef190 = ite201;;
  }
  number_t mx = macroDef190;
  card_t macroDef191 = alphas->length;
  number_t macroDef192 = 0;
  for(int idx = 0; idx <= (macroDef191) - (1); idx++){
    number_t acc0 = macroDef192;
    index_t i = idx;
    number_t x0 = alphas->arr[i];
    number_t cur = exp((x0) - (mx));
    macroDef192 = (acc0) + (cur);;
  }
  number_t semx174 = macroDef192;
  number_t macroDef197 = 0;
  for(int idx = 0; idx < K; idx++){
    number_t acc0 = macroDef197;
    index_t k = idx;
    array_number_t v = qs->arr[k];
    card_t macroDef193 = v->length;
    number_t macroDef194 = 0;
  for(int idx0 = 0; idx0 <= (macroDef193) - (1); idx0++){
    number_t acc2 = macroDef194;
    index_t i = idx0;
    number_t value = v->arr[i];
    number_t x1 = exp(value);
    number_t cur = (x1) * (x1);
    macroDef194 = (acc2) + (cur);;
  }
    array_number_t x0 = ls->arr[k];
    card_t macroDef195 = x0->length;
    number_t macroDef196 = 0;
  for(int idx0 = 0; idx0 <= (macroDef195) - (1); idx0++){
    number_t acc2 = macroDef196;
    index_t i = idx0;
    number_t x1 = x0->arr[i];
    number_t cur = (x1) * (x1);
    macroDef196 = (acc2) + (cur);;
  }
    number_t cur = (macroDef194) + (macroDef196);
    macroDef197 = (acc0) + (cur);;
  }
  return ((macroDef189) - (((double)((n))) * ((log(semx174)) + (mx)))) + ((0.5) * (macroDef197));
}
#else

double arr_max(int n, double* x)
{
  double m;
  int i;

  m = x[0];
  for (i = 1; i < n; i++)
  {
    if (x[i] > m)
      m = x[i];
  }
  return m;
}

double logsumexp(int n, double* x)
{
  int i;
  double mx, semx;

  mx = arr_max(n, x);
  semx = 0.;
  for (i = 0; i < n; i++)
  {
    semx += exp(x[i] - mx);
  }
  return log(semx) + mx;
}

double sqnorm(int d,
  double* x)
{
  int i;
  double out;

  out = 0;
  for (i = 0; i < d; i++)
  {
    out += x[i] * x[i];
  }
  return out;
}

double log_wishart_prior(int p, int k, 
  double wishart_gamma, 
  double wishart_m,
  double *sum_qs,
  double *Qdiags,
  double* icf)
{
  int n, ik, icf_sz;
  double out, C, frobenius;

  icf_sz = p*(p + 1) / 2;

  out = 0;
  for (ik = 0; ik < k; ik++)
  {
    frobenius = sqnorm(p, &Qdiags[ik*p]) + sqnorm(icf_sz - p, &icf[ik*icf_sz + p]);
    out = out + 0.5 * frobenius;
  }

  // the last bit is here so that tapenade would recognize that means and inv_cov_factors are variables
  return out /* - k*C + (Qdiags[0] - Qdiags[0]) + (icf[0] - icf[0]) */;
}

void preprocess_qs(int d, int k,
  double* icf,
  double* sum_qs,
  double* Qdiags)
{
  int icf_sz, ik, id;
  double q;

  icf_sz = d*(d + 1) / 2;
  for (ik = 0; ik < k; ik++)
  {
    sum_qs[ik] = 0.;
    for (id = 0; id < d; id++)
    {
      q = icf[ik*icf_sz + id];
      sum_qs[ik] += q;
      Qdiags[ik*d + id] = exp(q);
    }
  }
}

void Qtimesx(int d,
  double* Qdiag,
  double* ltri, // strictly lower triangular part
  double* x,
  double* out)
{
  int id, i, j, Lparamsidx;

  for (id = 0; id < d; id++)
    out[id] = Qdiag[id] * x[id];

  Lparamsidx = 0;
  for (i = 0; i < d; i++)
  {
    for (j = i + 1; j < d; j++)
    {
      out[j] = out[j] + ltri[Lparamsidx] * x[i];
      Lparamsidx = Lparamsidx + 1;
    }
  }
}

// out = a - b
void subtract(int d,
  double* x,
  double* y,
  double* out)
{
  int id;
  for (id = 0; id < d; id++)
  {
    out[id] = x[id] - y[id];
  }
}
void gmm_objective2(int d, int k, int n,
  double* alphas, 
  double* means,
  double* icf, 
  double* x,
  double wishart_gamma, 
  double wishart_m,
  double *err)
{
  int ik, ix, icf_sz;
  double *main_term, *sum_qs, *Qdiags, *xcentered, *Qxcentered;
  double slse, lse_alphas, CONSTANT;
  // CONSTANT = -n*d*0.5*log(2 * PI);
  icf_sz = d*(d + 1) / 2;

  main_term = (double *)malloc(k*sizeof(double));
  sum_qs = (double *)malloc(k*sizeof(double));
  Qdiags = (double *)malloc(d*k*sizeof(double));
  xcentered = (double *)malloc(d*sizeof(double));
  Qxcentered = (double *)malloc(d*sizeof(double));

  preprocess_qs(d, k, icf, sum_qs, Qdiags);

  slse = 0.;
  for (ix = 0; ix < n; ix++)
  {
    for (ik = 0; ik < k; ik++)
    {
      subtract(d, &x[ix*d], &means[ik*d], xcentered);
      Qtimesx(d, &Qdiags[ik*d], &icf[ik*icf_sz + d], xcentered, Qxcentered);

      main_term[ik] = alphas[ik] + sum_qs[ik] - 0.5*sqnorm(d, Qxcentered);
    }
    slse = slse + logsumexp(k, main_term);
  }
  free(main_term);
  free(xcentered);
  free(Qxcentered);

  lse_alphas = logsumexp(k, alphas);
  *err = /*CONSTANT + */slse - n*lse_alphas;

  *err = *err + log_wishart_prior(d, k, wishart_gamma, wishart_m, sum_qs, Qdiags, icf);

  free(sum_qs);
  free(Qdiags);

  // this is here so that tapenade would recognize that means and inv_cov_factors are variables
  *err = *err /* + ((means[0] - means[0]) +
    (icf[0] - icf[0])) */;
}
#endif


void test_gmm()
{
  int rng = 42;
  srand(rng);
  // std::mt19937 rng(42);
  // std::uniform_real_distribution<Real> dist(0, 1);

  // Problem size
  size_t n = 100000;
  size_t d = GMM_D;
  size_t K = GMM_K;
  size_t td = ((d) * ((d) + (1))) / (2);
  

  // Declare and fill GMM coeffs
  // Vector alphas{ K };
  // Vec<VectorD> means{ K, VectorD{ d } };
  // Vec<VectorD> qs{ K, VectorD{ d } };
  // Vector l0{ size_t(tri(d)) };
  // Vec<Vector> ls{ K, l0 };
#if defined TAPENADE
  array_number_t alphas = vector_fill(K, 0);
  array_number_t means = vector_fill(K * d, 0);
  array_number_t qs = vector_fill(K * d, 0);
  array_number_t ls = vector_fill(K * td, 0);
  array_number_t icf = vector_fill(K * td, 0);
  for (int k = 0; k < K; ++k) {
    alphas->arr[k] = dist(rng);
    for (int j = 0; j < d; ++j) {
      means->arr[k * d + j] = dist(rng) - 0.5;
      qs->arr[k * d + j] = 10.0*dist(rng) - 5.0;
    }
    for (int j = 0; j < td; ++j) {
      ls->arr[k * td + j] = dist(rng) - 0.5;
      if(j >= td - d)
        ls->arr[k * td + j] = 0;
      if(j < d) {
        icf->arr[k * td + j] = qs->arr[k * d + j];
      } else {
        icf->arr[k * td + j] = ls->arr[k * td + j - d];
      }
    }
  }

  // Declare and fill xs
  // Vec<VectorD> xs{ n, Vector{ d } };
  array_number_t xs = vector_fill(n * d, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < d; ++j)
      xs->arr[i * d + j] = dist(rng);

#else 
  array_number_t alphas = vector_fill(K, 0);
  array_array_number_t means = matrix_fill(K, d, 0);
  array_array_number_t qs = matrix_fill(K, d, 0);
  array_array_number_t ls = matrix_fill(K, td, 0);
  for (int k = 0; k < K; ++k) {
    alphas->arr[k] = dist(rng);
    for (int j = 0; j < d; ++j) {
      means->arr[k]->arr[j] = dist(rng) - 0.5;
      qs->arr[k]->arr[j] = 10.0*dist(rng) - 5.0;
    }
    for (int j = 0; j < ls->arr[k]->length; ++j) {
      ls->arr[k]->arr[j] = dist(rng) - 0.5;
      if(j >= ls->arr[k]->length - d)
        ls->arr[k]->arr[j] = 0;
    }
  }

  // Declare and fill xs
  // Vec<VectorD> xs{ n, Vector{ d } };
  array_array_number_t xs = matrix_fill(n, d, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < d; ++j)
      xs->arr[i]->arr[j] = dist(rng);
#endif

  // TOP_LEVEL_usecases_gmm_Qtimesv_test(0);

  // boost::timer::auto_cpu_timer t;
  timer_t t = tic();

  gmm_init(d, K, n);

  // Debug 150s 
    // Release 1s
  double total = 0;
  int N = 100;
#ifdef _DEBUG
  N = N / 10;  // Debug is roughly this much slower than release -- multiply timings.
#endif
  double wishart_m = 2.0;
  for (int count = 0; count < N; ++count) {
    double wishart_gamma = 1.0 / (1.0 + count);
    double res, tmp;

    // TODO icf instead of qs and ls
#if defined TAPENADE
    gmm_objective2(d, K, n, alphas->arr, means->arr, icf->arr, xs->arr, wishart_gamma, wishart_m, &res);
#else
    res = gmm_objective(xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
#endif
    // total += res;
    // gmm_objective_d(d, K, n, alphas->arr, alphas->arr, means->arr, means->arr, icf->arr, icf->arr, xs->arr, xs->arr, wishart_gamma, wishart_m, &tmp, &res);
    total += res;
  }

  // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall / double(N) / 1000.0 << "us" << std::endl;
  double elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / (double)(N));
}



#elif defined DO_MICRO

Real dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

#ifdef ADD3
#define DIM 100
#elif DOT
#include "tapanade/dot_prod_d-all.h"
#define DIM 100
#elif CROSS
#define DIM 3
#endif

array_number_t vector_fill(card_t rows, number_t value) {
  array_number_t macroDef82 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef82->length=rows;
  macroDef82->arr = (number_t*)malloc(sizeof(number_t) * rows);
  for(int i =0; i<rows; i++) {
    macroDef82->arr[i] = 0;
  }
  return macroDef82;
}

void test_micro(cardinality_t N)
{
  int rng = 42;
  srand(rng);
  array_number_t vec1 = vector_fill(DIM, 0.0);
  array_number_t vec2 = vector_fill(DIM, 0.0);
  array_number_t vec3 = vector_fill(DIM, 0.0);

  for (cardinality_t k = 0; k < DIM; ++k) {
    vec1->arr[k] = dist(rng);
    vec2->arr[k] = dist(rng);
    vec3->arr[k] = dist(rng);
  }

  timer_t t = tic();

  double total = 0;

  for (cardinality_t count = 0; count < N; ++count) {
    vec1->arr[0] += 1.0 / (2.0 + vec1->arr[0]);
    vec2->arr[1] += 1.0 / (2.0 + vec2->arr[1]);
#ifdef ADD3
#elif DOT
    double realResult;
    total +=  dot_prod_d(vec1, vec1, vec2, vec2, &realResult);
#elif CROSS
#endif
  }

  auto elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
}

#endif

int main(int argc, char *argv[])
{
#if defined DO_BA
  test_ba();
#elif defined DO_GMM
  test_gmm();
#elif defined DO_MICRO
  if(argc != 2) {
    printf("You should use the following format for running this program: %s <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  cardinality_t N = atoi(argv[1]);
  test_micro(N);
#endif
}


