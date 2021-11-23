#include "passwordcontroller.h"

PasswordController::PasswordController(QStringList a_input)
{
    this->m_inputText = a_input;
}

PasswordController::PasswordController()
{

}

void PasswordController::calculateComplexity()
{
    if (m_inputText.size() < 5){
        m_textComplexity = "Слабый";
        m_complexity = 0;
        return;
    }
    QString l_pass = pack(m_inputText);
    m_complexity += m_inputText.size() > 8 ? 2 : 1;
    m_complexity += containsInAlph(m_listcyrillicLowerAlph,l_pass) ? 1 : 0;
    m_complexity += containsInAlph(m_cyrillicUpperAlph,l_pass) ? 1 : 0;
    m_complexity += containsInAlph(m_engLowerAlph,l_pass) ? 1 : 0;
    m_complexity += containsInAlph(m_engUpperAlph,l_pass) ? 1 : 0;
    m_complexity += containsInAlph(m_specSymbols,l_pass) ? 1 : 0;

    if (m_complexity > 0 && m_complexity < 4) {
        m_textComplexity = "Нормальный";
    } else if (m_complexity >= 4 && m_complexity < 5) {
        m_textComplexity = "Хороший";
    } else if (m_complexity >= 5) {
        m_textComplexity = "Надёжный";
    }
}

void PasswordController::setNewPass(QStringList a_pass)
{
    m_inputText = a_pass;
    calculateComplexity();
}

QString PasswordController::getStringComp()
{
    return m_textComplexity;
}

int PasswordController::getIntComp()
{
    return m_complexity;
}

bool PasswordController::containsInAlph(QString a_alph, QString a_password)
{
    for(QChar c: a_password){
        if (a_alph.contains(c))
            return true;
    }
    return false;
}
QString PasswordController::pack(QStringList list)
{
    QString l_string = "";
    for (QString t:list){
        l_string+=t;
    }
    return l_string;
}
