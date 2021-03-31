#include "AppController.h"
#include <QDebug>
#include <QQmlProperty>
#include <QQmlComponent>


AppController::AppController(QQmlEngine *engine, QObject *parent) : QObject(parent)
{
    mEngine = engine;
    mDBSCAN_Algo = new DBSCAN_Algorithm(this);
}


void AppController::getAllObservations(QObject* group, int epsilon, int minPoints)
{
    setBIsRunning(true);
    qDebug() << "group->children().size(): " << group->children().size();
    mObservations.clear();
    for(int i=0; i<group->children().size(); i++){
        auto item = (QQuickItem*)group->children().at(i);
        mObservations.append(item);
    }

    mDBSCAN_Algo->initData(mObservations, epsilon, minPoints);
    setBIsRunning(false);
}

void AppController::addNewObservation(QObject *parent, float x, float y)
{
    QQmlEngine engine;
    QQmlComponent component(mEngine, "qrc:/Observation.qml", parent);
    QObject *object = component.create();
    QQmlProperty::write(object, "x", x);
    QQmlProperty::write(object, "y", y);
}

int AppController::getNumberOfOutliers() const
{
    return numberOfOutliers;
}

void AppController::setNumberOfOutliers(int value)
{
    numberOfOutliers = value;
    emit numberOfOutliersChanged();
}

int AppController::getNumberOfCluster() const
{
    return numberOfCluster;
}

void AppController::setNumberOfCluster(int value)
{
    if(value >= 0)
    {
        numberOfCluster = value;
        emit numberOfClusterChanged();
    }
}

void AppController::clear()
{
    setNumberOfCluster(0);
    setNumberOfOutliers(0);
}

bool AppController::getBIsRunning() const
{
    return bIsRunning;
}

void AppController::setBIsRunning(bool value)
{
    bIsRunning = value;
    emit bIsRunningChanged();
}
