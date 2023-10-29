#include <string> 
#include <vector> 
#include <fstream> 
#include <iostream> 
#include <iomanip> 
#include <map> 
#include <functional> 
#include <sstream> 
#include <algorithm>
#include <locale>

class Employee;

class Database {
private:
    std::string name_of_company;
    std::vector<Employee*> database;
    int count_of_employees;
public:
    Database(std::string user_name_of_company) {
        name_of_company = user_name_of_company;
        count_of_employees = 0;
    }

    void add_employee_to_database(Employee* person) {
        count_of_employees++;
        database.push_back(person);
    }

    int get_count_of_employees() { return count_of_employees; }

    std::vector<Employee*> get_database() { return database; }

    friend void print_data_about_engineers(const std::vector<Employee*>& database);
    friend void print_employees_with_parameters(const std::vector<Employee*>& main_database);
};


class Employee {
private:
    std::string name;
    std::string job_title;
    std::string departament;
    int year_of_born;
    int employee_index;
public:
    Employee(std::string user_name, int user_year_of_born,
        std::string user_job_title, std::string user_departament, Database& user_database)
        : name(user_name), year_of_born(user_year_of_born),
        job_title(user_job_title), departament(user_departament)
    {
        employee_index = user_database.get_count_of_employees() - 1;
    }

    int get_employee_index() { return employee_index; }

    std::string get_employee_name() { return name; }
    int get_employee_year_of_born() { return year_of_born; }
    std::string get_employee_job_title() { return job_title; }
    std::string get_employee_departament() { return departament; }

    ~Employee() {}
};


void print_data_about_engineers(const std::vector<Employee*>& database) {
    std::cout << std::setw(15) << "Name" << std::setw(5) << "Date"
        << std::setw(13) << "Job title" << std::setw(12) << "Departament" << std::endl;
    for (Employee* employee : database) {
        if (employee->get_employee_job_title() == "инженер") {
            std::cout << std::setw(15) << employee->get_employee_name()
                << std::setw(5) << employee->get_employee_year_of_born()
                << std::setw(13) << employee->get_employee_job_title()
                << std::setw(12) << employee->get_employee_departament() << std::endl;
        }
    }
}

void print_employees_with_parameters(const std::vector<Employee*>& main_database) {
    std::vector<Employee*> database;

    for (const auto& employee : main_database) {
        if (employee->get_employee_job_title() != "председатель") {
            database.push_back(employee);
        }
    }
    std::sort(database.begin(), database.end(), [](Employee* a, Employee* b) {
        return a->get_employee_year_of_born() < b->get_employee_year_of_born();
        });

    std::cout << "-----------------------------------------------" << std::endl;

    std::cout << std::setw(15) << "Name" << std::setw(5) << "Date"
        << std::setw(13) << "Job title" << std::setw(12) << "Departament" << std::endl;

    for (Employee* employee : database) {
        if (employee->get_employee_job_title() != "председатель") {
            std::cout << std::setw(15) << employee->get_employee_name()
                << std::setw(5) << employee->get_employee_year_of_born()
                << std::setw(13) << employee->get_employee_job_title()
                << std::setw(12) << employee->get_employee_departament() << std::endl;
        }
    }
}

using TempFunc = std::function<void(const std::vector<Employee*>& database)>;

enum class Type_of_operation {
    Print_enginers = 1,
    Print_not_chairman
};

std::map<Type_of_operation, TempFunc> operations = {
  {Type_of_operation::Print_enginers, [](const std::vector<Employee*>& database) -> void { print_data_about_engineers(database); }},
  {Type_of_operation::Print_not_chairman, [](const std::vector<Employee*>& database) -> void { print_employees_with_parameters(database); }}
};

int main() {
    std::setlocale(LC_ALL, "RUS");

    Database database("Stankin");

    int year;
    std::wstring name, job_title, department;

    std::wifstream file("data.txt");
    std::wstring line;

    if (file.is_open())
    {
        while (getline(file, line)) {
            std::wstringstream wss(line);

            getline(wss, name, L',');

            wss >> year >> std::ws;

            getline(wss, job_title, L',');

            getline(wss, department, L',');

            std::string uname(name.begin(), name.end());
            std::string ujob_title(job_title.begin(), job_title.end());
            std::string udepartment(department.begin(), department.end());

            Employee* employee = new Employee(uname, year, ujob_title, udepartment, database);
            database.add_employee_to_database(employee);
        }
    }
    file.close();

    auto iter = operations.find(Type_of_operation::Print_enginers);
    if (iter != operations.end()) {
        iter->second(database.get_database());
    }

    iter = operations.find(Type_of_operation::Print_not_chairman);
    if (iter != operations.end()) {
        iter->second(database.get_database());
    }

    for (const auto& employee : database.get_database()) {
        delete employee;
    }

    database.get_database().clear();

    return 0;
}