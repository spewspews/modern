#include <vector>
#include <iostream>

template <class T>
struct PrototypeCreator {
	T* create() {
		return proto_ ? proto_->clone() : nullptr;
	}
	void setPrototype(T* p)
	{
		proto_ = p;
	}
	T* getPrototype()
	{
		return proto_;
	}
private:
	T* proto_;
};

template <class T>
struct NewCreator {
	T* create() {
		return new T;
	}
};

template <class T>
struct GenCreator {
	void setGen(int gen)
	{
		gen_ = gen;
	}
	T* create()
	{
		auto p = new T;
		p->gen_ = gen_;
		return p;
	}
private:
	int gen_{-1};
};

struct Widget {
	int i;
	int gen_;
	Widget() : gen_(-1) {}
	void speak()
	{
		std::cout << "I'm widget number " << i << " of generation " << gen_ << '\n';
	}
	Widget* clone()
	{
		auto nw = new Widget;
		nw->gen_ = this->gen_;
		return nw;
	}
};

template
<
	class W,
	template<class> class CreationPolicy = NewCreator
>
struct Manager : public CreationPolicy<W> {
	std::vector<W*> widgets;
	W& newWidget()
	{
		auto nw = this->create();
		nw->i = widgets.size();
		widgets.push_back(nw);
		return *nw;
	}
};

int
main()
{
	Manager<Widget, GenCreator> wm1;
	// Widget w;
	// w.gen_ = 15;
	// wm1.setPrototype(&w);
	auto& w1 = wm1.newWidget();
	auto& w2 = wm1.newWidget();
	// w.gen_ = 20;
	wm1.setGen(20);
	auto& w3 = wm1.newWidget();
	w1.speak();
	w2.speak();
	w3.speak();

	Manager<Widget> wm2;
	auto& v1 = wm2.newWidget();
	v1.speak();
}
