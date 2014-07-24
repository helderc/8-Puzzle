#ifndef EIGHTPUZZLEINSTANCE_H
#define EIGHTPUZZLEINSTANCE_H

#include <QObject>
#include <QHash>
#include <QStringList>
#include <QString>
#include <QHashIterator>
#include <QList>
#include <QDebug>
#include <cstdlib>
#include <ctime>
#include <iostream>

class EightPuzzleInstance : public QObject
{
    Q_OBJECT
public:
    //explicit EightPuzzleInstance(QObject *parent = 0);

    explicit EightPuzzleInstance(QObject *parent = 0,
                                 QString currentState = tr("1:1_2:2_3:3_4:4_5:5_6:6_7:7_8:8_9:9"));

    QStringList *nextInstancesHeuristicOne();
    QStringList *nextInstancesHeuristicTwo();
    QStringList *nextPersonalInstance();
    QString nextInstanceRandomSolution();

    void shufflePuzzle(int numOfMovements);
    QHash<int, int> *getPiecesPosition();
    QString toString();
    QString toString(QHash<int, int> *someInstance);
    int decisionFunction();
    static int decisionFunction(QString someInstance);
    void initPiecesPosition(QString currentState);
    int getEmptyIndex();
    int getNextInstanceBasedOnEmptySpace(int i);

private:

    QString swapBlankSpace(int actualBlankSpace, int targetPieceToSwap);

    int pseudoRandomNumber(int max, int min);

    int randomSeedHelp;

    QHash<int, int> *instancePiecesPosition;
    
signals:
    
public slots:
    
};

#endif // EIGHTPUZZLEINSTANCE_H
