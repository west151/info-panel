#ifndef CPU_USAGE_MODEL_H
#define CPU_USAGE_MODEL_H

#include <QAbstractTableModel>

class cpu_usage_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum data_role {
        DATAROLE_CPU_NAME = Qt::UserRole + 1,
        DATAROLE_CPU_USAGE
    };

    enum model_columns {
        MC_CPU_NAME,
        MC_CPU_USAGE
    };

    cpu_usage_model(QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

public slots:
    void slot_add_data_to_model(const QVariantMap &value);

private:
    QMap<int, QString> m_columns_map;
    QVector<QPair<QString, double> > m_data;

    bool is_cpu_name(const QString &);
};

#endif // CPU_USAGE_MODEL_H
