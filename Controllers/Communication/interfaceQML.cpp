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



