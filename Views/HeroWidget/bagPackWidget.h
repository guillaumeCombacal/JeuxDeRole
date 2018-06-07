#ifndef BAGPACKWIDGET_H
#define BAGPACKWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QListWidget>
#include<QLabel>
#include<QLineEdit>

#include "sharedDataHero.h"

class BagPackWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pBagPackLayout;
    QLabel*      m_pBagPackLabel;

    QLabel*      m_pFoodLabel;
    QLabel*      m_pOrLabel;

    QLabel*      m_pFoodLabelValue;
    QLabel*      m_pOrLabelValue;

    QListWidget* m_pBagPackListWidget;

	
public:
    explicit BagPackWidget(QWidget *parent = 0);
    ~BagPackWidget();

    void refreshBagView(Bag bag);
signals:

private slots:


public slots:


};

#endif // BAGPACKWIDGET_H
