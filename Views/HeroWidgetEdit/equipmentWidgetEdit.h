#ifndef EQUIPMENTWIDGETEDIT_H
#define EQUIPMENTWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class EquipmentWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pEquipmentEditLayout;
    QLabel*      m_pEquipmentEditLabel;
    QLineEdit*   m_pHeadEdit;
    QLineEdit*   m_pChestEdit;
    QLineEdit*   m_pLegEdit;
    QLineEdit*   m_pFeetEdit;
    QLineEdit*   m_pHandEdit;
    QLineEdit*   m_pRightHandStuffEdit;
    QLineEdit*   m_pLeftHandStuffEdit;
	
    QLabel*      m_pHeadEditLabel;
    QLabel*      m_pChestEditLabel;
    QLabel*      m_pLegEditLabel;
    QLabel*      m_pFeetEditLabel;
    QLabel*      m_pHandEditLabel;
    QLabel*      m_pRightHandStuffEditLabel;
    QLabel*      m_pLeftHandStuffEditLabel;

public:
    explicit EquipmentWidgetEdit(QWidget *parent = 0);
    ~EquipmentWidgetEdit();

    void refreshEquipmentView(Equipment equipment);

    Equipment getEquipmentValues();

signals:

private slots:


public slots:


};

#endif // EQUIPMENTWIDGETEDIT_H
