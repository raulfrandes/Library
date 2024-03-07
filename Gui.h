#pragma once

#include "BooksService.h"
#include <set>
#include <map>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qmessagebox.h>
#include <qdesktopservices.h>
#include <QUrl>
#include <QtWidgets/qtableview.h>
#include <qpainter.h>
#include "Models.h"

using std::set;
using std::map;
using std::to_string;

class BasketGraphGui : public QWidget, public Observer
{
private:
	BooksService& serv;

public:
	BasketGraphGui(BooksService& serv) :serv{ serv } {
		serv.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 10;
		for (const auto& book : serv.getBasket()) {
			p.drawRect(x, 0, 20, 40);
			x += 40;
		}
	}
	~BasketGraphGui() {
		serv.removeObserver(this);
	}
};

class BasketGui : public QWidget, public Observer
{
private:
	BooksService& serv;

	MyTableModel* model;
	QTableView* basketTable;

	QPushButton* emptyBasketBtn;
	QPushButton* generateBasketBtn;
	QPushButton* exportBasketBtn;
	QLineEdit* textGenerate;
	QLineEdit* textExport;

	void update() override {
		reloadBasketTable(serv.getBasket());
	}

	void initBasketGui();
	void reloadBasketTable(const vector<Book>& books);
	void connectSignalsSlotsBasket();

	~BasketGui() {
		serv.removeObserver(this);
	}

public:
	BasketGui() = default;

	BasketGui(BooksService& serv) :serv{ serv } {
		serv.addObserver(this);
		initBasketGui();
		connectSignalsSlotsBasket();
		reloadBasketTable(serv.getBasket());
	}
};

class Gui :public QWidget
{
private:
	BooksService& serv;
	BasketGui* basket;
	BasketGraphGui* basketGraphWid;

	MyTableModel* model;
	QTableView* table;

	QPushButton* deleteBtn;
	QPushButton* sortByTitleBtn;
	QPushButton* sortByAuthorBtn;
	QPushButton* sortByYearGenreBtn;
	QPushButton* addBtn;
	QPushButton* updateBtn;
	QPushButton* filterByTitleBtn;
	QPushButton* filterByYearBtn;
	QPushButton* reloadBtn;
	QPushButton* basketBtn;
	QPushButton* basketGraphBtn;
	QPushButton* addBasketBtn;
	QPushButton* undoBtn;
	QPushButton* deleteBasketBtn;
	QPushButton* generateBasketBtn;
	QLineEdit* textTitle;
	QLineEdit* textAuthor;
	QLineEdit* textGenre;
	QLineEdit* textYear;

	QVBoxLayout* dynLy = new QVBoxLayout;
	QWidget* dynBtn = new QWidget;
	std::map<string, QPushButton*> genreBtn;

	void initGui();
	void connectSignalsSlots();
	void reloadTable(const vector<Book>& books);
	void addDynBtns(const vector<Book>& books);
public:
	Gui(BooksService& serv) :serv{ serv } {
		initGui();
		connectSignalsSlots();
		reloadTable(serv.getAll());
		addDynBtns(serv.getAll());
	}
};