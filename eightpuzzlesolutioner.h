#ifndef EIGHTPUZZLESOLUTIONER_H
#define EIGHTPUZZLESOLUTIONER_H

#include <QObject>
#include <QStack>
#include <QList>
#include "eightpuzzleinstance.h"

class EightPuzzleSolutioner : public QObject
{
    Q_OBJECT
public:
    explicit EightPuzzleSolutioner(QObject *parent = 0);
    
    QList<QString> heuristics(EightPuzzleInstance *actualInstance, int chooseHeuristic);

    enum HEURISTIC{

      HEURISTIC_ONE,
      HEURISTIC_TWO,
      RANDOM_SOLUTION,
      PERSONAL_HEURISTIC


    };

private:



    QString getNextInstance(QStringList *tempList, EightPuzzleInstance *actualInstance, int chooseHeuristic);
    QString obtainNextInstance(QHash<QString, int> *relationInstancesDecision, EightPuzzleInstance *actualInstance);
    void pushOnStack(EightPuzzleInstance *actualInstance, int chooseHeuristic);
    QList<QString> fixHeuristicTwo(QList<QString> *tempList);

    QHash<QString, EightPuzzleInstance *> *instancesFlow;
    QStack<QString> *lastInstances;
    int justToControll;


signals:
    
public slots:
    
};

#endif // EIGHTPUZZLESOLUTIONER_H
