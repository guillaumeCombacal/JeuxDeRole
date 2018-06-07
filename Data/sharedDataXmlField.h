#ifndef XMLFIELD_H
#define XMLFIELD_H

#include<QString>

struct XmlField
{
    QString m_type = "";
    QString m_value = "";
    int m_size = 0;
    int m_number = 0;
};

#endif // XMLFIELD_H
