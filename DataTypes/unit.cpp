#include "unit.h"

Unit::Unit(QObject *parent) : QObject(parent)
{
    //    metaCategory = QMetaEnum::fromType<Category>();
}

Unit::Category Unit::category() const {return m_category;}

void Unit::setCategoryName(const QString &newCategoryName)
{
    m_categoryName = newCategoryName;
    emit categoryNameChanged(m_categoryName);
}

void Unit::setCategory(const Category& newCategory) {
    m_category = newCategory;
    setCategoryName(metaCategory.valueToKey(m_category));
    emit categoryChanged(m_category);
}

double Unit::coefficient() const {return m_coefficient;}

void Unit::setCoefficient(const double &newCoefficient) {m_coefficient = newCoefficient;}

QString Unit::name() const {return m_name;}

void Unit::setName(const QString &newName) {m_name = newName;}



QString Unit::categoryName() const {
    return m_categoryName;
    qWarning() << "reading category name========";
}

