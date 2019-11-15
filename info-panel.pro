QT += quick

include(common.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    core_info_panel.h \
    model/info_panel_model.h \
    model/message_log.h \
    model/message_log_model.h \
    model/sort_filter_proxy_model.h \
    model/system_info.h \
    model/system_info_model.h \
    wokers/dmesg_process_wokers.h \
    wokers/system_info_workers.h

SOURCES += \
    core_info_panel.cpp \
    info_panel.cpp \
    model/info_panel_model.cpp \
    model/message_log.cpp \
    model/message_log_model.cpp \
    model/sort_filter_proxy_model.cpp \
    model/system_info.cpp \
    model/system_info_model.cpp \
    wokers/dmesg_process_wokers.cpp \
    wokers/system_info_workers.cpp

RESOURCES += \
    $$files(qml/*.qml) \
    qml.qrc

# Default rules for deployment.
unix: target.path = /opt/info_panel/bin
!isEmpty(target.path): INSTALLS += target
