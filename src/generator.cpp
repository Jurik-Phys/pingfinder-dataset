// Begin generator.cpp

#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>
#include "generator.h"
#include "dictionary.h"

Generator::Generator(QObject *parent) : QObject(parent){

    m_clients = generateClientDataset(m_firstDay, m_lastDay,
                                        m_minClientsPerDay, m_maxClientsPerDay);

    writeJson(m_clients);

    exit(0);
}

Generator::~Generator(){
}

QVector<Client> Generator::generateClientDataset(const int& firstDay,
                                                 const int& lastDay,
                                                 const int& minClientsPerDay,
                                                 const int& maxClientsPerDay){

    QVector<Client> res;
    int clientId = 0;

    for (int day = firstDay; day <= lastDay; day++ ){
        int thisDayClients = getDayClients(minClientsPerDay, maxClientsPerDay);
        qDebug() << "// *** DAY" << day << "*** //";
        for (int n = 1; n <= thisDayClients; n++){
            clientId++;
            Client iClient = generateSingleClient(clientId, day);

            qDebug() << "    Client №" << n;;
            qDebug() << "    > id          " << iClient.id;
            qDebug() << "    > nickname    " << iClient.nickname;
            qDebug() << "    > first name  " << iClient.firstName;
            qDebug() << "    > middle name " << iClient.middleName;
            qDebug() << "    > last name   " << iClient.lastName;
            qDebug() << "    > phone number" << iClient.phoneNumber;
            qDebug() << "    > reminder Day" << iClient.reminderDay;
            qDebug() << "    > pay amount  " << iClient.payAmount;
            qDebug() << "    > enabled     " << iClient.enabled;
            res.push_back(iClient);
        }
    }

    return res;
}

Client Generator::generateSingleClient(const int& id, const int& day){
    Client newClient ;

    QString sex = getRndSex();
    newClient.id = id;
    newClient.nickname    = getRndNickname();
    newClient.firstName   = getRndFirstName(sex);
    newClient.middleName  = getRndMiddleName(sex);
    newClient.lastName    = getRndLastName(sex);
    newClient.phoneNumber = getRndPhoneNumber();
    newClient.reminderDay  = day;
    newClient.payAmount   = getRndPayAmount();
    newClient.enabled     = true;

    return newClient;
}

int Generator::getDayClients(const int& minClientsPerDay,
                                                   const int& maxClientsPerDay){
    int res;
    res = QRandomGenerator::global()->bounded(minClientsPerDay,
                                                          maxClientsPerDay + 1);
    return res;
}

QString Generator::getRndNickname(){
    int lo = 0;
    int hi = Dictionary::nicknames.size();
    int nickIndex = QRandomGenerator::global()->bounded(lo,hi);

    return Dictionary::nicknames.at(nickIndex);
}

QString Generator::getRndSex(){
    int sexId = QRandomGenerator::global()->bounded(0, 2);
    QString sex;

    switch (sexId) {
        case 0:
            sex = "male";
            break;
        case 1:
            sex = "female";
            break;
    }

    return sex;
}

QString Generator::getRndFirstName(const QString& sex){
    QString firstName;
    int lo = 0;

    if (sex == "male"){
        int hi = Dictionary::maleFirstNames.size();
        int maleFirstNamesIndex = QRandomGenerator::global()->bounded(lo,hi);
        firstName = Dictionary::maleFirstNames.at(maleFirstNamesIndex);
    }
    else{
        int hi = Dictionary::femaleFirstNames.size();
        int femaleFirstNamesIndex = QRandomGenerator::global()->bounded(lo,hi);
        firstName = Dictionary::femaleFirstNames.at(femaleFirstNamesIndex);
    }

    return firstName;
}

QString Generator::getRndMiddleName(const QString& sex){
    QString middleName;
    int lo = 0;

    if (sex == "male"){
        int hi = Dictionary::maleMiddleNames.size();
        int maleMiddleNamesIndex = QRandomGenerator::global()->bounded(lo, hi);
        middleName = Dictionary::maleMiddleNames.at(maleMiddleNamesIndex);
    }
    else {
        int hi = Dictionary::femaleMiddleNames.size();
        int femaleMiddleNamesIndex = QRandomGenerator::global()->bounded(lo,hi);
        middleName = Dictionary::femaleMiddleNames.at(femaleMiddleNamesIndex);
    }

    return middleName;
}

QString Generator::getRndLastName(const QString& sex){
    QString lastName;
    int lo = 0;

    if (sex == "male"){
        int hi = Dictionary::maleLastNames.size();
        int maleLastNamesIndex = QRandomGenerator::global()->bounded(lo, hi);
        lastName = Dictionary::maleLastNames.at(maleLastNamesIndex);
    }
    else {
        int hi = Dictionary::femaleLastNames.size();
        int femaleLastNamesIndex = QRandomGenerator::global()->bounded(lo, hi);
        lastName = Dictionary::femaleLastNames.at(femaleLastNamesIndex);
    }

    return lastName;
}

QString Generator::getRndPhoneNumber(){
    QString phoneNumber = "+7-9";

    int     aaNum = QRandomGenerator::global()->bounded(0, 100);
    QString aaStr = QString("%1").arg(aaNum, 2, 10, QChar('0'));
    phoneNumber = phoneNumber + aaStr + "-";

    int     bbbNum = QRandomGenerator::global()->bounded(0, 1000);
    QString bbbStr = QString("%1").arg(bbbNum, 3, 10, QChar('0'));
    phoneNumber = phoneNumber + bbbStr + "-";

    int     ccNum = QRandomGenerator::global()->bounded(0, 100);
    QString ccStr = QString("%1").arg(ccNum, 2, 10, QChar('0'));
    phoneNumber = phoneNumber + ccStr + "-";

    int     ddNum = QRandomGenerator::global()->bounded(0, 100);
    QString ddStr = QString("%1").arg(ddNum, 2, 10, QChar('0'));
    phoneNumber = phoneNumber + ddStr;

    return phoneNumber;
}

int Generator::getRndPayAmount(){
    return QRandomGenerator::global()->bounded(100, 1001);
}

void Generator::writeJson(const QVector<Client>& clients){
    QJsonArray clientsArray;

    for (int i = 0; i < clients.size(); ++i){
        QJsonObject clientObj;
        clientObj["id"]           = clients[i].id;
        clientObj["nickname"]     = clients[i].nickname;
        clientObj["first_name"]   = clients[i].firstName;
        clientObj["middle_name"]  = clients[i].middleName;
        clientObj["last_name"]    = clients[i].lastName;
        clientObj["phone_number"] = clients[i].phoneNumber;
        clientObj["reminder_day"] = clients[i].reminderDay;
        clientObj["pay_amount"]   = clients[i].payAmount;
        clientObj["enabled"]      = clients[i].enabled;
        clientsArray.append(clientObj);
    }

    QJsonObject root;

    QJsonObject aboutObj;
    aboutObj["description"] = "Dataset для разработки и тестирования утилиты "
                                                              "pingfinder-msgd";

    root["about"] = aboutObj;
    root["clients"] = clientsArray;

    QJsonDocument doc(root);

    QFile file(m_jsonFullFileName);
    if (file.open(QIODevice::WriteOnly)){
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }

    qDebug() << "Generated dataset writed to" << m_jsonFullFileName;
}

// End generator.cpp
