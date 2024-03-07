#pragma once
#include "BooksFileRepo.h"
#include "Validator.h"
#include <functional>
#include "Basket.h"
#include "UndoAction.h"
#include <memory>
#include "Observer.h"

using std::function;
using std::copy_if;
using std::back_inserter;
using std::make_unique;
using std::unique_ptr;

class BooksService : public Observable
{
private:
	BooksFileRepo& repo;

	Validator& valid;

	Basket& basket;

	vector<unique_ptr<UndoAction>> undo_actions;
public:
	BooksService(BooksFileRepo& repo, Validator& valid, Basket& basket) noexcept;

	BooksService(const BooksService& other) = delete;

	void add(const string& title, const string& author, const string& genre, const int& year);

	const vector<Book>& getAll() const noexcept;

	void remove(const string& title, const string& author);

	void update(const string& title, const string& author, const string& new_genre, const int& new_year);

	const Book& search(const string& title, const string& author) const;

	vector<Book> filterByTitle(string title);

	vector<Book> filterByGenre(string genre);

	vector<Book> filterByYear(int year);

	vector<Book> sortByTitle();

	vector<Book> sortByAuthor();

	vector<Book> sortByYearGenre();

	bool addInBasket(const string& title);

	void deleteFromBasket(const string& title, const string& author);

	void emptyBasket() noexcept;

	bool generateBasket(int number_books);

	void exportBasket(const string& filename) const;

	int sizeBasket() const noexcept;

	const vector<Book>& getBasket() const noexcept;

	void undo();

	~BooksService() = default;
};

