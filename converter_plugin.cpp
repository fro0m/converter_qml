#include "converter_plugin.h"
#include "converter.h"

#include <qqml.h>

void ConverterPlugin::registerTypes(const char *uri)
{
    // @uri frumkin
    qmlRegisterType<Converter>(uri, 1, 0, "Converter");
    qmlRegisterType<Unit>(uri, 1, 0, "Unit");
}


