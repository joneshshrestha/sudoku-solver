#include <QApplication>

#include "soduku.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile File(":/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());


    Soduku w;

    w.setStyleSheet(StyleSheet);


    w.setWindowTitle("Soduku Solver");

    w.show();

    return a.exec();
}
