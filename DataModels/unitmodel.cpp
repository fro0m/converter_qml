#include "unitmodel.h"

UnitModel::UnitModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames[NameRole] = "name";
    m_roleNames[CategoryRole] = "category";
    m_roleNames[CategoryNameRole] = "categoryName";
    m_roleNames[CoefficientRole] = "coefficient";
}

UnitModel::~UnitModel()
{

}

QVariant UnitModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "data() is called. index.row()" << index.row();
    if(!index.isValid()) {
        qDebug() << "index is not valid";
        return QVariant();
    }
    int row = index.row();
    switch(role) {
    case NameRole:
        qDebug() << "name role fetched";
        return m_modelsByCategory[category].at(row)->name();
    case CategoryRole:
        qDebug() << "Category role fetched";
        return m_modelsByCategory[category].at(row)->category();
    case CategoryNameRole:
        qDebug() << "CategoryName role fetched";
        return m_modelsByCategory[category].at(row)->categoryName();
    case CoefficientRole:
        qDebug() << "Coefficient role fetched";
        return m_modelsByCategory[category].at(row)->coefficient();
    }
    return QVariant();
}

void UnitModel::updateCategory(Unit::Category category_)
{
    category = category_;//change key in ModelsByCategory to get new Model
    emit beginResetModel();
    emit endResetModel();
}

void UnitModel::updateCategory(int category_)
{
    updateCategory((Unit::Category)category_);
}

void UnitModel::setModelsByCategory(const QHash<Unit::Category, QList<Unit *> > &newModelsByCategory) {
    m_modelsByCategory = newModelsByCategory;
}

double UnitModel::getCoefficient(int row_) const
{
    qDebug() << "getCoefficient is called";
    return data(createIndex(row_, 0), CoefficientRole)
            .value<double>();
}

QHash<int, QByteArray> UnitModel::roleNames() const
{
    return m_roleNames;
}

int UnitModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug() << "rowCount is called. row is " << m_modelsByCategory[category].size();
    return m_modelsByCategory[category].size();;
}
