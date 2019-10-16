#include "core_info_panel.h"

#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <QString>
#include <QQmlContext>

#ifdef QT_DEBUG
#include <QDebug>
#endif

static const QString str_config_suffix(QString(".conf"));

core_info_panel::core_info_panel(const QString &app_name, QObject *parent) : QObject(parent)
{
//    str_config_location.append(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
//    str_config_location.append(QDir::separator());
//    str_config_location.append(app_name);
//    str_config_location.append(str_config_suffix);

//    ptr_remote_control_settings = new remote_control_settings;
}

bool core_info_panel::initialization()
{
    bool status(false);

//    qInfo("Сonfiguration file: '%s'", qUtf8Printable(str_config_location));

//    if(QFile::exists(str_config_location))
//        status = read_settings();
//    else
//        status = write_settings();

    return status;
}

void core_info_panel::program_launch(bool is_init_state)
{
    ptr_engine = new QQmlApplicationEngine(this);

//    QQmlContext *context = ptr_engine->rootContext();
//    context->setContextProperty("top_model", ptr_top_model);

//    ptr_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    //ptr_top_model->start();
}

