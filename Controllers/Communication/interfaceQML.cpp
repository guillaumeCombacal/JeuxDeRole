#include "interfaceQML.h"
#include "MainWindowController.h"

#include <QQuickView>
#include <QQmlContext>

InterfaceQML::InterfaceQML(MainWindowController* i_pMainWindowController, QQuickView* i_pViewQML):
    m_pMainWindowController(i_pMainWindowController),
    m_pViewQML(i_pViewQML)
{
}

InterfaceQML::~InterfaceQML()
{

}


void InterfaceQML::eventKeyboardFromQML(QJSValue keyValue)
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->eventKeyBoard(keyValue.toInt());
    }
}

void InterfaceQML::changeViewType(QJSValue keyValue)
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->changeView((ViewType)keyValue.toInt());
    }
}

void InterfaceQML::fightRequest()
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->fightRequest();
    }
}

void InterfaceQML::orientationRequest()
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->orientationRequest();
    }
}


void InterfaceQML::selectCharacterToAddInBattle(QVariantMap data)
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->selectCharacterToAddInBattle(data.value("name").toString(),
                                                              data.value("job").toString(),
                                                              data.value("nature").toString(),
                                                              data.value("lvl").toInt()
                                                              );
    }
}

void InterfaceQML::enterAddingCharacterState()
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->enterAddingCharacterState();
    }
}

void InterfaceQML::finishAddingCharacterState()
{
    if(m_pMainWindowController != NULL)
    {
        m_pMainWindowController->finishAddingCharacterState();
    }
}



