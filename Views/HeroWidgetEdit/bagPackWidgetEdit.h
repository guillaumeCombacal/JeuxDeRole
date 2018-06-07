#ifndef BAGPACKWIDGETEDIT_H
#define BAGPACKWIDGETEDIT_H

#include <QWidget>
#include<QGridLayout>
#include<QListWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>

#include "sharedDataHero.h"

class BagPackWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* m_pBagPackEditLayout;

    QLabel*      m_pBagPackEditLabel;
    QLabel*      m_pFoodEditLabel;
    QLabel*      m_pOrEditLabel;
    QLineEdit*   m_pFoodEditLineEdit;
    QLineEdit*   m_pOrEditLineEdit;
    QListWidget* m_pBagPackEditListWidget;

    QPushButton* m_pBtnAddInListWidget;
    QPushButton* m_pBtnRemoveFromListWidget;

    QLineEdit*   m_pLineEditNameItem;
    QLineEdit*   m_pLineEditNumber;

	
public:
    explicit BagPackWidgetEdit(QWidget *parent = 0);
    ~BagPackWidgetEdit();

    void refreshBagView(Bag bag);

    Bag getBagValues();
    QPushButton* getBtnAddItemInBag();
    QPushButton* getBtnRemoveItemFromBag();
    QString getValueNameItem();
    QString getValueNumberItem();

signals:

private slots:


public slots:


};

#endif // BAGPACKWIDGETEDIT_H
