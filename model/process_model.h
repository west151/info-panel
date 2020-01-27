#ifndef PROCESS_MODEL_H
#define PROCESS_MODEL_H

#include <QAbstractTableModel>

#include "process_info.h"

class process_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum data_role {
        DATAROLE_TIME_UPDATE = Qt::UserRole + 1,
        DATAROLE_USER,
        DATAROLE_PID,
        DATAROLE_CPU,
        DATAROLE_MEM,
        DATAROLE_COMMAND
    };

    enum model_columns {
        MC_TIME_UPDATE,
        MC_USER,
        MC_PID,
        MC_CPU,
        MC_MEM,
        MC_COMMAND
    };

    explicit process_model(QObject *parent = Q_NULLPTR);
    ~process_model() Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

public slots:
    //void slot_add_data_to_model(const process_info &);
    void slot_add_data_to_model(const QVector<process_info> &);
    //void slot_remove_data_from_model();

private:
    QMap<int, QString> m_columns_map;
    QVector<process_info> m_data;
};

#endif // PROCESS_MODEL_H
