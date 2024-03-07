#pragma once
#include "BooksFileRepo.h"

class UndoAction
{
public:
	virtual void doUndo() = 0;

	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
private:
	Book added_book;
	BooksFileRepo& repo;
public:
	UndoAdd(BooksFileRepo& repo, const Book& book) :repo{ repo }, added_book{ book } {}

	void doUndo() override {
		repo.remove(added_book.getTitle(), added_book.getAuthor());
	}
};

class UndoDelete : public UndoAction {
private:
	Book deleted_book;
	BooksFileRepo& repo;
public:
	UndoDelete(BooksFileRepo& repo, const Book& book) :repo{ repo }, deleted_book{ book } {}

	void doUndo() override {
		repo.add(deleted_book);
	}
};

class UndoUpdate : public UndoAction {
private:
	Book updated_book;
	BooksFileRepo& repo;
public:
	UndoUpdate(BooksFileRepo& repo, const Book& book) :repo{ repo }, updated_book{ book } {}

	void doUndo() override {
		repo.update(updated_book);
	}
};

