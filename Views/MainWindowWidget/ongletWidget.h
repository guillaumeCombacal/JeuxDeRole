#ifndef ONGLETWIDGET_H
#define ONGLETWIDGET_H

#include <QWidget>
#include<QHBoxLayout>
#include<QPushButton>

class OngletWidget : public QWidget
{
    Q_OBJECT

private:
	QHBoxLayout *m_pOngletLayout;
	QPushButton *m_pOngletWorldMapBtn;
	QPushButton *m_pOngletBattleBtn;
	QPushButton *m_pOngletHeroBtn;
	QPushButton *m_pOngletQuestBtn;

public:
    explicit OngletWidget(QWidget *parent = 0);

signals:

public slots:

private slots:
    void onSwitchView();

signals:
    void sendSwitchWidget(int idWidget);

};

#endif // ONGLETWIDGET_H
