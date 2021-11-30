#ifndef BIOMETRICKEYBOARDMODEL_H
#define BIOMETRICKEYBOARDMODEL_H

#include <QAbstractListModel>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>
#include <QtMath>
#include <QJsonObject>
#include <passwordcontroller.h>
struct TapKey{
    int keyDownTime;
    int keyUpTime;
    QString key;
    TapKey (int a_keyDownTime, int a_keyUpTime, QString a_key){
        keyDownTime = a_keyDownTime;
        keyUpTime = a_keyUpTime;
        key = a_key;
    }
};
class BiometricKeyboardModel : public QAbstractListModel
{
    Q_PROPERTY(QString complexity READ getComplexity NOTIFY complexityChanged)

    Q_PROPERTY(double dispersionPressTime READ dispersionPressTime NOTIFY statisticsChanged)
    Q_PROPERTY(double dispersionIntervals READ dispersionIntervals NOTIFY statisticsChanged)
    Q_PROPERTY(double expectedPressTime READ expectedPressTime NOTIFY statisticsChanged)
    Q_PROPERTY(double expectedIntervals READ expectedIntervals NOTIFY statisticsChanged)
    Q_PROPERTY(int pressTimeSum READ pressTimeSum NOTIFY statisticsChanged)
    Q_PROPERTY(int gallopSuperpos READ gallopSuperpos NOTIFY statisticsChanged)
    Q_PROPERTY(int absorption READ absorption NOTIFY statisticsChanged)

    Q_PROPERTY(QString currname READ currname WRITE setCurrname NOTIFY currnameChanged)
    Q_PROPERTY(QString vector READ vector WRITE setVector NOTIFY vectorChanged)

    Q_OBJECT
public:
    enum BiometricKeyboardModelRoles {
        BiometricKeyboardDownTime = Qt::UserRole +1,
        BiometricKeyboardUpTime,
        BiometricKeyboardKey
    };
    explicit BiometricKeyboardModel(QAbstractListModel *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;
//    Q_INVOKABLE void clearPass();
    //Q_INVOKABLE void appendRow(QKeyEvent a_keyEvent);
    Q_INVOKABLE void appendRow(QString a_key, int a_flag);

    bool containsInOpenKeys(QString a_t) const;
    bool isShiftDown();
    bool isOpenKey(QString a_k);
    int getOpenKeyIndex(QString a_key);
    bool isPressed(QString a_key);
    bool isSomethingPressed();
    void checkForInstaPressButt(QString a_key);

    QStringList convert ( QList<TapKey> a_taper);

    QString getComplexity();

    Q_INVOKABLE void removeLast();

    void calculateGistogramm();



    //statistic calculating
    void calculateStatictics();
    void clearStatistics();

    void createIntervals();
    void createPressTimesSelections();
    double calculateDispersion(QList<double> a_data, double a_value);
    double calculateExpectedValue(QList<double> a_data);
    void calculatePressTimeSumm();
    void calculateGallop();
    void calculateAbsorption();

    double dispersionPressTime() const;

    double dispersionIntervals() const;

    double expectedPressTime() const;

    double expectedIntervals() const;

    int pressTimeSum() const;

    int gallopSuperpos() const;

    int absorption() const;

    QString getStringFromTaper();

    Q_INVOKABLE void askForName();
    Q_INVOKABLE void saveCurrWithName(QString a_name);

    const QString &currname() const;
    void setCurrname(const QString &newCurrname);

    int calculateFunction(int t);
    double calculateHaar(int r, int m, int t);
    Q_INVOKABLE void calculateVector();
    void calculateAmplitude();
    Q_INVOKABLE void calculateGraphAmplitude();
    Q_INVOKABLE int getMinTime();

    QString arrayToString(double *a_Array);

    const QString &vector() const;
    void setVector(const QString &newVector);

signals:
    void complexityChanged();
    void addToGisrogramm(int a_index,int a_value);
    void removeFromGistogramm(int a_index);
    void statisticsChanged();
    void addToGisrogramm2(int a_index,double a_value);
    void addToAmplitudeFunction(int a_index,int a_value);

    void currnameChanged();

    void vectorChanged();

public slots:
void onUpdateTimer();

    // QAbstractItemModel interface
private:
    QList<TapKey> m_taper;
    double m_time;
    QTimer *m_timer;
    double m_lastTimeChange = -1;
    QDateTime *m_qtime;

    PasswordController* m_controller;
   // statistics
    QList<double> m_intervals;
    QList<double> m_pressTimeSelections;
//    double m_expectedValue;
    double m_dispersionPressTime = 0;
    double m_dispersionIntervals = 0;
    double m_expectedPressTime = 0;
    double m_expectedIntervals = 0;
    int m_pressTimeSum= 0;
    int m_gallopSuperpos= 0;
    int m_absorption = 0;

    QString m_currname ="";
    QList<double> m_vectorList;
    int m_amplitude;
    QString m_vector;

};

#endif // BIOMETRICKEYBOARDMODEL_H
