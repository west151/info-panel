#include "system_info_workers.h"
#include <QFont>
#include <QSysInfo>

system_info_workers::system_info_workers(QObject *parent) : QObject(parent)
{

}

void system_info_workers::slot_start_workers()
{
    system_info font_info;
    QFont font;

    font_info.set_parameter_name(tr("font family"));
    font_info.set_parameter_value(font.family());

    emit signal_result_system_info(font_info);

    system_info cpu_info;
    cpu_info.set_parameter_name(tr("cpu architecture"));
    cpu_info.set_parameter_value(QSysInfo::currentCpuArchitecture());

    emit signal_result_system_info(cpu_info);
}
