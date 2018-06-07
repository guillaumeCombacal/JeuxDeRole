#include "parserXml.h"

ParserXml::ParserXml()
{
   m_pDomDocument = new QDomDocument("domDoc");
   qDebug()<<"ParserXml()";
}

QList<XmlField> ParserXml::getListXmlField()
{
    return m_listXmlField;
}

bool ParserXml::readXmlFile(QString fileName)
{
    qDebug()<<"ParserXml::readXmlFile";

    bool bResult = false;    


    QFile xmlFile (fileName);

    // Open File
    if(!xmlFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Error open File";
        return bResult;
    }

    // Associate the content file with the QDomDocument
    if(!m_pDomDocument->setContent(&xmlFile))
    {
        qDebug()<<"Error l'objet n'a pas pu etre attribue à l'objet QDomDocument";
        return bResult;
    }

    //Processing
    if(m_pDomDocument != NULL)
    {
        qDebug()<<"Lecture";
        QDomElement domElement = m_pDomDocument->documentElement();
        QDomNode node = domElement.firstChild();

        while(!node.isNull())// Tant que le nœud n'est pas vide.
        {
            // On utilise cette propriété afin de transformer le nœud en éléments.
            // Cela nous permet aussi de récupérer l'élément ou nœud courant.
            QDomElement element = node.toElement();

            if(!element.isNull())
            {
                //If element is a STRUCT and contains others nodes
                if(element.attribute("type", 0) == "struct")
                {
                    //qDebug()<<element.attribute("dataType", 0);
                    //qDebug() << element.attribute("value", 0);
                    //qDebug() << node.childNodes().size();
                    // !!! qDebug() << node.firstChild().toElement().attribute("value", 0); !!!!

                    // Create The Field and push it to the list
                    XmlField field;
                    field.m_type  = element.attribute("type", 0);
                    field.m_value = element.attribute("value", 0);
                    field.m_size  = element.attribute("size", 0).toInt();
                    m_listXmlField.push_back(field);

                    QDomNodeList childNodes = node.childNodes();
                    readChildNodes(childNodes);
                }
                //If it's not a STRUCT
                else
                {
                    qDebug() << element.attribute("value", 0);

                    // Create The Field and push it to the list
                    XmlField field;
                    field.m_type  = element.attribute("type", 0);
                    field.m_value = element.attribute("value", 0);
                    field.m_size  = element.attribute("size", 0).toInt();
                    m_listXmlField.push_back(field);
                }
            }

            node = node.nextSibling();

            if(bResult == false)
            {
                bResult = true;
            }

        }
    }
    else
    {
        qDebug()<<"pDomDocument is NULLptr";
        return bResult;
    }


    xmlFile.close();

    return bResult;

}


void ParserXml::readChildNodes(QDomNodeList childNodes)
{

    qDebug() << "ParserXml::readChildNodes";

    for(int i=0; childNodes.count() > i; i++)
    {
        QDomNode node = childNodes.item(i);
        QDomElement element = node.toElement();

        // IF the field is a STRUCT
        if(!element.isNull())
        {
            //If element contains others nodes
            if(element.attribute("type", 0) == "struct")
            {
                qDebug()<<element.attribute("dataType", 0);
                qDebug()<<element.attribute("value", 0);

                // Create The Field and push it to the list
                XmlField field;
                field.m_type  = element.attribute("type", 0);
                field.m_value = element.attribute("value", 0);
                field.m_size  = element.attribute("size", 0).toInt();
                m_listXmlField.push_back(field);

                //Recursion
                QDomNodeList childNodes = node.childNodes();
                readChildNodes(childNodes);

            }
            //If it's not a STRUCT
            else
            {
                qDebug()<<element.attribute("value", 0);

                // Create The Field and push it to the list
                XmlField field;
                field.m_type  = element.attribute("type", 0);
                field.m_value = element.attribute("value", 0);
                field.m_size  = element.attribute("size", 0).toInt();
                field.m_number= element.attribute("number", 0).toInt();
                m_listXmlField.push_back(field);
            }
        }
    }
    qDebug() << "-----------------";

}



bool ParserXml::writeXmlFile(QString fileName, QList<XmlField> listFieldToSave)
{
    qDebug()<<"ParserXml::writeXmlFile";

    bool bResult = false;

    // Open File
    QFile xmlFile (fileName);

    if(!xmlFile.open(QIODevice::WriteOnly))
    {
        xmlFile.close();
        qDebug()<<"Error open File";
        std::printf("error ouverture du fichier");
        bResult = false;
        return bResult;
    }

    // QTextStream to write in the file
    QTextStream stream(&xmlFile);

    // First line in file
    stream << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << "\r\n";

    // Content of the XML file
    QDomDocument domDocument("domDoc");

    // Write the first/root node => Hero
    QDomElement rootNode = domDocument.createElement("hero");

    XmlField field;

    while(!listFieldToSave.isEmpty())
    {
       // Take the first element in the list and remove it from the list
       field = listFieldToSave.takeFirst();

       if(field.m_type == "struct")
       {
           QDomElement structField = domDocument.createElement(field.m_value);
           structField.setAttribute("size", field.m_size);
           structField.setAttribute("type", field.m_type);
           structField.setAttribute("value", field.m_value);

           int sizeStruct = field.m_size;

           for(int i=0; i<sizeStruct; i++)
           {
               if(!listFieldToSave.isEmpty())
               {
                   field = listFieldToSave.takeFirst();

                   QDomElement childField = domDocument.createElement(field.m_type);
                   childField.setAttribute("size", field.m_size);
                   childField.setAttribute("type", field.m_type);
                   childField.setAttribute("value", field.m_value);
                   childField.setAttribute("number", field.m_number);

                   structField.appendChild(childField);
               }
           }

           rootNode.appendChild(structField);
       }
       else
       {
           QDomElement singleField = domDocument.createElement(field.m_type);
           singleField.setAttribute("size", field.m_size);
           singleField.setAttribute("type", field.m_type);
           singleField.setAttribute("value", field.m_value);
           singleField.setAttribute("number", field.m_number);

           rootNode.appendChild(singleField);
       }
    }
    domDocument.appendChild(rootNode);

    /*QDomElement writeElem = domDocument.createElement("information");
    writeElem.setAttribute("id", 2);
    writeElem.setAttribute("value", "Une tempête arrive en France");

    domDocument.appendChild(writeElem);
*/

    // Convert the QDomDocument in a QString and write it
    QString writeDoc = domDocument.toString();
    stream << writeDoc;

    xmlFile.close();

    bResult = true;
    return bResult;
}
