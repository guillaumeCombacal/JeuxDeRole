#ifndef QUESTOBJECTWIDGETEDIT_H
#define QUESTOBJECTWIDGETEDIT_H

#include <QWidget>
#include<QGridLayout>
#include<QListWidget>
#include<QLabel>
#include<QPushButton>

#include "sharedDataHero.h"

class QuestObjectWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* m_pQuestObjectLayout;
    QLabel*      m_pQuestObjectLabel;
    QListWidget* m_pQuestObjectListWidget;

    QPushButton* m_pBtnAddInListWidget;
    QPushButton* m_pBtnRemoveFromListWidget;

    QLineEdit*   m_pLineEditNameQuestObj;
    QLineEdit*   m_pLineEditNumber;

	
public:
    explicit QuestObjectWidgetEdit(QWidget *parent = 0);
    ~QuestObjectWidgetEdit();

    void refreshQuestViewEdit(QuestObject questObject);

    QuestObject getQuestObjectValues();

    QPushButton* getBtnAddQuestObj();
    QPushButton* getBtnRemoveQuestObj();
    QString getValueQuestObj();
    QString getValueNumberQuestObj();

signals:

private slots:


public slots:


};

#endif // QUESTOBJECTWIDGETEDIT_H
