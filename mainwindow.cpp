#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    creatingTheWorld();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::creatingTheWorld()
{
    // Lista de posicoes possiveis
    listBoardPosition.insert(0, QRect(7, 7, 100, 100));
    listBoardPosition.insert(1, QRect(114, 7, 100, 100));
    listBoardPosition.insert(2, QRect(221, 7, 100, 100));
    listBoardPosition.insert(3, QRect(7, 113, 100, 100));
    listBoardPosition.insert(4, QRect(114, 113, 100, 100));
    listBoardPosition.insert(5, QRect(221, 113, 100, 100));
    listBoardPosition.insert(6, QRect(7, 220, 100, 100));
    listBoardPosition.insert(7, QRect(114, 220, 100, 100));
    listBoardPosition.insert(8, QRect(221, 220, 100, 100));

    //this->teste2 = new EightPuzzleSolutioner(this);
    //this->teste2->heuristics(this->teste, this->teste2->HEURISTIC_TWO);

    //this->teste->nextInstanceRandomSolution();
    //this->startStateHash();
}

void MainWindow::startStateHash()
{
    this->stateHash = new QHash<QString, QString>;
    this->stateHash->insert(tr("1:4_2:5_3:6_4:8_5:2_6:3_7:9_8:1_9:7"), tr("1:4_2:5_3:6_4:8_5:2_6:3_7:9_8:1_9:7"));
    //QHash<QString, QString>::const_iterator i = this->stateHash->find(tr("1:4_2:5_3:6_4:8_5:2_6:3_7:0_8:1_9:7"));
    QStringList tempList = this->stateHash->value(tr("1:4_2:5_3:6_4:8_5:2_6:3_7:9_8:1_9:7")).split("_");

    std::cout<<tempList[1].toStdString()<<std::endl;

}

void MainWindow::ordinaryMovement(QHash<int, int> *puzzleShuffled)
{
    QHashIterator<int, int> hashIt(*puzzleShuffled);

    // QHash(key, value)
    // QHash((2, 2)(9, 9)(8, 6)(5, 5)(4, 7)(7, 4)(6, 8)(1, 1)(3, 3))

    while (hashIt.hasNext()) {
        hashIt.next();

        // nao existe botao 9, entao pula a iteracao
        if (hashIt.value() == 9) continue;

        qDebug("Posicao a mover: (%d, %d)", hashIt.key(), hashIt.value());

        // pega o botao a mover e monta o nome para descobrir a posicao
        int posOrig = hashIt.value();
        QString btnName = "btn" + QString::number(posOrig);

        // busca o objeto na interface
        QPushButton *btn = ui->frame->findChild<QPushButton *>(btnName);

        if (!btn) {
            qDebug() << "ordinaryMovement: Nao acho o botao";
            break;
        }

        // Move o objeto para o local-1. A lista comeca no 0.
        btn->setGeometry(listBoardPosition.at(hashIt.key() -1));
    }
}

void MainWindow::fancyMovement(QList<QString> listMovements)
{
    stateMachine = new QStateMachine(this);

    // Lista de Estados
    QList<QState *> listStates;

    QState *state = new QState();

    foreach (QString s, listMovements) {

        qDebug() << "fancyMovement: " << s;

        QHash<int, int> hash = splitStringToHash(s);

        QState *nextState = new QState();

        state->assignProperty(ui->btn1, "geometry", listBoardPosition.at(hash.key(1) -1));
        state->assignProperty(ui->btn2, "geometry", listBoardPosition.at(hash.key(2) -1));
        state->assignProperty(ui->btn3, "geometry", listBoardPosition.at(hash.key(3) -1));
        state->assignProperty(ui->btn4, "geometry", listBoardPosition.at(hash.key(4) -1));
        state->assignProperty(ui->btn5, "geometry", listBoardPosition.at(hash.key(5) -1));
        state->assignProperty(ui->btn6, "geometry", listBoardPosition.at(hash.key(6) -1));
        state->assignProperty(ui->btn7, "geometry", listBoardPosition.at(hash.key(7) -1));
        state->assignProperty(ui->btn8, "geometry", listBoardPosition.at(hash.key(8) -1));

        QSignalTransition *t = state->addTransition(state, SIGNAL(propertiesAssigned()), nextState);

        t->addAnimation(new QPropertyAnimation(ui->btn1, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn2, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn3, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn4, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn5, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn6, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn7, "geometry"));
        t->addAnimation(new QPropertyAnimation(ui->btn8, "geometry"));

        listStates.append(state);

        state = nextState;

    }

    // O Ultimo estado tem config especial, apenas assignPropertie
    qDebug() << "fancyMovement: " << listMovements.last();
    QHash<int, int> hash = splitStringToHash(listMovements.last());
    state->assignProperty(ui->btn1, "geometry", listBoardPosition.at(hash.key(1) -1));
    state->assignProperty(ui->btn2, "geometry", listBoardPosition.at(hash.key(2) -1));
    state->assignProperty(ui->btn3, "geometry", listBoardPosition.at(hash.key(3) -1));
    state->assignProperty(ui->btn4, "geometry", listBoardPosition.at(hash.key(4) -1));
    state->assignProperty(ui->btn5, "geometry", listBoardPosition.at(hash.key(5) -1));
    state->assignProperty(ui->btn6, "geometry", listBoardPosition.at(hash.key(6) -1));
    state->assignProperty(ui->btn7, "geometry", listBoardPosition.at(hash.key(7) -1));
    state->assignProperty(ui->btn8, "geometry", listBoardPosition.at(hash.key(8) -1));
    //listStates.append(state);


    foreach(QState *state, listStates) {
        if (state == listStates.first()) {
            stateMachine->addState(state);
            stateMachine->setInitialState(state);
        }
        else
            stateMachine->addState(state);
    }

    stateMachine->start();

    qDebug() << "listStates: " << listStates.size();
}

void MainWindow::stateMovement(QList<QString> *listMovements)
{
    //listMovements
    foreach (QString s, *listMovements) {
        qDebug() << "stateMovement (s): " << s;
        QHash<int, int> hash = splitStringToHash(s);
        qDebug() << "stateMovement (hash): " << hash;
        ordinaryMovement(&hash);
    }
}

void MainWindow::setStatusBarText(QString text)
{
    ui->statusBar->showMessage(text);
}

QHash<int, int> MainWindow::splitStringToHash(QString stringToSplit)
{
    QHash<int, int> localHash;

    // primeiro split, separando os pares
    QStringList tempList = stringToSplit.split("_");

    QString auxIndex;
    QString auxValor;

    foreach(QString tempString, tempList){
        auxIndex = tempString.split(":")[0];
        auxValor = tempString.split(":")[1];

        localHash.insert(auxIndex.toInt(0, 10), auxValor.toInt(0, 10));
    }

    return localHash;
}



void MainWindow::on_btnShuffle_clicked()
{
    puzzleFirstStateShuffled = new EightPuzzleInstance(this);

    // embaralha de acordo com a quantidade de movimentos estabelecidos
    puzzleFirstStateShuffled->shufflePuzzle(ui->spbQtdadeMov->value());

    // primeiro estado do tabuleiro embaralhado
    QHash<int, int> *ht = puzzleFirstStateShuffled->getPiecesPosition();

    qDebug() << "Embaralhado: " << *ht;

    // move as pessas para seus locais embaralhada sem animacao alguma
    // é passado apenas o estado final apos embaralhar
    ordinaryMovement(ht);
}

void MainWindow::on_btnSolve_clicked()
{
    QTime time;

    // Heuristica 1 - Um Nivel
    if (ui->rdbHeuristics1->isChecked()) {
        time.start();
        puzzleSolutioner = new EightPuzzleSolutioner(this);
        QList<QString> puzzleSol = puzzleSolutioner->heuristics(puzzleFirstStateShuffled, puzzleSolutioner->HEURISTIC_ONE);
        setStatusBarText(QString("Heuristica 1 resolvida com: [%1] movimentos em [%2 ms]").arg(puzzleSol.size()).arg(time.elapsed()));
        fancyMovement(puzzleSol);
    }

    // Heuristica 2 - Dois Niveis
    if (ui->rdbHeuristics2->isChecked()) {
        time.start();
        puzzleSolutioner = new EightPuzzleSolutioner(this);
        QList<QString> puzzleSol = puzzleSolutioner->heuristics(puzzleFirstStateShuffled, puzzleSolutioner->HEURISTIC_TWO);
        setStatusBarText(QString("Heuristica 2 resolvida com: [%1] movimentos em [%2 ms]").arg(puzzleSol.size()).arg(time.elapsed()));
        fancyMovement(puzzleSol);
    }

    // Aleatorio
    if (ui->rdbRandom->isChecked()) {
        puzzleSolutioner = new EightPuzzleSolutioner(this);
        QList<QString> puzzleSol = puzzleSolutioner->heuristics(puzzleFirstStateShuffled, puzzleSolutioner->RANDOM_SOLUTION);
        fancyMovement(puzzleSol);
        setStatusBarText(QString("Busca Aleatoria resolvida com: [%1] movimentos").arg(puzzleSol.size()));
    }

    // Pessoal
    if (ui->rdbPersonal->isChecked()) {
        time.start();
        puzzleSolutioner = new EightPuzzleSolutioner(this);
        QList<QString> puzzleSol = puzzleSolutioner->heuristics(puzzleFirstStateShuffled, puzzleSolutioner->PERSONAL_HEURISTIC);
        fancyMovement(puzzleSol);
        setStatusBarText(QString("Busca Pessoal resolvida com: [%1] movimentos em [%2 ms]").arg(puzzleSol.size()).arg(time.elapsed()));
    }
}
