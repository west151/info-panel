#ifndef INFO_PANEL_MODEL_H
#define INFO_PANEL_MODEL_H

#include <QObject>

class info_panel_model : public QObject
{
    Q_OBJECT
public:
    explicit info_panel_model(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INFO_PANEL_MODEL_H
