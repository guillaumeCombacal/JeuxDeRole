#ifndef LOADSAVEHEROWIDGETEDIT_H
#define LOADSAVEHEROWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>

#include "sharedDataHero.h"

class CancelSaveHeroWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pLoadSaveHeroLayout;
    QPushButton* m_pCancelEdition;
    QPushButton* m_pSaveHero;
	
public:
    explicit CancelSaveHeroWidgetEdit(QWidget *parent = 0);
    ~CancelSaveHeroWidgetEdit();

    QPushButton *getBtnCancelEdition();
    QPushButton *getBtnSaveHero();

signals:
    void sendLoadHeroFromFile(QStringList listFiles);

private slots:

public slots:


};

#endif // LOADSAVEHEROWIDGETEDIT_H
