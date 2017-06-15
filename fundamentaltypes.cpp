#include <iostream>
#include <type_traits>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>

namespace mpl = boost::mpl;

template <class T>
struct MustBeSigned
{
	using SignedInts = mpl::vector<signed char, short, int, long>;
	using type = T;
	static_assert(mpl::contains<SignedInts, T>::value == true, "T is unsigned.");
};

template <class T>
struct MustBeSigned1
{
	using type = T;
	static_assert(std::is_signed<T>::value == true, "T is unsigned.");
};

int
main()
{
	MustBeSigned<int>::type i(-1);
	std::cout << i << '\n';

	MustBeSigned1<int>::type j(-2);
	std::cout << j << '\n';

	return 0;
}
