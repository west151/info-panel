#include "system_info_model.h"

system_info_model::system_info_model(QObject *parent): QAbstractTableModel(parent)
{
    m_columns_map.insert(MC_PARAMETER_NAME, tr("наименование"));
    m_columns_map.insert(MC_PARAMETER_VALUE, tr("значение"));
}

system_info_model::~system_info_model()
{

}

int system_info_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_columns_map.size();
    else
        return 0;
}

QVariant system_info_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if ((index.row() >= 0) && (index.row() < m_data.size())) {
            const auto &param = m_data.at(index.row());
            switch(role){
            case Qt::DisplayRole: {
                switch (index.column()) {
                case MC_PARAMETER_NAME:
                    return param.parameter_name();
                case DATAROLE_PARAMETER_VALUE:
                    return param.parameter_value();
                default:
                    break;
                }
                break;
            }
            case DATAROLE_PARAMETER_NAME:
                return param.parameter_name();
            case DATAROLE_PARAMETER_VALUE:
                return  param.parameter_value();
            default:
                Q_ASSERT("Не установлен обработчик возвращаемого результата");
                break;
            }
        }
    }
    return QVariant();
}

QVariant system_info_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role != Qt::DisplayRole) && (role != Qt::ToolTipRole))
        return QVariant();
    if ((section < 0) || (section >= m_columns_map.size()))
        return QVariant();
    return (orientation == Qt::Horizontal) ? QVariant::fromValue(m_columns_map.value(section))
                                           : QVariant::fromValue(section + 1);
}

QHash<int, QByteArray> system_info_model::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {DATAROLE_PARAMETER_NAME, "parameter"},
        {DATAROLE_PARAMETER_VALUE, "value"}
    };
    return roles;
}

int system_info_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

bool system_info_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void system_info_model::add_data_to_model(const system_info &value)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(value);
    endInsertRows();
}

void system_info_model::remove_data_from_model()
{
    if(m_data.size()>0) {
        beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
        m_data.clear();
        endRemoveRows();
    }
}
