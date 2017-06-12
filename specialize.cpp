#include <iostream>

template <class T, class U>
struct Widget {
	void Fun()
	{
		std::cout << "Generic impl\n";
	}
};

template <class T>
void
Widget<int, T>::Fun()
{
	std::cout << "Specialized impl\n";
}

int
main()
{
	Widget<double, int> w1;
	w1.Fun();
	Widget<int, int> w2;
	w2.Fun();
}
