#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <vector>


class Base {
public:
    Base(){
       my_int = 1;
    }

    virtual Base * my_copy() {
        // std::cout << "copy class 1" << std::endl;
        return new Base(*this);
    }

    // добавить в класс виртуальную функцию, которая выводит enum, которому она принадлежит

    virtual void enum_classificator() {
        std::cout << typeid((*this)).name() << "\n" << std::endl;
    }

    virtual void deleter_component() {
        std::cout << typeid((*this)).name() << " -> Base object deleted" << std::endl;
        delete this;
    }

    virtual ~Base() {}
protected:
    int my_int;
};



class Derived : public Base {
public:
    Derived () {
        my_char = '1';
    }
    
    virtual Base* my_copy() override //virtual table
    {
        // std::cout << "copy class 2" << std::endl;
        return new Derived(*this);
    }

    virtual void enum_classificator() override{
        std::cout << typeid((*this)).name() << "\n" << std::endl;
    }

    virtual void deleter_component() override{
        std::cout << typeid((*this)).name() << " -> Derived object deleted" << std::endl;
        delete this;
    }

    virtual ~Derived() {}
protected:
    char my_char;
};

/*
Создать ассоциативный контейнер
Ключ enum - значение lambda функция, которая возвращет указатель на объект

Массив из ключей
*/

enum class Type
{
    Base_type,
    Derived_type
};

using tempFunct = std::function<Base* ()>;

const std::map<Type, tempFunct> temp_of_objects = { {Type::Base_type, []() -> Base* {return new Base(); }},
                                               {Type::Derived_type, []() -> Base* {return new Derived(); }} };

std::vector<Type> array_of_types = { Type::Base_type, Type::Derived_type, Type::Base_type, Type::Base_type, Type::Derived_type };

std::vector<Base*> objects;
std::vector<Base*> copied_objects;

int main()
{

    /*
    Создать массив из типов
    Заполнить вектор обЪектами согласно предыдущему массиву
    Проверить что в векторе лежат классы которые совпадают с массивом
    Копирование в другой вектор
    Проверить что в векторе лежат классы которые совпадают с массивом
    */
    
    Base* object_to_add;
    for (const Type& item : array_of_types) {
        auto iter = temp_of_objects.find(item);
        object_to_add = iter->second();
        objects.push_back(object_to_add);
    }
    for (auto item : objects) {
        std::cout << typeid(*item).name() << std::endl;
    }
    std::cout << "[+] Checking objects vector completed" << "\n" << std::endl;


    for (auto item : objects) {
        copied_objects.push_back((*item).my_copy());
    }
    for (auto item : copied_objects) {
        std::cout << typeid(*item).name() << std::endl;
    }
    std::cout << "[+] Checking copied objects vector completed" << "\n" << "\n" << std::endl;


    for (Base* item : objects) {
        (*item).deleter_component();
    }
    objects.clear();
    std::cout << "[+] Objects vector cleared" << "\n" << std::endl;

    for (Base* item : copied_objects) {
        (*item).deleter_component();
    }
    copied_objects.clear();
    std::cout << "[+] Copied objects vector cleared" << std::endl;
}
