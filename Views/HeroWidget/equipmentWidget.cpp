#include "equipmentWidget.h"

#include "QDebug"


EquipmentWidget::EquipmentWidget(QWidget *parent) : QWidget(parent)
{
    m_pEquipmentLayout     = new QVBoxLayout();

    m_pLabelEquipment      = new QLabel("Equipement");

    m_pLabelHead                = new QLabel("Head");
    m_pLabelChest               = new QLabel("Chest");
    m_pLabelLeg                 = new QLabel("Leg");
    m_pLabelFeet                = new QLabel("Feet");
    m_pLabelHand                = new QLabel("Hand");
    m_pLabelRightHandStuff      = new QLabel("RightHandStuff");
    m_pLabelLeftHandStuff       = new QLabel("LeftHandStuff");

    m_pLabelHeadValue           = new QLabel("");
    m_pLabelChestValue          = new QLabel("");
    m_pLabelLegValue            = new QLabel("");
    m_pLabelFeetValue           = new QLabel("");
    m_pLabelHandValue           = new QLabel("");
    m_pLabelRightHandStuffValue = new QLabel("");
    m_pLabelLeftHandStuffValue  = new QLabel("");

    m_pEquipmentLayout->addWidget(m_pLabelEquipment);
    m_pEquipmentLayout->addWidget(m_pLabelHead);
    m_pEquipmentLayout->addWidget(m_pLabelHeadValue);
    m_pEquipmentLayout->addWidget(m_pLabelChest);
    m_pEquipmentLayout->addWidget(m_pLabelChestValue);
    m_pEquipmentLayout->addWidget(m_pLabelLeg);
    m_pEquipmentLayout->addWidget(m_pLabelLegValue);
    m_pEquipmentLayout->addWidget(m_pLabelFeet);
    m_pEquipmentLayout->addWidget(m_pLabelFeetValue);
    m_pEquipmentLayout->addWidget(m_pLabelHand);
    m_pEquipmentLayout->addWidget(m_pLabelHandValue);
    m_pEquipmentLayout->addWidget(m_pLabelRightHandStuff);
    m_pEquipmentLayout->addWidget(m_pLabelRightHandStuffValue);
    m_pEquipmentLayout->addWidget(m_pLabelLeftHandStuff);
    m_pEquipmentLayout->addWidget(m_pLabelLeftHandStuffValue);

    this->setLayout(m_pEquipmentLayout);
}

EquipmentWidget::~EquipmentWidget()
{
    if(m_pLabelEquipment != NULL)
    {
        delete m_pLabelEquipment;
    }
    if(m_pLabelHead != NULL)
    {
        delete m_pLabelHead;
    }
    if(m_pLabelHeadValue != NULL)
    {
        delete m_pLabelHeadValue;
    }
    if(m_pLabelChest != NULL)
    {
        delete m_pLabelChest;
    }
    if(m_pLabelChestValue != NULL)
    {
        delete m_pLabelChestValue;
    }
    if(m_pLabelLeg != NULL)
    {
        delete m_pLabelLeg;
    }
    if(m_pLabelLegValue != NULL)
    {
        delete m_pLabelLegValue;
    }
    if(m_pLabelFeet != NULL)
    {
        delete m_pLabelFeet;
    }
    if(m_pLabelFeetValue != NULL)
    {
        delete m_pLabelFeetValue;
    }
    if(m_pLabelHand != NULL)
    {
        delete m_pLabelHand;
    }
    if(m_pLabelHandValue != NULL)
    {
        delete m_pLabelHandValue;
    }
    if(m_pLabelRightHandStuff != NULL)
    {
        delete m_pLabelRightHandStuff;
    }
    if(m_pLabelRightHandStuffValue != NULL)
    {
        delete m_pLabelRightHandStuffValue;
    }
    if(m_pLabelLeftHandStuff != NULL)
    {
        delete m_pLabelLeftHandStuff;
    }
    if(m_pLabelLeftHandStuffValue != NULL)
    {
        delete m_pLabelLeftHandStuffValue;
    }
    if(m_pEquipmentLayout != NULL)
    {
        delete m_pEquipmentLayout;
    }
}

void EquipmentWidget::refreshEquipmentView(Equipment equipment)
{
    m_pLabelHeadValue->setText(equipment.m_Head);
    m_pLabelChestValue->setText(equipment.m_Chest);
    m_pLabelLegValue->setText(equipment.m_Leg);
    m_pLabelFeetValue->setText(equipment.m_Feet);
    m_pLabelHandValue->setText(equipment.m_Hand);
    m_pLabelRightHandStuffValue->setText(equipment.m_RightHandStuff);
    m_pLabelLeftHandStuffValue->setText(equipment.m_LeftHandStuff);
}


