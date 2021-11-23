#ifndef PASSWORDCONTROLLER_H
#define PASSWORDCONTROLLER_H

#include <QString>
#include <QStringList>



class PasswordController
{
public:    
    PasswordController(QStringList a_input);
    PasswordController();
    void calculateComplexity();
    void setNewPass(QStringList a_pass);
    QString getStringComp();
    int getIntComp();
    bool containsInAlph(QString a_alph, QString a_password);
    QString pack(QStringList list);
private:
    int m_complexity = 0;
    QString m_textComplexity;
    QStringList m_inputText;
    const QString m_listcyrillicLowerAlph = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    const QString m_cyrillicUpperAlph = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const QString m_engLowerAlph = "abcdefghijklmnopqrstuvwxyz";
    const QString m_engUpperAlph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString m_specSymbols = "~!@#$%^&*{}[]`|'?.,><:;";
};

#endif // PASSWORDCONTROLLER_H
