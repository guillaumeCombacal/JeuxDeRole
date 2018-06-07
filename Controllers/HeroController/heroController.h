#ifndef HEROCONTROLLER_H
#define HEROCONTROLLER_H

#include"heroWidgetEdit.h"
#include"heroWidget.h"
#include"parserXml.h"
#include"hero.h"

#include "sharedDataHero.h"

#include<QStringList>

class HeroController : public QObject
{

    Q_OBJECT

private:
    HeroWidgetEdit *m_pHeroWidgetEdit;
    HeroWidget *m_pHeroWidget;
    ParserXml *m_pParserXmlHero;
    std::vector<Hero> m_vectorHero;
    int m_indexCurrentHero;

private:
    void refreshHeroView(int index);
    void refreshEditableHeroView(int index);    

public:
    HeroController();
    ~HeroController();

    HeroWidgetEdit* getHeroWidgetEdit();
    HeroWidget* getHeroWidget();

public slots:
    void onLoadHero();
    void onEditHero();
    void onCancelEdition();
    void onSaveHero();
    void onNextHero();
    void onPreviousHero();
    void onLoadImgFaceHero();
    void onAddNewHero();

    void onAddItemInBag();
    void onRemoveItemFromBag();
    void onAddQuestObj();
    void onRemoveQuestObj();


signals:
    void sendSwitchHeroEditView();
    void sendSwitchHeroView();
};

#endif // HEROCONTROLLER_H
