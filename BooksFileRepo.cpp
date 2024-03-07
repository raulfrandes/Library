#include "BooksFileRepo.h"

void BooksFileRepo::loadFromFile() {
	ifstream in(filename);
	if (!in.is_open()) {
		throw FileExcept("Error at opening: " + filename);
	}
	while (!in.eof()) {
		Book book{ "", "", "", -1 };
		in >> book;
		if (book.getTitle() != "") {
			BooksRepo::add(book);
		}
	}
	in.close();
}

void BooksFileRepo::writeToFile() {
	ofstream out(filename);
	if (!out.is_open()) {
		throw FileExcept("Error at opening file.");
	}
	for (auto& book : getAll()) {
		out << book;
	}
	out.close();
}