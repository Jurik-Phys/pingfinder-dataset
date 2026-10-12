// Begin generator.h
#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QSet>
#include "client.h"

class Generator : public QObject {

    Q_OBJECT

    public:
        Generator(QObject *parent = nullptr);
        ~Generator();

        QVector<Client> generateClientDataset(const int& firstDay,
                                              const int& lastDay,
                                              const int& minClientsPerDay,
                                              const int& maxClientsPerDay);

        void writeJson(const QVector<Client>&);

    private:
        Client generateSingleClient(const int& id, const int& day);

    private:
        int getDayClients(const int& minClientsPerDay,
                                                   const int& maxClientsPerDay);
        QVector<Client> m_clients;
        QStringList getUniqueListOfRandNicknames();

        const int m_firstDay = 1;
        const int m_lastDay  = 31;
        const int m_minClientsPerDay = 4;
        const int m_maxClientsPerDay = 13;
        const QString m_jsonFullFileName = "/tmp/clients.json";

        QString getRndSex();
        QString getRndNickname(const int& clientId);
        QString getRndFirstName(const QString& sex);
        QString getRndMiddleName(const QString& sex);
        QString getRndLastName(const QString& sex);
        QString getRndPhoneNumber();
        int getRndPayAmount();

        // Используемые ники должны быть уникальны т.к., может возникнуть
        // проблема при отправке сообщения через pingfinder-push, где обращение
        // к клиенту идёт через его nickname, а о id данная утилита не знает и
        // знать не должна.
        QStringList   m_uniqueRandNicknames;
};


#endif
// End generator.h
