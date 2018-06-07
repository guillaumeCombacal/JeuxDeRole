#ifndef EFFECTWIDGET_H
#define EFFECTWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class EffectWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pEffectLayout;
    QLabel*      m_pEffectLabel;

    QLabel*      m_pLabelRaceEffect;
    QLabel*      m_pLabelClassEffect;
    QLabel*      m_pLabelBonusEffect;
    QLabel*      m_pLabelMalusEffect;

    QLabel*      m_pLabelRaceEffectValue;
    QLabel*      m_pLabelClassEffectValue;
    QLabel*      m_pLabelBonusEffectValue;
    QLabel*      m_pLabelMalusEffectValue;

public:
    explicit EffectWidget(QWidget *parent = 0);
    ~EffectWidget();

    void refreshEffectView(Effect effect);

signals:

private slots:


public slots:


};

#endif // EFFECTWIDGET_H
