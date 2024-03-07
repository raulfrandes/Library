#pragma once
#include "BooksRepo.h"
#include <fstream>
#include "Exceptions.h"

using std::ifstream;
using std::ofstream;
using std::endl;

class BooksFileRepo : public BooksRepo
{
private:
	string filename;

	void loadFromFile();

	void writeToFile();
public:
	BooksFileRepo(string filename) :BooksRepo(), filename{ filename } {
		loadFromFile();
	}

	BooksFileRepo() = default;

	void add(const Book& book) override {
		BooksRepo::add(book);
		writeToFile();
	}

	void remove(const string& title, const string& author) override {
		BooksRepo::remove(title, author);
		writeToFile();
	}

	const Book& search(const string& title, const string& author) const override {
		return BooksRepo::search(title, author);
	}

	void update(const Book& book) override {
		BooksRepo::update(book);
		writeToFile();
	}

	const vector<Book>& getAll() const noexcept override {
		return BooksRepo::getAll();
	}
};

