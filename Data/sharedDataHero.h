#ifndef SHAREDDATAHERO_H
#define SHAREDDATAHERO_H

#include<QString>
#include<map>
#include<QVariantMap>
#include<QObject>

enum Job
{
    SOLDIER=0,
    BLACK_WIZARD,
    WHITE_WIZARD,
    FIGHTER,
    NINJA,
    JOB_MAX
};

enum Nature
{
    HUMAN=0,
    BANGAA,
    VIERA,
    NU_MOU,
    MOG,
    NATURE_MAX
};

enum Sex
{
    MALE=0,
    FEMALE,
    SEX_MAX
};

struct Stats
{

public:
    unsigned int m_PV;
    unsigned int m_PV_max;
    unsigned int m_PA;
    unsigned int m_PA_max;
    unsigned int m_PM;
    unsigned int m_Force;
    unsigned int m_Dexterite;
    unsigned int m_Intelligence;
    unsigned int m_Protection;
    unsigned int m_Armure;
};

struct Features
{
    Stats m_sStats;
    unsigned int m_Lvl;
    unsigned int m_Xp;
    QString m_Name;
    Job     m_eJob;
    Nature  m_eNature;
    Sex     m_eSex;
    QString m_UrlImg;

};

namespace ComCppQml
{
    QVariantMap featuresToQVariantMap(const Features &features);
}

struct Equipment
{
    QString m_Head;
    QString m_Chest;
    QString m_Leg;
    QString m_Feet;
    QString m_Hand;
    QString m_RightHandStuff;
    QString m_LeftHandStuff;
};

struct Skills
{
    QString m_FirstFightSkill;
    QString m_SecondFightSkill;
    QString m_SupportFightSkill;
};

struct Effect
{
    QString m_ClassEffect;
    QString m_RaceEffect;
    QString m_MalusEffect;
    QString m_BonusEffect;
};

struct Bag
{
    int m_Or;
    int m_Nourriture;
    //std::vector<QString> m_vBag;
    std::map<QString, int> m_mapBag;
};

struct QuestObject
{
    //std::vector<QString> m_vQuestObject;
    std::map<QString, int> m_mapQuestObject;
};


static const QString tabUrlMenuCharacterImg[JOB_MAX][NATURE_MAX][SEX_MAX] =
{
    {//SOLDIER

        {//HUMAN
            {"/Ressources/qmlRessources/BattleMap/Soldier.png"},
            {"/Ressources/qmlRessources/"}
        },

        {//BANGAA
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
    },
    {//BLACK_WIZARD

        {//HUMAN
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//VIERA
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//NU_MOU
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//MOG
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
    },
    {//WHITE_WIZARD

        {//HUMAN
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//VIERA
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//NU_MOU
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        }
    },
    {//FIGHTER

        {//HUMAN
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//BANGAA
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
        {//MOG
            {"/Ressources/qmlRessources/"},
            {"/Ressources/qmlRessources/"}
        },
    },
};



#endif // SHAREDDATAHERO_H
