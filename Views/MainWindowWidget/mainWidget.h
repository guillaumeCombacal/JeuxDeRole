#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *m_pMainLayoutMainWidget;

    QWidget *m_pOngletWidget;

    QStackedWidget *m_pStackWidget;

public:
    explicit MainWidget(QWidget *ongletWidget, QWidget *worldMapWidget,  QWidget *battleWidget,
                        QWidget *heroWidget, QWidget *heroWidgetEdit,  QWidget *questWidget,
                        QWidget *parent = 0);
    ~MainWidget();

    QStackedWidget *getStackWidget();

signals:

public slots:
};

#endif // MAINWIDGET_H
