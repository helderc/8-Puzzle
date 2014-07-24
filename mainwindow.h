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
