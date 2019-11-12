#ifndef SYSTEM_INFO_MODEL_H
#define SYSTEM_INFO_MODEL_H

#include <QAbstractTableModel>
#include "system_info.h"

class system_info_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum data_role {
        DATAROLE_PARAMETER_NAME = Qt::UserRole + 1,
        DATAROLE_PARAMETER_VALUE
    };

    enum model_columns {
        MC_PARAMETER_NAME,
        MC_PARAMETER_VALUE
    };

    explicit system_info_model(QObject *parent = Q_NULLPTR);
    ~system_info_model() Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    void add_data_to_model(const system_info &value);
    void remove_data_from_model();

private:
    QMap<int, QString> m_columns_map;
    QVector<system_info> m_data;
};

#endif // SYSTEM_INFO_MODEL_H
