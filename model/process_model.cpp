#include "process_model.h"


process_model::process_model(QObject *parent): QAbstractTableModel(parent)
{
    m_columns_map.insert(MC_USER, tr("user"));
    m_columns_map.insert(MC_PID, tr("pid"));
    m_columns_map.insert(MC_CPU, tr("cpu"));
    m_columns_map.insert(MC_MEM, tr("mem"));
    m_columns_map.insert(MC_COMMAND, tr("command"));
}

process_model::~process_model()
{

}

int process_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_columns_map.size();
    else
        return 0;
}

QVariant process_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        if ((index.row() >= 0) && (index.row() < m_data.size())) {
            const auto &param = m_data.at(index.row());
            switch(role){
            case Qt::DisplayRole: {
                switch (index.column()) {
                case MC_USER:
                    return param.user();
                case MC_PID:
                    return param.pid();
                case MC_CPU:
                    return param.cpu_usage();
                case MC_MEM:
                    return param.mem_usage();
                case MC_COMMAND:
                    return param.command();
                default:
                    break;
                }
                break;
            }
            case DATAROLE_USER:
                return param.user();
            case DATAROLE_PID:
                return param.pid();
            case DATAROLE_CPU:
                return  param.cpu_usage();
            case DATAROLE_MEM:
                return  param.mem_usage();
            case DATAROLE_COMMAND:
                return  param.command();
            default:
                break;
            }
        }
    }
    return QVariant();
}

QVariant process_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role != Qt::DisplayRole) && (role != Qt::ToolTipRole))
        return QVariant();
    if ((section < 0) || (section >= m_columns_map.size()))
        return QVariant();
    return (orientation == Qt::Horizontal) ? QVariant::fromValue(m_columns_map.value(section))
                                           : QVariant::fromValue(section + 1);
}

QHash<int, QByteArray> process_model::roleNames() const
{
    static QHash<int, QByteArray> roles {
        {DATAROLE_USER, "user"},
        {DATAROLE_PID, "pid"},
        {DATAROLE_CPU, "cpu"},
        {DATAROLE_MEM, "mem"},
        {DATAROLE_COMMAND, "command"}
    };
    return roles;
}

int process_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

bool process_model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void process_model::slot_add_data_to_model(const process_info &value)
{
    if(is_pid(value)) {
        for(int i = 0; i < m_data.size(); ++i )
            if(m_data.at(i).pid() == value.pid()){
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

void process_model::slot_remove_data_from_model()
{
    if(m_data.size()>0) {
        beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
        m_data.clear();
        endRemoveRows();
    }
}

bool process_model::is_pid(const process_info &info)
{
    for(int i = 0; i < m_data.size(); ++i )
        if(m_data.at(i).pid() == info.pid())
            return true;

    return false;
}
