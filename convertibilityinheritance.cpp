#include <iostream>
#include <vector>
#include <type_traits>

struct Foo
{};

struct Bar
{
	Bar(const Foo&) {};
};

int
main()
{
	using namespace std;
	cout <<
		is_convertible<double, int>::value << '\n' <<
		is_convertible<char, char*>::value << '\n' <<
		is_convertible<size_t, vector<int>>::value << '\n' <<
		is_convertible<Foo, Bar>::value << '\n';
}
