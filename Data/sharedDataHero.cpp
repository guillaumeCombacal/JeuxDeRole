#include "sharedDataHero.h"

namespace ComCppQml
{
    QVariantMap featuresToQVariantMap(const Features &features)
    {
        QVariantMap statsMap;
        statsMap.insert("Armure", features.m_sStats.m_Armure);
        statsMap.insert("Dexterite", features.m_sStats.m_Dexterite);
        statsMap.insert("Force", features.m_sStats.m_Force);
        statsMap.insert("Intelligence", features.m_sStats.m_Intelligence);
        statsMap.insert("PA", QString::number(features.m_sStats.m_PA));
        statsMap.insert("MaxPA", QString::number(features.m_sStats.m_PA_max));
        statsMap.insert("PM", QString::number(features.m_sStats.m_PM));
        statsMap.insert("Protection", features.m_sStats.m_Protection);
        statsMap.insert("PV", QString::number(features.m_sStats.m_PV));
        statsMap.insert("MaxPV", QString::number(features.m_sStats.m_PV_max));
        statsMap.insert("Job", features.m_eJob);
        statsMap.insert("Race", features.m_eRace);
        statsMap.insert("Sex", features.m_eSex);
        statsMap.insert("Lvl", features.m_Lvl);
        statsMap.insert("Name", features.m_Name);
        statsMap.insert("Xp", QString::number(features.m_Xp));
        statsMap.insert("UrlImg", features.m_UrlImg);
        return statsMap;
    }
}
