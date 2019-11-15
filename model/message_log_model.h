#ifndef MESSAGE_LOG_MODEL_H
#define MESSAGE_LOG_MODEL_H

#include <QAbstractTableModel>
#include "message_log.h"

class message_log_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum data_role {
        DATAROLE_LOG_ID = Qt::UserRole + 1,
        DATAROLE_LOG_TEXT
    };

    enum model_columns {
        MC_LOG_ID,
        MC_LOG_TEXT
    };

    explicit message_log_model(QObject *parent = Q_NULLPTR);
    ~message_log_model() Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

    void add_data_to_model(const message_log &value);
    void remove_data_from_model();

private:
    QMap<int, QString> m_columns_map;
    QVector<message_log> m_data;
};

#endif // MESSAGE_LOG_MODEL_H
