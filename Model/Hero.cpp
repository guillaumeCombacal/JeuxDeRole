#include "Hero.h"

#include "QDebug"

Hero::Hero()
{
    // Init Default Feature values
    m_feature.m_FilenameImgFace = "";
    m_feature.m_Job = "";
    m_feature.m_Lvl = 1;
    m_feature.m_Name = "";
    m_feature.m_Race = "";
    m_feature.m_Sexe = "";
    m_feature.m_Xp = 0;

    // Init Default Stats values
    m_stats.m_Armure = 0;
    m_stats.m_Dexterite = 0;
    m_stats.m_Force = 0;
    m_stats.m_Intelligence = 0;
    m_stats.m_PA = 0;
    m_stats.m_PM = 0;
    m_stats.m_Protection = 0;
    m_stats.m_PV = 0;

    // Init Default Equipment values
    m_equipment.m_Chest = "";
    m_equipment.m_Feet = "";
    m_equipment.m_Hand = "";
    m_equipment.m_Head = "";
    m_equipment.m_LeftHandStuff = "";
    m_equipment.m_Leg = "";
    m_equipment.m_RightHandStuff = "";

    // Init Default Skills values
    m_skills.m_FirstFightSkill = "";
    m_skills.m_SecondFightSkill = "";
    m_skills.m_SupportFightSkill = "";

    // Init Default Effect values
    m_effect.m_BonusEffect = "";
    m_effect.m_ClassEffect = "";
    m_effect.m_MalusEffect = "";
    m_effect.m_RaceEffect = "";

    // Init Bag values
    m_bag.m_Nourriture = 0;
    m_bag.m_Or = 0;
    m_bag.m_mapBag.clear();

    // Init QuestObject values
    m_questObject.m_mapQuestObject.clear();
}

Hero::~Hero()
{

    /*if(!m_vBag.empty())
    {
        m_vBag.clear();
    }

    if(!m_vQuestObject.empty())
    {
        m_vQuestObject.clear();
    }*/
}

void Hero::addItemInBag(QString name, int number)
{
    /*for(int i=0; i<number; i++)
    {
        m_bag.m_vBag.push_back(name);
    }*/

    std::map<QString, int>::iterator it;
    it = m_bag.m_mapBag.find(name);

    // Si l'element est deja present dans la map, on incrémente sa valeur
    if(it != m_bag.m_mapBag.end())
    {
        it->second+=number;
    }
    else// Sinon on insert le nouvel élément
    {
        std::pair<QString, int> pairElement(name, number);
        m_bag.m_mapBag.insert(pairElement);
    }


}

void Hero::removeItemFromBag(QString name, int number)
{
    if(!m_bag.m_mapBag.empty())
    {
        std::map<QString, int>::iterator it;
        it = m_bag.m_mapBag.find(name);

        // Si l'element est present dans la map, on décrémente sa valeur
        if(it != m_bag.m_mapBag.end())
        {
            it->second-=number;

            // Si la valeur de l'élément tombe à zéro lors de la décrémentation il est détruit de la map
            if(it->second == 0 || it->second < 0)
            {
                m_bag.m_mapBag.erase(name);
            }
        }
        else// Si lélément n'est pas dans la map
        {
            qDebug()<<"l'élément "<<name<<" ne figure pas dans les objets";
        }
    }

}

void Hero::addQuestObj(QString name, int number)
{
    /*for(int i=0; i<number; i++)
    {
        m_questObject.m_vQuestObject.push_back(name);
    }*/

    std::map<QString, int>::iterator it;
    it = m_questObject.m_mapQuestObject.find(name);

    // Si l'element est deja present dans la map, on incrémente sa valeur
    if(it != m_questObject.m_mapQuestObject.end())
    {
        it->second+=number;
    }
    else// Sinon on insert le nouvel élément
    {
        std::pair<QString, int> pairElement(name, number);
        m_questObject.m_mapQuestObject.insert(pairElement);
    }
}

void Hero::removeQuestObj(QString name, int number)
{
    if(!m_questObject.m_mapQuestObject.empty())
    {
        std::map<QString, int>::iterator it;
        it = m_questObject.m_mapQuestObject.find(name);

        // Si l'element est present dans la map, on décrémente sa valeur
        if(it != m_questObject.m_mapQuestObject.end())
        {
            it->second-=number;

            // Si la valeur de l'élément tombe à zéro lors de la décrémentation il est détruit de la map
            if(it->second == 0 || it->second < 0)
            {
                m_questObject.m_mapQuestObject.erase(name);
            }
        }
        else// Si lélément n'est pas dans la map
        {
            qDebug()<<"l'élément "<<name<<" ne figure pas dans les objets";
        }
    }
}

void Hero::loadHero(QList<XmlField> listField)
{
    XmlField field;
    while(!listField.isEmpty())
    {
        // Take the first element in the list and remove it from the list
        field = listField.takeFirst();

        // the number of field in the struct
        int nbField;

        // If the field is a struct
        if(field.m_type == "struct")
        {

            //Feature
            if(field.m_value == "feature")
            {
                qDebug()<<"FEATURE LOADING";

                nbField = field.m_size;
                for(int i =0; i<nbField; i++)
                {
                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();

                        qDebug()<<"------ FIELD -------";
                        qDebug()<<field.m_size;
                        qDebug()<<field.m_type;
                        qDebug()<<field.m_value;
                        qDebug()<<"--------------------";

                        if(field.m_type == "name")
                        {
                            qDebug()<<"NAME_HERO =============> " << m_feature.m_Name;
                            m_feature.m_Name = field.m_value;
                        }
                        else if(field.m_type == "race")
                        {
                            m_feature.m_Race = field.m_value;
                        }
                        else if(field.m_type == "job")
                        {
                            m_feature.m_Job = field.m_value;
                        }
                        else if(field.m_type == "lvl")
                        {
                            m_feature.m_Lvl = field.m_value.toInt();
                        }
                        else if(field.m_type == "xp")
                        {
                            m_feature.m_Xp = field.m_value.toInt();
                        }
                        else if(field.m_type == "sexe")
                        {
                            m_feature.m_Sexe = field.m_value;
                        }
                        else if(field.m_type == "filenameImgFaceHero")
                        {
                            m_feature.m_FilenameImgFace = field.m_value;
                        }
                    }
                    else
                    {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty";
                    }
                }

            }
            //Stats
            else if(field.m_value == "stats")
            {

                qDebug()<<"STATS LOADING";

                nbField = field.m_size;
                for(int i =0; i<nbField; i++)
                {
                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();

                        if(field.m_type == "pv")
                        {
                            m_stats.m_PV = field.m_value.toInt();
                        }
                        else if(field.m_type == "pa")
                        {
                            m_stats.m_PA = field.m_value.toInt();
                        }
                        else if(field.m_type == "pm")
                        {
                            m_stats.m_PM = field.m_value.toInt();
                        }
                        else if(field.m_type == "force")
                        {
                            m_stats.m_Force = field.m_value.toInt();
                        }
                        else if(field.m_type == "dexterite")
                        {
                            m_stats.m_Dexterite = field.m_value.toInt();
                        }
                        else if(field.m_type == "intelligence")
                        {
                            m_stats.m_Intelligence = field.m_value.toInt();
                        }
                        else if(field.m_type == "protection")
                        {
                            m_stats.m_Protection = field.m_value.toInt();
                        }
                        else if(field.m_type == "armure")
                        {
                            m_stats.m_Armure = field.m_value.toInt();
                        }
                     }
                     else
                     {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty Stats";
                     }
                }
            }
            else if(field.m_value == "equipment")
            {
                qDebug()<<"EQUIPMENT LOADING";

                nbField = field.m_size;
                for(int i =0; i<nbField; i++)
                {
                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();

                        if(field.m_type == "head")
                        {
                            m_equipment.m_Head = field.m_value;
                        }
                        else if(field.m_type == "chest")
                        {
                            m_equipment.m_Chest = field.m_value;
                        }
                        else if(field.m_type == "leg")
                        {
                            m_equipment.m_Leg = field.m_value;
                        }
                        else if(field.m_type == "feet")
                        {
                            m_equipment.m_Feet = field.m_value;
                        }
                        else if(field.m_type == "hand")
                        {
                            m_equipment.m_Hand = field.m_value;
                        }
                        else if(field.m_type == "rightHandStuff")
                        {
                            m_equipment.m_RightHandStuff = field.m_value;
                        }
                        else if(field.m_type == "leftHandStuff")
                        {
                            m_equipment.m_LeftHandStuff = field.m_value;
                        }
                    }
                    else
                    {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty equipment";
                    }
                 }
            }
            else if(field.m_value == "skill")
            {
                qDebug()<<"SKILL LOADING";

                nbField = field.m_size;
                for(int i =0; i<nbField; i++)
                {
                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();
                        if(field.m_type == "firstFightSkill")
                        {
                            m_skills.m_FirstFightSkill = field.m_value;
                        }
                        else if(field.m_type == "secondFightSkill")
                        {
                            m_skills.m_SecondFightSkill = field.m_value;
                        }
                        else if(field.m_type == "supportFightSkill")
                        {
                            m_skills.m_SupportFightSkill = field.m_value;
                        }
                    }
                    else
                    {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty skill";
                    }

                 }
            }
            else if(field.m_value == "effect")
            {
                qDebug()<<"EFFECT LOADING";

                nbField = field.m_size;
                for(int i =0; i<nbField; i++)
                {
                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();
                        if(field.m_type == "classEffect")
                        {
                            m_effect.m_ClassEffect = field.m_value;
                        }
                        else if(field.m_type == "raceEffect")
                        {
                            m_effect.m_RaceEffect = field.m_value;
                        }
                        else if(field.m_type == "malusEffect")
                        {
                            m_effect.m_MalusEffect = field.m_value;
                        }
                        else if(field.m_type == "bonusEffect")
                        {
                            m_effect.m_BonusEffect = field.m_value;
                        }
                    }
                    else
                    {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty skill";
                    }

                 }
            }
            else if(field.m_value == "bag")
            {
                qDebug()<<"BAG LOADING";

                nbField = field.m_size;

                m_bag.m_mapBag.clear();

                for(int i =0; i<nbField; i++)
                {
                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();
                        if(field.m_type == "or")
                        {
                            m_bag.m_Or = field.m_value.toInt();
                        }
                        else if(field.m_type == "nourriture")
                        {
                            m_bag.m_Nourriture = field.m_value.toInt();
                        }
                        else if(field.m_type == "object")
                        {
                            //m_bag.m_vBag.push_back(field.m_value);
                            addItemInBag(field.m_value, field.m_number);
                        }
                    }
                    else
                    {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty";
                    }
                 }
            }
            else if(field.m_value == "questObject")
            {
                qDebug()<<"QUESTOBJECT LOADING => "<<field.m_size;

                m_questObject.m_mapQuestObject.clear();

                nbField = field.m_size;
                for(int i =0; i<nbField; i++)
                {

                    if(!listField.isEmpty())
                    {
                        field = listField.takeFirst();
                        if(field.m_type == "questObject")
                        {
                            //m_questObject.m_vQuestObject.push_back(field.m_value);
                            addQuestObj(field.m_value, field.m_number);

                        }
                    }
                    else
                    {
                        // TODO: SEND LOG
                        qDebug()<<"listField is empty";
                    }

                }
            }
        }
    }
}

void Hero::saveHeroValue(Stats stats, Feature feature, Equipment equipment,
                         Skills skills, Effect effect, Bag bag, QuestObject questObject)
{

    // Feature
    m_feature.m_Job = feature.m_Job;
    m_feature.m_Lvl = feature.m_Lvl;
    m_feature.m_Name = feature.m_Name;
    m_feature.m_Race = feature.m_Race;
    m_feature.m_Xp = feature.m_Xp;
    m_feature.m_Sexe = feature.m_Sexe;
    m_feature.m_FilenameImgFace = feature.m_FilenameImgFace;

    // Stats
    m_stats.m_PV = stats.m_PV;
    m_stats.m_PM = stats.m_PM;
    m_stats.m_PA = stats.m_PA;
    m_stats.m_Force = stats.m_Force;
    m_stats.m_Dexterite = stats.m_Dexterite;
    m_stats.m_Intelligence = stats.m_Intelligence;
    m_stats.m_Protection = stats.m_Protection;
    m_stats.m_Armure = stats.m_Armure;

    // Equipment
    m_equipment.m_Chest = equipment.m_Chest;
    m_equipment.m_Feet = equipment.m_Feet;
    m_equipment.m_Hand = equipment.m_Hand;
    m_equipment.m_Head = equipment.m_Head;
    m_equipment.m_LeftHandStuff = equipment.m_LeftHandStuff;
    m_equipment.m_Leg = equipment.m_Leg;
    m_equipment.m_RightHandStuff = equipment.m_RightHandStuff;

    // Skills
    m_skills.m_FirstFightSkill = skills.m_FirstFightSkill;
    m_skills.m_SecondFightSkill = skills.m_SecondFightSkill;
    m_skills.m_SupportFightSkill = skills.m_SupportFightSkill;

    // Effect
    m_effect.m_BonusEffect = effect.m_BonusEffect;
    m_effect.m_ClassEffect = effect.m_ClassEffect;
    m_effect.m_MalusEffect = effect.m_MalusEffect;
    m_effect.m_RaceEffect = effect.m_RaceEffect;

    // Bag
    m_bag.m_Nourriture = bag.m_Nourriture;
    m_bag.m_Or = bag.m_Or;

    m_bag.m_mapBag.clear();
    // Copie tous les obj de bag.m_mapBag dans m_bag.m_mapBag
    m_bag.m_mapBag.insert(bag.m_mapBag.begin(), bag.m_mapBag.end());

    // QuestObject
    m_questObject.m_mapQuestObject.clear();
    // Copie tous les questObj de questObject.m_mapQuestObject dans m_questObject.m_mapQuestObject
    m_questObject.m_mapQuestObject.insert(questObject.m_mapQuestObject.begin(), questObject.m_mapQuestObject.end());
}

void Hero::setImgFaceHero(QString filename)
{
    m_feature.m_FilenameImgFace = filename;
}


const Feature& Hero::getFeatureHero()
{
    return m_feature;
}

const QuestObject& Hero::getQuestObject()
{
    return m_questObject;
}

const Bag& Hero::getBag()
{
    return m_bag;
}

const Skills& Hero::getSkills()
{
    return m_skills;
}

const Effect& Hero::getEffect()
{
    return m_effect;
}

const Equipment& Hero::getEquipment()
{
    return m_equipment;
}

const Stats& Hero::getStats()
{
    return m_stats;
}

QList<XmlField> Hero::getXmlField()
{
    QList<XmlField> xmlFieldList;

    XmlField xmlField;

    // Iterator pour parcourir les maps Bag et QuestObj
    std::map<QString, int>::iterator it;

    // Feature
    xmlField.m_size = 7; xmlField.m_type = "struct"; xmlField.m_value = "feature";
    xmlFieldList.push_back(xmlField);

    xmlField.m_size = 1; xmlField.m_type = "name"; xmlField.m_value = m_feature.m_Name;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "race"; xmlField.m_value = m_feature.m_Race;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "job"; xmlField.m_value = m_feature.m_Job;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "lvl"; xmlField.m_value = QString::number(m_feature.m_Lvl);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "xp"; xmlField.m_value = QString::number(m_feature.m_Xp);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "sexe"; xmlField.m_value = m_feature.m_Sexe;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "filenameImgFaceHero"; xmlField.m_value = m_feature.m_FilenameImgFace;
    xmlFieldList.push_back(xmlField);

    // Stats
    xmlField.m_size = 8; xmlField.m_type = "struct"; xmlField.m_value = "stats";
    xmlFieldList.push_back(xmlField);

    xmlField.m_size = 1; xmlField.m_type = "pv"; xmlField.m_value = QString::number(m_stats.m_PV);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "pa"; xmlField.m_value = QString::number(m_stats.m_PA);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "pm"; xmlField.m_value = QString::number(m_stats.m_PM);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "force"; xmlField.m_value = QString::number(m_stats.m_Force);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "dexterite"; xmlField.m_value = QString::number( m_stats.m_Dexterite);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "intelligence"; xmlField.m_value = QString::number(m_stats.m_Intelligence);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "protection"; xmlField.m_value = QString::number(m_stats.m_Protection);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "armure"; xmlField.m_value = QString::number(m_stats.m_Armure);
    xmlFieldList.push_back(xmlField);

    // Equipment
    xmlField.m_size = 7; xmlField.m_type = "struct"; xmlField.m_value = "equipment";
    xmlFieldList.push_back(xmlField);

    xmlField.m_size = 1; xmlField.m_type = "head"; xmlField.m_value = m_equipment.m_Head;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "chest"; xmlField.m_value = m_equipment.m_Chest;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "leg"; xmlField.m_value = m_equipment.m_Leg;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "feet"; xmlField.m_value = m_equipment.m_Feet;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "hand"; xmlField.m_value = m_equipment.m_Hand;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "rightHandStuff"; xmlField.m_value = m_equipment.m_RightHandStuff;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "leftHandStuff"; xmlField.m_value = m_equipment.m_LeftHandStuff;
    xmlFieldList.push_back(xmlField);

    // Skills
    xmlField.m_size = 3; xmlField.m_type = "struct"; xmlField.m_value = "skill";
    xmlFieldList.push_back(xmlField);

    xmlField.m_size = 1; xmlField.m_type = "firstFightSkill"; xmlField.m_value = m_skills.m_FirstFightSkill;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "secondFightSkill"; xmlField.m_value = m_skills.m_SecondFightSkill;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "supportFightSkill"; xmlField.m_value = m_skills.m_SupportFightSkill;
    xmlFieldList.push_back(xmlField);

    // Effect
    xmlField.m_size = 4; xmlField.m_type = "struct"; xmlField.m_value = "effect";
    xmlFieldList.push_back(xmlField);

    xmlField.m_size = 1; xmlField.m_type = "classEffect"; xmlField.m_value = m_effect.m_ClassEffect;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "raceEffect"; xmlField.m_value = m_effect.m_RaceEffect;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "malusEffect"; xmlField.m_value = m_effect.m_MalusEffect;
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "bonusEffect"; xmlField.m_value = m_effect.m_BonusEffect;
    xmlFieldList.push_back(xmlField);

    // Bag m_bag.m_vBag.size() + 2 ==> éléments + or + nourriture
    xmlField.m_size = int(m_bag.m_mapBag.size()) + 2; xmlField.m_type = "struct"; xmlField.m_value = "bag";
    xmlFieldList.push_back(xmlField);

    xmlField.m_size = 1; xmlField.m_type = "or"; xmlField.m_value = QString::number(m_bag.m_Or);
    xmlFieldList.push_back(xmlField);
    xmlField.m_size = 1; xmlField.m_type = "nourriture"; xmlField.m_value = QString::number(m_bag.m_Nourriture);
    xmlFieldList.push_back(xmlField);

    for(it = m_bag.m_mapBag.begin();it != m_bag.m_mapBag.end(); ++it)
    {
        xmlField.m_size = 1; xmlField.m_type = "object"; xmlField.m_value = it->first; xmlField.m_number = it->second;
        xmlFieldList.push_back(xmlField);
    }


    // Quest Object
    xmlField.m_size = int(m_questObject.m_mapQuestObject.size()); xmlField.m_type = "struct"; xmlField.m_value = "questObject";
    xmlFieldList.push_back(xmlField);

    for(it = m_questObject.m_mapQuestObject.begin();it != m_questObject.m_mapQuestObject.end(); ++it)
    {
        xmlField.m_size = 1; xmlField.m_type = "questObject"; xmlField.m_value = it->first; xmlField.m_number = it->second;
        xmlFieldList.push_back(xmlField);
    }

    return xmlFieldList;
}
