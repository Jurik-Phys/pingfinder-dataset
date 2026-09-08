#include <QCoreApplication>
#include "src/generator.h"
#include "src/appInfo.h"

int main(int argc, char** argv){

    QCoreApplication app(argc, argv);

    QStringList args = QCoreApplication::arguments();

    // Print version to display & exit
    if (args.contains("-v") || args.contains("--version"))
    {
        AppInfo::print();
        return 0;
    }

    Generator* clientDatasetGenerator = new Generator(&app);

    return app.exec();
}
