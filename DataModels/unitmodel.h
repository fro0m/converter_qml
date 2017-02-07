#ifndef UnitModel_H
#define UnitModel_H

#include <QObject>
#include <QAbstractListModel>

#include "DataTypes/unit.h"

class UnitModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoleNames {
        NameRole = Qt::UserRole+1,
        CategoryRole = Qt::UserRole+2,
        CategoryNameRole = Qt::UserRole+3,
        CoefficientRole = Qt::UserRole+4
    };

    //explicit UnitModel(const QHash<Unit::Category, QList<Unit *> > &modelsByCategory_ = QHash<Unit::Category , QList<Unit *> >(), QObject *parent = 0);
    explicit UnitModel(QObject *parent = 0);
    ~UnitModel();


public: // interface QAbstractListModel
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
public: //service
    void setModelsByCategory(const QHash<Unit::Category, QList<Unit *> > & newModelsByCategory);
    Q_INVOKABLE double getCoefficient(int row_) const;
    Q_INVOKABLE void updateCategory(Unit::Category category_);
    Q_INVOKABLE void updateCategory(int category_);

signals:
    void countChanged(int arg);

protected: // interface QAbstractListModel
    virtual QHash<int, QByteArray> roleNames() const;
private:
    QHash<int, QByteArray> m_roleNames;

    QHash<Unit::Category, QList<Unit *> > m_modelsByCategory;
    Unit::Category category;
};
#endif // UnitModel_H
