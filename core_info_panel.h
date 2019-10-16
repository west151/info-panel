#ifndef CORE_SWEEP_REMOTE_CONTROL_H
#define CORE_SWEEP_REMOTE_CONTROL_H

#include <QObject>
#include <QQmlApplicationEngine>

class info_panel_model;

class core_info_panel : public QObject
{
    Q_OBJECT
public:
    explicit core_info_panel(QObject *parent = nullptr);

    // read file settings
    bool initialization();
    // program launch
    void program_launch(bool is_init_state);

signals:

public slots:

private:
    info_panel_model* ptr_info_panel_model {Q_NULLPTR};

    QQmlApplicationEngine* ptr_engine {Q_NULLPTR};
};

#endif // CORE_SWEEP_REMOTE_CONTROL_H
