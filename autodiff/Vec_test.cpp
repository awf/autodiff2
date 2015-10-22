
#include "Vec.h"

int main(int argc, char const* const* argv)
{
	typedef double Real;

	auto a = vec(1, 2, 3); // make vec of 3 ints

	Vec<Real> b = a;
	Vec<Real, 3> c = Vec<Real, 0, Vec_ZE>(3);
	Vec<Real, 3> d = Vec<Real, 3, Vec_ZE>();
}
