#ifndef HERO_H
#define HERO_H

#include<vector>
#include<QString>

#include"sharedDataXmlField.h"
#include"sharedDataHero.h"


class Hero
{

private:

    Stats m_stats;
    Feature m_feature;
    Equipment m_equipment;
    Skills m_skills;
    Effect m_effect;
    Bag m_bag;
    QuestObject m_questObject;


public:
     Hero();
    ~Hero();
     void loadHero(QList<XmlField> listField);
     void saveHeroValue(Stats stats, Feature feature, Equipment equipment,
                        Skills skills, Effect effect, Bag bag, QuestObject questObject);

     const Feature&     getFeatureHero();
     const QuestObject& getQuestObject();
     const Bag&         getBag();
     const Skills&      getSkills();
     const Effect&      getEffect();
     const Equipment&   getEquipment();
     const Stats&       getStats();

     void setImgFaceHero(QString filename);

     void addItemInBag(QString name, int number);
     void removeItemFromBag(QString name, int number);
     void addQuestObj(QString name, int number);
     void removeQuestObj(QString name, int number);

     QList<XmlField>    getXmlField();

};

#endif // HERO_H
