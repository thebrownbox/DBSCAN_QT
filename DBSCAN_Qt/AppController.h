#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>
#include "DBSCAN_Algorithm.h"

class DBSCAN_Algorithm;

class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numberOfCluster READ getNumberOfCluster WRITE setNumberOfCluster NOTIFY numberOfClusterChanged)
    Q_PROPERTY(int numberOfOutliers READ getNumberOfOutliers WRITE setNumberOfOutliers NOTIFY numberOfOutliersChanged)
    Q_PROPERTY(int bIsRunning READ getBIsRunning WRITE setBIsRunning NOTIFY bIsRunningChanged)
public:
    explicit AppController(QQmlEngine *engine, QObject *parent = nullptr);

    int getNumberOfCluster() const;
    void setNumberOfCluster(int value);

    int getNumberOfOutliers() const;
    void setNumberOfOutliers(int value);

    bool getBIsRunning() const;
    void setBIsRunning(bool value);

signals:
    void valueChanged(int newValue);
    void numberOfClusterChanged();
    void numberOfOutliersChanged();
    void bIsRunningChanged();

public slots:
    void getAllObservations(QObject* group, int epsilon, int minPoints);
    void addNewObservation(QObject* parent, float x, float y);
    void clear();

private:
    int numberOfCluster;
    int numberOfOutliers;
    bool bIsRunning;

    QQmlEngine *mEngine;
    QList<QQuickItem*> mObservations;
    DBSCAN_Algorithm* mDBSCAN_Algo;
};

#endif // APPCONTROLLER_H
