#include "Gui.h"

void Gui::initGui() {
	this->setWindowTitle("Library");
	this->setGeometry(350, 200, 800, 400);

	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	QWidget* rightWid = new QWidget;
	QVBoxLayout* vly = new QVBoxLayout;
	rightWid->setLayout(vly);

	table = new QTableView;
	model = new MyTableModel(serv.getAll());
	table->setModel(model);
	table->setFixedSize(table->columnWidth(0) * model->columnCount(), 300);
	vly->addWidget(table);

	QWidget* rightBtnWid = new QWidget;
	QHBoxLayout* underListLy = new QHBoxLayout;
	rightBtnWid->setLayout(underListLy);
	sortByTitleBtn = new QPushButton("Sort By Title");
	underListLy->addWidget(sortByTitleBtn);
	sortByAuthorBtn = new QPushButton("Sort By Author");
	underListLy->addWidget(sortByAuthorBtn);
	sortByYearGenreBtn = new QPushButton("Sort By Year And Genre");
	underListLy->addWidget(sortByYearGenreBtn);

	vly->addWidget(rightBtnWid);
	ly->addWidget(rightWid);

	QWidget* leftWid = new QWidget;
	QVBoxLayout* vly2 = new QVBoxLayout;
	leftWid->setLayout(vly2);

	QWidget* formWid = new QWidget;
	QFormLayout* form = new QFormLayout;
	formWid->setLayout(form);
	textTitle = new QLineEdit;
	form->addRow(new QLabel("Title:"), textTitle);
	textAuthor = new QLineEdit;
	form->addRow(new QLabel("Author:"), textAuthor);
	textGenre = new QLineEdit;
	form->addRow(new QLabel("Genre:"), textGenre);
	textYear = new QLineEdit;
	form->addRow(new QLabel("Year:"), textYear);
	vly2->addWidget(formWid);

	QWidget* leftBtnWid1 = new QWidget;
	QHBoxLayout* leftBtnLy1 = new QHBoxLayout;
	leftBtnWid1->setLayout(leftBtnLy1);
	addBtn = new QPushButton("Add");
	leftBtnLy1->addWidget(addBtn);
	deleteBtn = new QPushButton("Delete");
	leftBtnLy1->addWidget(deleteBtn);
	updateBtn = new QPushButton("Update");
	leftBtnLy1->addWidget(updateBtn);
	vly2->addWidget(leftBtnWid1);

	QWidget* leftBtnWid2 = new QWidget;
	QHBoxLayout* leftBtnLy2 = new QHBoxLayout;
	leftBtnWid2->setLayout(leftBtnLy2);
	filterByTitleBtn = new QPushButton("Filter By Title");
	leftBtnLy2->addWidget(filterByTitleBtn);
	filterByYearBtn = new QPushButton("Filter By Year");
	leftBtnLy2->addWidget(filterByYearBtn);
	reloadBtn = new QPushButton("Reload");
	leftBtnLy2->addWidget(reloadBtn);
	undoBtn = new QPushButton("Undo");
	leftBtnLy2->addWidget(undoBtn);
	vly2->addWidget(leftBtnWid2);

	QWidget* leftBtnWid3 = new QWidget;
	QHBoxLayout* leftBtnLy3 = new QHBoxLayout;
	leftBtnWid3->setLayout(leftBtnLy3);
	addBasketBtn = new QPushButton("Add In Basket");
	leftBtnLy3->addWidget(addBasketBtn);
	deleteBasketBtn = new QPushButton("Delete From Basket");
	leftBtnLy3->addWidget(deleteBasketBtn);
	generateBasketBtn = new QPushButton("Generate Basket");
	leftBtnLy3->addWidget(generateBasketBtn);
	vly2->addWidget(leftBtnWid3);

	QWidget* leftBtnWid4 = new QWidget;
	QHBoxLayout* leftBtnLy4 = new QHBoxLayout;
	leftBtnWid4->setLayout(leftBtnLy4);
	basketBtn = new QPushButton("Basket");
	leftBtnLy4->addWidget(basketBtn);
	basketGraphBtn = new QPushButton("Basket Graph");
	leftBtnLy4->addWidget(basketGraphBtn);
	vly2->addWidget(leftBtnWid4);

	vly2->addStretch();

	ly->addWidget(leftWid);

	dynBtn->setLayout(dynLy);
	ly->addWidget(dynBtn);
}

void Gui::connectSignalsSlots() {
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (table->selectionModel()->selectedIndexes().isEmpty()) {
			textTitle->setText("");
			textAuthor->setText("");
			textGenre->setText("");
			textYear->setText("");
			return;
		}
		int selRow = table->selectionModel()->selectedIndexes().at(0).row();
		auto cell0Index = table->model()->index(selRow, 0);
		auto cell1Index = table->model()->index(selRow, 1);
		auto cell2Index = table->model()->index(selRow, 2);
		auto cell3Index = table->model()->index(selRow, 3);
		QString title = table->model()->data(cell0Index, Qt::DisplayRole).toString();
		textTitle->setText(title);
		QString author = table->model()->data(cell1Index, Qt::UserRole).toString();
		textAuthor->setText(author);
		try {
			Book book = serv.search(title.toStdString(), author.toStdString());
			textGenre->setText(QString::fromStdString(book.getGenre()));
			textYear->setText(QString::number(book.getYear()));
		}
		catch (RepoExcept& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.get_msg()));
		}
		});

	QObject::connect(addBtn, &QPushButton::clicked, [&]() {
		try {
			serv.add(textTitle->text().toStdString(), textAuthor->text().toStdString(), textGenre->text().toStdString(), textYear->text().toInt());
			reloadTable(serv.getAll());
			addDynBtns(serv.getAll());
			textTitle->setText("");
			textAuthor->setText("");
			textGenre->setText("");
			textYear->setText("");
		}
		catch (RepoExcept& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
		}
		catch (ValidExcept& ex) {
			for (const auto& error : ex.get_msg()) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(error));
			}
		}
		});

	QObject::connect(deleteBtn, &QPushButton::clicked, [&]() {
		try {
			serv.remove(textTitle->text().toStdString(), textAuthor->text().toStdString());
			reloadTable(serv.getAll());
			addDynBtns(serv.getAll());
			textTitle->setText("");
			textAuthor->setText("");
			textGenre->setText("");
			textYear->setText("");
		}
		catch (RepoExcept& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
		}
		});

	QObject::connect(updateBtn, &QPushButton::clicked, [&]() {
		try {
			serv.update(textTitle->text().toStdString(), textAuthor->text().toStdString(), textGenre->text().toStdString(), textYear->text().toInt());
			reloadTable(serv.getAll());
			addDynBtns(serv.getAll());
			textTitle->setText("");
			textAuthor->setText("");
			textGenre->setText("");
			textYear->setText("");
		}
		catch (RepoExcept& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
		}
		catch (ValidExcept& ex) {
			for (const auto& error : ex.get_msg()) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(error));
			}
		}
		});

	QObject::connect(sortByTitleBtn, &QPushButton::clicked, [&]() {
		reloadTable(serv.sortByTitle());
		});

	QObject::connect(sortByAuthorBtn, &QPushButton::clicked, [&]() {
		reloadTable(serv.sortByAuthor());
		});

	QObject::connect(sortByYearGenreBtn, &QPushButton::clicked, [&]() {
		reloadTable(serv.sortByYearGenre());
		});

	QObject::connect(filterByTitleBtn, &QPushButton::clicked, [&]() {
		reloadTable(serv.filterByTitle(textTitle->text().toStdString()));
		});

	QObject::connect(filterByYearBtn, &QPushButton::clicked, [&]() {
		reloadTable(serv.filterByYear(textYear->text().toInt()));
		});

	QObject::connect(reloadBtn, &QPushButton::clicked, [&]() {
		reloadTable(serv.getAll());
		});

	QObject::connect(basketBtn, &QPushButton::clicked, [&]() {
		basket = new BasketGui{ serv };
		basket->show();
		});

	QObject::connect(basketGraphBtn, &QPushButton::clicked, [&]() {
		basketGraphWid = new BasketGraphGui{ serv };
		basketGraphWid->setWindowTitle("Basket Graph");
		basketGraphWid->show();
		});

	QObject::connect(addBasketBtn, &QPushButton::clicked, [&]() {
		try {
			serv.addInBasket(textTitle->text().toStdString());
		}
		catch (BasketExcept& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
		}
		});

	QObject::connect(deleteBasketBtn, &QPushButton::clicked, [&]() {
		try {
			serv.deleteFromBasket(textTitle->text().toStdString(), textAuthor->text().toStdString());
		}
		catch (BasketExcept& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
		}
		});

	QObject::connect(generateBasketBtn, &QPushButton::clicked, [&]() {
		QWidget* numGenWid = new QWidget;
		numGenWid->setWindowTitle("Number of generated books");
		QHBoxLayout* numGenLy = new QHBoxLayout;
		numGenWid->setLayout(numGenLy);
		QLineEdit* numGen = new QLineEdit;
		numGenLy->addWidget(numGen);
		QPushButton* ok = new QPushButton("Ok");
		numGenLy->addWidget(ok);
		numGenWid->setGeometry(600, 350, 300, 100);
		numGenWid->show();
		QObject::connect(ok, &QPushButton::clicked, [&, numGenWid, numGen]() {
			serv.generateBasket(numGen->text().toInt());
			numGenWid->close();
			});
		});

	QObject::connect(undoBtn, &QPushButton::clicked, [&]() {
		try {
			serv.undo();
			reloadTable(serv.getAll());
			addDynBtns(serv.getAll());
		}
		catch (FileExcept& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_msg()));
		}
		});
}

void Gui::reloadTable(const vector<Book>& books) {
	model->setBooks(books);
}

void BasketGui::initBasketGui() {
	setWindowTitle("Rental Basket");
	QHBoxLayout* basketLy = new QHBoxLayout;
	setLayout(basketLy);

	basketTable = new QTableView;
	model = new MyTableModel(serv.getBasket());
	basketTable->setModel(model);
	basketLy->addWidget(basketTable);

	QWidget* basketRightWid = new QWidget;
	QVBoxLayout* basketRightLy = new QVBoxLayout;
	basketRightWid->setLayout(basketRightLy);

	QWidget* basketForm = new QWidget;
	QFormLayout* basketFormLy = new QFormLayout;
	basketForm->setLayout(basketFormLy);
	textGenerate = new QLineEdit;
	basketFormLy->addRow(new QLabel("Number of books:"), textGenerate);
	textExport = new QLineEdit;
	basketFormLy->addRow(new QLabel("Filename:"), textExport);
	basketRightLy->addWidget(basketForm);

	QWidget* basketUnderBtn = new QWidget;
	QVBoxLayout* basketUnderLy = new QVBoxLayout;
	basketUnderBtn->setLayout(basketUnderLy);
	emptyBasketBtn = new QPushButton("Empty basket");
	basketUnderLy->addWidget(emptyBasketBtn);
	generateBasketBtn = new QPushButton("Generate basket");
	basketUnderLy->addWidget(generateBasketBtn);
	exportBasketBtn = new QPushButton("Export basket");
	basketUnderLy->addWidget(exportBasketBtn);
	basketRightLy->addWidget(basketUnderBtn);

	basketLy->addWidget(basketRightWid);
}

void BasketGui::connectSignalsSlotsBasket() {
	QObject::connect(emptyBasketBtn, &QPushButton::clicked, [&]() {
		serv.emptyBasket();
		});

	QObject::connect(generateBasketBtn, &QPushButton::clicked, [&]() {
		serv.generateBasket(textGenerate->text().toInt());
		});

	QObject::connect(exportBasketBtn, &QPushButton::clicked, [&]() {
		serv.exportBasket(textExport->text().toStdString());
		QUrl fileUrl = QUrl::fromLocalFile(textExport->text());
		QDesktopServices::openUrl(fileUrl);
		});
}

void BasketGui::reloadBasketTable(const vector<Book>& books) {
	model->setBooks(books);
}

void Gui::addDynBtns(const vector<Book>& books) {
	set<string> genres;
	for (const auto& book : books) {
		genres.insert(book.getGenre());
	}
	for (const auto& genre : genres) {
		if (genreBtn.find(genre) != genreBtn.end()) {
			continue;
		}
		QPushButton* genreB = new QPushButton(QString::fromStdString(genre));
		dynLy->addWidget(genreB);
		genreBtn[genre] = genreB;

		QObject::connect(genreB, &QPushButton::clicked, this, [genre, this]() {
			int numBooks = serv.filterByGenre(genre).size();
			QMessageBox::information(this, "Number of books", QString::fromStdString(to_string(numBooks)));
			});
	}
	vector<string> genreToDelete;
	for (const auto& pair : genreBtn) {
		if (genres.find(pair.first) == genres.end()) {
			genreToDelete.push_back(pair.first);
		}
	}
	for (const auto& gen : genreToDelete) {
		delete genreBtn[gen];
		this->genreBtn.erase(gen);
	}
}