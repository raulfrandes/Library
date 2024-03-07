#pragma once
#include "Book.h"
#include <vector>
#include <utility>
#include <gsl/gsl_util>
#include <random>
#include <algorithm>
#include <fstream>
#include "Exceptions.h"

using std::shuffle;
using std::vector;
using std::pair;
using std::make_pair;
using gsl::at;
using std::default_random_engine;
using std::ofstream;
using std::find_if;

class Basket
{
private:
	vector<Book> basket;

	bool exist(const string& title, const string& author);
public:
	Basket() = default;

	void emptyBasket() noexcept;

	void addBook(const Book& book);

	void deleteBook(const string& title, const string& author);

	void generateBasket(const vector<Book>& books, int number_books);

	void exportBasket(const string& filename);

	int sizeBasket() const noexcept;

	const vector<Book>& getAll() const noexcept;

	~Basket() = default;
};