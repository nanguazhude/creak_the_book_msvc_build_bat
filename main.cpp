
#include <QtCore/QtCore>
#include <array>
static const QDir * globalDir{ nullptr };

class Item {
public:
    QString dirName;
    QDir dir;
    QString dirPath;
    template<typename T>
    inline Item(T && arg) : dirName{ std::forward<T>(arg) } {
        dir = QDir(globalDir->filePath(QStringLiteral("../") + dirName));
        dirPath = dir.canonicalPath();
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication varApp{ argc, argv };

    QDir varDir{ CURRENT_DIR };
    globalDir = &varDir;

    const std::array globalItems = {
        Item{ QStringLiteral("sstd_copy_qml") },
        Item{ QStringLiteral("sstd_qml_moc") },
        Item{ QStringLiteral("sstd_library") },
        Item{ QStringLiteral("sstd_qt_qml_quick_library") },
        Item{ QStringLiteral("chapter01") },
        Item{ QStringLiteral("chapter02") },
        Item{ QStringLiteral("chapter03") },
        Item{ QStringLiteral("chapter04") },
        Item{ QStringLiteral("chapter05") },
        Item{ QStringLiteral("chapter06") },
        Item{ QStringLiteral("chapter07") },
        Item{ QStringLiteral("chapter08") },
        Item{ QStringLiteral("chapter09") },
        Item{ QStringLiteral("chapter10") },
        Item{ QStringLiteral("sstd_introduce_qmake") },
        Item{ QStringLiteral("sstd_create_windows_qt_dll_link") },
        //Item{ QStringLiteral("creak_the_book_msvc_build_bat") },
    };

    QFile varFile{ varDir.filePath(QStringLiteral("../update.all.msvc.bat")) };

    if (!varFile.open(QIODevice::WriteOnly)) {
        qDebug() << varDir.filePath(QStringLiteral("../update.all.msvc.bat"));
        return -2;
    }
    QTextStream varOut{ &varFile };

    {/*copy qtenv2.bat ... */
        QDir varQtBinDir{ CURRENT_QT_BIN_DIR };
        QFile varFile{ varQtBinDir.filePath(QStringLiteral("qtenv2.bat")) };
        if (!varFile.open(QIODevice::ReadOnly)) {
            return -3;
        }
        QTextStream varRead{ &varFile };
        varOut << varRead.readAll();
        varOut << endl;
    }

    /*create every msvc project ... */
    for (const auto & varI : globalItems) {
        varOut << endl;
        varOut << QStringLiteral(R"(cd /D )") << varI.dirPath << endl;
        varOut << QStringLiteral(R"(qmake -r -tp vc)") << endl;
    }

    return 0;
}




