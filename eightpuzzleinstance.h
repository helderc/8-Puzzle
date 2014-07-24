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
