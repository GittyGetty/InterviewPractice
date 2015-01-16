#include <iostream>
#include <memory>

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

size_t destructor_count = 0;
class MyClass {
public:
    ~MyClass() {
        std::cout << "Destructor call #" << ++destructor_count << std::endl;
    }
};

typedef std::unique_ptr<MyClass[]> ManagedC;

void test_dynamic_2darray1() {
    size_t dimension1 = 10, dimension2 = 10;

    auto managed_array = std::unique_ptr<ManagedC[]>(new ManagedC[dimension1]);
    for (size_t i = 0; i < dimension1; ++i)
        managed_array[i] = ManagedC(new MyClass[dimension2]);
}

void test_dynamic_2darray2() {
    size_t dimension1 = 10, dimension2 = 10;

    auto simple_array = new MyClass*[dimension1];
    for (size_t i = 0; i < dimension1; ++i)
        simple_array[i] = new MyClass[dimension2];
}
