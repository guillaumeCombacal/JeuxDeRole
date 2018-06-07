#ifndef QUESTOBJECTWIDGET_H
#define QUESTOBJECTWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QListWidget>
#include<QLabel>

#include "sharedDataHero.h"

class QuestObjectWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pQuestObjectLayout;
    QLabel*      m_pQuestObjectLabel;
    QListWidget* m_pQuestObjectListWidget;

	
public:
    explicit QuestObjectWidget(QWidget *parent = 0);
    ~QuestObjectWidget();

    void refreshQuestView(QuestObject questObject);

signals:

private slots:


public slots:


};

#endif // QUESTOBJECTWIDGET_H
