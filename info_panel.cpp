#include <QGuiApplication>

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
    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication::setOrganizationName("info-panel");
    QGuiApplication::setOrganizationDomain("info-panel-system");

#ifdef QT_DEBUG
    qInstallMessageHandler(sweep_message_output);
#endif

    QGuiApplication app(argc, argv);

    core_info_panel core;
    bool init_state = core.initialization();
    core.program_launch(init_state);

    return app.exec();
}