
#include <iostream>
#include "Vec.h"

template <class T>
struct vector_printer {
  const T& t;
  vector_printer(const T& t) :t(t) {}
};

template <class T>
std::ostream& operator<<(std::ostream& s, vector_printer<T> const& t)
{
  s << "[ ";
  std::copy(std::begin(t.t), std::end(t.t), std::ostream_iterator<decltype(*std::begin(t.t))>(s, " "));
  return s << "]";

}

template <class T>
vector_printer<T> pr(const T& t) {
  return vector_printer<T>(t);
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

        Vec<Real> e = b + a;

        std::cout << pr(e) << std::endl;
}
