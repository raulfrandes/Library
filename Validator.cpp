#include "Validator.h"

void Validator::validate(const Book& book) {
	vector<string> message;
	if (book.getTitle().size() == 0) {
		message.push_back("Invalid title!!\n");
	}
	if (book.getAuthor().size() == 0) {
		message.push_back("Invalid author!!\n");
	}
	if (book.getGenre().size() == 0) {
		message.push_back("Invalid genre!!\n");
	}
	if (book.getYear() < 0) {
		message.push_back("Invalid year!!\n");
	}
	if (message.size() > 0) {
		throw ValidExcept(message);
	}
}