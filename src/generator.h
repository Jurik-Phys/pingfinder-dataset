// Begin generator.h
#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
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

        const int m_firstDay = 1;
        const int m_lastDay  = 31;
        const int m_minClientsPerDay = 4;
        const int m_maxClientsPerDay = 13;
        const QString m_jsonFullFileName = "/tmp/clients.json";

        QString getRndSex();
        QString getRndNickname();
        QString getRndFirstName(const QString& sex);
        QString getRndMiddleName(const QString& sex);
        QString getRndLastName(const QString& sex);
        QString getRndPhoneNumber();
        int getRndPayAmount();
};


#endif
// End generator.h
