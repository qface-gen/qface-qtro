{# Copyright (c) Pelagicore AB 2016 #}
{% set class = 'Abstract{0}'.format(interface) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include <QtCore>
#include <QtRemoteObjects>

#include "{{interface|lower}}replica.h"
{% for property in interface.properties %}
{% if property.type.is_model and property.type.nested.is_complex %}
#include "{{property.type.nested|lower}}model.h"
{% endif %}
{% endfor %}
#include "variantmodel.h"
{% for struct in module.structs %}
#include "{{struct|lower}}.h"
{% endfor %}
{% for enum in module.enums %}
#include "{{enum|lower}}.h"
{% endfor %}

class {{class}} : public QObject
{
    Q_OBJECT
{% for property in interface.properties %}
{% if property.type.is_model %}
    Q_PROPERTY(QAbstractItemModelReplica* {{property}} READ {{property}})
{% else %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} {% if not property.readonly %}WRITE set{{property|upperfirst}} {% endif %}{% if not property.const %}NOTIFY {{property}}Changed{% endif %})
{% endif %}
{% endfor %}

public:
    {{class}}(QObject *parent = nullptr);
    ~{{class}}();

public Q_SLOTS:
{% for operation in interface.operations %}
    virtual {{operation|returnType}} {{operation}}({{operation.parameters|map('parameterType')|join(', ')}});
{% endfor %}

public:
{% for property in interface.properties if not property.type.is_model %}
    virtual void set{{property|upperfirst}}({{ property|parameterType }});
    virtual {{property|returnType}} {{property}}() const;
{% endfor %}
{% for property in interface.properties if property.type.is_model %}
    QAbstractItemModelReplica* {{property}}() const;
{% endfor %}

Q_SIGNALS:
{% for signal in interface.signals %}
    void {{signal}}({{signal.parameters|map('parameterType')|join(', ')}});
{% endfor %}
{% for property in interface.properties %}
    void {{property}}Changed();
{% endfor %}

protected:
    void setupConnections();

private:
    {{interface}}Replica* m_replica;
{% for property in interface.properties if property.type.is_model %}
    QAbstractItemModelReplica *m_{{property|lowerfirst}};
{% endfor %}
};
