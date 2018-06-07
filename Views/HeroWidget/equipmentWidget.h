#ifndef EQUIPMENTWIDGET_H
#define EQUIPMENTWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class EquipmentWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pEquipmentLayout;
    QLabel*      m_pLabelEquipment;

    QLabel*      m_pLabelHead;
    QLabel*      m_pLabelChest;
    QLabel*      m_pLabelLeg;
    QLabel*      m_pLabelFeet;
    QLabel*      m_pLabelHand;
    QLabel*      m_pLabelRightHandStuff;
    QLabel*      m_pLabelLeftHandStuff;
	
    QLabel*      m_pLabelHeadValue;
    QLabel*      m_pLabelChestValue;
    QLabel*      m_pLabelLegValue;
    QLabel*      m_pLabelFeetValue;
    QLabel*      m_pLabelHandValue;
    QLabel*      m_pLabelRightHandStuffValue;
    QLabel*      m_pLabelLeftHandStuffValue;

public:
    explicit EquipmentWidget(QWidget *parent = 0);
    ~EquipmentWidget();

    void refreshEquipmentView(Equipment equipment);

signals:

private slots:


public slots:


};

#endif // EQUIPMENTWIDGET_H
