#include "heroController.h"
#include<QFileDialog>

#include "loggerfile.h"

HeroController::HeroController()
{
    m_pHeroWidgetEdit = new HeroWidgetEdit();
    m_pHeroWidget     = new HeroWidget();

    connect(m_pHeroWidget->getLoadEditHeroWidget()->getBtnLoadHero(), SIGNAL(clicked(bool)),
            this, SLOT(onLoadHero()));

    connect(m_pHeroWidget->getLoadEditHeroWidget()->getBtnEditHero(), SIGNAL(clicked(bool)),
            this, SLOT(onEditHero()));

    connect(m_pHeroWidget->getLoadEditHeroWidget()->getBtnAddNewHero(), SIGNAL(clicked(bool)),
            this, SLOT(onAddNewHero()));

    connect(m_pHeroWidget->getBtnNextHero(), SIGNAL(clicked(bool)),
            this, SLOT(onNextHero()));

    connect(m_pHeroWidget->getBtnPreviousHero(), SIGNAL(clicked(bool)),
            this, SLOT(onPreviousHero()));

    connect(m_pHeroWidgetEdit->getBagPackWidgetEdit()->getBtnAddItemInBag(), SIGNAL(clicked(bool)),
            this, SLOT(onAddItemInBag()));
    connect(m_pHeroWidgetEdit->getBagPackWidgetEdit()->getBtnRemoveItemFromBag(), SIGNAL(clicked(bool)),
            this, SLOT(onRemoveItemFromBag()));
    connect(m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getBtnAddQuestObj(), SIGNAL(clicked(bool)),
            this, SLOT(onAddQuestObj()));
    connect(m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getBtnRemoveQuestObj(), SIGNAL(clicked(bool)),
            this, SLOT(onRemoveQuestObj()));

    connect(m_pHeroWidgetEdit->getCancelSaveHeroWidgetEdit()->getBtnCancelEdition(), SIGNAL(clicked(bool)),
            this, SLOT(onCancelEdition()));

    connect(m_pHeroWidgetEdit->getCancelSaveHeroWidgetEdit()->getBtnSaveHero(), SIGNAL(clicked(bool)),
            this, SLOT(onSaveHero()));

    connect(m_pHeroWidgetEdit->getFeatureHeroWidgetEdit()->getBtnImgHero(), SIGNAL(clicked(bool)),
            this, SLOT(onLoadImgFaceHero()));

    m_pParserXmlHero = new ParserXml();

    m_indexCurrentHero = 0;
}

HeroController::~HeroController()
{
    if(m_pHeroWidgetEdit != NULL)
    {
        delete m_pHeroWidgetEdit;
    }
    if(m_pHeroWidget != NULL)
    {
        delete m_pHeroWidget;
    }
    if(m_pParserXmlHero != NULL)
    {
        delete m_pParserXmlHero;
    }
}

HeroWidgetEdit *HeroController::getHeroWidgetEdit()
{
    return m_pHeroWidgetEdit;
}

HeroWidget *HeroController::getHeroWidget()
{
    return m_pHeroWidget;
}

void HeroController::onLoadHero()
{
    QFileDialog dialog(m_pHeroWidget->getLoadEditHeroWidget());
    dialog.setDirectory(QDir::rootPath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter("XML files(*.xml)");

    QStringList listFiles;

    if (dialog.exec())
    {
        //qDebug()<<dialog.selectedFiles();
        //Q_EMIT sendLoadHeroFromFile(dialog.selectedFiles());
        listFiles = dialog.selectedFiles();
    }

    if(!listFiles.isEmpty())
    {
        foreach(QString file, listFiles)
        {
            //qDebug()<<file;
            m_pParserXmlHero->readXmlFile(file);

            //Create the Hero, Attention la variable "hero" contient les champs de l'instance de hero précédent
            Hero hero;
            hero.loadHero(m_pParserXmlHero->getListXmlField());
            m_vectorHero.push_back(hero);
        }
    }


    // Refresh the Hero view, Active Edit button if m_vectorHero is not empty
    if(!m_vectorHero.empty())
    {
        m_indexCurrentHero = 0;

        refreshHeroView(m_indexCurrentHero);
    }
    else
    {
        qDebug()<<"le vecteur Hero est vide !!!";
    }

}

void HeroController::onEditHero()
{
    if(!m_vectorHero.empty())
    {
        refreshEditableHeroView(m_indexCurrentHero);
        Q_EMIT sendSwitchHeroEditView();
    }
    else
    {
        qDebug()<<"HeroController::onEditHero() : le vecteur Hero est vide !!!";
    }
}

void HeroController::onAddNewHero()
{
    Hero hero;
    m_vectorHero.push_back(hero);
    refreshHeroView(0);
}

void HeroController::onCancelEdition()
{
    refreshHeroView(m_indexCurrentHero);
    Q_EMIT sendSwitchHeroView();
}

void HeroController::onSaveHero()
{

    //qDebug()<<"onSaveHero ----------> "<< m_pHeroWidgetEdit->getFeatureHeroWidgetEdit()->getFeatureValues().m_Xp;

    // Update the Hero
    m_vectorHero[m_indexCurrentHero].saveHeroValue(m_pHeroWidgetEdit->getStatsWidgetEdit()->getStatsValues(),
                                                   m_pHeroWidgetEdit->getFeatureHeroWidgetEdit()->getFeatureValues(),
                                                   m_pHeroWidgetEdit->getEquipmentWidgetEdit()->getEquipmentValues(),
                                                   m_pHeroWidgetEdit->getSkillsWidgetEdit()->getSkillsValues(),
                                                   m_pHeroWidgetEdit->getEffectWidgetEdit()->getEffectValues(),
                                                   m_pHeroWidgetEdit->getBagPackWidgetEdit()->getBagValues(),
                                                   m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getQuestObjectValues());

    // Save the xml File
    QString fileName = QFileDialog::getSaveFileName(m_pHeroWidgetEdit->getCancelSaveHeroWidgetEdit(),
                                                    tr("Save File"), tr(""), tr("XML files(*.xml)"));

    QList<XmlField> listXmlField = m_vectorHero[m_indexCurrentHero].getXmlField();

    m_pParserXmlHero->writeXmlFile(fileName, listXmlField);

    // Refresh the view
    refreshHeroView(m_indexCurrentHero);
    Q_EMIT sendSwitchHeroView();
}

void HeroController::onLoadImgFaceHero()
{
    //LoggerFile::write(Q_FUNC_INFO, "onLoadImgFaceHero");// logger;

    // Save the change values in feature herowidget edit before refresh the view
    m_vectorHero[m_indexCurrentHero].saveHeroValue(m_pHeroWidgetEdit->getStatsWidgetEdit()->getStatsValues(),
                                                   m_pHeroWidgetEdit->getFeatureHeroWidgetEdit()->getFeatureValues(),
                                                   m_pHeroWidgetEdit->getEquipmentWidgetEdit()->getEquipmentValues(),
                                                   m_pHeroWidgetEdit->getSkillsWidgetEdit()->getSkillsValues(),
                                                   m_pHeroWidgetEdit->getEffectWidgetEdit()->getEffectValues(),
                                                   m_pHeroWidgetEdit->getBagPackWidgetEdit()->getBagValues(),
                                                   m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getQuestObjectValues());

    QString fileName = QFileDialog::getOpenFileName(m_pHeroWidgetEdit->getFeatureHeroWidgetEdit(),
                                                    tr("Open File"), tr(""), tr("Images (*.png *.xpm *.jpg)"));


    m_vectorHero[m_indexCurrentHero].setImgFaceHero(fileName);

    m_pHeroWidgetEdit->getFeatureHeroWidgetEdit()->refreshFeatureView(m_vectorHero[m_indexCurrentHero].getFeatureHero());
}

void HeroController::onNextHero()
{
    if(m_indexCurrentHero == m_vectorHero.size()-1)
    {
        m_indexCurrentHero = 0;
    }
    else
    {
        m_indexCurrentHero++;
    }
    refreshHeroView(m_indexCurrentHero);

}

void HeroController::onPreviousHero()
{
    if(m_indexCurrentHero == 0)
    {
        m_indexCurrentHero = int(m_vectorHero.size())-1;
    }
    else
    {
        m_indexCurrentHero--;
    }
    refreshHeroView(m_indexCurrentHero);
}

void HeroController::onAddItemInBag()
{
    QString nameItem = m_pHeroWidgetEdit->getBagPackWidgetEdit()->getValueNameItem();
    int numberItem = m_pHeroWidgetEdit->getBagPackWidgetEdit()->getValueNumberItem().toInt();

    if(nameItem != "" || numberItem > 0)
    {
        m_vectorHero[m_indexCurrentHero].addItemInBag(nameItem, numberItem);
        refreshEditableHeroView(m_indexCurrentHero);
    }
}

void HeroController::onRemoveItemFromBag()
{
    QString nameItem = m_pHeroWidgetEdit->getBagPackWidgetEdit()->getValueNameItem();
    int numberItem = m_pHeroWidgetEdit->getBagPackWidgetEdit()->getValueNumberItem().toInt();

    if(nameItem != "" || numberItem > 0)
    {
        m_vectorHero[m_indexCurrentHero].removeItemFromBag(nameItem, numberItem);
        refreshEditableHeroView(m_indexCurrentHero);
    }

}

void HeroController::onAddQuestObj()
{
    QString nameQuestObj = m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getValueQuestObj();
    int numberQuestObj = m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getValueNumberQuestObj().toInt();

    if(nameQuestObj != "" || numberQuestObj > 0)
    {
        m_vectorHero[m_indexCurrentHero].addQuestObj(nameQuestObj, numberQuestObj);
        refreshEditableHeroView(m_indexCurrentHero);
    }
}

void HeroController::onRemoveQuestObj()
{
    QString nameQuestObj = m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getValueQuestObj();
    int numberQuestObj = m_pHeroWidgetEdit->getQuestObjectWidgetEdit()->getValueNumberQuestObj().toInt();

    if(nameQuestObj != "" || numberQuestObj > 0)
    {
        m_vectorHero[m_indexCurrentHero].removeQuestObj(nameQuestObj, numberQuestObj);
        refreshEditableHeroView(m_indexCurrentHero);
    }
}

/* There is only one widget for edit action and another one to display data,
 * So, each time we switch on another hero we have to refresh the hero data,
 *
 * BRIEF: refresh the view which display hero data (so not the editable view)
 */
void HeroController::refreshHeroView(int index)
{
    if(!m_vectorHero.empty())
    {
        Hero hero = m_vectorHero[index];

        // Enable button
        m_pHeroWidget->getLoadEditHeroWidget()->getBtnEditHero()->setEnabled(true);

        if(m_vectorHero.size() > 1)
        {
          m_pHeroWidget->getBtnNextHero()->setEnabled(true);
          m_pHeroWidget->getBtnPreviousHero()->setEnabled(true);
        }

        // Refresh View
        m_pHeroWidget->refreshView(hero.getStats(), hero.getFeatureHero(), hero.getEquipment(),
                                   hero.getSkills(), hero.getEffect(), hero.getBag(), hero.getQuestObject());
    }
    else
    {
        qDebug()<<"HeroController::refreshHeroView ---> Vector Hero is empty";
    }

}


/* Refresh the editable view
 *
 */
void HeroController::refreshEditableHeroView(int index)
{
    Hero hero = m_vectorHero[index];

    m_pHeroWidgetEdit->refreshView(hero.getStats(), hero.getFeatureHero(), hero.getEquipment(),
                               hero.getSkills(), hero.getEffect(), hero.getBag(), hero.getQuestObject());
}

