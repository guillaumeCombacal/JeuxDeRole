#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>
#include <QString>

enum LevelLog
{
    DEBUG,
    INFO,
    ERROR
};

class ILogger
{
public:
   virtual ~ILogger   ( void ) {}
   virtual void write( const QString& ) = 0;
};

#endif // ILOGGER_H
