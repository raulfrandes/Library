#include "BooksService.h"

BooksService::BooksService(BooksFileRepo& repo, Validator& valid, Basket& basket) noexcept :repo{ repo }, valid{ valid }, basket{ basket } {}

void BooksService::add(const string& title, const string& author, const string& genre, const int& year) {
	Book book{ title, author, genre, year };
	valid.validate(book);
	repo.add(book);
	undo_actions.push_back(make_unique<UndoAdd>(repo, book));
}

const vector<Book>& BooksService::getAll() const noexcept {
	return repo.getAll();
}

void BooksService::remove(const string& title, const string& author) {
	Book book = repo.search(title, author);
	repo.remove(title, author);
	undo_actions.push_back(make_unique<UndoDelete>(repo, book));
}

void BooksService::update(const string& title, const string& author, const string& new_genre, const int& new_year) {
	Book new_book{ title, author, new_genre, new_year };
	Book old_book = repo.search(title, author);
	valid.validate(new_book);
	repo.update(new_book);
	undo_actions.push_back(make_unique<UndoUpdate>(repo, old_book));
}

const Book& BooksService::search(const string& title, const string& author) const {
	return repo.search(title, author);
}

vector<Book> BooksService::filterByTitle(string title) {
	vector<Book> filtered;
	vector<Book> books = repo.getAll();
	copy_if(books.begin(), books.end(), back_inserter(filtered), [title](const Book& book) {return book.getTitle() == title; });
	return filtered;
}

vector<Book> BooksService::filterByGenre(string genre) {
	vector<Book> filtered;
	vector<Book> books = repo.getAll();
	copy_if(books.begin(), books.end(), back_inserter(filtered), [genre](const Book& book) {return book.getGenre() == genre; });
	return filtered;
}

vector<Book> BooksService::filterByYear(int year) {
	vector<Book> filtered;
	vector<Book> books = repo.getAll();
	copy_if(books.begin(), books.end(), back_inserter(filtered), [year](const Book& carte) noexcept {return carte.getYear() == year; });
	return filtered;
}

vector<Book> BooksService::sortByTitle() {
	vector<Book> books = repo.getAll();
	sort(books.begin(), books.end(), cmpTitle);
	return books;
}

vector<Book> BooksService::sortByAuthor() {
	vector<Book> books = repo.getAll();
	sort(books.begin(), books.end(), cmpAuthor);
	return books;
}

vector<Book> BooksService::sortByYearGenre() {
	vector<Book> books = repo.getAll();
	sort(books.begin(), books.end(), cmpYearGenre);
	return books;
}

bool BooksService::addInBasket(const string& title) {
	vector<Book> books = filterByTitle(title);
	if (books.empty()) {
		return false;
	}
	for (const auto& book : books) {
		basket.addBook(book);
	}
	notify();
	return true;
}

void BooksService::deleteFromBasket(const string& title, const string& author) {
	basket.deleteBook(title, author);
	notify();
}

void BooksService::emptyBasket() noexcept {
	basket.emptyBasket();
	notify();
}

bool BooksService::generateBasket(int number_books) {
	vector<Book> books = repo.getAll();
	if (books.empty()) {
		return false;
	}
	basket.generateBasket(books, number_books);
	notify();
	return true;
}

void BooksService::exportBasket(const string& filename) const {
	basket.exportBasket(filename);
}

int BooksService::sizeBasket() const noexcept {
	return basket.sizeBasket();
}

const vector<Book>& BooksService::getBasket() const noexcept {
	return basket.getAll();
}

void BooksService::undo() {
	if (undo_actions.empty()) {
		throw FileExcept("No more operations to undo!");
	}
	const unique_ptr<UndoAction>& act = undo_actions.back();
	act->doUndo();
	undo_actions.pop_back();
}