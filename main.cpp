#include <QApplication>
#include "gui/mainwindow.h"
#include "test/tests.h"
#include "basicobjectmetafactory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    diagramster::BasicObjectMetaFactory::registerMetaTypes();

    diagramster::test::execUnitTests(argc, argv);

    diagramster::MainWindow w;
    w.show();

    return a.exec();
}
