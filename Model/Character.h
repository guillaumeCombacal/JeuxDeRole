#ifndef CHARACTER_H
#define CHARACTER_H

#include<vector>
#include<QString>
#include<QVector>

class Character
{

private:

    int m_positionOnBattleMap;// -1 -> there is no Battle currently

public:
     Character();
     virtual ~Character();


};

#endif // CHARACTER_H
