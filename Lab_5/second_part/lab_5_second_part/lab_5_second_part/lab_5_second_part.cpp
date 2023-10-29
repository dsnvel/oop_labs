#include <string>
#include <iostream>
#include <vector>
#include <list>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW


class A {
public:
	std::string s;

	A() {
		std::cout << "Конструктор по умолчанию класса А" << std::endl;
	}

	A(const char* a) {
		s = a;
		std::cout << "Пользовательский Конструктор класса A" << std::endl;
		std::cout << s << std::endl;
	}

	A(const A& obj){
		std::cout << "Конструктор копирования класса A" << std::endl;
	}

	virtual A* my_copy_object() {
		return new A(*this);
	}

	virtual void del_object() {
		this->~A();
	}

	virtual ~A() {
		std::cout << "Деструктор класса A" << std::endl;
		std::cout << typeid(*this).name() << std::endl;
	}
};

class B : public A {
public:
	B() {
		std::cout << "Конструктор  класса B" << std::endl;
	}
	B(const char* a) :A(a) {
		std::cout << "Пользовательский Конструктор класса B" << std::endl;
		std::cout << a << std::endl;
	}

	B(const B& obj) : A(obj) {
		std::cout << "Конструктор копирования класса B" << std::endl;
	}

	virtual A* my_copy_object() {
		return new B(*this);
	}

	virtual void del_object() override {
		this->~B();
	}

	virtual ~B() override{
		std::cout << "Деструктор класса B" << std::endl;
		std::cout << typeid(*this).name() << std::endl;
	}
};

void del(std::vector<A*> v) {
	std::cout << "Удаление объектов вектора" << std::endl;
	for (A* item : v) {
		item->del_object();
	}

}

void del(std::list <A*> l) {
	std::cout << "Удаление объектов списка" << std::endl;
	for (A* item : l) {
		item->del_object();
	}
}

void my_copy(std::vector<A*>* v, std::list <A*> l) {
	for (A* item : l) {
		v->push_back(item->my_copy_object());
		std::cout << "Add object to v" << std::endl;
	}
}

std::vector<A*> v;
std::list <A*> l;

int main() {
	setlocale(LC_ALL, "RUS");
	l.push_back(new A("first"));
	l.push_back(new B("second"));

	my_copy(&v, l);


	del(v);
	v.clear();

	del(l);
	l.clear();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}