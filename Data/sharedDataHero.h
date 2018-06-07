#ifndef SHAREDDATAHERO_H
#define SHAREDDATAHERO_H

#include<QString>
#include<map>

struct Stats
{
    int m_PV;
    int m_PA;
    int m_PM;
    int m_Force;
    int m_Dexterite;
    int m_Intelligence;
    int m_Protection;
    int m_Armure;
};

struct Feature
{
    int m_Lvl;
    int m_Xp;
    QString m_Name;
    QString m_Job;
    QString m_Race;
    QString m_Sexe;
    QString m_FilenameImgFace;
};

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



#endif // SHAREDDATAHERO_H
