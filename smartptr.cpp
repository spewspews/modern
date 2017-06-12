#include <iostream>

template <class T>
struct DefaultThreadModel
{
	struct Lock {
		Lock(T&)
		{
			std::cout << "Locking it up\n";
		}
		~Lock()
		{
			std::cout << "Unlocking it\n";
		}
	};
};

template <class T>
struct DefaultStorage
{
	using PointerType = T*;
	using ReferenceType = T&;
protected:
	PointerType getPointer()
	{
		return ptr_;
	}
	void setPointer(PointerType ptr)
	{
		ptr_ = ptr;
	}
private:
	PointerType ptr_;
};

class Bar {
	int bar;
};

template <class T>
struct VectorStorage
{
	using PointerType = T*;
	using ReferenceType = 
	std::vector<T> things(20);
};

template
<
	class T,
	template<class> class ThreadingModel,
	template<class> class Storage
>
struct SmartPtr : public Storage<T>
{
	using PointerType = typename Storage<T>::PointerType;
	using Lock = typename ThreadingModel<T>::Lock;
	SmartPtr(PointerType ptr)
	{
		this->setPointer(ptr);
	}
	PointerType operator->()
	{
		auto ptr = this->getPointer();
		Lock lock(*ptr);
		return ptr;
	}
};

struct Foo
{
	int bar;
	double baz;
};

int
main()
{
	SmartPtr<Foo, DefaultThreadModel, DefaultStorage> fooptr(new Foo);
	fooptr->bar = 3;
	fooptr->baz = 3.14;
}
