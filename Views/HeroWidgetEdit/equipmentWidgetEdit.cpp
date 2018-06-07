#include "equipmentWidgetEdit.h"

#include "QDebug"


EquipmentWidgetEdit::EquipmentWidgetEdit(QWidget *parent) : QWidget(parent)
{
    m_pEquipmentEditLayout     = new QVBoxLayout();

    m_pEquipmentEditLabel      = new QLabel("Equipement");

    m_pHeadEdit                = new QLineEdit("Head");
    m_pChestEdit               = new QLineEdit("Chest");
    m_pLegEdit                 = new QLineEdit("Leg");
    m_pFeetEdit                = new QLineEdit("Feet");
    m_pHandEdit                = new QLineEdit("Hand");
    m_pRightHandStuffEdit      = new QLineEdit("RightHandStuff");
    m_pLeftHandStuffEdit       = new QLineEdit("LeftHandStuff");

    m_pHeadEditLabel           = new QLabel("Tête");
    m_pChestEditLabel          = new QLabel("Poitrine");
    m_pLegEditLabel            = new QLabel("Jambe");
    m_pFeetEditLabel           = new QLabel("Pied");
    m_pHandEditLabel           = new QLabel("Main");
    m_pRightHandStuffEditLabel = new QLabel("Objet Main Droite");
    m_pLeftHandStuffEditLabel  = new QLabel("Objet Main Gauche");

    m_pEquipmentEditLayout->addWidget(m_pEquipmentEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pHeadEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pHeadEdit);
    m_pEquipmentEditLayout->addWidget(m_pChestEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pChestEdit);
    m_pEquipmentEditLayout->addWidget(m_pLegEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pLegEdit);
    m_pEquipmentEditLayout->addWidget(m_pFeetEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pFeetEdit);
    m_pEquipmentEditLayout->addWidget(m_pHandEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pHandEdit);
    m_pEquipmentEditLayout->addWidget(m_pRightHandStuffEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pRightHandStuffEdit);
    m_pEquipmentEditLayout->addWidget(m_pLeftHandStuffEditLabel);
    m_pEquipmentEditLayout->addWidget(m_pLeftHandStuffEdit);

    this->setLayout(m_pEquipmentEditLayout);
}

EquipmentWidgetEdit::~EquipmentWidgetEdit()
{
    if(m_pEquipmentEditLabel != NULL)
    {
        delete m_pEquipmentEditLabel;
    }
    if(m_pHeadEdit != NULL)
    {
        delete m_pHeadEdit;
    }
    if(m_pChestEdit != NULL)
    {
        delete m_pChestEdit;
    }
    if(m_pLegEdit != NULL)
    {
        delete m_pLegEdit;
    }
    if(m_pFeetEdit != NULL)
    {
        delete m_pFeetEdit;
    }
    if(m_pHandEdit != NULL)
    {
        delete m_pHandEdit;
    }
    if(m_pRightHandStuffEdit != NULL)
    {
        delete m_pRightHandStuffEdit;
    }
    if(m_pLeftHandStuffEdit != NULL)
    {
        delete m_pLeftHandStuffEdit;
    }
    if(m_pEquipmentEditLayout != NULL)
    {
        delete m_pEquipmentEditLayout;
    }
}

void EquipmentWidgetEdit::refreshEquipmentView(Equipment equipment)
{
    m_pHeadEdit->setText(equipment.m_Head);
    m_pChestEdit->setText(equipment.m_Chest);
    m_pLegEdit->setText(equipment.m_Leg);
    m_pFeetEdit->setText(equipment.m_Feet);
    m_pHandEdit->setText(equipment.m_Hand);
    m_pRightHandStuffEdit->setText(equipment.m_RightHandStuff);
    m_pLeftHandStuffEdit->setText(equipment.m_LeftHandStuff);
}

Equipment EquipmentWidgetEdit::getEquipmentValues()
{
    Equipment equipment;

    equipment.m_Chest = m_pChestEdit->text();
    equipment.m_Feet = m_pFeetEdit->text();
    equipment.m_Hand = m_pHandEdit->text();
    equipment.m_Head = m_pHeadEdit->text();
    equipment.m_LeftHandStuff = m_pLeftHandStuffEdit->text();
    equipment.m_Leg = m_pLegEdit->text();
    equipment.m_RightHandStuff = m_pRightHandStuffEdit->text();

    return equipment;
}


