#pragma once
#include "Book.h"
#include <vector>
#include <exception>
#include <algorithm>
#include <gsl/util>
#include "Exceptions.h"

using std::exception;
using std::vector;
using std::find_if;
using std::iterator;
using gsl::at;

class BooksRepo
{
private:
	vector<Book> books;

	bool exist(const Book& book);
public:
	BooksRepo() = default;

	BooksRepo(const BooksRepo& other) = delete;

	virtual void add(const Book& book);

	virtual const Book& search(const string& title, const string& author) const;

	virtual void remove(const string& title, const string& author);

	virtual void update(const Book& book);

	virtual const vector<Book>& getAll() const noexcept;

	virtual ~BooksRepo() = default;
};

