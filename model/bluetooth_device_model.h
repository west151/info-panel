#ifndef BLUETOOTH_DEVICE_MODEL_H
#define BLUETOOTH_DEVICE_MODEL_H

#include <QAbstractTableModel>

#include "bluetooth_device_info.h"

class bluetooth_device_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum data_role {
        DATAROLE_ADDRESS = Qt::UserRole + 1,
        DATAROLE_NAME
    };

    enum model_columns {
        MC_ADDRESS,
        MC_NAME
    };

    explicit bluetooth_device_model(QObject *parent = Q_NULLPTR);
    ~bluetooth_device_model() Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

public slots:
    void slot_add_data_to_model(const bluetooth_device_info &value);
    void slot_remove_data_from_model();

private:
    QMap<int, QString> m_columns_map;
    QVector<bluetooth_device_info> m_data;
};

#endif // BLUETOOTH_DEVICE_MODEL_H
