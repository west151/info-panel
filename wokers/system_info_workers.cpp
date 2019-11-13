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

    // font family
    emit signal_result_system_info(font_info);

    // cpu architecture
    emit signal_result_system_info(system_info(tr("cpu architecture"), QSysInfo::currentCpuArchitecture()));
    // build cpu architecture
    emit signal_result_system_info(system_info(tr("build cpu architecture"), QSysInfo::buildCpuArchitecture()));
    // build abi
    emit signal_result_system_info(system_info(tr("build abi"), QSysInfo::buildAbi()));

    // kernel type
    emit signal_result_system_info(system_info(tr("kernel type"), QSysInfo::kernelType()));
    // kernel version
    emit signal_result_system_info(system_info(tr("kernel version"), QSysInfo::kernelVersion()));
    // product version
    emit signal_result_system_info(system_info(tr("product version"), QSysInfo::productVersion()));
}
