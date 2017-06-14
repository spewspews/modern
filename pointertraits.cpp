#include <vector>
#include <array>
#include <iostream>
#include <type_traits>

int
main()
{
	const auto iterIsPtr = std::is_pointer<std::vector<int>::iterator>::value;
	std::cout << "std::vector<int>::iterator is " <<
		(iterIsPtr ? "fast" : "smart") << '\n';

	const auto arrayIterIsPtr = std::is_pointer<std::array<int,5>::iterator>::value;
	std::cout << "std::array<int,5>::iterator is " <<
		(arrayIterIsPtr ? "fast" : "smart") << '\n';

	return 0;
}
