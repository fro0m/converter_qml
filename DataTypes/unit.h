#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QMetaEnum>
#include <QDebug>

class Unit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Category category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(double coefficient READ coefficient WRITE setCoefficient NOTIFY coefficientChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString categoryName READ categoryName WRITE setCategoryName NOTIFY categoryNameChanged)

public:
    enum Category {
        Pressure,
        Length,
        Luminance,
        LuminousEnergy,
        LuminousIntensity,
        MagneticField,
        MagnetomotiveForce,
        MolarMass,
        Power,
        RadioactiveDecay,
        RadioactivityEquivalentDose,
        Speed,
        Temperature,
        Volume,
        Weight
    };
    Q_ENUM(Category)

private:
    Category m_category;
    double m_coefficient = 1;
    QString m_name;
    QString m_categoryName;

    QMetaEnum metaCategory = QMetaEnum::fromType<Category>();


public:
    explicit Unit(QObject *parent = 0);


    /*Q_INVOKABLE*/ Category category() const; //NOTE Q_INVOKABLE?
    void setCategory(const Category& newCategory);

    double coefficient() const;
    void setCoefficient(const double &newCoefficient);

    QString name() const;
    void setName(const QString &newName);

    QString categoryName() const;
    void setCategoryName(const QString &newCategoryName);

signals:
    void categoryChanged(const Category newCategory);
    void coefficientChanged(const double NewCoefficient);
    void nameChanged(const QString &NewName);
    void categoryNameChanged(const QString &NewCategoryName);


public slots:
};
#endif // UNIT_H
