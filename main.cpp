#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include "BooksService.h"
#include "Gui.h"
// #include "Teste.h"

int main(int argc, char* argv[])
{
    // Teste teste;
    // teste.all_tests();

    QApplication a(argc, argv);
    BooksFileRepo repo{ "Books.txt" };
    Validator valid;
    Basket basket;
    BooksService serv{ repo, valid, basket };
    Gui gui{ serv };
    gui.show();
    a.exec();

    return 0;
}
