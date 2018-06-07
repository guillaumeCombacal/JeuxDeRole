#ifndef PARSERXML_H
#define PARSERXML_H

#include <QtXml>

#include"sharedDataXmlField.h"

class ParserXml
{
public:
    ParserXml();
    bool readXmlFile(QString fileName);
    bool writeXmlFile(QString fileName, QList<XmlField> fieldToSave);
    QList<XmlField> getListXmlField();

private:
    void readChildNodes(QDomNodeList childNodes);

private:
    QDomDocument *m_pDomDocument;
    QList<XmlField> m_listXmlField;
};

#endif // PARSERXML_H
