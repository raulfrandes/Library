#pragma once
#include "Book.h"
#include <vector>
#include "Exceptions.h"

using std::vector;

class Validator
{
public:
	void validate(const Book& book);
};

