#ifndef EFFECTWIDGETEDIT_H
#define EFFECTWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class EffectWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pEffectEditLayout;
    QLabel*      m_pEffectEditLabel;
    QLineEdit*   m_pRaceEffectEdit;
    QLineEdit*   m_pClassEffectEdit;
    QLineEdit*   m_pBonusEffectEdit;
    QLineEdit*   m_pMalusEffectEdit;
    QLabel*      m_pRaceEffectEditLabel;
    QLabel*      m_pClassEffectEditLabel;
    QLabel*      m_pBonusEffectEditLabel;
    QLabel*      m_pMalusEffectEditLabel;

public:
    explicit EffectWidgetEdit(QWidget *parent = 0);
    ~EffectWidgetEdit();

    void refreshEffectView(Effect effect);

    Effect getEffectValues();

signals:

private slots:


public slots:


};

#endif // EFFECTWIDGETEDIT_H
