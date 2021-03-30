#ifndef DBSCAN_ALGORITHM_H
#define DBSCAN_ALGORITHM_H
#include <QObject>
#include <QQuickItem>
#include "AppController.h"

typedef  QQuickItem* Node;

class AppController;

class DBSCAN_Algorithm
{
public:
    static int NOISE;
    static int UNCLASSIFIED;
    static int EPSILON;
    static int MIN_POINT;

public:
    DBSCAN_Algorithm(AppController* app);
    void initData(QList<Node> data, int epsilon, int minPoint);

    void DBSCAN();
    bool expandCluster(Node currentNode, int nClusterId);

    QList<Node> getNeighbors(Node currentNode);
    void setClusterId(QList<Node> neighbors, int nClusterId);
    void setClusterId(Node node, int nClusterId);

    float distance(Node p, Node q);

    void delay(int mSec);
private:
    QList<Node> mObservations;
    QMap<Node, int> mLabels;
    AppController *mApp;
};

#endif // DBSCAN_ALGORITHM_H
