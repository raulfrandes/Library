#include "Basket.h"

void Basket::emptyBasket() noexcept {
	basket.clear();
}

void Basket::addBook(const Book& book) {
	if (exist(book.getTitle(), book.getAuthor())) {
		throw BasketExcept("Book already rented!");
	}
	else {
		basket.push_back(book);
	}
}

void Basket::deleteBook(const string& title, const string& author) {
	if (exist(title, author)) {
		basket.erase(find_if(basket.begin(), basket.end(), [title, author](const Book& book) {
			return book.getTitle() == title && book.getAuthor() == author;
			}));
	}
	else {
		throw BasketExcept("Book does not exist!");
	}
}

bool Basket::exist(const string& title, const string& author) {
	for (const auto& book : basket) {
		if (book.getTitle() == title && book.getAuthor() == author) {
			return true;
		}
	}
	return false;
}

void Basket::generateBasket(const vector<Book>& books, int number_books) {
	emptyBasket();
	vector<Book> stock = books;
	shuffle(stock.begin(), stock.end(), default_random_engine(gsl::narrow_cast<unsigned int>(time(nullptr))));
	while (number_books && !stock.empty()) {
		addBook(stock.back());
		stock.pop_back();
		number_books--;
	}
}

void Basket::exportBasket(const string& filename) {
	ofstream fout(filename);
	fout << "<html>\n"
		"<head>\n"
		"	<style>\n"
		"		body {\n"
		"			font-size: 1.5em;\n"
		"			background-color: rgb(32,33,36);\n"
		"			color: #bdc1c6;\n"
		"			font-family: arial,sans-serif;\n"
		"			text-align: center;\n"
		"		}\n"
		"		table, th, td {\n"
		"			border: 2px solid;\n"
		"			font-size: 0.9em;\n"
		"		}\n"
		"		table {\n"
		"			width: 800px;\n"
		"			border-collapse: collapse;\n"
		"			margin-left: auto;\n"
		"			margin-right: auto;\n"
		"		}\n"
		"		td {\n"
		"			text-align: center;\n"
		"			padding: 10px;\n"
		"		}\n"
		"		th {\n"
		"			padding: 10px;\n"
		"		}\n"
		"		h3 {\n"
		"			padding: 15px;\n"
		"		}\n"
		"	</style>\n"
		"</head>\n"
		"<body>\n"
		"	<h3>Rental basket</h3>\n"
		"	<table>\n"
		"		<tr>\n"
		"			<th>Title</th>\n"
		"			<th>Author</th>\n"
		"			<th>Genre</th>\n"
		"			<th>Year of release</th>\n"
		"		</tr>\n";
	for (const auto& book : basket)
	{
		fout << "		<tr>\n";
		fout << "			<td>" << book.getTitle() << "</td>\n"
			<< "			<td>" << book.getAuthor() << "</td>\n"
			<< "			<td>" << book.getGenre() << "</td>\n"
			<< "			<td>" << book.getYear() << "</td>\n"
			<< "		</tr>\n";
	}
	fout << "	</table>\n"
		"</body>\n"
		"</html>";
	fout.close();
}

int Basket::sizeBasket() const noexcept {
	return gsl::narrow_cast<int>(basket.size());
}

const vector<Book>& Basket::getAll() const noexcept {
	return basket;
}