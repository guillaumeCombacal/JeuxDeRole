#include "loggerfile.h"

#include<QTime>

// Init la variable static du fichier qui sera éxrit
QFile LoggerFile::m_file("LogRPG_program.txt");

bool LoggerFile::m_isOpened = false;

LevelLog LoggerFile::m_levelLog = ERROR;

LoggerFile::LoggerFile()
{

}



LoggerFile::~LoggerFile()
{
    /*if(m_file != NULL)
    {
        delete m_file;
    }
    */
}

void LoggerFile::readConfFile()
{
    QFile confFile("configurationFile.txt");
    QTextStream stream(&confFile);

    if(!confFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
        // ERREUR ouverture fichier
    }

    // Si le fichier de configuration est ouvert
    // Lecture intégrale du fichier
    QString allDataFile = stream.readAll();

    // On récupère les data par split
    QStringList values = allDataFile.split(" ");

    if(values[1] == "DEBUG")
    {
        m_levelLog = DEBUG;
    }
    else if(values[1] == "INFO")
    {
        m_levelLog = INFO;
    }
    else if(values[1] == "ERROR")
    {
        m_levelLog = ERROR;
    }

}



void LoggerFile::write( LevelLog levelLog, const QString& function, const QString& msg )
{
    // Vérifie si le fichier est déjà ouvert
    if(!m_isOpened)
    {
        if(!m_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
            // ERREUR ouverture fichier
        }
       m_isOpened = true;
    }


    // Si le fichier est ouvert
    if(m_isOpened)
    {
        // Association d'un flux vers le fichier de sortie
        QTextStream l_stream(&m_file);
        l_stream.setCodec("UTF-8");

        // Ecriture de la ligne de log => Date | Time | Importance | Classe::Function | Message
        l_stream << QDate::currentDate().toString() << " "
                 << QTime::currentTime().toString() << "   "
                 << function << " "
                 << msg << endl;
    }

}
