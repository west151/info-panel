#include <QGuiApplication>
#include <QFontDatabase>
#include <QIcon>

#ifdef QT_DEBUG
    #include <QDebug>
    #include <QScreen>
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
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#ifdef QT_DEBUG
    qInstallMessageHandler(sweep_message_output);
#endif

    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication::setOrganizationName("info-panel");
    QGuiApplication::setOrganizationDomain("info-panel-system");
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("://icon/organization.png"));

    // fonts
    QFont font_old;
    int id = QFontDatabase::addApplicationFont("://fonts/opensans/OpenSans-Semibold.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font_family(family);
    app.setFont(font_family);

#ifdef QT_DEBUG
    qDebug() << QObject::tr("Font system:") << font_old.family();
    qDebug() << QObject::tr("Install font:") << app.font().family();
#endif

#ifdef QT_DEBUG
    // screens
    QList<QScreen*> screens = qApp->screens();

    for(int i = 0; i < screens.size(); ++i)
    {
        qDebug() << QObject::tr("Screen:");
        qDebug() << QObject::tr("   id:") << i;
        qDebug() << QObject::tr("   name:") << screens.at(i)->name();
        qDebug() << QObject::tr("   model:") << screens.at(i)->model();
        qDebug() << QObject::tr("   manufacturer:") << screens.at(i)->manufacturer();
        qDebug() << QObject::tr("   serial:") << screens.at(i)->serialNumber();
        qDebug() << QObject::tr("   width:") << screens.at(i)->availableSize().width();
        qDebug() << QObject::tr("   height:") << screens.at(i)->availableSize().height();
    }
#endif

    core_info_panel core;
    bool init_state = core.initialization();
    core.program_launch(init_state);

    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     &core, SLOT(slot_exit_handler()));

    return app.exec();
}
