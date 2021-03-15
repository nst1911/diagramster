#include "gui/mainwindow.h"
#include "test/tests.h"
#include <QApplication>

#include "basicobjectfactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    diagramster::BasicObjectFactory::registerMetaTypes();

    diagramster::test::execUnitTests(argc, argv);

    diagramster::MainWindow w;
    w.show();

    return a.exec();
}
