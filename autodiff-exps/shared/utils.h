#pragma once

#pragma warning (disable : 4996) // fopen

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <Eigen/Dense>
#include <Eigen/StdVector>
#include "light_matrix.h"

#include "defs.h"

typedef double Real;

typedef long cardinality_t; 
typedef int card_t; 


template <class T>
using Vec = Eigen::Matrix<T, Eigen::Dynamic, 1>;

template <class T, size_t Size>
using VecF = Eigen::Matrix<T, Size, 1>;

template <class T>
using Vec2 = VecF<T, 2>;

template <class T>
using Vec3 = VecF<T, 3>;

template <typename Iter, typename T>
void vcopy(Iter p, T t)
{
  *p = t;
}

template <typename Iter, typename T, typename... Ts>
void vcopy(Iter p, T t, Ts... ts)
{
  *p++ = t;
  vcopy(p, ts...);
}

template <typename T, typename... Ts>
auto vec(T t, Ts ... ts) -> VecF<T, 1 + sizeof...(Ts)> {
  VecF<T, 1 + sizeof...(Ts)> v;
  vcopy(v.data(), t, ts...);
  return v;
}

#include <stdlib.h>
#include <time.h>

/** Timing */

typedef struct timer_t {
  clock_t start;
} timer_t;

timer_t tic() {
  timer_t res;
  res.start = clock();
  return res;
}

float toc(timer_t t) {
  clock_t end = clock();
  float milliseconds = (float)(end - t.start) * 1000.0 / CLOCKS_PER_SEC;
  // printf("%s -- %d (ms)\n", s, (int)milliseconds);
  return milliseconds;
}



using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::getline;

template<typename T>
using avector = vector<T, Eigen::aligned_allocator<T>>;

typedef struct { int verts[3]; } Triangle;
typedef struct
{
  vector<string> bone_names;
  vector<int> parents; // assumimng that parent is earlier in the order of bones
  avector<Eigen::Matrix4d> base_relatives;
  avector<Eigen::Matrix4d> inverse_base_absolutes;
  Eigen::Matrix3Xd base_positions;
  Eigen::ArrayXXd weights;
  vector<Triangle> triangles;
  bool is_mirrored;
} HandModelEigen;

typedef struct
{
  HandModelEigen model;
  vector<int> correspondences;
  Eigen::Matrix3Xd points;
} HandDataEigen;

class HandModelLightMatrix
{
public:
  vector<string> bone_names;
  vector<int> parents; // assumimng that parent is earlier in the order of bones
  vector<LightMatrix<double>> base_relatives;
  vector<LightMatrix<double>> inverse_base_absolutes;
  LightMatrix<double> base_positions;
  LightMatrix<double> weights;
  vector<Triangle> triangles;
  bool is_mirrored;
};

class HandDataLightMatrix
{
public:
  HandModelLightMatrix model;
  vector<int> correspondences;
  LightMatrix<double> points;
};

// rows is nrows+1 vector containing
// indices to cols and vals. 
// rows[i] ... rows[i+1]-1 are elements of i-th row
// i.e. cols[row[i]] is the column of the first
// element in the row. Similarly for values.
class BASparseMat
{
public:
  int n, m, p; // number of cams, points and observations
  int nrows, ncols;
  vector<int> rows;
  vector<int> cols;
  vector<double> vals;

  BASparseMat() {}
  BASparseMat(int n_, int m_, int p_) : n(n_), m(m_), p(p_)
  {
    nrows = 2 * p + p;
    ncols = BA_NCAMPARAMS*n + 3 * m + p;
    rows.reserve(nrows + 1);
    int nnonzero = (BA_NCAMPARAMS + 3 + 1) * 2 * p + p;
    cols.reserve(nnonzero);
    vals.reserve(nnonzero);
    rows.push_back(0);
  }

  void insert_reproj_err_block(int obsIdx, 
    int camIdx,int ptIdx,const double* const J)
  {
    int n_new_cols = BA_NCAMPARAMS + 3 + 1;
    rows.push_back(rows.back() + n_new_cols);
    rows.push_back(rows.back() + n_new_cols);

    for (int i_row = 0; i_row < 2; i_row++)
    {
      for (int i = 0; i < BA_NCAMPARAMS; i++)
      {
        cols.push_back(BA_NCAMPARAMS*camIdx + i);
        vals.push_back(J[2 * i + i_row]);
      }
      int col_offset = BA_NCAMPARAMS*n;
      int val_offset = BA_NCAMPARAMS * 2;
      for (int i = 0; i < 3; i++)
      {
        cols.push_back(col_offset + 3 * ptIdx + i);
        vals.push_back(J[val_offset + 2 * i + i_row]);
      }
      col_offset += 3 * m;
      val_offset += 3 * 2;
      cols.push_back(col_offset + obsIdx);
      vals.push_back(J[val_offset + i_row]);
    }
  }

  void insert_w_err_block(int wIdx, double w_d)
  {
    rows.push_back(rows.back() + 1);
    cols.push_back(BA_NCAMPARAMS*n + 3 * m + wIdx);
    vals.push_back(w_d);
  }
};

void read_gmm_instance(const string& fn,
  int *d, int *k, int *n, 
  vector<double>& alphas,
  vector<double>& means,
  vector<double>& icf,
  vector<double>& x,
  Wishart& wishart,
  bool replicate_point)
{
  FILE *fid = fopen(fn.c_str(), "r");

  fscanf(fid, "%i %i %i", d, k, n);

  int d_ = *d, k_ = *k, n_ = *n;

  int icf_sz = d_*(d_ + 1) / 2;
  alphas.resize(k_);
  means.resize(d_*k_);
  icf.resize(icf_sz*k_);
  x.resize(d_*n_);

  for (int i = 0; i < k_; i++)
  {
    fscanf(fid, "%lf", &alphas[i]);
  }

  for (int i = 0; i < k_; i++)
  {
    for (int j = 0; j < d_; j++)
    {
      fscanf(fid, "%lf", &means[i*d_ + j]);
    }
  }

  for (int i = 0; i < k_; i++)
  {
    for (int j = 0; j < icf_sz; j++)
    {
      fscanf(fid, "%lf", &icf[i*icf_sz + j]);
    }
  }

  if (replicate_point)
  {
    for (int j = 0; j < d_; j++)
    {
      fscanf(fid, "%lf", &x[j]);
    }
    for (int i = 0; i < n_; i++)
    {
      memcpy(&x[i*d_], &x[0], d_ * sizeof(double));
    }
  }
  else
  {
    for (int i = 0; i < n_; i++)
    {
      for (int j = 0; j < d_; j++)
      {
        fscanf(fid, "%lf", &x[i*d_ + j]);
      }
    }
  }

  fscanf(fid, "%lf %i", &(wishart.gamma), &(wishart.m));

  fclose(fid);
}

void read_ba_instance(const string& fn, 
  int& n, int& m, int& p,
  vector<double>& cams, 
  vector<double>& X, 
  vector<double>& w, 
  vector<int>& obs, 
  vector<double>& feats)
{
  FILE *fid = fopen(fn.c_str(), "r");

  fscanf(fid, "%i %i %i", &n, &m, &p);
  int nCamParams = 11;

  cams.resize(nCamParams*n);
  X.resize(3*m);
  w.resize(p);
  obs.resize(2*p);
  feats.resize(2*p);

  for (int j = 0; j < nCamParams; j++)
    fscanf(fid, "%lf", &cams[j]);
  for (int i = 1; i < n; i++)
    memcpy(&cams[i*nCamParams], &cams[0], nCamParams*sizeof(double));

  for (int j = 0; j < 3; j++)
    fscanf(fid, "%lf", &X[j]);
  for (int i = 1; i < m; i++)
    memcpy(&X[i*3], &X[0], 3*sizeof(double));

  fscanf(fid, "%lf", &w[0]);
  for (int i = 1; i < p; i++)
    w[i] = w[0];

  int camIdx = 0;
  int ptIdx = 0;
  for (int i = 0; i < p; i++)
  {
    obs[i * 2 + 0] = (camIdx++ % n);
    obs[i * 2 + 1] = (ptIdx++ % m);
  }

  fscanf(fid, "%lf %lf", &feats[0], &feats[1]);
  for (int i = 1; i < p; i++)
  {
    feats[i * 2 + 0] = feats[0];
    feats[i * 2 + 1] = feats[1];
  }

  fclose(fid);
}

void write_J_sparse(const string& fn, const BASparseMat& J)
{
  std::ofstream out(fn);
  out << J.nrows << " " << J.ncols << endl;
  out << J.rows.size() << endl;
  for (size_t i = 0; i < J.rows.size(); i++)
  {
    out << J.rows[i] << " ";
  }
  out << endl;
  out << J.cols.size() << endl;
  for (size_t i = 0; i < J.cols.size(); i++)
  {
    out << J.cols[i] << " ";
  }
  out << endl;
  for (size_t i = 0; i < J.vals.size(); i++)
  {
    out << J.vals[i] << " ";
  }
  out.close();
}

void write_J(const string& fn, int Jrows, int Jcols, double **J)
{
  std::ofstream out(fn);
  out << Jrows << " " << Jcols << endl;
  for (int i = 0; i < Jrows; i++)
  {
    for (int j = 0; j < Jcols; j++)
    {
      out << J[i][j] << " ";
    }
    out << endl;
  }
  out.close();
}

void write_J(const string& fn, int Jrows, int Jcols, double *J)
{
  std::ofstream out(fn);
  out << Jrows << " " << Jcols << endl;
  for (int i = 0; i < Jrows; i++)
  {
    for (int j = 0; j < Jcols; j++)
    {
      out << J[j * Jrows + i] << " ";
    }
    out << endl;
  }
  out.close();
}

void write_times(double tf, double tJ)
{
  cout << "tf = " << std::scientific << tf << "s" << endl;
  cout << "tJ = " << tJ << "s" << endl;
  cout << "tJ/tf = " << tJ / tf << "s" << endl;
}

void write_times(const string& fn, double tf, double tJ, double *t_sparsity = nullptr)
{
  std::ofstream out(fn);
  out << std::scientific << tf << " " << tJ;
  if (t_sparsity)
    out << " " << *t_sparsity;
  out << endl;
  out << "tf tJ";
  if (t_sparsity)
    out << " t_sparsity";
  out << endl;
  out << "tf = " << std::scientific << tf << "s" << endl;
  out << "tJ = " << tJ << "s" << endl;
  out << "tJ/tf = " << tJ / tf << "s" << endl;
  out.close();
}

void read_hand_model(const string& path, HandModelEigen *pmodel)
{
  const char DELIMITER = ':';
  auto& model = *pmodel;
  std::ifstream bones_in(path + "bones.txt");
  string s;
  while (bones_in.good())
  {
    getline(bones_in, s, DELIMITER);
    if (s.empty())
      continue;
    model.bone_names.push_back(s);
    getline(bones_in, s, DELIMITER);
    model.parents.push_back(std::stoi(s));
    double tmp[16];
    for (int i = 0; i < 16; i++)
    {
      getline(bones_in, s, DELIMITER);
      tmp[i] = std::stod(s);
    }
    model.base_relatives.push_back(Eigen::Map<Eigen::Matrix4d>(tmp));
    model.base_relatives.back().transposeInPlace();
    for (int i = 0; i < 15; i++)
    {
      getline(bones_in, s, DELIMITER);
      tmp[i] = std::stod(s);
    }
    getline(bones_in, s, '\n');
    tmp[15] = std::stod(s);
    model.inverse_base_absolutes.push_back(Eigen::Map<Eigen::Matrix4d>(tmp));
    model.inverse_base_absolutes.back().transposeInPlace();
  }
  bones_in.close();
  int n_bones = (int)model.bone_names.size();

  std::ifstream vert_in(path + "vertices.txt");
  int n_vertices = 0;
  while (vert_in.good())
  {
    getline(vert_in, s);
    if (!s.empty())
      n_vertices++;
  }
  vert_in.close();

  model.base_positions.resize(3, n_vertices);
  model.weights = Eigen::ArrayXXd::Zero(n_bones, n_vertices);
  vert_in = std::ifstream(path + "vertices.txt");
  for (int i_vert = 0; i_vert < n_vertices; i_vert++)
  {
    for (int j = 0; j < 3; j++)
    {
      getline(vert_in, s, DELIMITER);
      model.base_positions(j, i_vert) = std::stod(s);
    }
    for (int j = 0; j < 3 + 2; j++)
    {
      getline(vert_in, s, DELIMITER); // skip
    }
    getline(vert_in, s, DELIMITER);
    int n = std::stoi(s);
    for (int j = 0; j < n; j++)
    {
      getline(vert_in, s, DELIMITER);
      int i_bone = std::stoi(s);
      if (j == n - 1)
        getline(vert_in, s, '\n');
      else
        getline(vert_in, s, DELIMITER);
      model.weights(i_bone, i_vert) = std::stod(s);
    }
  }
  vert_in.close();

  std::ifstream triangles_in(path + "triangles.txt");
  string ss[3];
  while (triangles_in.good())
  {
    getline(triangles_in, ss[0], DELIMITER);
    if (ss[0].empty())
      continue;

    getline(triangles_in, ss[1], DELIMITER);
    getline(triangles_in, ss[2], '\n');
    Triangle curr;
    for (int i = 0; i < 3; i++)
      curr.verts[i] = std::stoi(ss[i]);
    model.triangles.push_back(curr);
  }
  triangles_in.close();

  model.is_mirrored = false;
}

void read_hand_instance(const string& model_dir, const string& fn_in, 
  vector<double>* theta, HandDataEigen *data, vector<double> *us = nullptr)
{
  read_hand_model(model_dir, &data->model);
  std::ifstream in(fn_in);
  int n_pts, n_theta;
  in >> n_pts >> n_theta;
  data->correspondences.resize(n_pts);
  data->points.resize(3, n_pts);
  for (int i = 0; i < n_pts; i++)
  {
    in >> data->correspondences[i];
    for (int j = 0; j < 3; j++)
    {
      in >> data->points(j, i);
    }
  }
  if (us != nullptr)
  {
    us->resize(2 * n_pts);
    for (int i = 0; i < 2 * n_pts; i++)
    {
      in >> (*us)[i];
    }
  }
  theta->resize(n_theta);
  for (int i = 0; i < n_theta; i++)
  {
    in >> (*theta)[i];
  }
  in.close();
}

void read_hand_model(const string& path, HandModelLightMatrix *pmodel)
{
  const char DELIMITER = ':';
  auto& model = *pmodel;
  std::ifstream bones_in(path + "bones.txt");
  string s;
  while (bones_in.good())
  {
    getline(bones_in, s, DELIMITER);
    if (s.empty())
      continue;
    model.bone_names.push_back(s);
    getline(bones_in, s, DELIMITER);
    model.parents.push_back(std::stoi(s));
    double tmp[16];
    for (int i = 0; i < 16; i++)
    {
      getline(bones_in, s, DELIMITER);
      tmp[i] = std::stod(s);
    }
    model.base_relatives.emplace_back(4, 4);
    model.base_relatives.back().set(tmp);
    model.base_relatives.back().transpose_in_place();
    for (int i = 0; i < 15; i++)
    {
      getline(bones_in, s, DELIMITER);
      tmp[i] = std::stod(s);
    }
    getline(bones_in, s, '\n');
    tmp[15] = std::stod(s);
    model.inverse_base_absolutes.emplace_back(4, 4);
    model.inverse_base_absolutes.back().set(tmp);
    model.inverse_base_absolutes.back().transpose_in_place();
  }
  bones_in.close();
  int n_bones = (int)model.bone_names.size();

  std::ifstream vert_in(path + "vertices.txt");
  int n_vertices = 0;
  while (vert_in.good())
  {
    getline(vert_in, s);
    if (!s.empty())
      n_vertices++;
  }
  vert_in.close();

  model.base_positions.resize(4, n_vertices);
  model.base_positions.set_row(3, 1.);
  model.weights.resize(n_bones, n_vertices);
  model.weights.fill(0.);
  vert_in = std::ifstream(path + "vertices.txt");
  for (int i_vert = 0; i_vert < n_vertices; i_vert++)
  {
    for (int j = 0; j < 3; j++)
    {
      getline(vert_in, s, DELIMITER);
      model.base_positions(j, i_vert) = std::stod(s);
    }
    for (int j = 0; j < 3 + 2; j++)
    {
      getline(vert_in, s, DELIMITER); // skip
    }
    getline(vert_in, s, DELIMITER);
    int n = std::stoi(s);
    for (int j = 0; j < n; j++)
    {
      getline(vert_in, s, DELIMITER);
      int i_bone = std::stoi(s);
      if (j == n - 1)
        getline(vert_in, s, '\n');
      else
        getline(vert_in, s, DELIMITER);
      model.weights(i_bone, i_vert) = std::stod(s);
    }
  }
  vert_in.close();

  std::ifstream triangles_in(path + "triangles.txt");
  string ss[3];
  while (triangles_in.good())
  {
    getline(triangles_in, ss[0], DELIMITER);
    if (ss[0].empty())
      continue;

    getline(triangles_in, ss[1], DELIMITER);
    getline(triangles_in, ss[2], '\n');
    Triangle curr;
    for (int i = 0; i < 3; i++)
      curr.verts[i] = std::stoi(ss[i]);
    model.triangles.push_back(curr);
  }
  triangles_in.close();

  model.is_mirrored = false;
}

void read_hand_instance(const string& model_dir, const string& fn_in, 
  vector<double>* theta, HandDataLightMatrix *data, vector<double> *us = nullptr)
{
  read_hand_model(model_dir, &data->model);
  std::ifstream in(fn_in);
  int n_pts, n_theta;
  in >> n_pts >> n_theta;
  data->correspondences.resize(n_pts);
  data->points.resize(3, n_pts);
  for (int i = 0; i < n_pts; i++)
  {
    in >> data->correspondences[i];
    for (int j = 0; j < 3; j++)
    {
      in >> data->points(j, i);
    }
  }
  if (us != nullptr)
  {
    us->resize(2 * n_pts);
    for (int i = 0; i < 2 * n_pts; i++)
    {
      in >> (*us)[i];
    }
  }
  theta->resize(n_theta);
  for (int i = 0; i < n_theta; i++)
  {
    in >> (*theta)[i];
  }
  in.close();
}
