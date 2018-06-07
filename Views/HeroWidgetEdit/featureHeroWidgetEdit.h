#ifndef FEATUREHEROWIDGETEDIT_H
#define FEATUREHEROWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>

#include "sharedDataHero.h"

class FeatureHeroWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* m_pFeatureHeroLayout;
    QPushButton* m_pBtnImgFaceHero;
    QString      m_filenameImgFaceHero;

    QLineEdit*   m_pName;
    QLineEdit*   m_pRace;
    QLineEdit*   m_pSexe;
    QLineEdit*   m_pLevel;
    QLineEdit*   m_pXp;
    QLineEdit*   m_pJob;

    QLabel*      m_pLabelName;
    QLabel*      m_pLabelRace;
    QLabel*      m_pLabelSexe;
    QLabel*      m_pLabelLevel;
    QLabel*      m_pLabelXp;
    QLabel*      m_pLabelJob;

	
public:
    explicit FeatureHeroWidgetEdit(QWidget *parent = 0);
    ~FeatureHeroWidgetEdit();

    void refreshFeatureView(Feature feature);

    Feature getFeatureValues();
    QPushButton* getBtnImgHero();

signals:

private slots:


public slots:


};

#endif // FEATUREHEROWIDGETEDIT_H
