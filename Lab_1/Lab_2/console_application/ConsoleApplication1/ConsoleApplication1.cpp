#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>


class Car {
public:
	Car(const std::string& model, const std::string& brand)
		: m_model(model), m_brand(brand) {}

	virtual ~Car() {}

	std::string get_model() { return m_model; }

	virtual std::string get_brand() { return m_brand; }

protected:
	std::string m_brand;
	std::string m_model;
};


class Mercedes : public Car {
public:
	Mercedes(const std::string& c_model, const std::string& brand):Car(c_model, brand) {}

	virtual ~Mercedes() {}
};


class Audi : public Car {
public:
	Audi(const std::string& c_model, const std::string& brand) :Car(c_model, brand) {}

	virtual ~Audi() {}
};


class BMW : public Car {
public:
	BMW(const std::string& c_model, const std::string& brand) :Car(c_model, brand) {
	}
	virtual ~BMW () {}
};


class Autopark {
public:
	Autopark () {}

	void add_car_to_autopark(Car* car) {
		m_autopark.push_back(car);
	}

	void show_autopark() {
		for (Car* car : m_autopark) {
			std::cout << car->get_brand() << " " << car->get_model() << std::endl;
		}
	}
private:
	std::vector<Car*> m_autopark;
};

using tempFunct = std::function<Car* (const std::string&, const std::string&)>;

const std::map <std::string, tempFunct > dictionary = { {"Mercedes", [](const auto& model, const auto& brand) -> Car* {return new Mercedes(model, brand); } },
														{"BMW", [](const auto& model, const auto& brand) -> Car* {return new BMW(model, brand); } },
														{"Audi", [](const auto& model, const auto& brand) -> Car* {return new Audi(model, brand); } } };


void main() {
	Autopark park;

	std::string line;

	std::string model_of_car;
	std::string car_brand;

	std::ifstream file("data.txt");

	if (file.is_open())
	{
		while (getline(file, line))
		{
			file >> car_brand;
			file >> model_of_car;

			auto iter = dictionary.find(car_brand);
			if (iter != dictionary.end()) {
				Car* car_to_add = iter->second(model_of_car, car_brand);
				park.add_car_to_autopark(car_to_add);
			}
		}
	}
	file.close();

	park.show_autopark();
}
