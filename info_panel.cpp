#include <QGuiApplication>
#include <QFontDatabase>

#ifdef QT_DEBUG
    #include <QDebug>
#endif

#include "core_info_panel.h"

void sweep_message_output(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    }
}

int main(int argc, char *argv[])
{

#ifdef QT_DEBUG
    qInstallMessageHandler(sweep_message_output);
#endif

    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication::setOrganizationName("info-panel");
    QGuiApplication::setOrganizationDomain("info-panel-system");
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QFont font_old;
    int id = QFontDatabase::addApplicationFont("://fonts/opensans/OpenSans-Semibold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font_family(family);
    app.setFont(font_family);

#ifdef QT_DEBUG
    qDebug() << QObject::tr("Font system:") << font_old.family();
    qDebug() << QObject::tr("Install font:") << app.font().family();
#endif

    core_info_panel core;
    bool init_state = core.initialization();
    core.program_launch(init_state);

    return app.exec();
}
