/**
 * @file interventions.c
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Implementation of Intervention logic and specific reports.
 */

#include <stdio.h>   // Provides standard input and output functions (e.g., printf, scanf)
#include <stdlib.h>  // Provides functions for memory allocation, process control, conversions, etc.

#include "interventions.h"
#include "input.h"

/**
 * @brief Helper function to calculate the difference in minutes between two dates.
 */
int diffMinutes(DateTime start, DateTime end) {
    long t1 = start.year * 525600 + start.month * 43200 + start.day * 1440 + start.hour * 60 + start.minute;
    long t2 = end.year * 525600 + end.month * 43200 + end.day * 1440 + end.hour * 60 + end.minute;
    return (int)(t2 - t1);
}

/**
 * @brief Displays the Intervention management menu.
 */
void menuInterventions(InterventionNode** head, OccurrenceNode* occHead, FirefighterNode* fireHead, EquipmentNode* equipHead, int* idSeq) {
    int op;
    do {
        printf("\n--- GESTÃO DE INTERVENÇÕES ---\n");
        printf("1. Criar Intervenção\n2. Listar Intervenções\n3. Atualizar Estado\n4. Cancelar Intervenção\n");
        printf("5. Relatório de Estatísticas e Eficiência\n0. Voltar\n");
        op = getInt(0, 5, "Opção: ");

        switch (op) {
            case 1:
                *head = createIntervention(*head, occHead, fireHead, equipHead, idSeq);
            break;
            case 2:
                listInterventions(*head);
            break;
            case 3:
                updateIntervention(*head);
            break;
            case 4:
                *head = deleteIntervention(*head);
            break;
            case 5:
                reportInterventionStats(*head);
            break;
        }
    } while (op != 0);
}

/**
 * @brief Creates a new intervention linked to resources.
 */
InterventionNode* createIntervention(InterventionNode* head, OccurrenceNode* occHead, FirefighterNode* fireHead, EquipmentNode* equipHead, int* idSeq) {
    InterventionNode* newNode = (InterventionNode*) malloc(sizeof(InterventionNode));
    if (!newNode) return head;

    (*idSeq)++;
    newNode->data.id = *idSeq;

    int occId = getInt(1, 99999, "ID da Ocorrência Associada: ");
    newNode->data.idOccurrence = occId;

    printf("--- Data de Início ---\n");
    newNode->data.start.day = getInt(1,31,"Dia: ");
    newNode->data.start.month = getInt(1,12,"Mês: ");
    newNode->data.start.year = getInt(2020,2030,"Ano: ");
    newNode->data.start.hour = getInt(0,23,"Hora: ");
    newNode->data.start.minute = getInt(0,59,"Minuto: ");

    newNode->data.end.day = 0;
    newNode->data.end.year = 0;

    printf("Atribuir ID do Bombeiro: ");
    int fId = getInt(1, 99999, "");
    newNode->data.assignedFirefighterId = fId;

    while(fireHead) {
        if(fireHead->data.id == fId) {
            fireHead->data.totalInterventions++;
            printf("Bombeiro %s atribuído.\n", fireHead->data.name);
            break;
        }
        fireHead = fireHead->next;
    }

    newNode->data.status = IN_PLANNING;
    newNode->next = head;
    printf("Intervenção %d criada.\n", *idSeq);
    return newNode;
}

/**
 * @brief Lists all interventions.
 */
void listInterventions(InterventionNode* head) {
    if(!head) { printf("Sem intervenções.\n"); return; }
    printf("\nID | OCORRÊNCIA | ESTADO\n");
    while(head) {
        char statusStr[20];
        if(head->data.status == IN_PLANNING) sprintf(statusStr, "Planeamento");
        else if(head->data.status == RUNNING) sprintf(statusStr, "Em Curso");
        else sprintf(statusStr, "Concluída");

        if(head->data.status != INTERVENTION_INACTIVE)
             printf("%d | %d | %s\n", head->data.id, head->data.idOccurrence, statusStr);
        head = head->next;
    }
}

/**
 * @brief Updates the status of an intervention.
 */
void updateIntervention(InterventionNode* head) {
    int id = getInt(1, 99999, "ID da Intervenção: ");
    while(head) {
        if(head->data.id == id) {
            printf("Novo Estado (0-Planeamento, 1-Em Curso, 2-Concluída): ");
            int st = getInt(0, 2, "");
            head->data.status = (InterventionStatus)st;
            if(st == 2) {
                printf("--- Data de Fim ---\n");
                head->data.end.day = getInt(1,31,"Dia: ");
                head->data.end.hour = getInt(0,23,"Hora: ");
                head->data.end.minute = getInt(0,59,"Minuto: ");
            }
            return;
        }
        head = head->next;
    }
}

/**
 * @brief Cancels an intervention.
 */
InterventionNode* deleteIntervention(InterventionNode* head) {
    int id = getInt(1, 99999, "ID a cancelar: ");
    InterventionNode* current = head;
    while(current) {
        if(current->data.id == id) {
            current->data.status = INTERVENTION_INACTIVE;
            printf("Intervenção cancelada.\n");
            return head;
        }
        current = current->next;
    }
    printf("ID não encontrado.\n");
    return head;
}

/**
 * @brief REPORT: Efficiency Stats.
 */
void reportInterventionStats(InterventionNode* head) {
    printf("\n=== ESTATÍSTICAS DA INTERVENÇÃO ===\n");
    int count = 0;
    int totalDuration = 0;

    while(head) {
        if(head->data.status == FINISHED) {
            int dur = diffMinutes(head->data.start, head->data.end);
            if(dur > 0) {
                totalDuration += dur;
                count++;
            }
        }
        head = head->next;
    }

    if(count > 0) printf("- Duração Média: %d minutos\n", totalDuration / count);
    else printf("- Nenhuma intervenção concluída.\n");

    printf("- Total Concluídas: %d\n", count);
}

void saveInterventions(InterventionNode* head) {
    FILE* fp = fopen(FILE_INTERVENTIONS, "wb");
    if (!fp) return;
    while(head) {
        fwrite(&head->data, sizeof(Intervention), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

InterventionNode* loadInterventions(int* idSeq) {
    FILE* fp = fopen(FILE_INTERVENTIONS, "rb");
    if (!fp) return NULL;
    InterventionNode* head = NULL;
    Intervention temp;
    *idSeq = 0;
    while(fread(&temp, sizeof(Intervention), 1, fp)){
        InterventionNode* newNode = (InterventionNode*)malloc(sizeof(InterventionNode));
        newNode->data = temp;
        newNode->next = head;
        head = newNode;
        if(temp.id > *idSeq) *idSeq = temp.id;
    }
    fclose(fp);
    return head;
}

void freeInterventions(InterventionNode* head) {
    InterventionNode* temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}