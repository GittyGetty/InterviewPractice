#include <iostream>

/************************************************************************/

class C {
public:
	C(const char* s) {
		name_ = s;
		std::cout << name_ << " constructed.\n";
	}

	~C() {
		std::cout << name_ << " destructed.\n";
	}

	void introduce_yourself() {
		std::cout << "Hi! My name is " << name_ << ".\n";
	}

	void stuff() {
		std::cout << "Hi! I have been allocated at address " << this << ".\n";
	}

private:
	const char* name_;
};

void test_auto() {
	std::auto_ptr<C> p(new C("C1"));
	p->introduce_yourself();
}

void test_auto2() {
	C* c = new C("C2");
	c->introduce_yourself();
}

/************************************************************************/

class Base1 {};
class Base2 : public Base1 {};
class Derived : public Base2 {
private:
	int a;

public:
	Derived() { a = 100; }

	void foo() {
		std::cout << a << std::endl;
	}
};

/************************************************************************/