#include "biometricuser.h"

#include <QJsonArray>

BiometricUser::BiometricUser()
{

}

BiometricUser::BiometricUser(int a_id,QString a_name, QString a_pass, QList<double> a_biomVect)
{
    m_id = a_id;
    m_name = a_name;
    m_pass = a_pass;
    m_biomVect = a_biomVect;
}

void BiometricUser::read(const QJsonObject &json)
{
    if (json.contains("id") && json["id"].isDouble())
        m_id = json["id"].toInt();

    if (json.contains("name") && json["name"].isString())
        m_name = json["name"].toString();

    if (json.contains("pass") && json["pass"].isString())
        m_pass = json["pass"].toString();

    if (json.contains("biomVect") && json["biomVect"].isArray()) {
        QJsonArray biomVectArray = json["biomVect"].toArray();
        m_biomVect.clear();
        m_biomVect.reserve(biomVectArray.size());
        for (int npcIndex = 0; npcIndex < biomVectArray.size(); ++npcIndex) {
            m_biomVect.append(biomVectArray[npcIndex].toDouble());
        }
    }
}

void BiometricUser::write(QJsonObject &json) const
{
    json["id"] = m_id;
    json["name"] = m_name;
    json["pass"] = m_pass;
    QJsonArray biomVectArray;
    for (const double &i : m_biomVect) {
        biomVectArray.append(i);
    }
    json["biomVect"] = biomVectArray;
}

QString BiometricUser::getName() const
{
    return m_name;
}

void BiometricUser::setName(const QString &newName)
{
    m_name = newName;
}

QString BiometricUser::getPass() const
{
    return m_pass;
}

void BiometricUser::setPass(const QString &newPass)
{
    m_pass = newPass;
}

QList<double> BiometricUser::getBiomVect() const
{
    return m_biomVect;
}

void BiometricUser::setBiomVect(const QList<double> &newBiomVect)
{
    m_biomVect = newBiomVect;
}

int BiometricUser::getId() const
{
    return m_id;
}

void BiometricUser::setId(int newId)
{
    m_id = newId;
}
