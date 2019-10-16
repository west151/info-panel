#ifndef CORE_SWEEP_REMOTE_CONTROL_H
#define CORE_SWEEP_REMOTE_CONTROL_H

#include <QObject>
#include <QQmlApplicationEngine>

class core_info_panel : public QObject
{
    Q_OBJECT
public:
    explicit core_info_panel(const QString &app_name, QObject *parent = nullptr);

    // read file settings
    bool initialization();
    // program launch
    void program_launch(bool is_init_state);

signals:

public slots:

private:
    QString str_config_location;

    QQmlApplicationEngine* ptr_engine {Q_NULLPTR};


//    bool read_settings();
//    bool write_settings();
};

#endif // CORE_SWEEP_REMOTE_CONTROL_H
