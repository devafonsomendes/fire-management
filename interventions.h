/**
 * @file interventions.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Defines functions for managing Interventions and their reports.
 */

#ifndef INTERVENTIONS_H
#define INTERVENTIONS_H

#include "data.h"

/**
 * @brief Displays the Intervention management menu and handles user selection.
 *
 * @param head Double pointer to the head of the intervention linked list.
 * @param occHead Pointer to the head of the occurrence linked list (for linking).
 * @param fireHead Pointer to the head of the firefighter linked list (for assignment).
 * @param equipHead Pointer to the head of the equipment linked list (for assignment).
 * @param idSeq Pointer to the ID sequence counter.
 */
void menuInterventions(InterventionNode** head, OccurrenceNode* occHead, FirefighterNode* fireHead, EquipmentNode* equipHead, int* idSeq);

/**
 * @brief Creates a new intervention linked to an occurrence and resources.
 *
 * @param head Pointer to the current head of the intervention linked list.
 * @param occHead Pointer to the head of the occurrence linked list.
 * @param fireHead Pointer to the head of the firefighter linked list.
 * @param equipHead Pointer to the head of the equipment linked list.
 * @param idSeq Pointer to the ID sequence counter.
 * @return Returns the new head of the linked list.
 */
InterventionNode* createIntervention(InterventionNode* head, OccurrenceNode* occHead, FirefighterNode* fireHead, EquipmentNode* equipHead, int* idSeq);

/**
 * @brief Lists all registered interventions in the console.
 *
 * @param head Pointer to the head of the intervention linked list.
 */
void listInterventions(InterventionNode* head);

/**
 * @brief Updates the status or details (e.g., end date) of an intervention.
 *
 * @param head Pointer to the head of the intervention linked list.
 */
void updateIntervention(InterventionNode* head);

/**
 * @brief Cancels an intervention (Soft Delete / Inactive status).
 *
 * @param head Pointer to the head of the intervention linked list.
 * @return Returns the head of the linked list.
 */
InterventionNode* deleteIntervention(InterventionNode* head);

/**
 * @brief REPORT: Generates statistics on efficiency, duration, and resource usage.
 *
 * @param head Pointer to the head of the intervention linked list.
 */
void reportInterventionStats(InterventionNode* head);

/**
 * @brief Saves the intervention list to a binary file.
 *
 * @param head Pointer to the head of the intervention linked list.
 */
void saveInterventions(InterventionNode* head);

/**
 * @brief Loads the intervention list from a binary file.
 *
 * @param idSeq Pointer to store the highest ID found.
 * @return Returns the pointer to the head of the loaded linked list.
 */
InterventionNode* loadInterventions(int* idSeq);

/**
 * @brief Frees all memory allocated for the intervention list.
 *
 * @param head Pointer to the head of the intervention linked list.
 */
void freeInterventions(InterventionNode* head);

#endif // INTERVENTIONS_H