#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class Link {
private:
	std::string link_text;
public:
	Link(std::string user_text_link) {
		link_text = user_text_link;
	}

	std::string get_link_text() { return link_text; }

	~Link() {}
};

class Database {
private:
	std::vector<Link*> database;
public:
	Database() {}

	void add_link(Link* link) { database.push_back(link); }

	void print_sorted_links() {
		std::vector<Link*> database_of_rus_links;
		std::vector<Link*> database_of_en_links;

		for (Link* object : database) {
			if (object->get_link_text()[1] <= 127) {
				database_of_en_links.push_back(object);
			}
				
			else database_of_rus_links.push_back(object);
		}

		std::sort(database_of_rus_links.begin(), database_of_rus_links.end(), [](Link* link_1, Link* link_2) {
			return link_1->get_link_text()[1] < link_2->get_link_text()[1];
			});

		std::sort(database_of_en_links.begin(), database_of_en_links.end(), [](Link* link_1, Link* link_2) {
			return link_1->get_link_text()[1] < link_2->get_link_text()[1];
			});

		print_list(database_of_rus_links, database_of_en_links, "without digits");
		print_list(database_of_rus_links, database_of_en_links, "with digits");
	}

	void print_list(std::vector<Link*> rus_links, std::vector<Link*> en_links, std::string type_of_print) {
		if (type_of_print == "without digits") {
			std::cout << "---------------------------------------------" << std::endl;
			for (Link* link : rus_links) {
				std::cout << link->get_link_text() << std::endl;
			}
			std::cout << "---------------------------------------------" << std::endl;
			for (Link* link : en_links) {
				std::cout << link->get_link_text() << std::endl;
			}
		}

		else if (type_of_print == "with digits") {
			std::cout << "---------------------------------------------" << std::endl;
			int number_of_link = 1;
			for (Link* link : rus_links) {
				std::cout << number_of_link << "." << link->get_link_text() << std::endl;
				number_of_link++;
			}
			for (Link* link : en_links) {
				std::cout << number_of_link << "." << link->get_link_text() << std::endl;
				number_of_link++;
			}
		}
	}

	~Database () {}
};

int main() {
	setlocale(LC_ALL, "RUS");

	Database database;

	std::wifstream file("data.txt");
	std::wstring line;
	std::wstring skip;

	std::wstring link;

	if (file.is_open()) {
		while (getline(file, line)) {
			std::wstringstream wss(line);
			wss >> skip;

			getline(wss, link, L'\n');

			std::string ulink(link.begin(), link.end());

			Link* link_for_add = new Link(ulink);
			database.add_link(link_for_add);
		}
	}
	file.close();

	database.print_sorted_links();

	return 0;
}