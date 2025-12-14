/**
 * @file statistics.c
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.3
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Implementation of strategic reports and additional decision-support tools.
 */

#include <stdio.h> // Provides standard input and output functions (e.g., printf, scanf)

#include "statistics.h"

/**
 * @brief Helper function to calculate the difference in minutes between two dates.
 */
int calcMinutes(DateTime start, DateTime end) {
    long t1 = start.year * 525600 + start.month * 43200 + start.day * 1440 + start.hour * 60 + start.minute;
    long t2 = end.year * 525600 + end.month * 43200 + end.day * 1440 + end.hour * 60 + end.minute;
    return (int)(t2 - t1);
}

/**
 * @brief ADDITIONAL FUNCTIONALITY: Operational Capacity Monitor.
 *
 * Displays a real-time dashboard showing the percentage of available resources.
 * It strictly ignores INACTIVE (deleted) resources.
 */
void showOperationalMonitor(FirefighterNode* fHead, EquipmentNode* eHead) {
    printf("\n=== MONITOR DE CAPACIDADE OPERACIONAL ===\n");

    int totalF = 0, freeF = 0;
    while(fHead) {
        if (fHead->data.status == FIREFIGHTER_INACTIVE) {
            fHead = fHead->next;
            continue;
        }

        totalF++;

        if(fHead->data.status == AVAILABLE) {
            freeF++;
        }

        fHead = fHead->next;
    }

    int totalE = 0, freeE = 0;
    while(eHead) {
        if (eHead->data.status == EQUIPMENT_INACTIVE) {
            eHead = eHead->next;
            continue;
        }

        totalE++;
        if(eHead->data.status == OPERATIONAL) {
            freeE++;
        }
        eHead = eHead->next;
    }

    printf("Recursos Humanos (Bombeiros):\n");
    if(totalF > 0) {
        float perc = (float)freeF / totalF * 100;
        printf(" -> %d livres de %d totais (%.1f%%)\n", freeF, totalF, perc);

        if(perc < 20.0) printf(" Capacidade Crítica! Chamar reforços.\n");
        else printf(" Situação Estável.\n");
    } else {
        printf(" -> Sem dados de bombeiros ativos.\n");
    }

    printf("\nRecursos Materiais (Equipamentos):\n");
    if(totalE > 0) {
        float perc = (float)freeE / totalE * 100;
        printf(" -> %d operacionais de %d totais (%.1f%%)\n", freeE, totalE, perc);

        if(perc < 20.0) printf(" Frota perto do limite!\n");
        else printf(" Situação Estável.\n");
    } else {
        printf(" -> Sem dados de equipamentos ativos.\n");
    }

    printf("=========================================\n");
}

/**
 * @brief REPORT 1: Operational Efficiency Analysis.
 */
void reportOperationalEfficiency(OccurrenceNode* head) {
    printf("\n=== RELATÓRIO DE EFICIÊNCIA OPERACIONAL ===\n");
    printf("Tempo médio de resolução por Tipo de Incidente (minutos):\n");

    int forestTime = 0, forestCount = 0;
    int urbanTime = 0, urbanCount = 0;
    int indTime = 0, indCount = 0;

    while(head) {
        if(head->data.status == OCCURRENCE_INACTIVE || head->data.endedAt.year == 0) {
            head = head->next;
            continue;
        }

        if(head->data.status == RESOLVED) {
            int duration = calcMinutes(head->data.timestamp, head->data.endedAt);
            if (duration < 0) duration = 0;

            if(head->data.type == FOREST) { forestTime += duration; forestCount++; }
            else if(head->data.type == URBAN) { urbanTime += duration; urbanCount++; }
            else if(head->data.type == INDUSTRIAL) { indTime += duration; indCount++; }
        }
        head = head->next;
    }

    printf("- FLORESTAL: %d min (média) baseada em %d incidentes resolvidos.\n",
           forestCount ? forestTime/forestCount : 0, forestCount);
    printf("- URBANO:    %d min (média) baseada em %d incidentes resolvidos.\n",
           urbanCount ? urbanTime/urbanCount : 0, urbanCount);
    printf("- INDUSTRIAL:%d min (média) baseada em %d incidentes resolvidos.\n",
           indCount ? indTime/indCount : 0, indCount);
}

/**
 * @brief REPORT 2: Equipment Usage and Strain Analysis.
 */
void reportEquipmentStrain(EquipmentNode* head) {
    printf("\n=== ANÁLISE DE DESGASTE DE EQUIPAMENTO ===\n");
    int total = 0, maintenance = 0, operational = 0;

    while(head) {
        if(head->data.status == EQUIPMENT_INACTIVE) {
            head = head->next;
            continue;
        }

        total++;
        if(head->data.status == MAINTENANCE) maintenance++;
        if(head->data.status == OPERATIONAL) operational++;

        head = head->next;
    }

    printf("Total da Frota: %d unidades\n", total);
    printf("Prontidão Operacional: %.1f%%\n", total ? (float)operational/total * 100 : 0);
    printf("Rácio de Manutenção: %.1f%%\n", total ? (float)maintenance/total * 100 : 0);

    if(total && (float)maintenance/total > 0.3) {
        printf("Percentagem de manutenção elevada (>30%%)! Considerar novas aquisições.\n");
    } else {
        printf("O estado da frota é considerado saudável.\n");
    }
}

void recommendResources(FirefighterNode* fHead, EquipmentNode* eHead) {
}