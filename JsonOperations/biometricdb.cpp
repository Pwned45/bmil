#include "biometricdb.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

BiometricDB::BiometricDB(QString a_dbName)
{
    m_dbName = a_dbName;
}

 QString BiometricDB::dbName() const
{
    return m_dbName;
}

void BiometricDB::setDbName(const QString &newDbName)
{
    m_dbName = newDbName;
}

QList<BiometricUser> BiometricDB::users() const
{
    return m_users;
}

void BiometricDB::setUsers(const QList<BiometricUser> &newUsers)
{
    m_users = newUsers;
}

QString BiometricDB::append(BiometricUser a_user)
{
    for (int i = 0 ; i < m_users.size(); i++){
        if(m_users.at(i).getName() == a_user.getName()){
            return "такое имя пользователя уже существует";
        }
    }
    m_users.append(a_user);
    m_users[m_users.size()-1].setId(m_users.size()-1);
    return "регистрация успешна";
}

int BiometricDB::getLastId()
{
    if (m_users.size() == 0){
        return -1;
    }
    int l_lastID = -1;
    for (int i = m_users.size()-1 ; i > 0; i--){
        if(l_lastID < m_users.at(i).getId()) {
            l_lastID =  m_users.at(i).getId();
        }
    }
    return l_lastID;
}

QString BiometricDB::autorization(BiometricUser a_user)
{
    for (int i = 0 ; i < m_users.size(); i ++){
        if(a_user.getName() == m_users.at(i).getName() &&
                a_user.getPass() == m_users.at(i).getPass()){
            if (vectorTest(a_user.getBiomVect(),m_users.at(i).getBiomVect())){
                QString avec = vectorToString(a_user.getBiomVect());
                return "авторизация успешна для " + a_user.getName() + " с вектором " + avec;
            } else {
                return "авторизация по биометрическому вектору неуспешна";
            }
        }
    }
    return "данный пользователь не найден";
}

bool BiometricDB::vectorTest(QList<double> a_vec1, QList<double> a_vec2)
{
  if(a_vec1.size() != a_vec2.size()){
      return false;
  }
  double l_sum1 = 0;
  double l_sum2 = 0;
  for (int i = 0 ; i< a_vec1.size(); i++){
      l_sum1+= fabs(a_vec1.at(i));
      l_sum2+= fabs(a_vec2.at(i));
  }
  if (l_sum1 < l_sum2 +m_amplitudeOnCount && l_sum1 +m_amplitudeOnCount > l_sum2){
      return true;
  }
  return false;
}

QString BiometricDB::vectorToString(QList<double> a_vec)
{
    QString l_s;
    for (double v:a_vec){
        l_s+=QString::number(v) + " ";
    }
    return l_s;
}

bool BiometricDB::load()
{
    QFile loadFile("C:/Users/Daniil/Desktop/fm/db.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    QTextStream(stdout) << "Loaded save for "
                        << loadDoc["player"]["name"].toString()
                        << " using "
                        << ("JSON") << "...\n";
    return true;
}

bool BiometricDB::save() const
{
    QFile saveFile("C:/Users/Daniil/Desktop/fm/db.json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        printf("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    saveFile.write(QJsonDocument(gameObject).toJson());

    return true;
}

void BiometricDB::read(const QJsonObject &json)
{
    if (json.contains("dbName") && json["dbName"].isString())
        m_dbName = json["dbName"].toString();

    if (json.contains("users") && json["users"].isArray()) {
        QJsonArray npcArray = json["users"].toArray();
        m_users.clear();
        m_users.reserve(npcArray.size());
        for (int npcIndex = 0; npcIndex < npcArray.size(); ++npcIndex) {
            QJsonObject npcObject = npcArray[npcIndex].toObject();
            BiometricUser npc;
            npc.read(npcObject);
            m_users.append(npc);
        }
    }
}

void BiometricDB::write(QJsonObject &json) const
{
    json["dbName"] = m_dbName;
    QJsonArray npcArray;
    for (const BiometricUser &npc : m_users) {
        QJsonObject npcObject;
        npc.write(npcObject);
        npcArray.append(npcObject);
    }
    json["users"] = npcArray;
}
