#include <iostream>
#include <boost/mpl/vector.hpp>

namespace mpl = boost::mpl;

template <class T>
struct Type2Type {
	using type = T;
};

struct Bar{};

struct Foo
{
	Foo(const Bar&){}
};

struct Widget
{
	int i_;
	Widget(const Bar&, int i) : i_(i) {}
};

template <class T, class U>
T* create(const U& arg, Type2Type<T>)
{
	return new T(arg);
}

template <class U>
Widget* create(const U& arg, Type2Type<Widget>)
{
	return new Widget(arg, -1);
}

int
main()
{
	auto foo = create(Bar(), Type2Type<Widget>());
	std::cout << foo->i_ << '\n';
	return 0;
}
