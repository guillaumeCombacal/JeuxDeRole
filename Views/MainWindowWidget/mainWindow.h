#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "mainWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainWidget *mainWidget, QWidget *parent = 0);
    ~MainWindow();

private:
    MainWidget *m_pMainWidget ;

    QMenu *m_pFileMenu;
    QAction *m_pActLoadingGame;
    QAction *m_pActSavingGame;
    QMenuBar *m_pMenuBar;

private:
    void createMenuBar();
};

#endif // MAINWINDOW_H
