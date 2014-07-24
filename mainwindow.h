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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QTime>
#include <QDebug>
#include <QStateMachine>
#include <QSignalTransition>

#include "eightpuzzleinstance.h"
#include "eightpuzzlesolutioner.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnShuffle_clicked();
    void on_btnSolve_clicked();

private:
    QStateMachine *stateMachine;

    QHash<QString, QString> *stateHash;
    EightPuzzleInstance *puzzleFirstStateShuffled;
    EightPuzzleSolutioner *puzzleSolutioner;


    Ui::MainWindow *ui;
    // lista de todas as posicoes dos quadrados
    QList<QRect> listBoardPosition;

    void creatingTheWorld();
    void startStateHash();
    void ordinaryMovement(QHash<int, int> *puzzleShuffled);
    void fancyMovement(QList<QString> listMovements);
    void stateMovement(QList<QString> *listMovements);
    void setStatusBarText(QString text);
    QHash<int, int> splitStringToHash(QString stringToSplit);
};

#endif // MAINWINDOW_H
