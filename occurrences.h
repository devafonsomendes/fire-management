/**
* @file occurrences.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Defines functions for managing Occurrences/Incidents (Create, Read, Update, Delete) and persistence.
 */

#ifndef OCCURRENCES_H
#define OCCURRENCES_H

#include "data.h"

/**
 * @brief Displays the Occurrence management menu.
 *
 * @param head Double pointer to the head of the linked list.
 * @param idSeq Pointer to the ID sequence counter.
 */
void menuOccurrences(OccurrenceNode** head, int* idSeq);

/**
 * @brief Creates a new occurrence and adds it to the list.
 *
 * @param head Pointer to the current head of the linked list.
 * @param idSeq Pointer to the ID sequence counter.
 * @return Returns the new head of the linked list.
 */
OccurrenceNode* createOccurrence(OccurrenceNode* head, int* idSeq);

/**
 * @brief Lists all registered occurrences.
 *
 * @param head Pointer to the head of the linked list.
 */
void listOccurrences(OccurrenceNode* head);

/**
 * @brief Updates the state or details of an occurrence.
 *
 * @param head Pointer to the head of the linked list.
 */
void updateOccurrence(OccurrenceNode* head);

/**
 * @brief Cancels an occurrence (Soft delete).
 *
 * @param head Pointer to the head of the linked list.
 * @return Returns the head of the linked list.
 */
OccurrenceNode* deleteOccurrence(OccurrenceNode* head);

/**
 * @brief Saves occurrences to a binary file.
 *
 * @param head Pointer to the head of the linked list.
 */
void saveOccurrences(OccurrenceNode* head);

/**
 * @brief Loads occurrences from a binary file.
 *
 * @param idSeq Pointer to store the highest ID found.
 * @return Returns the pointer to the head of the loaded linked list.
 */
OccurrenceNode* loadOccurrences(int* idSeq);

/**
 * @brief Frees memory allocated for occurrences.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeOccurrences(OccurrenceNode* head);

/**
 * @brief Reports analysis by location and frequency.
 */
void listOccurrenceStats(OccurrenceNode* head);

#endif // OCCURRENCES_H