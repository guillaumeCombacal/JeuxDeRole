#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>

class BattleWidget : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout* m_pLayoutBattleMapWidget;

public:
    explicit BattleWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // BATTLEWIDGET_H
