#include "xmlserializer.h"

namespace ralph {
    namespace data {
        XmlSerializer::XmlSerializer()
        {

        }

        XmlSerializer::~XmlSerializer()
        {

        }

        QString XmlSerializer::serialize(DataObject &obj)
        {
            QDomDocument doc;
            this->serialize(obj, doc);

            return doc.toString();
        }

        void XmlSerializer::serialize(DataObject &obj, QFile &file)
        {
            QDataStream stream(&file);

            return serialize(obj, stream);
        }

        void XmlSerializer::serialize(DataObject &obj, QDataStream &stream)
        {
            QString str = this->serialize(obj);
            stream << str.toUtf8();
        }

        void XmlSerializer::serialize(DataObject &obj, QDomDocument &doc)
        {
            QDomElement node = doc.createElement(obj.metaObject()->className());

            this->serializeContent(obj, doc, node);

            doc.appendChild(node);
        }

        void XmlSerializer::serialize(DataObject &obj, QDomDocument &doc, QDomNode &parent)
        {
            QDomElement node = doc.createElement(obj.metaObject()->className());

            this->serializeContent(obj, doc, node);

            parent.appendChild(node);
        }

        void XmlSerializer::serializeContent(DataObject &obj, QDomDocument &doc, QDomNode &node)
        {
            const QMetaObject* metaObject = obj.metaObject();
            for(int i = 1; i < metaObject->propertyCount(); i++)
            {
                QString tName(metaObject->property(i).typeName());
                QString pName = metaObject->property(i).name();
                QDomElement prop = doc.createElement(pName);

                if(!QString(pName).startsWith("__g_"))
                {
                    QString gpName = pName;
                    gpName.insert(0, "__g_");

                    if(tName.startsWith("QSharedPointer<"))
                    {
                        this->serialize(*obj.property(gpName.toStdString().c_str()).value<DataObject*>(), doc, prop);
                    }
                    else if(tName.startsWith("QList<"))
                    {
                        if(tName.startsWith("QList<QSharedPointer<"))
                        {
                            QList<DataObject*> iterable = obj.property(gpName.toStdString().c_str()).value<QList<DataObject*>>();
                            foreach(DataObject* item, iterable)
                            {
                                this->serialize(*item, doc, prop);
                            }
                        }
                        else
                        {
                            QList<QVariant> iterable = obj.property(gpName.toStdString().c_str()).value<QList<QVariant>>();
                            foreach(const QVariant& item, iterable)
                            {
                                QDomElement elem = doc.createElement(item.typeName());
                                QDomText txt = doc.createTextNode(item.toString());
                                elem.appendChild(txt);
                                prop.appendChild(elem);
                            }
                        }
                    }
                    else
                    {
                        QDomText txt = doc.createTextNode(obj.property(pName.toStdString().c_str()).toString());
                        prop.appendChild(txt);
                    }
                    node.appendChild(prop);
                }
            }
        }

        QSharedPointer<DataObject> XmlSerializer::deserialize(QString &text)
        {
            QDomDocument doc;
            doc.setContent(text);

            return QSharedPointer<DataObject>(this->deserialize(doc));

        }

        QSharedPointer<DataObject> XmlSerializer::deserialize(QFile &file)
        {
            QDataStream stream(&file);

            return deserialize(stream);
        }

        QSharedPointer<DataObject> XmlSerializer::deserialize(QDataStream &stream)
        {
            QByteArray arr;
            stream >> arr;

            QString str = QString::fromUtf8(arr);
            QSharedPointer<DataObject> obj = this->deserialize(str);
            return obj;
        }

        DataObject* XmlSerializer::deserialize(QDomDocument &doc)
        {
            QDomNode root = doc.firstChild();
            DataObject* obj = DataObjectFactory::create(root.nodeName());
            this->deserializeContent(root, *obj);

            return obj;
        }

        DataObject* XmlSerializer::deserialize(QDomNode &node)
        {
            DataObject* obj = DataObjectFactory::create(node.nodeName());
            this->deserializeContent(node, *obj);

            return obj;
        }

        void XmlSerializer::deserializeContent(QDomNode &node, DataObject &obj)
        {
            const QMetaObject* metaObject = obj.metaObject();
            QDomNodeList nodes = node.childNodes();
            for(int i = 0; i < nodes.length(); i++)
            {
                QDomNode cNode = nodes.at(i);
                QString pName = cNode.nodeName();
                QVariant var = obj.property(pName.toStdString().c_str());
                if(var.isValid() && !QString(pName).startsWith("__g_"))
                {
                    QString tName(var.typeName());
                    QString gpName = pName;
                    gpName.insert(0, "__g_");

                    if(tName.startsWith("QSharedPointer<"))
                    {
                        QDomNode rNode = cNode.firstChild();
                        DataObject* dO = this->deserialize(rNode);
                        obj.setProperty(gpName.toStdString().c_str(), QVariant::fromValue(dO));
                    }
                    else if(tName.startsWith("QList<"))
                    {
                        bool isRef = tName.startsWith("QList<QSharedPointer<");
                        QDomNodeList rNodes = cNode.childNodes();

                        if(rNodes.length() > 0)
                        {
                            if(isRef)
                            {
                                QList<DataObject*> list;
                                for(int j = 0; j < rNodes.length(); j++)
                                {
                                    QDomNode rNode = rNodes.at(j);
                                    DataObject* dO = this->deserialize(rNode);
                                    list.append(dO);
                                }
                                QVariant nvar;
                                nvar.setValue(list);
                                obj.setProperty(gpName.toStdString().c_str(), nvar);
                            }
                            else
                            {
                                QVariant gvar = obj.property(gpName.toStdString().c_str());
                                QList<QVariant> list = gvar.value<QList<QVariant>>();
                                list.clear();
                                QVariant::Type elemTypeId = QVariant::Invalid;
                                for(int j = 0; j < rNodes.length(); j++)
                                {
                                    QDomNode rNode = rNodes.at(j);
                                    QString etName = rNode.nodeName();
                                    if(elemTypeId == QVariant::Invalid)
                                        elemTypeId = QVariant::nameToType(etName.toStdString().c_str());

                                    if(elemTypeId != QVariant::Invalid)
                                    {
                                        QString txt = rNode.toElement().text();
                                        QVariant value(txt);
                                        value.convert(elemTypeId);
                                        list.append(value);
                                    }
                                }
                                QVariant nvar = QVariant(list);
                                obj.setProperty(gpName.toStdString().c_str(), nvar);
                            }
                        }
                    }
                    else
                    {
                        QString etName = metaObject->property(metaObject->indexOfProperty(pName.toStdString().c_str())).typeName();
                        QString txt = cNode.toElement().text();
                        QVariant value(txt);
                        value.convert(QVariant::nameToType(etName.toStdString().c_str()));
                        obj.setProperty(pName.toStdString().c_str(), value);
                    }
                }
            }
        }

    }
}
