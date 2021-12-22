#ifndef BIOMETRICUSER_H
#define BIOMETRICUSER_H

#include <QJsonObject>
#include <QList>
#include <QString>



class BiometricUser
{
public:
    BiometricUser();
    BiometricUser(int a_id, QString a_name, QString a_pass, QList<double> a_biomVect);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

     QString getName() const;
    void setName(const QString &newName);

     QString getPass() const;
    void setPass(const QString &newPass);

     QList<double> getBiomVect() const;
    void setBiomVect(const QList<double> &newBiomVect);

    int getId() const;
    void setId(int newId);

private:
    int m_id;
    QString m_name;
    QString m_pass;
    QList<double> m_biomVect;
};

#endif // BIOMETRICUSER_H
