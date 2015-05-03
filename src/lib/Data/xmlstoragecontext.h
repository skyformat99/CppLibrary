#ifndef XMLSTORAGECONTEXT_H
#define XMLSTORAGECONTEXT_H

#include <QtCore>
#include <QtXml>
#include "storagecontext.h"

class XmlStorageContext : public StorageContext
{
public:
    XmlStorageContext(QFile& file);
    ~XmlStorageContext();

protected:
    virtual void onSave(const QUuid& id) override;
    virtual void onSaveAll() override;
    virtual void onUpdate(const QUuid& id) override;
    virtual void onUpdateAll() override;
    virtual ContextObject* onGet(const QUuid& id) override;

private:
    QFile& _file;

    void createNewXml() const;
    void loadFromXml(const QUuid& id);
    void createDomElementFor(QDomDocument& doc, const QUuid& id, bool createSubs, bool deleteExisting);
};

#endif // XMLSTORAGECONTEXT_H
