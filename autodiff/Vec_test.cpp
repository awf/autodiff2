
#include "Vec.h"

//template <class T, class CT>
//struct Vec<Vec<T, 0, CT>, 0, CT> {  // Actually use some traits to map these
//  Vec(size_t n, Vec<T, 0, CT> const& fill_value);
//};

template <class Container_U, class Container_V>
auto dot_too_generic(Container_U const& u, Container_V const& v) ->
decltype(*std::begin(u) * *std::begin(v))
{
  typedef decltype(*std::begin(u) * *std::begin(v)) ret_t;
  ret_t accum{ 0 };
  for (auto pu = std::begin(u), pv = std::begin(u); pu != std::end(u); ++pu, ++pv)
    accum += *pu * *pv;
  return accum;
}

void f()
{
  Vec<double, 3> a;
  Vec<double, 3> b;
  double d = dot_too_generic(a, b);
}


int main(int argc, char const* const* argv)
{
	typedef double Real;

	auto a = vec(1, 2, 3); // make vec of 3 ints

	Vec<Real> b = a;
	Vec<Real, 3> c = Vec<Real, 0, Vec_ZE>(3);
	Vec<Real, 3> d = Vec<Real, 3, Vec_ZE>();

        std::cout << pr(a) << std::endl;
        std::cout << pr(b) << std::endl;
        std::cout << pr(c) << std::endl;
        std::cout << pr(d) << std::endl;

        Vec<Real> e = a + a;

        std::cout << pr(e) << std::endl;

        std::cout << dot_too_generic(a, a) << std::endl;
}
