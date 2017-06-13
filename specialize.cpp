#include <iostream>

template <class T, class U>
struct Widget
{
	void Foo()
	{
		std::cout << "Foo: Generic impl\n";
	}
	void Bar()
	{
		std::cout << "Bar: Generic impl\n";
	}
};

template <>
void
Widget<int, int>::Foo()
{
	std::cout << "Foo: Specialized impl\n";
}

int
main()
{
	Widget<double, int> w1;
	w1.Foo();
	w1.Bar();
	Widget<int, int> w2;
	w2.Foo();
	w2.Bar();
}
