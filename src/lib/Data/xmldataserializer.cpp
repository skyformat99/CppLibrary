#include "xmldataserializer.h"

XmlDataSerializer::XmlDataSerializer()
{

}

XmlDataSerializer::~XmlDataSerializer()
{

}

QString XmlDataSerializer::Serialize(DataObject& obj)
{
    QDomDocument doc;
    this->Serialize(obj, doc);

    return doc.toString();
}

void XmlDataSerializer::Serialize(DataObject& obj, QFile& file)
{
    auto str = this->Serialize(obj);

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    try {
        QTextStream stream(&file);
        stream << str;
    } catch(...) {
        file.close();
        throw;
    }
    file.close();
}

void XmlDataSerializer::Serialize(DataObject& obj, QDomDocument& doc)
{
    auto node = doc.createElement(obj.metaObject()->className());

    this->SerializeContent(obj, doc, node);

    doc.appendChild(node);
}

void XmlDataSerializer::Serialize(DataObject& obj, QDomDocument& doc, QDomNode& parent)
{
    auto node = doc.createElement(obj.metaObject()->className());

    this->SerializeContent(obj, doc, node);

    parent.appendChild(node);
}

void XmlDataSerializer::SerializeContent(DataObject& obj, QDomDocument& doc, QDomNode& node)
{
    auto metaObject = obj.metaObject();
    for(auto i = 1; i < metaObject->propertyCount(); i++)
    {
        QString tName(metaObject->property(i).typeName());
        auto pName = metaObject->property(i).name();
        auto prop = doc.createElement(pName);

        if(tName.endsWith("*"))
        {
            DataObject& fObj = *obj.property(pName).value<DataObject*>();
            this->Serialize(fObj, doc, prop);
        }
        else if(tName.startsWith("QList<"))
        {
            auto isRef = tName.endsWith("*>");
            QSequentialIterable iterable = obj.property(pName).value<QSequentialIterable>();
            foreach(const QVariant& item, iterable)
            {
                if(isRef)
                {
                    DataObject& fObj = *item.value<DataObject*>();
                    this->Serialize(fObj, doc, prop);
                }
                else
                {
                    auto elem = doc.createElement(item.typeName());
                    auto txt = doc.createTextNode(item.toString());
                    elem.appendChild(txt);
                    prop.appendChild(elem);
                }
            }
        }
        else
        {
            auto txt = doc.createTextNode(obj.property(pName).toString());
            prop.appendChild(txt);
        }
        node.appendChild(prop);
    }
}

DataObject* XmlDataSerializer::Deserialize(QString& text)
{
    QDomDocument doc;
    doc.setContent(text);

    return this->Deserialize(doc);

}

DataObject* XmlDataSerializer::Deserialize(QFile& file)
{
    QString str;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    try {
        QTextStream stream(&file);
        str = stream.readAll();
    } catch(...) {
        file.close();
        throw;
    }
    file.close();

    auto obj = this->Deserialize(str);
    return obj;
}

DataObject* XmlDataSerializer::Deserialize(QDomDocument& doc)
{
    auto root = doc.firstChild();
    auto obj = DataObjectFactory::createInstance(root.nodeName());
    this->DeserializeContent(root, *obj);

    return obj;
}

DataObject* XmlDataSerializer::Deserialize(QDomNode& node)
{
    auto obj = DataObjectFactory::createInstance(node.nodeName());
    this->DeserializeContent(node, *obj);

    return obj;
}

void XmlDataSerializer::DeserializeContent(QDomNode& node, DataObject& obj)
{
    auto metaObject = obj.metaObject();
    auto nodes = node.childNodes();
    for(auto i = 0; i < nodes.length(); i++)
    {
        auto cNode = nodes.at(i);
        auto pName = cNode.nodeName();
        auto var = obj.property(pName.toStdString().c_str());
        if(var.isValid())
        {
            QString tName(var.typeName());

            if(tName.endsWith("*"))
            {
                auto rNode = cNode.firstChild();
                auto dO = this->Deserialize(rNode);
                obj.setProperty(pName.toStdString().c_str(), QVariant::fromValue(dO));
            }
            else if(tName.startsWith("QList<"))
            {
                auto isRef = tName.endsWith("*>");
                auto rNodes = cNode.childNodes();

                if(rNodes.length() > 0)
                {
                    if(isRef)
                    {
                        auto list = var.value<QList<DataObject*>>();
                        for(auto j = 0; j < rNodes.length(); j++)
                        {
                            auto rNode = rNodes.at(j);
                            auto dO = this->Deserialize(rNode);
                            list.append(dO);
                        }
                        var.setValue(list);
                        obj.setProperty(pName.toStdString().c_str(), var);
                    }
                    else
                    {
                        QVariantList list = qvariant_cast<QVariantList>(var);
                        for(auto j = 0; j < rNodes.length(); j++)
                        {
                            auto rNode = rNodes.at(j);
                            auto etName = rNode.nodeName();
                            auto txt = rNode.toElement().text();
                            QVariant value(txt);
                            value.convert(QVariant::nameToType(etName.toStdString().c_str()));
                            list.append(value);
                        }
                        auto nvar = QVariant(list);
                        auto listTypeId = metaObject->property(metaObject->indexOfProperty(pName.toStdString().c_str())).userType();
                        nvar.convert(QVariant::nameToType(listTypeId));
                        obj.setProperty(pName.toStdString().c_str(), nvar);
                    }
                }
            }
            else
            {
                auto etName = metaObject->property(metaObject->indexOfProperty(pName.toStdString().c_str())).typeName();
                auto txt = cNode.toElement().text();
                QVariant value(txt);
                value.convert(QVariant::nameToType(etName));
                obj.setProperty(pName.toStdString().c_str(), value);
            }
        }
    }
}
