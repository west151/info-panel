#include "cpu_usage_model.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

cpu_usage_model::cpu_usage_model(QObject *parent) : QAbstractTableModel(parent)
{
    m_columns_map.insert(MC_CPU_NAME, tr("cpu_name"));
    m_columns_map.insert(MC_CPU_USAGE, tr("cpu_usage"));
}

int cpu_usage_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_columns_map.size();
    else
        return 0;
}

QVariant cpu_usage_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if ((index.row() >= 0) && (index.row() < m_data.size())) {
            const auto &param = m_data.at(index.row());
            switch(role){
            case Qt::DisplayRole: {
                switch (index.column()) {
                case MC_CPU_NAME:
                    return param.first;
                case MC_CPU_USAGE:
                    return param.second;
                default:
                    break;
                }
                break;
            }
            case DATAROLE_CPU_NAME:
                return param.first;
            case DATAROLE_CPU_USAGE:
                return param.second;
            default:
                break;
            }
        }
    }
    return QVariant();
}

QVariant cpu_usage_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role != Qt::DisplayRole) && (role != Qt::ToolTipRole))
        return QVariant();
    if ((section < 0) || (section >= m_columns_map.size()))
        return QVariant();
    return (orientation == Qt::Horizontal) ? QVariant::fromValue(m_columns_map.value(section))
                                           : QVariant::fromValue(section + 1);
}

QHash<int, QByteArray> cpu_usage_model::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {DATAROLE_CPU_NAME, "cpu_name"},
        {DATAROLE_CPU_USAGE, "cpu_usage"}
    };
    return roles;
}

int cpu_usage_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

void cpu_usage_model::slot_add_data_to_model(const QVariantMap &value)
{
    const QStringList cpu_names(value.keys());

    for(int i = 0; i < cpu_names.size(); ++i )
    {
        const auto cpu_name = cpu_names.at(i);

        QPair<QString, double> data(cpu_name, value.value(cpu_name).toLongLong());

        if(is_cpu_name(cpu_name))
        {
            beginResetModel();
            m_data[i] = data;
            endResetModel();
        }else{
            beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
            m_data.append(data);
            endInsertRows();
        }
    }
}

bool cpu_usage_model::is_cpu_name(const QString &value)
{
    for(int i = 0; i < m_data.size(); ++i )
        if(m_data.at(i).first == value)
            return true;

    return false;
}
