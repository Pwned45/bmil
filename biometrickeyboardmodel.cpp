#include "biometrickeyboardmodel.h"

#include <QDate>
#include <QKeySequence>

BiometricKeyboardModel::BiometricKeyboardModel(QAbstractListModel *parent) : QAbstractListModel(parent)
{
    beginResetModel();
    //QList<TapKey> l_list ;
    //l_list.append(TapKey(1,1,"x"));
    //m_taper->append(new TapKey(1,1,"x"));
    endResetModel();
    m_controller = new PasswordController();
    m_timer = new QTimer();
    m_time = 0;
    connect(m_timer, SIGNAL(timeout()),this,SLOT(onUpdateTimer()));
    m_timer->start(5);

//    qDebug() <<;

}

int BiometricKeyboardModel::rowCount(const QModelIndex &parent) const
{
    return m_taper.size();
}

QVariant BiometricKeyboardModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (index.row()<0 || index.row()>=m_taper.size()){
        return QVariant();
    }
            switch ( role )
            {
                case BiometricKeyboardModelRoles::BiometricKeyboardDownTime: //string
                {
                    value = m_taper.at(index.row()).keyDownTime;
                }
                break;
                case BiometricKeyboardModelRoles::BiometricKeyboardUpTime: //string
                {
                    value = m_taper.at(index.row()).keyUpTime;

                }
                break;
                case BiometricKeyboardModelRoles::BiometricKeyboardKey: //string
                {
                    value = m_taper.at(index.row()).key;
//                    qDebug() << QKeySequence(m_taper.at(index.row()).key).toString();
//                    qDebug() << Q;

//                    value = m_taper.at(index.row()).keyDownTime;
//                    value = m_taper.at(index.row()).keyUpTime;
                }
                break;
            }

            return value;

}

bool BiometricKeyboardModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row()<0 || index.row()>=m_taper.size()){
        return false;
    }
            switch ( role )
            {
                case BiometricKeyboardModelRoles::BiometricKeyboardDownTime: //string
                {
                    m_taper[index.row()].keyDownTime = value.toInt();
                    emit dataChanged(index,QModelIndex());
                    return true;
                }
                break;
                case BiometricKeyboardModelRoles::BiometricKeyboardUpTime: //string
                {
                    m_taper[index.row()].keyUpTime = value.toInt();
                    emit dataChanged(index,QModelIndex());
                    return true;
                }
                case BiometricKeyboardModelRoles::BiometricKeyboardKey: //string
                  {
                    m_taper[index.row()].key = value.toString();
//                    m_taper[index.row()].keyUpTime =
//                    m_taper[index.row()].keyDownTime =
                    emit dataChanged(index,QModelIndex());
                    return true;
                  }
            }
            return false;
}

QHash<int, QByteArray> BiometricKeyboardModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[BiometricKeyboardDownTime] = "downTime";
    roles[BiometricKeyboardUpTime] = "upTime";
    roles[BiometricKeyboardKey] = "key";
    return roles;
}

void BiometricKeyboardModel::appendRow(QString a_key, int a_flag)
{
    m_qtime = new QDateTime();
    if(a_flag == 0) {
    if (!isOpenKey(a_key)) {
        beginInsertRows(QModelIndex(),m_taper.size(),m_taper.size());
        m_taper.append(TapKey(m_qtime->currentMSecsSinceEpoch(),-1,a_key));
        m_lastTimeChange = m_qtime->currentMSecsSinceEpoch();
        endInsertRows();
        m_controller->setNewPass(convert(m_taper));
        complexityChanged();
    }
    } else {
        if (isOpenKey(a_key)) {
            int l_wasChange = getOpenKeyIndex(a_key);
            m_taper[l_wasChange].keyUpTime = m_qtime->currentMSecsSinceEpoch();
//            m_lastTimeChange = m_qtime->currentMSecsSinceEpoch();
            qDebug() << "was changed " << a_key;
            emit dataChanged(index(l_wasChange,0),index(l_wasChange,0));
            checkForInstaPressButt(a_key);
//            emit addToGisrogramm(m_taper.at(m_taper.size()-1).key,
            if (m_taper.at(m_taper.size()-1).keyUpTime != -1) {
                addToGisrogramm(
                            m_taper.size()-1,
                            m_taper.at(m_taper.size()-1).keyUpTime -
                            m_taper.at(m_taper.size()-1).keyDownTime);
                if (m_taper.size()>1)
                addToGisrogramm2(m_taper.size()-1,(m_taper.at(m_taper.size()-1).keyDownTime
                                  - m_taper.at(m_taper.size()-2).keyDownTime)/1000.0);
}
//            if(isSomethingPressed())
            calculateStatictics();
        }
    }


}

bool BiometricKeyboardModel::containsInOpenKeys(QString a_t) const
{
    for (TapKey t : m_taper){
        if (t.key == a_t && t.keyUpTime == -1)
            return true;
    }
    return false;
}

bool BiometricKeyboardModel::isShiftDown()
{
    for (TapKey t : m_taper){
//        if (t.key == Qt::SHIFT)
            return true;
    }
    return false;
}

bool BiometricKeyboardModel::isOpenKey(QString a_k)
{
    for (int i = 0; i < m_taper.size() ; i++){
            if (m_taper.at(i).keyUpTime == -1 && m_taper.at(i).key == a_k) {
                return true;
            }

    }
    return false;
}

int BiometricKeyboardModel::getOpenKeyIndex(QString a_key)
{
    for (int i = 0; i < m_taper.size() ; i++){
        if (m_taper.at(i).key == a_key && m_taper.at(i).keyUpTime == -1)
            return i;
    }
    return -1;
}

bool BiometricKeyboardModel::isPressed(QString a_key)
{
    for (TapKey t : m_taper){
        if (t.key == a_key && t.keyUpTime != -1)
            return true;
    }
    return false;
}

bool BiometricKeyboardModel::isSomethingPressed()
{
    for (TapKey t : m_taper){
        if (t.keyUpTime == -1)
            return true;
    }
    return false;
}

void BiometricKeyboardModel::checkForInstaPressButt(QString a_key)
{
    int l_trueDownTime = -1;
    int l_trueUpTime = -1;
    int l_iStart = -1;
    int l_iEnd = -1;
    for (int i = 0; i < m_taper.size(); i++) {
        if(m_taper.at(i).key == a_key){
            int l_diff = m_taper.at(i).keyUpTime - m_taper.at(i).keyDownTime;
            if (l_diff >= 1 && l_diff <= 35) {
                l_trueDownTime = m_taper.at(i).keyDownTime;
                l_iStart = i;
                break;
            }
        }
    }
    for (int i = m_taper.size()-1; i >= 0; i--) {
        if(m_taper.at(i).key == a_key){
            int l_diff = m_taper.at(i).keyUpTime - m_taper.at(i).keyDownTime;
            if (l_diff >= 1 && l_diff <= 35) {
                l_trueUpTime = m_taper.at(i).keyUpTime;
                l_iEnd = i;
                break;
            }
        }
    }
    if (l_trueUpTime!= -1 && l_trueDownTime!= -1) {
        m_taper[l_iStart].keyDownTime = l_trueDownTime;
        m_taper[l_iStart].keyUpTime = l_trueUpTime;
        beginRemoveRows(QModelIndex(),l_iStart+1, l_iEnd);
        m_taper.remove(l_iStart,l_iEnd-l_iStart);
        endRemoveRows();
    }
}

QStringList BiometricKeyboardModel::convert(QList<TapKey> a_taper)
{
    QStringList l_list;
    for (TapKey t: a_taper){
        l_list.append(t.key);
    }
    return l_list;
}

QString BiometricKeyboardModel::getComplexity()
{
    return m_controller->getStringComp();
}

void BiometricKeyboardModel::removeLast()
{
    if (m_taper.size() > 0) {
    beginRemoveRows(QModelIndex(),m_taper.size()-1, m_taper.size()-1);
    m_taper.remove(m_taper.size()-1,1);
    endRemoveRows();
    m_controller->setNewPass(convert(m_taper));
    if(m_taper.size() == 0) {
        complexityChanged();
        clearStatistics();
    }
    }

}

void BiometricKeyboardModel::calculateStatictics()
{
    if (m_taper.size() == 0){
        clearStatistics();
        return;
    }
    createIntervals();
    createPressTimesSelections();
    // отобразить expected value intervals
    m_expectedIntervals = calculateExpectedValue(m_intervals);
    m_dispersionIntervals = calculateDispersion(m_intervals,m_expectedIntervals);
    m_expectedPressTime = calculateExpectedValue(m_pressTimeSelections);
    m_dispersionPressTime = calculateDispersion(m_pressTimeSelections,m_expectedPressTime);

    calculatePressTimeSumm();

    calculateGallop();
    calculateAbsorption();

    emit statisticsChanged();

}

void BiometricKeyboardModel::clearStatistics()
{
    m_intervals.clear();
    m_pressTimeSelections.clear();
    m_dispersionPressTime = 0;
    m_dispersionIntervals = 0;
    m_expectedPressTime = 0;
    m_expectedIntervals = 0;
    m_pressTimeSum= 0;
    m_gallopSuperpos= 0;
    m_absorption = 0;


    emit statisticsChanged();
}

void BiometricKeyboardModel::createIntervals()
{
    m_intervals.clear();
    for (int i = 1 ; i < m_taper.size(); i++){
        m_intervals.append(abs((m_taper.at(i).keyDownTime - m_taper.at(i-1).keyDownTime))/1000.);
         qDebug() << "append " << ((m_taper.at(i).keyDownTime - m_taper.at(i-1).keyDownTime)/1000.);
    }
}

void BiometricKeyboardModel::createPressTimesSelections()
{
    m_pressTimeSelections.clear();
    for (TapKey t: m_taper){
        if (t.keyUpTime != -1)
            m_pressTimeSelections.append(t.keyUpTime - t.keyDownTime);
        else m_pressTimeSelections.append(0 - t.keyDownTime);
    }
}

double BiometricKeyboardModel::calculateDispersion(QList<double> a_data, double a_value)
{
    if (a_data.size() < 2) {
        m_dispersionIntervals = 0;
        m_dispersionPressTime = 0;
        return 0;
    }
    double numeration = 0;
    for (int i = 0; i< a_data.size() ; i++){
        numeration+= (a_data.at(i)-a_value)*(a_data.at(i)-a_value);
    }
    return numeration/(a_data.size()-1);

}

double BiometricKeyboardModel::calculateExpectedValue(QList<double> a_data)
{
    if (a_data.size() == 0) {
        return 0;
    }
    double numeration = 0;
    for (int i = 0; i< a_data.size() ; i++){
        numeration += a_data.at(i);
    }
    qDebug() << "num " << (numeration*1.0)/a_data.size();
    return (numeration*1.0)/a_data.size();

}

void BiometricKeyboardModel::calculatePressTimeSumm()
{
    if (m_taper.size() == 0) {
        m_pressTimeSum = 0;
        return;
    }
    double l_sum = 0;
    for (TapKey t: m_taper){
        l_sum += t.keyUpTime - t.keyDownTime;
    }
    m_pressTimeSum = l_sum;

}

void BiometricKeyboardModel::calculateGallop()
{
    int superposition = 0;

    for (int i = 0; i < m_taper.size() - 1; i++) {
      for (int j = i + 1; j < m_taper.size(); j++) {
        if (m_taper.at(j).keyDownTime > m_taper.at(i).keyUpTime) {
          continue;
        }
        if (
          m_taper.at(j).keyDownTime < m_taper.at(i).keyUpTime &&
          m_taper.at(j).keyUpTime < m_taper.at(i).keyUpTime
        ) {
          continue;
        }

        if (
          m_taper.at(j).keyDownTime < m_taper.at(i).keyUpTime &&
          m_taper.at(j).keyUpTime > m_taper.at(i).keyUpTime
        ) {
          superposition += m_taper.at(i).keyUpTime - m_taper.at(j).keyDownTime;
        }
      }
    }

    m_gallopSuperpos = superposition;
}

void BiometricKeyboardModel::calculateAbsorption()
{
    int superposition = 0;

    for (int i = 0; i < m_taper.size() - 1; i++) {
      for (int j = i + 1; j < m_taper.size(); j++) {
        if (m_taper.at(j).keyDownTime >  m_taper.at(i).keyUpTime) {
          continue;
        }

        if (
          m_taper.at(j).keyDownTime <  m_taper.at(i).keyUpTime &&
          m_taper.at(j).keyUpTime <  m_taper.at(i).keyUpTime
        ) {
          superposition += m_taper.at(j).keyUpTime - m_taper.at(j).keyDownTime;
        }
      }
    }
    m_absorption = superposition;
}

void BiometricKeyboardModel::onUpdateTimer()
{
    m_time+= 0.005;
    //    qDebug() << "timer = " << m_time;
}

int BiometricKeyboardModel::absorption() const
{
    return m_absorption;
}

int BiometricKeyboardModel::pressTimeSum() const
{
    return m_pressTimeSum;
}

int BiometricKeyboardModel::gallopSuperpos() const
{
    return m_gallopSuperpos;
}

double BiometricKeyboardModel::expectedIntervals() const
{
    return m_expectedIntervals;
}

double BiometricKeyboardModel::expectedPressTime() const
{
    return m_expectedPressTime;
}

double BiometricKeyboardModel::dispersionIntervals() const
{
    return m_dispersionIntervals;
}

double BiometricKeyboardModel::dispersionPressTime() const
{
    return m_dispersionPressTime;
}

//void BiometricKeyboardModel::appendRow(QKeyEvent a_keyEvent)
//{

//}

//void BiometricKeyboardModel::appendRow()
//{

//}

