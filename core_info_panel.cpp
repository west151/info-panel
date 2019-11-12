#include "core_info_panel.h"

#include <QString>
#include <QQmlContext>

#include "model/info_panel_model.h"
#include "model/system_info_model.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

core_info_panel::core_info_panel(QObject *parent) : QObject(parent),
    ptr_info_panel_model(new info_panel_model(this)),
    ptr_system_info_model(new system_info_model(this))
{

}

bool core_info_panel::initialization()
{
    bool status(false);

    return status;
}

void core_info_panel::program_launch(bool is_init_state)
{
    ptr_engine = new QQmlApplicationEngine(this);

    QQmlContext *context = ptr_engine->rootContext();
    context->setContextProperty("info_panel_model", ptr_info_panel_model);
    context->setContextProperty("system_info_model", ptr_system_info_model);

    ptr_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));
}
