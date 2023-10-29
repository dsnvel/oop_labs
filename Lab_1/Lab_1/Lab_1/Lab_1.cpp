#include <iostream>
#include <string>
#include <vector>


enum class TypeOfBook {
    technical,
    literary
};


class Book {
public:
    Book(const std::string& autor, const std::string& name_of_book, TypeOfBook type_of_book) :
        m_autor(autor),
        m_name_of_book(name_of_book),
        m_type_of_book(type_of_book) {}

    TypeOfBook get_type() const { return m_type_of_book; }
private:
    const std::string m_autor;
    const std::string m_name_of_book;
    const TypeOfBook m_type_of_book;
};


using vecLibrary = std::vector<Book>;

class Library {
public:
    void add_book(const std::string& autor, const std::string& name_of_book, TypeOfBook type_of_book) {
        if (autor.empty() || name_of_book.empty()) {
           throw std::invalid_argument("invalid data");
        }
        m_library.emplace_back(autor, name_of_book, type_of_book);
    }

    const vecLibrary& get_collection() {
        return m_library;
    }

    void print_count_by_types_noSwitch() {
        int count_technical_books = 0;
        int count_literary_books = 0;

        for (const Book& book : m_library)
        {
            TypeOfBook type = book.get_type();

            if (type == TypeOfBook::technical)
                count_technical_books++;
            if (type == TypeOfBook::literary)
                count_literary_books++;
        }

        std::cout << "Count of technical books:" << count_technical_books << std::endl;
        std::cout << "Count of literary books:" << count_literary_books << std::endl;
    }

    void print_count_by_types_withSwitch() {
        int count_technical_books = 0;
        int count_literary_books = 0;

        for (const Book& book : m_library)
        {
            switch (book.get_type())
            {
            case TypeOfBook::technical:
                count_technical_books++;
                break;
            case TypeOfBook::literary:
                count_literary_books++;
                break;
            default:
                break;
            }
        }

        std::cout << "Count of technical books:" << count_technical_books << std::endl;
        std::cout << "Count of literary books:" << count_literary_books << std::endl;
    }
private:
     vecLibrary m_library;
};


int main()
{
    Library lib;

    try {
        lib.add_book("Ray Bredberry", "Fahrenheit 451", TypeOfBook::literary);
        lib.add_book("Clean Code", "", TypeOfBook::technical);
        lib.add_book("To Paradise", "Hanya Yanagihara", TypeOfBook::literary);
    }
    catch (const std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
    }

    lib.print_count_by_types_withSwitch();
    lib.print_count_by_types_noSwitch();
}
