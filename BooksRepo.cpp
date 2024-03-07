#include "BooksRepo.h"

void BooksRepo::add(const Book& book) {
	if (exist(book)) {
		throw RepoExcept("The book with title: " + book.getTitle() + " and author: " + book.getAuthor() + " already exists!");
	}
	books.push_back(book);
}

const Book& BooksRepo::search(const string& title, const string& author) const {
	vector<Book>::const_iterator it;
	it = find_if(books.begin(), books.end(), [title, author](const Book& carte) {return ((carte.getTitle() == title) && (carte.getAuthor() == author)); });
	if (it != books.end()) {
		return *it;
	}
	throw RepoExcept("The book with the title: " + title + " and author: " + author + " does not exist!");
}

void BooksRepo::remove(const string& title, const string& author) {
	int i = 0;
	int ok = 0;
	for (const auto& book : books) {
		if (book.getTitle() == title && book.getAuthor() == author) {
			books.erase(books.begin() + i);
			ok = 1;
		}
		i++;
	}
	if (!ok) {
		throw RepoExcept("The book with the title: " + title + " and author: " + author + " does not exist!");
	}
}

void BooksRepo::update(const Book& book) {
	int i = 0;
	int ok = 0;
	for (const auto& b : books) {
		if (b.getTitle() == book.getTitle() && b.getAuthor() == book.getAuthor()) {
			at(books, i) = book;
			ok = 1;
		}
		i++;
	}
	if (!ok) {
		throw RepoExcept("The book with the title: " + book.getTitle() + " and author: " + book.getAuthor() + " does not exist!");
	}
}

const vector<Book>& BooksRepo::getAll() const noexcept {
	return books;
}

bool BooksRepo::exist(const Book& book) {
	try {
		search(book.getTitle(), book.getAuthor());
		return true;
	}
	catch (RepoExcept&) {
		return false;
	}
}
