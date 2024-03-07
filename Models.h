#pragma once

#include <QAbstractTableModel>
#include "Book.h"
#include <QDebug>

class MyTableModel : public QAbstractTableModel
{
private:
	vector<Book> books;

public:
	MyTableModel(const vector<Book>& books) :books{ books } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return books.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Book book = books[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(book.getTitle());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(book.getAuthor());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(book.getGenre());
			}
			else if (index.column() == 3) {
				return QString::number(book.getYear());
			}
		}
		if (role == Qt::UserRole) {
			Book book = books[index.row()];
			return QString::fromStdString(book.getAuthor());
		}

		return QVariant{};
	}

	void setBooks(const vector<Book>& b) {
		beginResetModel();
		books = b;
		endResetModel();
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};