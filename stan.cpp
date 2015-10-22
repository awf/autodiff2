
#include <stan/agrad/rev.hpp>
#include <stan/agrad/rev/matrix.hpp>
#include <stan/agrad/autodiff.hpp>

using stan::agrad::jacobian;
using stan::agrad::jacobian_fixed;
using stan::agrad::exp;

template <class T, int N>
using VecBase = Eigen::Matrix<T, N, 1>;

template <class T>
using Vec2 = VecBase<T, 2>;

template <class T>
using Vec = Eigen::Matrix<T, Eigen::Dynamic, 1>;

template <class T>
using Mat = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template <class T>
struct GMM {
	size_t K; // number of Gaussians
	size_t d; // dimension of Gaussian

	Vec<T> alphas;
	Mat<T> mus; // Size dxK.  Columns are means
	Mat<T> LDs; // Size dxK. square - root - inverse - covariances, diagonal
	Mat<T> LTs; // Size MxK. square - root - inverse - covariances, lower triangle, M = d*(d - 1) / 2
};

double test_ll(GMM<double> const& gmm, Vec<double> const& x)
{
	auto K = gmm.K;
	auto d = gmm.d;

}

// 
// fun2(x,y) = [x+x, 3 * x * y]
struct fun2 {
	template <typename T>
	Vec2<T> operator()(const Vec2<T>& x) const {
		return Vec2<T>(x(0) + exp(x(0)), 3 * x(0) * x(1));
	}
};

int main()
{
	using Eigen::Matrix;  
	using Eigen::Dynamic;
	
	int K = 4;
	int d = 3;
	

	Vec2<double> x(2, -3);

	fun2 f;
	std::cout << f(x) << std::endl;

	Matrix<double, Dynamic, 1> fx;
	Matrix<double, Dynamic, Dynamic> J;
	jacobian_fixed<fun2, 2, 2>(f, x, fx, J);

	std::cout << "J=" << J << std::endl;

	Matrix<double, Dynamic, 1> fx_rev;
	Matrix<double, Dynamic, Dynamic> J_rev;
	//jacobian<double>(fun2(), x, fx_rev, J_rev);

}

