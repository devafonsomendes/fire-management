/**
 * @file firefighters.c
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Implementation of the logic for the Firefighter management module.
 */

#include <stdio.h>   // Provides standard input and output functions (e.g., printf, scanf)
#include <stdlib.h>  // Provides functions for memory allocation, process control, conversions, etc.

#include "firefighters.h"
#include "input.h"

/**
 * @brief Displays the Firefighter management menu.
 */
void menuFirefighters(FirefighterNode** head, int* idSeq) {
    int op;
    do {
        printf("\n--- GESTÃO DE BOMBEIROS ---\n");
        printf("1. Adicionar Bombeiro\n");
        printf("2. Listar Bombeiros\n");
        printf("3. Atualizar Estado\n");
        printf("4. Remover Bombeiro\n");
        printf("5. Ranking de Desempenho (Relatório)\n");
        printf("0. Voltar\n");
        op = getInt(0, 5, "Opção: ");
        switch (op) {
            case 1:
                *head = createFirefighter(*head, idSeq);
            break;
            case 2:
                listFirefighters(*head);
            break;
            case 3:
                updateFirefighter(*head);
            break;
            case 4:
                *head = deleteFirefighter(*head);
            break;
            case 5:
                listFirefighterRanking(*head);
            break;
        }
    } while (op != 0);
}

/**
 * @brief Creates a new firefighter.
 */
FirefighterNode* createFirefighter(FirefighterNode* head, int* idSeq) {
    FirefighterNode* newNode = (FirefighterNode*) malloc(sizeof(FirefighterNode));
    if (!newNode) return head;

    (*idSeq)++;
    newNode->data.id = *idSeq;

    cleanInputBuffer();
    getString(newNode->data.name, MAX_STRING, "Nome do Bombeiro: ");
    getString(newNode->data.specialty, MAX_STRING, "Especialidade: ");

    newNode->data.status = AVAILABLE;
    newNode->data.totalInterventions = 0;
    newNode->data.totalResponseTime = 0;
    newNode->next = head;

    printf("Bombeiro criado com ID %d.\n", *idSeq);
    return newNode;
}

/**
 * @brief Lists all active firefighters.
 */
void listFirefighters(FirefighterNode* head) {
    if (!head) { printf("Nenhum bombeiro registado.\n"); return; }
    printf("\n%-5s | %-30s | %-20s | %-10s | %-5s\n", "ID", "NOME", "ESPECIALIDADE", "ESTADO", "INTERVENÇÕES");
    FirefighterNode* current = head;
    while (current) {
        if (current->data.status != FIREFIGHTER_INACTIVE) {
            printf("%-5d | %-30s | %-20s | %-10d | %-5d\n",
                   current->data.id, current->data.name, current->data.specialty, current->data.status, current->data.totalInterventions);
        }
        current = current->next;
    }
}

/**
 * @brief Updates the status of an existing firefighter.
 *
 * @param head Pointer to the head of the linked list.
 */
void updateFirefighter(FirefighterNode* head) {
    int id = getInt(1, 99999, "ID do Bombeiro a editar: ");
    FirefighterNode* current = head;
    while (current) {
        if (current->data.id == id && current->data.status != FIREFIGHTER_INACTIVE) {
            printf("Novo Estado (0-Disp, 1-Ocup, 2-Inat): ");
            int st = getInt(0, 2, "");
            current->data.status = (FirefighterStatus) st;
            printf("Estado atualizado.\n");
            return;
        }
        current = current->next;
    }
    printf("Bombeiro não encontrado.\n");
}

/**
 * @brief Performs a soft delete on a firefighter (sets state to INACTIVE).
 *
 * @param head Pointer to the head of the linked list.
 * @return Returns the head of the linked list.
 */
FirefighterNode* deleteFirefighter(FirefighterNode* head) {
    int id = getInt(1, 99999, "ID do Bombeiro a remover: ");
    FirefighterNode* current = head;
    while (current) {
        if (current->data.id == id) {
            current->data.status = FIREFIGHTER_INACTIVE;
            printf("Bombeiro removido (Inativo).\n");
            return head;
        }
        current = current->next;
    }
    printf("Bombeiro não encontrado.\n");
    return head;
}

/**
 * @brief REPORT: Ranking based on completed interventions.
*/
void listFirefighterRanking(FirefighterNode* head) {
    printf("\n=== RANKING DE DESEMPENHO (BOMBEIROS) ===\n");
    printf("%-30s | %-15s\n", "NOME", "INTERVENÇÕES");
    printf("------------------------------------------------\n");

    while(head) {
        if(head->data.status != FIREFIGHTER_INACTIVE) {
            printf("%-30s | %d concluídas\n", head->data.name, head->data.totalInterventions);
        }
        head = head->next;
    }
}

/**
 * @brief Saves the firefighter list to a binary file.
 *
 * @param head Pointer to the head of the linked list.
 */
void saveFirefighters(FirefighterNode* head) {
    FILE* fp = fopen(FILE_FIREFIGHTERS, "wb");
    if (!fp) return;
    while(head) {
        fwrite(&head->data, sizeof(Firefighter), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

/**
 * @brief Loads the firefighter list from a binary file.
 *
 * @param idSeq Pointer to store the highest ID found (to resume sequencing).
 * @return Returns the pointer to the head of the loaded linked list.
 */
FirefighterNode* loadFirefighters(int* idSeq) {
    FILE* fp = fopen(FILE_FIREFIGHTERS, "rb");
    if (!fp) return NULL;
    FirefighterNode* head = NULL;
    Firefighter temp;
    *idSeq = 0;
    while(fread(&temp, sizeof(Firefighter), 1, fp)){
        FirefighterNode* newNode = (FirefighterNode*)malloc(sizeof(FirefighterNode));
        if (!newNode) break;
        newNode->data = temp;
        newNode->next = head;
        head = newNode;
        if(temp.id > *idSeq) *idSeq = temp.id;
    }
    fclose(fp);
    return head;
}

/**
 * @brief Frees all memory allocated for the firefighter list.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeFirefighters(FirefighterNode* head) {
    FirefighterNode* temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}