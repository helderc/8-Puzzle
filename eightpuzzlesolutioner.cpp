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

#include "eightpuzzlesolutioner.h"

EightPuzzleSolutioner::EightPuzzleSolutioner(QObject *parent)
    : QObject(parent)
{

    this->instancesFlow = new QHash<QString, EightPuzzleInstance *>;
    this->lastInstances = new QStack<QString>;
    this->justToControll = 0;

}


QList<QString> EightPuzzleSolutioner::heuristics(EightPuzzleInstance *actualInstance, int chooseHeuristic)
{
    QStringList *tempList;
    QString tempString;

    while(true){

         std::cout<<"INSTANCIA ATUAL "<<actualInstance->toString().toStdString()<<std::endl;



        //std::cout<<"INSTANCIA ATUAL ESTÁ CONTIDA NO DICIONÁRIO?"<<instancesFlow->contains(actualInstance->toString())<<std::endl;



        this->pushOnStack(actualInstance, chooseHeuristic);

        if(actualInstance->decisionFunction() == 0){

            //std::cout<<"INSTANCIA ATUAL "<<actualInstance->toString().toStdString()<<std::endl;
            //std::cout<<"Tamanho da pilha contada "<<this->justToControll<<std::endl;
            //std::cout<<"Tamanho da pilha pela pilha "<<this->lastInstances->size()<<std::endl;

            break;

        }

        if(HEURISTIC_ONE == chooseHeuristic){
            //std::cout<<"Heuristica UM"<<std::endl;
            tempList = actualInstance->nextInstancesHeuristicOne();
        }
        else if(HEURISTIC_TWO == chooseHeuristic)
            tempList = actualInstance->nextInstancesHeuristicTwo();
        else if(RANDOM_SOLUTION == chooseHeuristic)
            tempString = actualInstance->nextInstanceRandomSolution();
        else if( PERSONAL_HEURISTIC == chooseHeuristic){

            tempList = actualInstance->nextPersonalInstance();

        }


        if((HEURISTIC_ONE == chooseHeuristic) || (HEURISTIC_TWO == chooseHeuristic) ||
                (PERSONAL_HEURISTIC == chooseHeuristic)){

            //std::cout<<"Próxima instância"<<std::endl;
            tempString = this->getNextInstance(tempList, actualInstance, chooseHeuristic);

        }


        actualInstance = new EightPuzzleInstance(NULL, tempString);

        //system("pause");


    }


    //if(HEURISTIC_TWO == chooseHeuristic) {
     //   this->fixHeuristicTwo(&this->lastInstances->toList());
    //}

    return this->lastInstances->toList();

}

QString EightPuzzleSolutioner::getNextInstance(QStringList *tempList, EightPuzzleInstance *actualInstance, int chooseHeuristic)
{
    QString tempString2;
    QHash<QString, int> *decisionFunctions = new QHash<QString, int>;

    foreach (QString tempString, tempList->toStdList()){


        decisionFunctions->insert(tempString, EightPuzzleInstance::decisionFunction(tempString));
        //std::cout<<"FILHA DA ATUAL:"<<tempString.toStdString()<<". PESO: "<<EightPuzzleInstance::decisionFunction(tempString)<<std::endl;


    }
    tempString2 = this->obtainNextInstance(decisionFunctions, actualInstance);

    //std::cout<<"TEMPSTRING LOGO ANTES DE RETORNAR DE getNextInstance: "<<tempString2.toStdString()<<std::endl;

    return tempString2;

}

QString EightPuzzleSolutioner::obtainNextInstance(QHash<QString, int> *relationInstancesDecision,
                                                  EightPuzzleInstance *actualInstance)
{
    QString tempString;
    QString aux;
    int min = 1000;

    for(int i = 0; i < relationInstancesDecision->size(); i++){

        if(!this->instancesFlow->contains(relationInstancesDecision->keys().value(i))){

            //std::cout<<"relationInstancesDecision->keys().value(i) "<<relationInstancesDecision->keys().value(i).toStdString()<<std::endl;

            tempString = relationInstancesDecision->keys().value(i);
            min = relationInstancesDecision->value(tempString);
            relationInstancesDecision->remove(relationInstancesDecision->keys().value(i));

            aux = tempString;

            //std::cout<<"PRIMEIRA STRING LIVRE : "<<aux.toStdString()<<". COM PESO: "<<min<<std::endl;

            break;

        }

    }

    for(int i = 0; i < relationInstancesDecision->size(); i++){

        //std::cout<<relationInstancesDecision->value(relationInstancesDecision->keys().value(i))<<std::endl;

        //std::cout<<"PROXIMA FILHA A SER AVALIADA : "<<relationInstancesDecision->keys().value(i).toStdString()<<" . COM PESO: "<<relationInstancesDecision->value(relationInstancesDecision->keys().value(i))<<std::endl;



        if(min > relationInstancesDecision->value(relationInstancesDecision->keys().value(i))){

            aux = tempString;

            //std::cout<<"O valor de decisão da instancia"<<relationInstancesDecision->keys().value(i).toStdString()<<std::endl;
            //std::cout<<"e'' menor que o da instancia"<<aux.toStdString()<<std::endl;


            if(this->instancesFlow->contains(relationInstancesDecision->keys().value(i))){

                //std::cout<<"A instancia "<<relationInstancesDecision->keys().value(i).toStdString()<<" ja foi visitada"<<std::endl;
                //relationInstancesDecision->remove(relationInstancesDecision->keys().value(i));

            }
            else{// */

                //std::cout<<"A instancia"<<relationInstancesDecision->keys().value(i).toStdString()<<"nao foi visitada"<<std::endl;

                tempString = relationInstancesDecision->keys().value(i);
                min = relationInstancesDecision->value(tempString);
                //relationInstancesDecision->remove(relationInstancesDecision->keys().value(i));

                aux = tempString;

                //std::cout<<"FILHA ESCOLHIDA ATUALIZADA : "<<aux.toStdString()<<". COM PESO : "<<min<<std::endl;

            }


        }

    }



    if(this->instancesFlow->contains(tempString) || tempString == NULL){

        //std::cout<<lastInstances->isEmpty()<<std::endl;

        if(!lastInstances->isEmpty()){

            this->justToControll--;
            lastInstances->pop();
            //this->instancesFlow->remove(tempString);
            aux = tempString;

            //std::cout<<"A instancia "<<aux.toStdString()<<"ja existe no dicionario, ela será desempilhada! "<<std::endl;

        }
        if(!lastInstances->isEmpty()){

            tempString = lastInstances->value(lastInstances->size()-1);
            //lastInstances->push(tempString);

            aux = tempString;

            //std::cout<<"Pega a intancia anterior "<<aux.toStdString()<<std::endl;

            //system("pause");


        }

    }

    //std::cout<<"FILHA ESCOLHIDA : "<<aux.toStdString()<<std::endl;

    aux = tempString;

    return aux;


}
//*/

void EightPuzzleSolutioner::pushOnStack(EightPuzzleInstance *actualInstance, int chooseHeuristic)
{

    if(!instancesFlow->contains(actualInstance->toString())){

        justToControll++;
        if(chooseHeuristic != this->RANDOM_SOLUTION){

            instancesFlow->insert(actualInstance->toString(), actualInstance);
            //std::cout<<"Adicionando "<<actualInstance->toString().toStdString()<<" a lista de estados visitados"<<std::endl;

        }

        lastInstances->append(actualInstance->toString());
        //std::cout<<"Adicionando "<<actualInstance->toString().toStdString()<<" a pilha"<<std::endl;

    }

}

QList<QString> EightPuzzleSolutioner::fixHeuristicTwo(QList<QString> *tempList)
{
    QStringList tempStringList, tempStringList2;
    QString *tempString = new QString();
    int index = 0, auxValue = 0, index2 = 0, auxValue2 = 0;
    bool ok;

    //PERCORRE TODA A LISTA
    for(int i=0; i<tempList->size(); i+=2){

        //std::cout<<tempList->value(i).toStdString()<<std::endl;
        //std::cout<<tempList->value(i+1).toStdString()<<std::endl;
        //std::cout<<"Tamanho da lista a ser arrumada para a heuristica 2 "<<tempList->size()<<std::endl;

        tempStringList = tempList->value(i).split("_");
        tempStringList2 = tempList->value(i+1).split("_");



        tempString->clear();

        index = 0;
        auxValue = 0;
        index = 0;
        auxValue = 0;


        for(int j=0; j < tempStringList.size(); j++){

            //std::cout<<"j: "<<j<<std::endl;

            if(tempStringList.value(j).split(":")[1].toInt(&ok, 10) == 9){

                index = tempStringList.value(j).split(":")[0].toInt(&ok, 10);
                auxValue = tempStringList.value(j).split(":")[1].toInt(&ok, 10);
                //std::cout<<"index: "<<index<<". auxValue: "<<auxValue<<std::endl;
                break;

            }

        }

        for(int j=0; j < tempStringList2.size(); j++){


            if(tempStringList2.value(j).split(":")[0].toInt(&ok, 10) == index){

                auxValue2 = tempStringList2.value(j).split(":")[1].toInt(&ok, 10);
                //std::cout<<". auxValue2: "<<auxValue2<<std::endl;
                break;

            }

        }

        for(int j=0; j < tempStringList.size(); j++){

            if(tempStringList.value(j).split(":")[1].toInt(&ok, 10) == auxValue2){

                index2 = tempStringList.value(j).split(":")[0].toInt(&ok, 10);
                //std::cout<<"index2: "<<index2<<std::endl;
            }


        }

        if(index == 1)
            tempString->append(tr("%1:%2").arg(index).arg(auxValue2));
        else if(index2 == 1)
            tempString->append(tr("%1:%2").arg(index2).arg(auxValue));
        else tempString->append(tr("1:%1").arg(tempList->value(i).split("_")[0].split(":")[1].toInt(&ok, 10)));

        for(int j=1; j <=8; j++){

            if(index == j+1)
                tempString->append(tr("_%1:%2").arg(index).arg(auxValue2));
            else if(index2 == j+1)
                tempString->append(tr("_%1:%2").arg(index2).arg(auxValue));
            else tempString->append(tr("_%1:%2").arg(j+1).arg(tempList->value(i).split("_")[j].split(":")[1].toInt(&ok, 10)));

            //std::cout<<tempString->toStdString()<<std::endl;

        }



        //std::cout<<tempString->toStdString()<<std::endl;

        tempList->insert(i+1, *tempString);


    }

    return *tempList;
}




