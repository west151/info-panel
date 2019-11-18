#include "message_log_model.h"

message_log_model::message_log_model(QObject *parent): QAbstractTableModel(parent)
{
    m_columns_map.insert(MC_LOG_ID, tr("наименование"));
    m_columns_map.insert(MC_LOG_TEXT, tr("значение"));
}

message_log_model::~message_log_model()
{
}

int message_log_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_columns_map.size();
    else
        return 0;
}

QVariant message_log_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if ((index.row() >= 0) && (index.row() < m_data.size())) {
            const auto &param = m_data.at(index.row());
            switch(role){
            case Qt::DisplayRole: {
                switch (index.column()) {
                case MC_LOG_ID:
                    return param.message_log_id();
                case DATAROLE_LOG_TEXT:
                    return param.message_log_text();
                default:
                    break;
                }
                break;
            }
            case DATAROLE_LOG_ID:
                return param.message_log_id();
            case DATAROLE_LOG_TEXT:
                return  param.message_log_text();
            default:
                Q_ASSERT("Не установлен обработчик возвращаемого результата");
                break;
            }
        }
    }
    return QVariant();
}

QVariant message_log_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role != Qt::DisplayRole) && (role != Qt::ToolTipRole))
        return QVariant();
    if ((section < 0) || (section >= m_columns_map.size()))
        return QVariant();
    return (orientation == Qt::Horizontal) ? QVariant::fromValue(m_columns_map.value(section))
                                           : QVariant::fromValue(section + 1);
}

QHash<int, QByteArray> message_log_model::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {DATAROLE_LOG_ID, "message_log_id"},
        {DATAROLE_LOG_TEXT, "message_log_text"}
    };
    return roles;
}

int message_log_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

bool message_log_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void message_log_model::slot_add_data_to_model(const message_log &value)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(value);
    endInsertRows();
}

void message_log_model::slot_remove_data_from_model()
{
    if(m_data.size()>0) {
        beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
        m_data.clear();
        endRemoveRows();
    }
}
