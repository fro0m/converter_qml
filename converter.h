#ifndef CONVERTER_H
#define CONVERTER_H

#include <QQuickItem>

//#include <cmath>

#include "DataTypes/numberofunits.h"
#include "DataModels/unitmodel.h"

class Converter : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Converter)
    Q_CLASSINFO("DefaultProperty", "units")

    Q_PROPERTY(QQmlListProperty<Unit> units READ units NOTIFY unitsChanged)//units taken from QML as Unit objects
    Q_PROPERTY(QList<QObject *> categoryModel READ categoryModel NOTIFY categoryModelChanged)
    Q_PROPERTY(QVariant sourceUnitModel READ sourceUnitModel NOTIFY sourceUnitModelChanged)
    Q_PROPERTY(QVariant convertedUnitModel READ convertedUnitModel NOTIFY convertedUnitModelChanged)
    //source and converted values
    Q_PROPERTY(double convertedValue READ convertedValue WRITE setConvertedValue NOTIFY convertedValueChanged)
    Q_PROPERTY(double sourceValue READ sourceValue WRITE setSourceValue NOTIFY sourceValueChanged)
public:
    Converter(QQuickItem *parent = 0);
public:// properties getters
    QQmlListProperty<Unit> units();
    int unitCount() const;
    Unit *unit(int index) const;
    QList<QObject *> categoryModel();
public://source and converted
    QVariant sourceUnitModel();
    QVariant convertedUnitModel();

    double convertedValue() const;
    double sourceValue() const;
public://service
    Q_INVOKABLE int getModelCategory(int index); //fetch category from CategoryModel
    Q_INVOKABLE void convert(const double sourceCoefficient, const double convertedCoefficient);
    /*Q_INVOKABLE int modifyFactor() {//TODO
        qDebug() << "modifyFactor";
        for(int i = 0; i < m_convertedUnitModel.rowCount(QModelIndex()); i++) {
            //dbg qDebug() << m_convertedUnitModel.getCoefficient(i);
            if(m_convertedValue * m_convertedUnitModel.getCoefficient(i) )
        }
        return i;//new index for convertedUnitModel
    }*/

private: //models
    QList<QObject *> m_categoryDataModel;
    UnitModel m_sourceUnitModel; //{modelsByCategory, 0}; we have to initialize after
    UnitModel m_convertedUnitModel;
private://properties

private://source and converted data
    double m_convertedValue;
    double m_sourceValue;
private: //service
    bool initialized = false;
    QList<Unit*> m_units;
    QHash<Unit::Category, QList<Unit *> > modelsByCategory;

public slots://service
    void initialize();//set up data models from object config
public slots://source and converted
    void setSourceValue(const double newSourceValue);
    void setConvertedValue(const double newConvertedValue);

signals:
    void unitsChanged();
    void categoryModelChanged();
    void sourceUnitModelChanged();
    void convertedUnitModelChanged();
signals://source and converted
    void sourceValueChanged(const double newSourceValue);
    void convertedValueChanged(const double newConvertedValue);
};


#endif // CONVERTER_H
