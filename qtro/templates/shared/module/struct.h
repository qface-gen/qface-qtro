{% set class = '{0}'.format(struct) %}
/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#ifndef {{class|upper}}_H
#define {{class|upper}}_H


#include <QtCore>

{{module|open_ns}}

class {{class}}Data;

class {{class}}
{
    Q_GADGET
{% for field in struct.fields %}
    Q_PROPERTY({{field|ns}}{{field|returnType}} {{field}} READ {{field}} WRITE set{{field|upperfirst}})
{% endfor %}

public:
    {{class}}();
    {{class}}(const {{class}} &other);
    ~{{class}}();

    static void registerTypes(const char* uri="{{module}}");
    Q_INVOKABLE {{class}} clone();

    {{class}} &operator=(const {{class}} &other);

{% for field in struct.fields %}
    void set{{field|upperfirst}}({{field|parameterType}});
    {{field|returnType}} {{field}}() const;

{% endfor %}

    QDataStream& toStream(QDataStream& stream) const;
    QDataStream& fromStream(QDataStream& stream);
    bool operator==(const {{class}} &other) const;
    bool operator!=(const {{class}} &other) const;
private:
    QExplicitlySharedDataPointer <{{class}}Data> d;
};


{{module|close_ns}}

QDataStream &operator<<(QDataStream &ds, const {{module|ns}}{{class}} &obj);
QDataStream &operator>>(QDataStream &ds, {{module|ns}}{{class}} &obj);

Q_DECLARE_METATYPE({{module|ns}}{{class}})

#endif // {{class|upper}}_H
