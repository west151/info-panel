#include "bluetooth_device_model.h"

bluetooth_device_model::bluetooth_device_model(QObject *parent): QAbstractTableModel(parent)
{
    m_columns_map.insert(MC_ADDRESS, tr("address"));
    m_columns_map.insert(MC_NAME, tr("name"));
    m_columns_map.insert(MC_DATE_TIME, tr("date_time"));
}

bluetooth_device_model::~bluetooth_device_model()
{
}

int bluetooth_device_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_columns_map.size();
    else
        return 0;
}

QVariant bluetooth_device_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if ((index.row() >= 0) && (index.row() < m_data.size())) {
            const auto &param = m_data.at(index.row());
            switch(role){
            case Qt::DisplayRole: {
                switch (index.column()) {
                case MC_DATE_TIME:
                    return param.date_time().toLocalTime();
                case MC_ADDRESS:
                    return param.address();
                case MC_NAME:
                    return param.name();
                default:
                    break;
                }
                break;
            }
            case DATAROLE_DATE_TIME:
                return param.date_time().toLocalTime();
            case DATAROLE_ADDRESS:
                return param.address();
            case DATAROLE_NAME:
                return  param.name();
            default:
                break;
            }
        }
    }
    return QVariant();
}

QVariant bluetooth_device_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role != Qt::DisplayRole) && (role != Qt::ToolTipRole))
        return QVariant();
    if ((section < 0) || (section >= m_columns_map.size()))
        return QVariant();
    return (orientation == Qt::Horizontal) ? QVariant::fromValue(m_columns_map.value(section))
                                           : QVariant::fromValue(section + 1);
}

QHash<int, QByteArray> bluetooth_device_model::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {DATAROLE_ADDRESS, "address"},
        {DATAROLE_NAME, "name"},
        {DATAROLE_DATE_TIME, "date_time"}
    };
    return roles;
}

int bluetooth_device_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

bool bluetooth_device_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void bluetooth_device_model::slot_add_data_to_model(const bluetooth_device_info &value)
{
    if(is_address(value)) {
        for(int i = 0; i < m_data.size(); ++i )
            if(m_data.at(i).address() == value.address()){
                beginResetModel();
                m_data[i] = value;
                endResetModel();
            }
    } else {
        beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
        m_data.append(value);
        endInsertRows();
    }
}

void bluetooth_device_model::slot_remove_data_from_model()
{
    if(m_data.size()>0) {
        beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
        m_data.clear();
        endRemoveRows();
    }
}

bool bluetooth_device_model::is_address(const bluetooth_device_info &info)
{
    for(int i = 0; i < m_data.size(); ++i )
        if(m_data.at(i).address() == info.address())
            return true;

    return false;
}
