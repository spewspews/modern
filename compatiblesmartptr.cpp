#include <iostream>

template <class T>
struct NoDeref {};

template <class T>
struct EmptyCheck
{
	EmptyCheck() {};
	EmptyCheck(const NoDeref<T>&) {};
	void check(T*) {}
};

template
<
	class T,
	template <class> class CheckingPolicy
>
struct SmartPtr : CheckingPolicy<T>
{
	SmartPtr(T* ptr) : ptr_(ptr) {}

	template
	<
		class T1,
		template <class> class CP1
	>
	SmartPtr(const SmartPtr<T1, CP1>& p) :
		CheckingPolicy<T>(p),
		ptr_(p.ptr_)
	{}

	T* operator->()
	{
		this->check(ptr_);
		return ptr_;
	}

	T& operator*()
	{
		this->check(ptr_);
		return *ptr_;
	}
	T* ptr_;
};

int
main()
{
	SmartPtr<int, EmptyCheck> ptr(new int);
	SmartPtr<int, NoDeref> foo(new int(3));
	*ptr = 5;
	// *foo = 10;
	SmartPtr<int, EmptyCheck> foochange = foo;
	std::cout << "foochange is " << *foochange << '\n';
	SmartPtr<int, NoDeref> bar = ptr;
	return 0;
}
