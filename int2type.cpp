#include <iostream>
#include <boost/mpl/int.hpp>

namespace mpl = boost::mpl;

template <class T, int which>
struct Foo {
	void
	operator()(T* ptr)
	{
		doIt(ptr, mpl::int_<which>());
	}
private:
	void
	doIt(T* ptr, mpl::int_<0>)
	{
		ptr->bar();
		std::cout << "doIt for " << 0 << '\n';
	}
	void
	doIt(T* ptr, mpl::int_<1>)
	{
		ptr->baz();
		std::cout << "doIt for " << 1 << '\n';
	}
};

template <class T, int which>
struct Foo1
{
	void operator()(T* ptr)
	{
		doIt(ptr, std::integral_constant<int, which>());
	}
private:
	void
	doIt(T* ptr, std::integral_constant<int, 0>)
	{
		ptr->bar();
		std::cout << "foo1 doIt for " << 0 << '\n';
	}
	void
	doIt(T* ptr, std::integral_constant<int, 1>)
	{
		ptr->baz();
		std::cout << "foo1 doIt for " << 1 << '\n';
	}
};

struct Bar {
	void
	bar()
	{
		std::cout << "bar\n";
	}
};

struct Baz {
	void
	baz()
	{
		std::cout << "baz\n";
	}
};

int
main()
{
	Foo<Bar, 0> foo;
	foo(new Bar);
	Foo<Baz, 1> anotherfoo;
	anotherfoo(new Baz);

	Foo1<Bar, 0> foo1;
	foo1(new Bar);
	return 0;
}
