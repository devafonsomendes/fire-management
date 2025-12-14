/**
 * @file occurrences.c
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Implementation of the logic for the Occurrence management module.
 */

#include <stdio.h>   // Provides standard input and output functions (e.g., printf, scanf)
#include <stdlib.h>  // Provides functions for memory allocation, process control, conversions, etc.
#include <string.h> // Provides functions for string manipulation (e.g., strcpy, strlen)

#include "occurrences.h"
#include "input.h"

/**
 * @brief Helper function to read date and time from user input.
 *
 * @return Returns the populated DateTime structure.
 */
DateTime readDateTime() {
    DateTime dt;
    printf("--- Data e Hora ---\n");
    dt.day = getInt(1, 31, "Dia: ");
    dt.month = getInt(1, 12, "Mês: ");
    dt.year = getInt(2020, 2030, "Ano: ");
    dt.hour = getInt(0, 23, "Hora: ");
    dt.minute = getInt(0, 59, "Minuto: ");
    return dt;
}

/**
 * @brief Displays the Occurrence management menu.
 */
void menuOccurrences(OccurrenceNode** head, int* idSeq) {
    int op;
    do {
        printf("\n--- GESTÃO DE OCORRÊNCIAS ---\n");
        printf("1. Registar Ocorrência\n2. Listar Ocorrências\n3. Atualizar Estado\n4. Cancelar Ocorrência\n");
        printf("5. Estatísticas por Localização (Relatório)\n0. Voltar\n");
        op = getInt(0, 5, "Opção: ");
        switch (op) {
            case 1:
                *head = createOccurrence(*head, idSeq);
            break;
            case 2:
                listOccurrences(*head);
            break;
            case 3:
                updateOccurrence(*head);
            break;
            case 4:
                *head = deleteOccurrence(*head);
            break;
            case 5:
                listOccurrenceStats(*head);
            break;
        }
    } while (op != 0);
}

/**
 * @brief Creates a new occurrence.
 */
OccurrenceNode* createOccurrence(OccurrenceNode* head, int* idSeq) {
    OccurrenceNode* newNode = (OccurrenceNode*) malloc(sizeof(OccurrenceNode));
    if (!newNode) return head;

    (*idSeq)++;
    newNode->data.id = *idSeq;

    cleanInputBuffer();
    getString(newNode->data.location, MAX_STRING, "Localização: ");

    printf("Tipo (0-Florestal, 1-Urbano, 2-Industrial)\n");
    newNode->data.type = (OccurrenceType) getInt(0, 2, "Tipo: ");

    printf("Prioridade (0-Baixa, 1-Normal, 2-Alta)\n");
    newNode->data.priority = (Priority) getInt(0, 2, "Prioridade: ");

    newNode->data.timestamp = readDateTime();
    newNode->data.status = REPORTED;

    newNode->data.endedAt.year = 0;

    newNode->next = head;
    printf("Ocorrência registada com ID %d.\n", *idSeq);
    return newNode;
}

/**
 * @brief Lists all occurrences.
 */
void listOccurrences(OccurrenceNode* head) {
    if(!head) { printf("Sem ocorrências registadas.\n"); return; }
    printf("\n%-5s | %-20s | %-10s | %-10s\n", "ID", "LOCAL", "PRIORIDADE", "ESTADO");
    OccurrenceNode* current = head;
    while (current) {
        if (current->data.status != OCCURRENCE_INACTIVE) {
            printf("%-5d | %-20s | %-10d | %-10d\n",
                current->data.id, current->data.location, current->data.priority, current->data.status);
        }
        current = current->next;
    }
}

/**
 * @brief Updates the status of an occurrence.
 */
void updateOccurrence(OccurrenceNode* head) {
    int id = getInt(1, 99999, "ID da Ocorrência: ");
    OccurrenceNode* current = head;
    while(current) {
        if(current->data.id == id && current->data.status != OCCURRENCE_INACTIVE) {
            printf("Novo Estado (0-Reportada, 1-Em Intervenção, 2-Concluída): ");
            int st = getInt(0, 2, "Estado: ");
            current->data.status = (OccurrenceStatus)st;

            if (st == RESOLVED) {
                printf("Inserir Data de Conclusão:\n");
                current->data.endedAt = readDateTime();
            }

            printf("Estado atualizado.\n");
            return;
        }
        current = current->next;
    }
    printf("Ocorrência não encontrada.\n");
}

/**
 * @brief Cancels an occurrence (Soft Delete).
 */
OccurrenceNode* deleteOccurrence(OccurrenceNode* head) {
    int id = getInt(1, 99999, "ID a cancelar: ");
    OccurrenceNode* current = head;
    while(current) {
        if(current->data.id == id) {
            current->data.status = OCCURRENCE_INACTIVE;
            printf("Ocorrência cancelada.\n");
            return head;
        }
        current = current->next;
    }
    printf("ID não encontrado.\n");
    return head;
}

/**
 * @brief REPORT: Stats by location.
 */
void listOccurrenceStats(OccurrenceNode* head) {
    if(!head) { printf("Sem dados para estatísticas.\n"); return; }

    printf("\n--- ANÁLISE POR LOCALIZAÇÃO E FREQUÊNCIA ---\n");

    OccurrenceNode* outer = head;
    while (outer) {
        if (outer->data.status == OCCURRENCE_INACTIVE) { outer = outer->next; continue; }

        int duplicate = 0;
        OccurrenceNode* checker = head;
        while(checker != outer) {
            if(strcmp(checker->data.location, outer->data.location) == 0 && checker->data.status != OCCURRENCE_INACTIVE) {
                duplicate = 1;
                break;
            }
            checker = checker->next;
        }

        if (!duplicate) {
            int count = 0;
            OccurrenceNode* inner = outer;
            while(inner) {
                if(strcmp(inner->data.location, outer->data.location) == 0 && inner->data.status != OCCURRENCE_INACTIVE) {
                    count++;
                }
                inner = inner->next;
            }
            printf("- %s: %d incidente(s)\n", outer->data.location, count);
        }
        outer = outer->next;
    }
}

void saveOccurrences(OccurrenceNode* head) {
    FILE* fp = fopen(FILE_OCCURRENCES, "wb");
    if (!fp) return;
    while(head){
        fwrite(&head->data, sizeof(Occurrence), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

OccurrenceNode* loadOccurrences(int* idSeq) {
    FILE* fp = fopen(FILE_OCCURRENCES, "rb");
    if (!fp) return NULL;
    OccurrenceNode* head = NULL;
    Occurrence temp;
    *idSeq = 0;
    while(fread(&temp, sizeof(Occurrence), 1, fp)){
        OccurrenceNode* newNode = (OccurrenceNode*)malloc(sizeof(OccurrenceNode));
        newNode->data = temp;
        newNode->next = head;
        head = newNode;
        if(temp.id > *idSeq) *idSeq = temp.id;
    }
    fclose(fp);
    return head;
}

void freeOccurrences(OccurrenceNode* head) {
    OccurrenceNode* temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}