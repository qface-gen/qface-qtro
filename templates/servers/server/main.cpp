#include <QtCore>
#include <QtRemoteObjects>

{% for interface in module.interfaces %}
#include "{{interface|lower}}service.h"
{% endfor %}

void registerModel(QRemoteObjectHostBase* host, QAbstractItemModel* model, const QString& name)
{
    Q_ASSERT(host);
    Q_ASSERT(model);
    QVector<int> roles = model->roleNames().keys().toVector();
    host->enableRemoting(model, name, roles);
    qDebug() << "model at: " << name;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QRemoteObjectRegistryHost host(QUrl("local:{{module}}"));
    qDebug() << "registry at: " << host.registryUrl().toString();

{% for interface in module.interfaces %}
    // create {{interface}} service
    QScopedPointer<{{interface}}Service> {{interface|lowerfirst}}Service(new {{interface}}Service);
    host.enableRemoting({{interface|lowerfirst}}Service.data(), "{{interface.qualified_name}}");
    qDebug() << "service at: {{interface.qualified_name}}";
{% for property in interface.properties if property.type.is_model %}
    registerModel(&host, {{interface|lowerfirst}}Service->{{property}}(), "{{property.qualified_name}}");
{% endfor %}

{% endfor %}
    return a.exec();
}
