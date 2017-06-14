#include <iostream>
#include <vector>
#include <type_traits>
#include <boost/mpl/if.hpp>

template<typename T, bool isPoly>
struct MyContainerTraits
{
	using ValueType = T*;
};

template<typename T>
struct MyContainerTraits<T, false>
{
	using ValueType = T;
};

template<typename T, bool isPoly>
struct MyContainer : public std::vector<typename MyContainerTraits<T, isPoly>::ValueType>
{
	using Traits = MyContainerTraits<T, isPoly>;
	using ValueType = typename Traits::ValueType;
};

struct Foo
{
	Foo(int i) : i_(i) {}
	int foo()
	{
		return i_;
	}
private:
	int i_;
};

namespace mpl = boost::mpl;

template<typename T, bool isPoly>
struct MyContainer1 : public std::vector<typename mpl::if_c<isPoly, T*, T>::type>
{
	using ValueType = typename mpl::if_c<isPoly, T*, T>::type;
};

template<typename T, bool isPoly>
struct MyContainer2 : public std::vector<std::conditional_t<isPoly, T*, T>>
{
	using ValueType = std::conditional_t<isPoly, T*, T>;
};

int
main()
{
	MyContainer<Foo, true> c;
	c.push_back(new Foo(3));
	auto foo = c[0];
	std::cout << foo->foo() << '\n';

	MyContainer1<Foo, true> c1;
	c1.push_back(new Foo(3));
	auto foo1 = c1[0];
	std::cout << foo1->foo() << '\n';

	MyContainer2<Foo, true> c2;
	c2.push_back(new Foo(3));
	auto foo2 = c2[0];
	std::cout << foo2->foo() << '\n';

	return 0;
}
