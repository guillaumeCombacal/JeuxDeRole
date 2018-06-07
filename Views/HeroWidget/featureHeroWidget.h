#ifndef FEATUREHEROWIDGET_H
#define FEATUREHEROWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>

#include "sharedDataHero.h"

class FeatureHeroWidget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* m_pFeatureHeroLayout;
    QLabel*      m_pLabelImgFaceHero;
    QImage*      m_pImgFaceHero;

    QLabel*      m_pLabelName;
    QLabel*      m_pLabelLevel;
    QLabel*      m_pLabelJob;
    QLabel*      m_pLabelRace;
    QLabel*      m_pLabelXp;
    QLabel*      m_pLabelSexe;

    QLabel*      m_pLabelNameValue;
    QLabel*      m_pLabelLevelValue;
    QLabel*      m_pLabelJobValue;
    QLabel*      m_pLabelRaceValue;
    QLabel*      m_pLabelXpValue;
    QLabel*      m_pLabelSexeValue;

public:
    explicit FeatureHeroWidget(QWidget *parent = 0);
    ~FeatureHeroWidget();

    void refreshFeatureView(Feature feature);
signals:

private slots:


public slots:


};

#endif // FEATUREHEROWIDGET_H
