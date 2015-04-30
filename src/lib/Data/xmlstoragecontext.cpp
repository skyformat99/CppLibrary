#include "xmlstoragecontext.h"

#define WORD_STORE "store"

XmlStorageContext::XmlStorageContext(QFile &file) : _file(file)
{
}

XmlStorageContext::~XmlStorageContext()
{

}

void XmlStorageContext::onSave(const QUuid &id)
{
    if(this->hash.contains(id))
    {
        QMutexLocker(&this->mutex);
        if(!this->_file.exists())
            this->createNewXml();
        else
        {
            QDomDocument doc("storage");

            if(!this->_file.open(QIODevice::ReadOnly))
                throw(new CouldNotOpenStorageFileForRead);
            doc.setContent(&this->_file);
            this->_file.close();

            this->createDomElementFor(doc, id, true, true);

            if(!this->_file.open(QIODevice::WriteOnly))
                throw(new CouldNotOpenStorageFileForWrite);

            QTextStream ts(&this->_file);
            ts << doc.toString();

            this->_file.close();
        }
    }
    else throw(new ObjectNotFoundInDataContextException(id));
}

void XmlStorageContext::onSaveAll()
{
    QDomDocument doc(WORD_STORE);
    auto root = doc.createElement(WORD_STORE);
    doc.appendChild(root);

    foreach(auto id, this->hash.keys())
    {
        this->createDomElementFor(doc, id, false, false);
    }

    if(!this->_file.open(QIODevice::WriteOnly))
        throw(new CouldNotOpenStorageFileForWrite);

    QTextStream ts(&this->_file);
    ts << doc.toString();

    this->_file.close();
}

void XmlStorageContext::createDomElementFor(QDomDocument &doc, const QUuid &id, bool createSubs, bool deleteExisting)
{
    auto root = doc.documentElement();
    if(deleteExisting)
    {
        QDomNode toRemove;
        auto list = root.childNodes();
        auto cnt = list.count();
        for(auto i = 0; i < cnt; i++)
        {
            auto child = list.at(i);
            auto element = child.toElement();
            QUuid childId(element.attribute("id"));
            if(childId == id)
            {
                toRemove = child;
                break;
            }
        }

        if(!toRemove.isNull())
            root.removeChild(toRemove);
    }

    auto element = doc.createElement(this->hash.value(id)->metaObject()->className());
    root.appendChild(element);

    ContextObject *obj = this->hash.value(id);
    auto metaObject = obj->metaObject();
    for(auto i = 1; i < metaObject->propertyCount(); i++)
    {
        QString tName(metaObject->property(i).typeName());
        auto pName = metaObject->property(i).name();

        if(tName.endsWith("*"))
        {
            auto fObj = (ContextObject*)obj->property(pName).value<ContextObject*>();
            element.setAttribute(pName, fObj->id().toString());

            if(createSubs)
                this->createDomElementFor(doc, fObj->id(), createSubs, deleteExisting);
        }
        else if(tName.startsWith("QList"))
        {
            auto pElement = doc.createElement(pName);
            element.appendChild(pElement);

            QSequentialIterable iterable = obj->property(pName).value<QSequentialIterable>();
            foreach(const QVariant& item, iterable)
            {
                auto fObj = item.value<ContextObject*>();
                auto rElement = doc.createElement("ref");
                rElement.setAttribute("id", fObj->id().toString());
                pElement.appendChild(rElement);

                if(createSubs)
                    this->createDomElementFor(doc, fObj->id(), createSubs, deleteExisting);
            }
        }
        else
        {
            element.setAttribute(pName, obj->property(pName).toString());
        }
    }
}

void XmlStorageContext::onUpdate(const QUuid &id)
{
    if(this->hash.contains(id))
    {
        QMutexLocker(&this->mutex);
        if(!this->_file.exists())
            this->createNewXml();
        else
        {
            this->loadFromXml(id);
        }
    }
    else throw(new ObjectNotFoundInDataContextException(id));
}

void XmlStorageContext::onUpdateAll()
{
    QMutexLocker(&this->mutex);
    if(!this->_file.exists())
        this->createNewXml();
    else
    {
        // TODO load all objects from xml
    }
}

ContextObject *XmlStorageContext::onGet(const QUuid &id)
{
    QMutexLocker(&this->mutex);
    if(!this->hash.contains(id))
        this->loadFromXml(id);

    return StorageContext::onGet(id);
}

void XmlStorageContext::createNewXml() const
{
    this->_file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&this->_file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeEndDocument();
    this->_file.close();
}

void XmlStorageContext::loadFromXml(const QUuid &id)
{
    if(!this->_file.exists())
        this->createNewXml();

    // TODO load single object from xml
}

