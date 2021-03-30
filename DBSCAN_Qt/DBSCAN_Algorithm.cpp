#include "DBSCAN_Algorithm.h"
#include <cmath>
#include <QTime>

int DBSCAN_Algorithm::NOISE = -1;
int DBSCAN_Algorithm::UNCLASSIFIED = 0;
int DBSCAN_Algorithm::EPSILON = 0;
int DBSCAN_Algorithm::MIN_POINT = 0;

DBSCAN_Algorithm::DBSCAN_Algorithm(AppController* app)
{
    mApp = app;
}

void DBSCAN_Algorithm::initData(QList<Node> data, int epsilon, int minPoint)
{
    mObservations.clear();
    mLabels.clear();

    mObservations.append(data);
    EPSILON = epsilon;
    MIN_POINT = minPoint;

    qDebug() << "Size: " << mObservations.size() << " Eps: " << EPSILON << " MinPoint: " << MIN_POINT;
    qDebug() << distance(mObservations[0], mObservations[1]);

    DBSCAN();
}

void DBSCAN_Algorithm::DBSCAN()
{
    int nClusterId = 1;
    for(int i = 0; i < mObservations.size(); i++){
        auto currentNode = mObservations[i];
        if(mLabels[currentNode] == UNCLASSIFIED){
            if(expandCluster(currentNode, nClusterId)){
                nClusterId++;
            }
        }
    }

    int count = 0;
    for(Node p : mObservations){
        if(mLabels[p] == NOISE){
            count++;
            mApp->setNumberOfOutliers(count);
        }
    }
}

bool DBSCAN_Algorithm::expandCluster(Node currentNode, int nClusterId)
{
    auto neighbors = getNeighbors(currentNode);
    if(neighbors.size() < MIN_POINT){
        // currentNode is NOISE
        setClusterId(currentNode, NOISE);
        return false;
    }else{
        // currentNode is core point
        setClusterId(neighbors, nClusterId);
        neighbors.removeOne(currentNode);

        while(neighbors.isEmpty() == false)
        {
            auto nextNode = neighbors.first();
            auto nextNeighbors = getNeighbors(nextNode);
            if(nextNeighbors.size() >= MIN_POINT)
            {
                for(Node p : nextNeighbors)
                {
                    if(mLabels[p] == NOISE || mLabels[p] == UNCLASSIFIED)
                    {
                        // If p is UNCLASSIFIED => should do BFS with p
                        if(mLabels[p] == UNCLASSIFIED){
                            neighbors.append(p);
                        }
                        // If p is NOISE that means it already checked => skip!
                        setClusterId(p, nClusterId);
                    }
                }
            }
            neighbors.removeOne(nextNode);
        }
    }


    return true;
}

QList<Node> DBSCAN_Algorithm::getNeighbors(Node currentNode)
{
    QList<Node> neighbors;
    for(Node t : mObservations){
        if(distance(t, currentNode) <= EPSILON){
            neighbors.append(t);
        }
    }
    return neighbors;
}

void DBSCAN_Algorithm::setClusterId(QList<Node> neighbors, int nClusterId)
{
    for(Node node : neighbors){
        mLabels[node] = nClusterId;
        node->setProperty("label", nClusterId);
        delay(200);
        mApp->setNumberOfCluster(nClusterId);
    }
}

void DBSCAN_Algorithm::setClusterId(Node node, int nClusterId)
{
    mLabels[node] = nClusterId;
    node->setProperty("label", nClusterId);
    mApp->setNumberOfCluster(nClusterId);
    delay(200);
}

float DBSCAN_Algorithm::distance(Node p, Node q)
{
    return sqrt( pow(p->x() - q->x(), 2)  + pow(p->y() - q->y(),2));
}

void DBSCAN_Algorithm::delay(int mSec)
{
    QTime dieTime= QTime::currentTime().addMSecs(mSec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
