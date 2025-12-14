/**
* @mainpage Sistema de Gestão de Incêndios
 *
 * @section intro_sec Introdução
 *
 * Este projeto foi desenvolvido no âmbito da Unidade Curricular de Laboratório de Programação.
 * O objetivo é gerir recursos de uma corporação de bombeiros, incluindo pessoal, equipamentos e ocorrências.
 *
 * @section features_sec Funcionalidades Principais
 *
 * - **Gestão de Entidades:** Criar, Listar, Atualizar e Remover (CRUD) Bombeiros, Equipamentos e Ocorrências.
 * - **Operações:** Gestão de Intervenções e alocação de recursos.
 * - **Persistência:** Todos os dados são guardados em ficheiros binários.
 * - **Estratégia:** Painel de controlo com estatísticas e monitorização em tempo real.
 *
 * @section authors_sec Autores
 *
 * - **Afonso Mendes** (8250706)
 * - **Rodrigo Ferreira** (8250433)
 *
 * @date 2025-2026
 */

#include <stdio.h> // Provides standard input and output functions (e.g., printf, scanf)

#include "firefighters.h"
#include "occurrences.h"
#include "equipments.h"
#include "interventions.h"
#include "statistics.h"

#include "input.h"
#include "data.h"

/**
 * @brief Entry point of the Firefighter Management System.
 *
 * Initializes the application by loading data from files (persistence), displays the main menu,
 * and handles user interactions for managing different components of the system.
 *
 * The main menu includes the functions for:
 * - Firefighters Management (Create, List, Update, Delete)
 * - Occurrences/Incidents Management (Create, List, Update, Delete)
 * - Equipments Management (Create, List, Update, Delete)
 *
 * @return Returns 0 upon successful program termination.
 */
int main() {
    // Initialize all linked list pointers to NULL
    FirefighterNode* listFirefighters = NULL;
    OccurrenceNode* listOccurrences = NULL;
    EquipmentNode* listEquipments = NULL;
    InterventionNode* listInterventions = NULL;

    // Initialize ID counters
    int idFirefighter = 0, idOccurrence = 0, idEquipment = 0, idIntervention = 0;

    // Loading binary files ensures data persistence between sessions.
    listFirefighters = loadFirefighters(&idFirefighter);
    listOccurrences = loadOccurrences(&idOccurrence);
    listEquipments = loadEquipments(&idEquipment);
    listInterventions = loadInterventions(&idIntervention);

    // Welcome messages
    printf("Bem-vindo ao projeto Gestão de incêndios!\n");
    printf("Desenvolvido por Afonso Mendes e Rodrigo Ferreira.\n\n");

    int option;

    do {
        printf("\n-----MENU PRINCIPAL-----\n");
        printf("1. Gerir Bombeiros\n");
        printf("2. Gerir Ocorrências\n");
        printf("3. Gerir Equipamentos\n");
        printf("4. Gerir Intervenções\n");
        printf("5. Painel Estratégico\n");
        printf("0. Sair\n");

        option = getInt(0, 5, "Escolha uma opção: ");

        switch (option) {
            case 1:
                menuFirefighters(&listFirefighters, &idFirefighter);
            break;
            case 2:
                menuOccurrences(&listOccurrences, &idOccurrence);
            break;
            case 3:
                menuEquipments(&listEquipments, &idEquipment);
            break;
            case 4:
                menuInterventions(&listInterventions, listOccurrences, listFirefighters, listEquipments, &idIntervention);
            break;
            case 5:
                printf("\n--- ESTATÍSTICAS E ESTRATÉGIA ---\n");
                printf("1. Monitor de Capacidade Operacional\n");
                printf("2. Relatório de Eficiência Operacional (Tempo/Tipo)\n");
                printf("3. Análise de Desgaste de Equipamento (Manutenção)\n");
                printf("0. Voltar\n");

                int subOp = getInt(0, 3, "Opção: ");

                if (subOp == 1) showOperationalMonitor(listFirefighters, listEquipments);
                if (subOp == 2) reportOperationalEfficiency(listOccurrences);
                if (subOp == 3) reportEquipmentStrain(listEquipments);
            break;
            case 0:
                // Save information
                saveFirefighters(listFirefighters);
                saveOccurrences(listOccurrences);
                saveEquipments(listEquipments);
                saveInterventions(listInterventions);

                // Critical step to prevent memory leaks in the operating system.
                freeFirefighters(listFirefighters);
                freeOccurrences(listOccurrences);
                freeEquipments(listEquipments);
                freeInterventions(listInterventions);
            break;
        }
    } while (option != 0);

    return 0;
}