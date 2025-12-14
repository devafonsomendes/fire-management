/**
* @file equipments.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Defines functions for managing Equipment resources (Create, Read, Update, Delete) and persistence.
 */

#ifndef EQUIPMENTS_H
#define EQUIPMENTS_H

#include "data.h"

/**
 * @brief Displays the Equipment management menu.
 *
 * @param head Double pointer to the head of the linked list.
 * @param idSeq Pointer to the ID sequence counter.
 */
void menuEquipments(EquipmentNode** head, int* idSeq);

/**
 * @brief Creates a new equipment item and adds it to the list.
 *
 * @param head Pointer to the current head of the linked list.
 * @param idSeq Pointer to the ID sequence counter.
 * @return Returns the new head of the linked list.
 */
EquipmentNode* createEquipment(EquipmentNode* head, int* idSeq);

/**
 * @brief Lists all available equipment.
 *
 * @param head Pointer to the head of the linked list.
 */
void listEquipments(EquipmentNode* head);

/**
 * @brief Updates the status of an equipment item.
 *
 * @param head Pointer to the head of the linked list.
 */
void updateEquipment(EquipmentNode* head);

/**
 * @brief Removes an equipment item (Soft delete).
 *
 * @param head Pointer to the head of the linked list.
 * @return Returns the head of the linked list.
 */
EquipmentNode* deleteEquipment(EquipmentNode* head);

/**
 * @brief Saves equipment data to a binary file.
 *
 * @param head Pointer to the head of the linked list.
 */
void saveEquipments(EquipmentNode* head);

/**
 * @brief Loads equipment data from a binary file.
 *
 * @param idSeq Pointer to store the highest ID found.
 * @return Returns the pointer to the head of the loaded linked list.
 */
EquipmentNode* loadEquipments(int* idSeq);

/**
 * @brief Frees memory allocated for equipment.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeEquipments(EquipmentNode* head);

#endif // EQUIPMENTS_H