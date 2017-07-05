{% set class = '{0}AbstractSource'.format(interface) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#include "{{interface|lower}}abstractsource.h"


{{class}}::{{class}}(QObject *parent)
    : {{interface}}SimpleSource(parent)
{% for property in interface.properties if property.type.is_model %}
{% if property.type.nested.is_primitive %}
    , m_{{property}}(new VariantModel(this))
{% else %}
    , m_{{property}}(new {{property.type.nested|upperfirst}}Model(this))
{% endif %}
{% endfor %}
{
}

{% for property in interface.properties if property.type.is_model %}
{% if property.type.nested.is_primitive %}
VariantModel* {{class}}::{{property}}() const
{
    return m_{{property}};
}
{% else %}
{{property.type.nested|upperfirst}}Model* {{class}}::{{property}}() const
{
    return m_{{property}};
}
{% endif %}
{% endfor %}

{% for operation in interface.operations %}
{{operation|returnType}} {{class}}::{{operation}}({{operation|parameters}})
{
    qDebug() << "{{class}}::{{operation}}(...): Not implemented";
    {% for parameter in operation.parameters %}
    Q_UNUSED({{parameter}})
    {% endfor %}
}
{% endfor %}
