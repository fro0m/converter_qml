#include "converter.h"

/*Converter::Converter(QQuickItem *parent):
    QQuickItem(parent)
{
    m_sourceValue = 0;
    m_convertedValue = 0;
    //dbg qDebug() << m_sourceUnits.at(1);

    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

Converter::~Converter()
{
}


void Converter::setSourceValue(const double newSourceValue)
{
    //isNaN check
    if (newSourceValue == newSourceValue) m_sourceValue = newSourceValue;
    else return;

    convert(m_sourceValue);
    //if (m_source == source)
     //   return;

    //m_source = source;
    emit sourceValueChanged(m_sourceValue);
}

void Converter::setConvertedValue(const double newConvertedValue)
{
    m_convertedValue = newConvertedValue;
    emit convertedValueChanged(m_convertedValue);
}

void Converter::convert(const double &sourceValue_) {
    //converts in proportion convertedValue = 2*sourcevalue
    double  coefficient = ConvertionCoefficients[m_sourceComboBoxIndex]
            / ConvertionCoefficients[m_convertedComboBoxIndex];
     //double tempSourceValue = sourceValue_ / ConvertionCoefficients[]
    setConvertedValue(coefficient * sourceValue_);
}
*/


Converter::Converter(QQuickItem *parent):
    QQuickItem(parent)
{
    setObjectName("ConverterObject");
}

QQmlListProperty<Unit> Converter::units()
{

    return QQmlListProperty<Unit>(this, m_units);

}

int Converter::unitCount() const
{
    return m_units.size();
}

Unit *Converter::unit(int index) const
{
    return m_units.at(index);
}

QList<QObject *> Converter::categoryModel()
{
    qWarning() << "getting categoryModel";
    if(!initialized) {
        initialize();
        initialized = true;
    }
    return m_categoryDataModel;
}

QVariant Converter::sourceUnitModel()
{
    qDebug() << "Returning source unit model";
    return QVariant::fromValue<QObject *>(&m_sourceUnitModel);
}

QVariant Converter::convertedUnitModel()
{
    qDebug() << "Returning converted unit model";
    return QVariant::fromValue<QObject *>(&m_convertedUnitModel);
}

double Converter::convertedValue() const {
    return m_convertedValue;
}

double Converter::sourceValue() const {
    return m_sourceValue;
}

int Converter::getModelCategory(int index) {
    qDebug() << "getModelCategory is called, Index is " << index;
    Unit::Category tempCategory = qobject_cast<Unit *>(m_categoryDataModel.at(index))->category();
    return (int)tempCategory;
}

void Converter::convert(const double sourceCoefficient, const double convertedCoefficient)
{
    qDebug() << "sourceValue is "<< m_sourceValue << "convert function called with coefficient " << sourceCoefficient << convertedCoefficient <<
                "value is " << m_sourceValue * convertedCoefficient / sourceCoefficient;
    setConvertedValue(m_sourceValue * convertedCoefficient / sourceCoefficient);
    //emit convertedValueChanged(m_convertedValue);
}

void Converter::initialize()
{
    qWarning() << "initizalization started--------------" << unitCount();

    for(int i = 0; i < unitCount(); i++) {

        Unit *tempUnit = unit(i);
        modelsByCategory[tempUnit->category()] << unit(i); //.append(*tempUnit);
        //modelsByCategory[tempUnit->category()].value().setName(unit(i)->name());
    }

    //dbg qWarning() << "number of categories " << modelsByCategory.size();

    for(auto i = modelsByCategory.begin(); i != modelsByCategory.end(); i++) {
        //qWarning() << 3;
        //put at first place etalon element with coefficient = 1
        for (int g = 0; g < i.value().size(); g++) {
            if (i.value().at(g)->coefficient() == 1) {
                i.value().swap(0, g);
                //taking our category as Unit obj from first element (etalon element)
                m_categoryDataModel << qobject_cast<QObject *>(i.value().at(0));
                break;
            }
            else if (g == i.value().size() - 1)
                qWarning() << i.value().at(g)->categoryName() << " has no etalon element with coefficient = 1 and has been ignored";
        }
        //qWarning() << " ";
    }
    //dbg checking sizes of datamodel
    for (int k = Unit::Pressure; k <= Unit::Weight; k++) {
        qWarning() << "size of  ModelsByCategory[" << k << "] is " << modelsByCategory[(Unit::Category)k].size();
    }

    m_sourceUnitModel.setModelsByCategory(modelsByCategory); //setting up a initialized ModelsByCategory hash
    m_convertedUnitModel.setModelsByCategory(modelsByCategory);
    //dbg qWarning() << metaCategory.valueToKey(2);
    qWarning() << "initizalization finished--------------" << unitCount();

}

void Converter::setSourceValue(const double newSourceValue)
{
    m_sourceValue = newSourceValue;
    emit sourceValueChanged(m_sourceValue);
}

void Converter::setConvertedValue(const double newConvertedValue)
{
    m_convertedValue = newConvertedValue;
    emit convertedValueChanged(m_convertedValue);
}

