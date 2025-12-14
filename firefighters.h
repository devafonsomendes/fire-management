/**
 * @file firefighters.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Defines functions for managing Firefighters (Create, Read, Update, Delete) and data persistence.
 */

#ifndef FIREFIGHTERS_H
#define FIREFIGHTERS_H

#include "data.h"

/**
 * @brief Displays the Firefighter management menu and handles user selection.
 *
 * @param head Double pointer to the head of the linked list (to allow modification).
 * @param idSeq Pointer to the ID sequence counter.
 */
void menuFirefighters(FirefighterNode** head, int* idSeq);

/**
 * @brief Creates a new firefighter and adds it to the list.
 *
 * @param head Pointer to the current head of the linked list.
 * @param idSeq Pointer to the ID sequence counter to generate a new unique ID.
 * @return Returns the new head of the linked list.
 */
FirefighterNode* createFirefighter(FirefighterNode* head, int* idSeq);

/**
 * @brief Lists all active firefighters in the console.
 *
 * @param head Pointer to the head of the linked list.
 */
void listFirefighters(FirefighterNode* head);

/**
 * @brief Updates the status of an existing firefighter.
 *
 * @param head Pointer to the head of the linked list.
 */
void updateFirefighter(FirefighterNode* head);

/**
 * @brief Performs a soft delete on a firefighter (sets state to INACTIVE).
 *
 * @param head Pointer to the head of the linked list.
 * @return Returns the head of the linked list.
 */
FirefighterNode* deleteFirefighter(FirefighterNode* head);

/**
 * @brief Saves the firefighter list to a binary file.
 *
 * @param head Pointer to the head of the linked list.
 */
void saveFirefighters(FirefighterNode* head);

/**
 * @brief Loads the firefighter list from a binary file.
 *
 * @param idSeq Pointer to store the highest ID found (to resume sequencing).
 * @return Returns the pointer to the head of the loaded linked list.
 */
FirefighterNode* loadFirefighters(int* idSeq);

/**
 * @brief Frees all memory allocated for the firefighter list.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeFirefighters(FirefighterNode* head);

/**
 * @brief Lists firefighters ranked by the number of interventions.
 * @param head Pointer to the head of the linked list.
 */
void listFirefighterRanking(FirefighterNode* head);

#endif // FIREFIGHTERS_H