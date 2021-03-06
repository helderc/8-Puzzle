/***************************************************************************

Copyright (c) 2014, Helder C. R. de Oliveira and Pedro Gava
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

* Neither the name of the {organization} nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/

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
