#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "warrior.h"
#include "dragon.h"
#include "element.h"
#include "rent.h"

void warriorsSubMenu(int subCod) {
    int i, code;
    Warrior* warriorP;
    Warrior warrior;
    switch (subCod) {
            case 1:
                if(getWarriorsLength() == 0) {
                    printf("Nenhum guerreiro encontrado!\n");
                } else {
                    for(i = 0; i < getWarriorsLength(); i++) {
                        warriorP = getWarriorByIndex(i);
                        printf("Codigo: %d\nNome: %s\nTitulo: %s\nReino: %s\n\n",
                            warriorP->cod,
                            warriorP->name,
                            warriorP->title,
                            warriorP->kingdom
                        );
                        free(warriorP);
                    }
                }
                break;

            case 2:
                printf("Qual o nome do guerreiro?\n");
                scanf("%s", warrior.name);

                printf("Qual o título do guerreiro?\n");
                scanf("%s", warrior.title);

                printf("Qual o reino do guerreiro?\n");
                scanf("%s", warrior.kingdom);

                if(saveWarrior(warrior) == 1) {
                    printf("Guerreiro salvo com sucesso!\n");
                } else {
                    printf("Erro ao salvar guerreiro!\n");
                }
                break;

            case 3:
                printf("Qual o codigo do guerreiro?\n");
                scanf("%d", &warrior.cod);

                printf("Qual o novo nome do guerreiro?\n");
                scanf("%s", warrior.name);
                
                printf("Qual o novo título do guerreiro?\n");
                scanf("%s", warrior.title);
                
                printf("Qual o novo reino do guerreiro?\n");
                scanf("%s", warrior.kingdom);

                int updateResult = updateWarrior(warrior);
                if(updateResult == 1) {
                     printf("Guerreiro atualizado com sucesso!\n");
                } else if(updateResult == 2) {
                    printf("Guerreiro não existe!\n");
                } else {
                    printf("Erro ao atualizar guerreiro!\n");
                }                 
                break;
            
            case 4:
                printf("Digite o código do guerreiro:\n");
                scanf("%d", &code);

                warriorP = getWarriorByCod(code);
                if (warriorP != NULL) {
                    printf("Guerreiro encontrado com sucesso! Nome: %s\n", warriorP->name);
                    free(warriorP);
                } else {
                    printf("Guerreiro não encontrado\n");
                }
                
                break;
            
            case 5:
                printf("Digite o código do guerreiro:\n");
                scanf("%d", &code);

                int deleteResult = deleteWarriorByCod(code);
                if(deleteResult == 1) {
                    printf("Guerreiro deletado com sucesso!\n");
                } else if (deleteResult == 2) {
                    printf("O guerreiro esta em uma locacao, nao eh possivel apaga-lo!\n");
                } else {
                    printf("Guerreiro não encontrado\n");
                }
            
            default:
                break;
            }
}

void dragonsSubMenu(int subCod) {
    int i, code;
    Element* elementP;
    Dragon* dragonP;
    Dragon dragon;
    switch (subCod) {
            case 1:
                if(getDragonsLength() == 0) {
                    printf("Nenhum dragão encontrado!\n");
                } else {
                    for(i = 0; i < getDragonsLength(); i++) {
                        dragonP = getDragonByIndex(i);
                        elementP = getElementByCod(dragonP->elementCode);
                        printf("Codigo: %d\nNome: %s\nIdade: %d\nValor diário: %.2f\nUnidades: %d\nElemento: %s\n\n",
                            dragonP->cod,
                            dragonP->name,
                            dragonP->age,
                            dragonP->dailyValue,
                            dragonP->units,
                            elementP->name
                        );
                        free(dragonP);
                        free(elementP);
                    }
                }
                break;

            case 2:
                printf("Qual o nome do dragão?\n");
                scanf("%s", dragon.name);

                printf("Qual a idade do dragão?\n");
                scanf("%d", &dragon.age);

                printf("Qual o valor diário do dragão?\n");
                scanf("%f", &dragon.dailyValue);

                printf("Quantas unidades tem no estoque?\n");
                scanf("%d", &dragon.units);

                printf("Qual o codigo do elemento do dragão?\n");
                scanf("%d", &dragon.elementCode);

                int saveResult = saveDragon(dragon);
                if(saveResult == 1) {
                  printf("Dragao salvo com sucesso!\n");
                } else if(saveResult == 2) {
                    printf("Elemento não encontrado! Tente novamente\n");
                } else {
                    printf("Erro ao salvar dragao!\n");;
                }

                break;

            case 3:
                printf("Qual o codigo do dragao?\n");
                scanf("%d", &dragon.cod);

                printf("Qual o novo nome do dragao?\n");
                scanf("%s", dragon.name);
                
                printf("Qual a nova idade do dragao?\n");
                scanf("%d", &dragon.age);
                
                printf("Qual o novo valor do dragao?\n");
                scanf("%f", &dragon.dailyValue);
                
                printf("Qual o novo valor de unidades no estoque?\n");
                scanf("%d", &dragon.units);

                int updateResult = updateDragon(dragon);
                if(updateResult == 1) {
                    printf("Dragao atualizado com sucesso!\n");
                } else if(updateResult == 2) {
                    printf("Dragao nao encontrado!\n");
                } else {
                    printf("Erro ao atualizar dragao!\n");
                }

                break;
            
            case 4:
                printf("Digite o código do dragão:\n");
                scanf("%d", &code);

                dragonP = getDragonByCod(code);
                if (dragonP != NULL) {
                    printf("Dragão encontrado com sucesso! Nome: %s\n", dragonP->name);
                    free(dragonP);
                } else {
                    printf("Dragão não encontrado\n");
                }
                
                break;
            
            case 5:
                printf("Digite o código do dragão:\n");
                scanf("%d", &code);
                
                int deleteResult = deleteDragonByCod(code);
                if(deleteResult == 1) {
                    printf("Dragao deletado com sucesso!\n");
                } else if (deleteResult == 2) {
                    printf("O dragao esta em uma locacao, nao eh possivel apaga-lo!\n");
                } else {
                    printf("Erro ao deletar dragao!\n");
                }
            
            default:
                break;
            }
}

void elementsSubMenu(int subCod) {
    int i, code;
    Element* elementP;
    Element element;
    switch (subCod) {
            case 1:
                if(getElementsLength() == 0) {
                    printf("Nenhum elemento encontrado!\n");
                } else {
                    for(i = 0; i < getElementsLength(); i++) {
                        elementP = getElementByIndex(i);
                        printf("Codigo: %d\nNome: %s\nVulnerabilidade: %s\n\n",
                            elementP->cod,
                            elementP->name,
                            elementP->vulnerability
                        );
                        free(elementP);
                    }
                }
                break;

            case 2:
                printf("Qual o nome do elemento?\n");
                scanf("%s", element.name);

                printf("Qual a vulnerabilidade do elemento?\n");
                scanf("%s", element.vulnerability);

                if(saveElement(element) == 1) {
                    printf("Elemento salvo com sucesso!\n");
                } else {
                    printf("Erro ao salvar elemento!\n");
                }
                break;
            
            case 3:
                printf("Qual o codigo do elemento?\n");
                scanf("%d", &element.cod);

                printf("Qual o novo nome do elemento?\n");
                scanf("%s", element.name);
                
                printf("Qual a nova vulnerabilidade do elemento?\n");
                scanf("%s", element.vulnerability);

                int updateResult = updateElement(element);
                if(updateResult == 1) {
                    printf("Elemento atualizado com sucesso!\n");
                } else if(updateResult == 2) {
                    printf("Elemento não existe!\n");
                } else {
                    printf("Erro ao atualizar elemento!\n");
                }

                break;


            case 4:
                printf("Digite o código do elemento:\n");
                scanf("%d", &code);

                elementP = getElementByCod(code);
                if (elementP != NULL) {
                    printf("Elemento encontrado com sucesso! Nome: %s\n", elementP->name);
                    free(elementP);
                } else {
                    printf("Elemento não encontrado\n");
                }
                
                break;
            
            case 5:
                printf("Digite o código do elemento:\n");
                scanf("%d", &code);

                int deleteResult = deleteElementByCod(code);

                if(deleteResult == 1) {
                    printf("Elemento deletado com sucesso!\n");
                } else if (deleteResult == 2) {
                    printf("Voce tem um dragao que depende desse elemento, apague-o antes\n");
                } else {
                    printf("Elemento não encontrado\n");
                }
            
            default:
                break;
            }
}

void rentsSubMenu(int subCod) {
    int i, code;
    Rent rent;
    Rent* rentP;
    Dragon* dragonP;
    Warrior* warriorP;
    
    switch (subCod) {
            case 1:
                if(getRentsLength() == 0) {
                    printf("Nenhuma locacao encontrada!\n");
                } else {
                    for(i = 0; i < getRentsLength(); i++) {
                        rentP = getRentByIndex(i);
                        dragonP = getDragonByCod(rentP->dragonCod);
                        warriorP = getWarriorByCod(rentP->warriorCod);
                        printf("Codigo: %d\nPago: %s\nData fim: %s\nData inicio: %s\nGuerreiro: %s\nDragao: %s\n\n",
                            rentP->cod,
                            rentP->paid == 1 ? "Sim" : "Não",
                            rentP->endRentDate,
                            rentP->startRentDate,
                            warriorP->name,
                            dragonP->name
                        );
                        free(rentP);
                        free(dragonP);
                        free(warriorP);
                    }
                }
                break;

            case 2:
                rent.paid = 0;

                printf("Qual a data final da locacao?\n");
                scanf("%s", rent.endRentDate);

                printf("Qual a data inicial da locacao?\n");
                scanf("%s", rent.startRentDate);

                printf("Qual o codigo do guerreiro que irá locar?\n");
                scanf("%d", &rent.warriorCod);

                printf("Qual o codigo do dragao locado?\n");
                scanf("%d", &rent.dragonCod);

                int saveResult = saveRent(rent);

                if(saveResult == 1) {
                    printf("Locacao salva com sucesso!\n");
                } else if(saveResult == 2) {
                    printf("Guerreiro nao encontrado! Tente novamente\n");
                } else if(saveResult == 3) {
                    printf("Dragao nao encontrado! Tente novamente\n");
                } else if(saveResult == 4) {
                    printf("Dragao sem unidades disponiveis\n");
                } else {
                    printf("Erro ao salvar locacao!\n");
                }

                break;

            case 3:
                printf("Qual o codigo da locacao?\n");
                scanf("%d", &rent.cod);

                printf("Qual a nova data final da locação?\n");
                scanf("%s", rent.endRentDate);

                printf("Qual a nova data inicial da locação?\n");
                scanf("%s", rent.startRentDate);

                int updateResult = updateRent(rent);

                if(updateResult == 1) {
                    printf("Locacao atualizada com sucesso!\n");
                } else if(updateResult == 2) {
                    printf("Locacao não existe!\n");
                } else {
                    printf("Erro ao atualizar locacao!\n");
                }

                break;
            
            case 4:
                printf("Digite o codigo da locacao:\n");
                scanf("%d", &code);

                rentP = getRentByCod(code);
                if (rentP != NULL) {
                    dragonP = getDragonByCod(rentP->dragonCod);
                    warriorP = getWarriorByCod(rentP->warriorCod);
                    printf("Locacao encontrada com sucesso! Guerreiro: %s\nDragao: %s\n",
                        warriorP->name,
                        dragonP->name
                    );
                    free(rentP);
                    free(dragonP);
                    free(warriorP);
                } else {
                    printf("Locacao não encontrada\n");
                }
                
                break;
            
            case 5:
                printf("Locacoes nao finalizadas:\n\n");

                for(i = 0; i < getRentsLength(); i++) {
                    rentP = getRentByIndex(i);
                    if(rentP->paid == 0) {
                    // Exibe somente locações não finalizadas
                        dragonP = getDragonByCod(rentP->dragonCod);
                        warriorP = getWarriorByCod(rentP->warriorCod);
                        printf("Codigo: %d\nData fim: %s\nData inicio: %s\nGuerreiro: %s\nDragao: %s\n\n",
                            rentP->cod,
                            rentP->endRentDate,
                            rentP->startRentDate,
                            warriorP->name,
                            dragonP->name
                        );
                        free(dragonP);
                        free(warriorP);
                    }
                    free(rentP);
                }

                printf("Digite o código da locacao a ser finalizada:\n");
                scanf("%d", &code);

                int finishResult = finishRentByCod(code);

                if(finishResult == 1) {
                    printf("Locacao finalizada com sucesso!\n");
                } else if(finishResult == 2) {
                    printf("Locacao não encontrada!\n");
                } else if(finishResult == 3) {
                    printf("Locacao ja foi finalizada!\n");
                } else {
                    printf("Erro ao finalizar locacao!\n");
                }
            
            default:
                break;
            }
}

int main(int argc, char const *argv[]) {
    int cod = -1, subCod;

    initWarriors();
    initDragons();
    initElements();
    initRents();

    do {
        printf("0 - Sair\n");
        printf("1 - Guerreiros\n");
        printf("2 - Dragoes\n");
        printf("3 - Elementos de dragoes\n");
        printf("4 - Locacoes\n");
        scanf("%d", &cod);
        subCod = -1;

        while(subCod != 0 && cod != 0) {
            printf("0 - Sair\n");
            printf("1 - Listar\n");
            printf("2 - Cadastrar\n");
            printf("3 - Alterar\n");
            printf("4 - Pesquisar\n");
            if(cod == 4) {
                printf("5 - Finalizar\n");
            } else {
                printf("5 - Excluir\n");
            }
            scanf("%d", &subCod);

            switch (cod) {
            case 1:
                warriorsSubMenu(subCod);
                break;
            case 2:
                dragonsSubMenu(subCod);
                break;
            case 3:
                elementsSubMenu(subCod);
                break;
            case 4:
                rentsSubMenu(subCod);
                break;
            default:
                break;
            }
        } 
    } while (cod != 0);

    finishWarriors();
    finishDragons();
    finishElements();
    finishRents();
    return 0;
}
