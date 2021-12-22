#ifndef BIOMETRICDB_H
#define BIOMETRICDB_H

#include "biometricuser.h"

#include <QJsonObject>
#include <QList>
#include "JsonOperations/biometricuser.h"

class BiometricDB
{
public:
    BiometricDB() = default;
    BiometricDB(QString a_dbName);

    bool load();
    bool save() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;

     QString dbName() const;
    void setDbName(const QString &newDbName);

     QList<BiometricUser> users() const;
    void setUsers(const QList<BiometricUser> &newUsers);

    QString append(BiometricUser a_user);
    int getLastId();
    QString autorization(BiometricUser a_user);

private:
    QString m_dbName;
    QList<BiometricUser> m_users;

    bool vectorTest(QList<double> a_vec1, QList<double> a_vec2);
    QString vectorToString(QList<double> a_vec);

    double m_amplitudeOnCount = 200;
};

#endif // BIOMETRICDB_H
