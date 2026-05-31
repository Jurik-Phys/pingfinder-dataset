#include <QCoreApplication>
#include "src/generator.h"

int main(int argc, char** argv){

    QCoreApplication app(argc, argv);

    Generator* clientDatasetGenerator = new Generator(&app);

    return app.exec();
}
