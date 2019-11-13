#ifndef INFO_PANEL_MODEL_H
#define INFO_PANEL_MODEL_H

#include <QObject>
#include <QDateTime>

class QTimer;

class info_panel_model : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString system_time READ system_time NOTIFY signal_time_changed)
public:
    explicit info_panel_model(QObject *parent = nullptr);

    void start();
    QString system_time()const;

signals:
    void signal_time_changed();

private:
    QDateTime m_system_time;
    QTimer *m_timer;

private slots:
    void slot_system_time_update();
};

#endif // INFO_PANEL_MODEL_H
