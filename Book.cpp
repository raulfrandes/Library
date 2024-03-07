#include "Book.h"

Book::Book(const string& title, const string& author, const string& genre, int year) :title{ title }, author{ author }, genre{ genre }, year{ year } {}

Book::Book(const Book& other) :title{ other.title }, author{ other.author }, genre{ other.genre }, year{ other.year } {
}

Book& Book::operator=(const Book& other) {
    this->title = other.title;
    this->author = other.author;
    this->genre = other.genre;
    this->year = other.year;
    return *this;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getGenre() const {
    return genre;
}

int Book::getYear() const noexcept {
    return year;
}

void Book::setTitle(const string& new_title) {
    title = new_title;
}

void Book::setAuthor(const string& new_author) {
    author = new_author;
}

void Book::setGenre(const string& new_genre) {
    genre = new_genre;
}

void Book::setYear(int new_year) noexcept {
    year = new_year;
}

bool cmpTitle(const Book& b1, const Book& b2) {
    return b1.getTitle() < b2.getTitle();
}

bool cmpAuthor(const Book& b1, const Book& b2) {
    return b1.getAuthor() < b2.getAuthor();
}

bool cmpYearGenre(const Book& b1, const Book& b2) {
    if (b1.getYear() == b2.getYear()) {
        return b1.getGenre() < b2.getGenre();
    }
    return b1.getYear() < b2.getYear();
}

ostream& operator<<(ostream& out, const Book& book) {
    out << book.getTitle() << "," << book.getAuthor() << "," << book.getGenre() << "," << book.getYear() << endl;
    return out;
}

vector<string> splitString(const string& str, const string& del) {
    int start, end = -1 * gsl::narrow_cast<int>(del.size());
    vector<string> splited;
    do {
        start = end + gsl::narrow_cast<int>(del.size());
        end = gsl::narrow_cast<int>(str.find(del, start));
        splited.push_back(str.substr(start, end - start));
    } while (end != -1);
    return splited;
}

istream& operator>>(istream& in, Book& book) {
    string line;
    getline(in, line);
    vector<string> parts = splitString(line, ",");
    if (parts.size() != 4) {
        return in;
    }
    book.setTitle(at(parts, 0));
    book.setAuthor(at(parts, 1));
    book.setGenre(at(parts, 2));
    book.setYear(stoi(at(parts, 3)));
    return in;
}