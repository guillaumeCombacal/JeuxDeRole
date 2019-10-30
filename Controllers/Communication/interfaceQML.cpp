#include "interfaceQML.h"
#include "MainWindowController.h"

InterfaceQML::InterfaceQML(MainWindowController* i_pMainWindowController):
    m_pMainWindowController(i_pMainWindowController)
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



