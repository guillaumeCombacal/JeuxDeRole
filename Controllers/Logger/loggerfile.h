#ifndef LOGGERFILE_H
#define LOGGERFILE_H

#include"ilogger.h"

#include <QFile>
#include <QString>
#include <QTextStream>


class LoggerFile : public ILogger
{
public:
    LoggerFile();
    virtual ~LoggerFile();

    static void write( LevelLog levelLog, const QString& function, const QString& );
    static void readConfFile();

    static LevelLog m_levelLog;

private:

    // Le fichier dans lequel on écrit doit être commun à toutes les instances LoggerFile pour éviter d'écraser le file à chaque fois
    static QFile m_file;
    static bool m_isOpened;
};

#endif // LOGGERFILE_H
