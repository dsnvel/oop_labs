#include <vector>
#include <iostream>

class Detail {
protected:
	Detail(){}
public:
	static Detail* create_detail() {
		return new Detail();
	}

	template <typename T> friend 
		void add_object (T* obj, std::vector<Detail*>* container);
};

class Create : Detail {
protected:
	Create() : Detail() {}
public:
	static Detail* create_object() {
		return new Create();
	}

	template <typename T> friend
		void add_object(T* obj, std::vector<Detail*>* container);
};


template <typename T> void add_object(T* obj, std::vector<Detail*>* container) {
	container->push_back(obj);
}


std::vector<Detail*> database;

int main() {
	for (int i = 0; i < 6; i++) {
		if (i % 2 == 0) {
			add_object(Detail::create_detail(), &database);
			std::cout << "[+] Object from class Detail created and added to database" << std::endl;
		}
		else {
			add_object(Create::create_object(), &database);
			std::cout << "[+] Object from class Create created and added to database" << std::endl;
		}
	}
}