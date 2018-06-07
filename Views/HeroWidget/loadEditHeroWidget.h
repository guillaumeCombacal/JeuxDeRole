#ifndef LOADSAVEHEROWIDGET_H
#define LOADSAVEHEROWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>

#include "sharedDataHero.h"

class LoadEditHeroWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pLoadSaveHeroLayout;
    QPushButton* m_pBtnLoadHero;
    QPushButton* m_pBtnEditHero;
    QPushButton* m_pBtnAddNewHero;
	
public:
    explicit LoadEditHeroWidget(QWidget *parent = 0);
    ~LoadEditHeroWidget();

    QPushButton *getBtnLoadHero();
    QPushButton *getBtnEditHero();
    QPushButton *getBtnAddNewHero();

signals:
    void sendLoadHeroFromFile(QStringList listFiles);

private slots:

public slots:


};

#endif // LOADSAVEHEROWIDGET_H
