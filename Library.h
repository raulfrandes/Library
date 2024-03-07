#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Library.h"

class Library : public QMainWindow
{
    Q_OBJECT

public:
    Library(QWidget *parent = nullptr);
    ~Library();

private:
    Ui::LibraryClass ui;
};
