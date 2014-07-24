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

#include "eightpuzzleinstance.h"


EightPuzzleInstance::EightPuzzleInstance(QObject *parent, QString currentState):
    QObject(parent)
{

    this->initPiecesPosition(currentState);

    //qDebug()<<"ATUAL :"<<this->toString();

    randomSeedHelp = 0;

    //this->decisionFunction();
    //this->decisionFunction(currentState);
    //this->nextInstancesHeuristicOne();
    //this->nextInstancesHeuristicTwo();

}

QStringList *EightPuzzleInstance::nextInstancesHeuristicOne()
{

    QStringList *tempList;
    QHash<int, int>::const_iterator i = this->instancePiecesPosition->constBegin();

    int blankPosition;

    tempList = new QStringList();

    //VERIFICA ONDE ESTA O ESPAÇO EM BRANCO
    while (i != this->instancePiecesPosition->constEnd()) {

        if(i.value() == 9){

            blankPosition = i.key();
            break;

        }

        ////std::cout<<i.key() <<":"<<i.value()<<std::endl;
        i++;
    }

    //GERA STRINGS COM O FORMATO DOS FILHOS DA ATUAL INSTANCIA DO PUZZLE
    switch(blankPosition){


    case 1:

        //ESPAÇO EM BRANCO VAI PARA A CASA 2
        tempList->append(this->swapBlankSpace(1, 2));

        //ESPAÇO EM BRANCO VAI PARA A CASA 4
        tempList->append(this->swapBlankSpace(1, 4));

        break;

    case 2:
        //ESPAÇO EM BRANCO VAI PARA A CASA 1
        tempList->append(this->swapBlankSpace(2, 1));

        //ESPAÇO EM BRANCO VAI PARA A CASA 3
        tempList->append(this->swapBlankSpace(2, 3));

        //ESPAÇO EM BRANCO VAI PARA A CASA 5
        tempList->append(this->swapBlankSpace(2, 5));

        break;

    case 3:

        //ESPAÇO EM BRANCO VAI PARA CASA 2
        tempList->append(this->swapBlankSpace(3, 2));

        //ESPAÇO EM BRANCO VAI PARA CASA 6
        tempList->append(this->swapBlankSpace(3, 6));

        break;

    case 4:
        //ESPAÇO EM BRANCO VAI PARA CASA 1
        tempList->append(this->swapBlankSpace(4, 1));

        //ESPAÇO EM BRANCO VAI PARA CASA 5
        tempList->append(this->swapBlankSpace(4, 5));

        //ESPAÇO EM BRANCO VAI PARA CASA 7
        tempList->append(this->swapBlankSpace(4, 7));

        break;

    case 5:

        //ESPAÇO EM BRANCO VAI PARA CASA 2
        tempList->append(this->swapBlankSpace(5, 2));

        //ESPAÇO EM BRANCO VAI PARA CASA 4
        tempList->append(this->swapBlankSpace(5, 4));

        //ESPAÇO EM BRANCO VAI PARA CASA 6
        tempList->append(this->swapBlankSpace(5, 6));

        //ESPAÇO EM BRANCO VAI PARA CASA 6
        tempList->append(this->swapBlankSpace(5, 8));

        break;

    case 6:

        //ESPAÇO EM BRANCO VAI PARA CASA 3
        tempList->append(this->swapBlankSpace(6, 3));

        //ESPAÇO EM BRANCO VAI PARA CASA 5
        tempList->append(this->swapBlankSpace(6, 5));

        //ESPAÇO EM BRANCO VAI PARA CASA 9
        tempList->append(this->swapBlankSpace(6, 9));

        break;

    case 7:

        //ESPAÇO EM BRANCO VAI PARA CASA 4
        tempList->append(this->swapBlankSpace(7, 4));

        //ESPAÇO EM BRANCO VAI PARA CASA 8
        tempList->append(this->swapBlankSpace(7, 8));

        break;

    case 8:

        //ESPAÇO EM BRANCO VAI PARA CASA 7
        tempList->append(this->swapBlankSpace(8, 7));

        //ESPAÇO EM BRANCO VAI PARA CASA 5
        tempList->append(this->swapBlankSpace(8, 5));

        //ESPAÇO EM BRANCO VAI PARA CASA 9
        tempList->append(this->swapBlankSpace(8, 9));

        break;

    case 9:

        //ESPAÇO EM BRANCO VAI PARA CASA 6
        tempList->append(this->swapBlankSpace(9, 6));

        //ESPAÇO EM BRANCO VAI PARA CASA 8
        tempList->append(this->swapBlankSpace(9, 8));

        break;

    }



    return tempList;

}

QStringList *EightPuzzleInstance::nextInstancesHeuristicTwo()
{

    QStringList *tempStringList;
    QStringList *tempStringList2 = new QStringList();
    QList<EightPuzzleInstance *> puzzleList;

    tempStringList = this->nextInstancesHeuristicOne();

    //qDebug()<<"Estado inicial"<<this->toString();

    foreach (QString tempString, *(tempStringList)){

        puzzleList.append(new EightPuzzleInstance(NULL, tempString));
        //qDebug()<<"Primeiro nível"<<tempString;
    }

    foreach (EightPuzzleInstance *tempInstance, puzzleList){

        foreach (QString tempString, *tempInstance->nextInstancesHeuristicOne()){

            tempStringList2->append(tempString);
            //qDebug()<<"Segundo nível"<<tempString;

        }
    }



    return tempStringList2;

}

QStringList *EightPuzzleInstance::nextPersonalInstance()
{
    QStringList *tempStringList;
    QStringList *tempStringList2 = new QStringList();
    QList<EightPuzzleInstance *> puzzleList;

    tempStringList = this->nextInstancesHeuristicTwo();

    foreach (QString tempString, *(tempStringList)){

        puzzleList.append(new EightPuzzleInstance(NULL, tempString));
        //qDebug()<<"Primeiro nível"<<tempString;
    }

    foreach (EightPuzzleInstance *tempInstance, puzzleList){

        foreach (QString tempString, *tempInstance->nextInstancesHeuristicTwo()){

            tempStringList2->append(tempString);
            //qDebug()<<"Segundo nível"<<tempString;

        }
    }

    return tempStringList2;

}

QString EightPuzzleInstance::nextInstanceRandomSolution()
{

    QStringList *tempStringList;

    tempStringList = this->nextInstancesHeuristicOne();

    int random = this->pseudoRandomNumber(tempStringList->size()-1, 1);

    qDebug()<<tempStringList->value(random);

    return tempStringList->value(random);

}

void EightPuzzleInstance::initPiecesPosition(QString currentState)
{
    this->instancePiecesPosition = new QHash<int, int>;

    QStringList tempList = currentState.split("_");

    bool ok;

    QString auxIndex;
    QString auxValor;

    foreach (QString tempString, tempList){

        auxIndex = tempString.split(":")[0];
        auxValor = tempString.split(":")[1];

        this->instancePiecesPosition->insert(auxIndex.toInt(&ok, 10), auxValor.toInt(&ok, 10));

        //qDebug<<this->instancePiecesPosition->value(auxIndex.toInt(&ok, 10));

    }

}

int EightPuzzleInstance::getEmptyIndex()
{

    QStringList tempList = this->toString().split("_");
    int i;
    bool ok;

    for(i=1; i<=9; i++){

        if(tempList.value(i-1).split(":")[1].toInt(&ok, 10) == 9) break;

    }

    return i;


}

QString EightPuzzleInstance::toString()
{
    QString actualInstance;

    actualInstance.append(tr("1:%1").arg(this->instancePiecesPosition->value(1)));

    for(int i=2; i<=9; i++){

        actualInstance.append(tr("_%1:%2").arg(i).arg(this->instancePiecesPosition->value(i)));

    }
    //qDebug()<<actualInstance.toStdString();


    return actualInstance;

}

QString EightPuzzleInstance::toString(QHash<int, int> *someInstance)
{

    QString instance;

    instance.append(tr("1:%1").arg(someInstance->value(1)));

    for(int i=2; i<=9; i++){

        instance.append(tr("_%1:%2").arg(i).arg(someInstance->value(i)));

    }



    //qDebug()<<instance.toStdString();


    return instance;

}

int EightPuzzleInstance::decisionFunction()
{

    int decisionValor = 0;
    int j;


    for(int i=1; i<=8; i++){


        for(j=1; j<=9; j++)
            if(this->instancePiecesPosition->value(j) == i) break;

        //qDebug()<<"("<<i<<"-"<<j<<")^2 ="<<(i-j)*(i-j);

        //auxValor = this->instancePiecesPosition->value(j);
        decisionValor = decisionValor +  ((i-j)*(i-j));



    }

    //qDebug()<<decisionValor;

    //system("pause");



    return decisionValor;

}
/*
int EightPuzzleInstance::decisionFunctionPersonal()
{

    int decisionValor = 0;
    int blankPosition=0;

    for(int i=1; i<=9; i++){

        blankPosition = i;

        if(this->instancePiecesPosition->value(i) == 9)

            switch(blankPosition){


            case 1:

                decisionValor = (this->instancePiecesPosition->value(2) + this->instancePiecesPosition->value(4))/2;

                break;

            case 2:

                decisionValor = (this->instancePiecesPosition->value(1) + this->instancePiecesPosition->value(3)+
                                 this->instancePiecesPosition->value(5))/3;

                break;

            case 3:

                decisionValor = (this->instancePiecesPosition->value(2) + this->instancePiecesPosition->value(6))/2;

                break;

            case 4:

                decisionValor = (this->instancePiecesPosition->value(1) + this->instancePiecesPosition->value(5)+
                                 this->instancePiecesPosition->value(7))/3;

                break;

            case 5:

                decisionValor = (this->instancePiecesPosition->value(2) + this->instancePiecesPosition->value(6)+
                                 this->instancePiecesPosition->value(4) + this->instancePiecesPosition->value(8))/4;

                break;

            case 6:

                decisionValor = (this->instancePiecesPosition->value(3) + this->instancePiecesPosition->value(5)+
                                 this->instancePiecesPosition->value(9))/3;

                break;

            case 7:

                decisionValor = (this->instancePiecesPosition->value(4) + this->instancePiecesPosition->value(8))/2;

                break;

            case 8:

                decisionValor = (this->instancePiecesPosition->value(5) + this->instancePiecesPosition->value(7)+
                                 this->instancePiecesPosition->value(9))/3;

                break;

            case 9:

                decisionValor = (this->instancePiecesPosition->value(6) + this->instancePiecesPosition->value(8))/2;

                break;

            default: break;

            }


    }
    return decisionValor;

}
*/

/*
int EightPuzzleInstance::verifyDiference(QString tempString)
{

    QStringList tempList = tempString.split("_");

    int decisionValor=0;

    bool ok;

    for(int i=1; i<=9; i++){

        if(tempList.value(i-1).split(":").value(0).toInt(&ok, 10) == this->getEmptyIndex()){


            //std::cout<<tempList.value(i-1).split(":").value(1).toInt(&ok, 10)<<"-"<<this->decisionFunctionPersonal()<<std::endl;

            decisionValor = (tempList.value(i-1).split(":").value(1).toInt(&ok, 10)-this->decisionFunctionPersonal())*
                    (tempList.value(i-1).split(":").value(1).toInt(&ok, 10)-this->decisionFunctionPersonal());


            return decisionValor;

        }
    }

    return decisionValor;
}
*/

/*
int EightPuzzleInstance::decisionFunctionPersonal(QString someInstance)
{
    int decisionValor = 0;
    int blankPosition=0;
    bool ok;

    QStringList tempList = someInstance.split("_");

    for(int i=1; i<=9; i++){

        blankPosition = i;

        if(tempList.value(i-1).split(":")[1].toInt(&ok, 10) == 9)

            switch(blankPosition){


            case 1:

                decisionValor = (tempList.value(1).split(":")[1].toInt(&ok, 10) + tempList.value(3).split(":")[1].toInt(&ok, 10))/2;

                break;

            case 2:

                decisionValor = (tempList.value(0).split(":")[1].toInt(&ok, 10) + tempList.value(2).split(":")[1].toInt(&ok, 10)+
                        tempList.value(4).split(":")[1].toInt(&ok, 10))/3;

                break;

            case 3:

                decisionValor = (tempList.value(1).split(":")[1].toInt(&ok, 10) + tempList.value(5).split(":")[1].toInt(&ok, 10))/2;

                break;

            case 4:

                decisionValor = (tempList.value(0).split(":")[1].toInt(&ok, 10) + tempList.value(4).split(":")[1].toInt(&ok, 10)+
                        tempList.value(6).split(":")[1].toInt(&ok, 10))/3;

                break;

            case 5:

                decisionValor = (tempList.value(1).split(":")[1].toInt(&ok, 10) + tempList.value(3).split(":")[1].toInt(&ok, 10)+
                        tempList.value(5).split(":")[1].toInt(&ok, 10) + tempList.value(7).split(":")[1].toInt(&ok, 10))/4;

                break;

            case 6:

                decisionValor = (tempList.value(2).split(":")[1].toInt(&ok, 10) + tempList.value(4).split(":")[1].toInt(&ok, 10)+
                        tempList.value(8).split(":")[1].toInt(&ok, 10))/3;

                break;

            case 7:

                decisionValor = (tempList.value(3).split(":")[1].toInt(&ok, 10) + tempList.value(7).split(":")[1].toInt(&ok, 10))/2;

                break;

            case 8:

                decisionValor = (tempList.value(4).split(":")[1].toInt(&ok, 10) + tempList.value(6).split(":")[1].toInt(&ok, 10)+
                        tempList.value(8).split(":")[1].toInt(&ok, 10))/3;

                break;

            case 9:

                decisionValor = (tempList.value(5).split(":")[1].toInt(&ok, 10) + tempList.value(7).split(":")[1].toInt(&ok, 10))/2;

                break;

            }


    }

    return decisionValor;


}
*/

int EightPuzzleInstance::decisionFunction(QString someInstance)
{

    QStringList tempList = someInstance.split("_");

    int decisionValor = 0;
    int j;

    bool ok;


    for(int i=1; i<=8; i++){

        for(j=1; j<=9; j++)
            if(tempList.value(j-1).split(":")[1].toInt(&ok, 10) == i) break;

        //qDebug()<<"("<<i<<"-"<<j<<")^2 ="<<(i-j)*(i-j);

        //qDebug()<<"decisionValor ="<<decisionValor<<"+"<<((i-j)*(i-j));

        decisionValor = decisionValor + ((i-j)*(i-j));


    }



    //qDebug()<<"int EightPuzzleInstance::decisionFunction(QString someInstance)"<<decisionValor;

    //system("pause");
    return decisionValor;

}

QString EightPuzzleInstance::swapBlankSpace(int actualBlankSpace, int targetPieceToSwap)
{
    int aux;
    QHash<int, int> auxHash;

    auxHash = *(this->instancePiecesPosition);

    aux = auxHash.value(targetPieceToSwap);
    auxHash.insert(targetPieceToSwap, 9);
    auxHash.insert(actualBlankSpace, aux);

    //qDebug()<<this->toString(&auxHash).toStdString();

    return this->toString(&auxHash);

}

void EightPuzzleInstance::shufflePuzzle(int numOfMovements)
{
    QStringList *tempStringList;

    for(int i = 0; i < numOfMovements; i++){

        tempStringList = this->nextInstancesHeuristicOne();

        int random = this->pseudoRandomNumber(tempStringList->size()-1, 1);

        //qDebug()<<tempStringList->value(random);

        this->initPiecesPosition(tempStringList->value(random));

    }

}

int EightPuzzleInstance::pseudoRandomNumber(int max, int min)
{

    srand((unsigned)time(0) + randomSeedHelp++); //para gerar números aleatórios reais.


    return rand()%(max-min+1) + min;

}

QHash<int, int> *EightPuzzleInstance::getPiecesPosition()
{
    return this->instancePiecesPosition;

}

