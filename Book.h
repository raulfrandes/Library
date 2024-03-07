#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <gsl/gsl_util>

using std::string;
using std::vector;
using std::cout;
using std::ostream;
using std::istream;
using std::endl;
using std::find;
using gsl::at;

class Book
{
	string title;
	string author;
	string genre;
	int year;
public:
	Book(const string& title, const string& author, const string& genre, int year);

	Book() = default;

	Book(const Book& other);

	Book& operator=(const Book& other);

	Book(Book&& other) noexcept = default;

	Book& operator=(Book&& other) noexcept = default;

	string getTitle() const;

	string getAuthor() const;

	string getGenre() const;

	int getYear() const noexcept;

	void setTitle(const string& new_title);

	void setAuthor(const string& new_author);

	void setGenre(const string& new_genre);

	void setYear(int new_year) noexcept;

	friend ostream& operator<<(ostream& out, const Book& book);

	friend istream& operator>>(istream& in, Book& book);

	~Book() = default;
};

vector<string> splitString(const string& str, const string& del);

bool cmpTitle(const Book& b1, const Book& b2);

bool cmpAuthor(const Book& b1, const Book& b2);

bool cmpYearGenre(const Book& b1, const Book& b2);

ostream& operator<<(ostream& out, const Book& book);

istream& operator>>(istream& in, Book& book);