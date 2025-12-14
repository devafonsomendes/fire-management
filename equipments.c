/**
 * @file equipments.c
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Implementation of the logic for the Equipment management module.
 */

#include <stdio.h>   // Provides standard input and output functions (e.g., printf, scanf)
#include <stdlib.h>  // Provides functions for memory allocation, process control, conversions, etc.

#include "equipments.h"
#include "input.h"

/**
 * @brief Displays the Equipment management menu.
 *
 * @param head Double pointer to the head of the linked list.
 * @param idSeq Pointer to the ID sequence counter.
 */
void menuEquipments(EquipmentNode** head, int* idSeq) {
    int op;
    do {
        printf("\n--- GESTÃO DE EQUIPAMENTOS ---\n");
        printf("1. Adicionar Equipamento\n2. Listar Equipamentos\n3. Alterar Estado\n4. Remover Equipamento\n0. Voltar\n");
        op = getInt(0, 4, "Opção: ");
        switch (op) {
            case 1:
                *head = createEquipment(*head, idSeq);
            break;
            case 2:
                listEquipments(*head);
            break;
            case 3:
                updateEquipment(*head);
            break;
            case 4:
                *head = deleteEquipment(*head);
            break;
        }
    } while (op != 0);
}

/**
 * @brief Creates a new equipment item and adds it to the list.
 *
 * @param head Pointer to the current head of the linked list.
 * @param idSeq Pointer to the ID sequence counter.
 * @return Returns the new head of the linked list.
 */
EquipmentNode* createEquipment(EquipmentNode* head, int* idSeq) {
    EquipmentNode* newNode = (EquipmentNode*) malloc(sizeof(EquipmentNode));
    if (!newNode) return head;

    (*idSeq)++;
    newNode->data.id = *idSeq;

    cleanInputBuffer();
    getString(newNode->data.designation, MAX_STRING, "Designação: ");
    getString(newNode->data.type, MAX_STRING, "Tipo (ex: Mangueira): ");

    newNode->data.status = OPERATIONAL;
    newNode->next = head;

    printf("Equipamento registado ID: %d\n", *idSeq);
    return newNode;
}

/**
 * @brief Lists all available equipment.
 *
 * @param head Pointer to the head of the linked list.
 */
void listEquipments(EquipmentNode* head) {
    if(!head) { printf("Sem equipamentos.\n"); return; }
    printf("\n%-5s | %-20s | %-15s | %-10s\n", "ID", "DESIGNAÇÃO", "TIPO", "ESTADO");
    EquipmentNode* current = head;
    while (current) {
        if (current->data.status != EQUIPMENT_INACTIVE) {
            printf("%-5d | %-20s | %-15s | %-10d\n",
                   current->data.id, current->data.designation, current->data.type, current->data.status);
        }
        current = current->next;
    }
}

/**
 * @brief Updates the status of an equipment item.
 *
 * @param head Pointer to the head of the linked list.
 */
void updateEquipment(EquipmentNode* head) {
    int id = getInt(1, 99999, "ID do Equipamento: ");
    EquipmentNode* current = head;
    while(current) {
        if(current->data.id == id && current->data.status != EQUIPMENT_INACTIVE) {
            printf("Novo Estado (0-Operacional, 1-Em Uso, 2-Manutenção): ");
            int st = getInt(0, 2, "");
            current->data.status = (EquipmentStatus)st;
            printf("Estado atualizado.\n");
            return;
        }
        current = current->next;
    }
    printf("Equipamento não encontrado.\n");
}

/**
 * @brief Removes an equipment item (Soft delete).
 *
 * @param head Pointer to the head of the linked list.
 * @return Returns the head of the linked list.
 */
EquipmentNode* deleteEquipment(EquipmentNode* head) {
    int id = getInt(1, 99999, "ID a remover: ");
    EquipmentNode* current = head;
    while(current) {
        if(current->data.id == id) {
            current->data.status = EQUIPMENT_INACTIVE;
            printf("Equipamento removido.\n");
            return head;
        }
        current = current->next;
    }
    printf("ID não encontrado.\n");
    return head;
}

/**
 * @brief Saves equipment data to a binary file.
 *
 * @param head Pointer to the head of the linked list.
 */
void saveEquipments(EquipmentNode* head) {
    FILE* fp = fopen(FILE_EQUIPMENTS, "wb");
    if (!fp) return;
    while(head){
        fwrite(&head->data, sizeof(Equipment), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

/**
 * @brief Loads equipment data from a binary file.
 *
 * @param idSeq Pointer to store the highest ID found.
 * @return Returns the pointer to the head of the loaded linked list.
 */
EquipmentNode* loadEquipments(int* idSeq) {
    FILE* fp = fopen(FILE_EQUIPMENTS, "rb");
    if (!fp) return NULL;
    EquipmentNode* head = NULL;
    Equipment temp;
    *idSeq = 0;
    while(fread(&temp, sizeof(Equipment), 1, fp)){
        EquipmentNode* newNode = (EquipmentNode*)malloc(sizeof(EquipmentNode));
        newNode->data = temp;
        newNode->next = head;
        head = newNode;
        if(temp.id > *idSeq) *idSeq = temp.id;
    }
    fclose(fp);
    return head;
}

/**
 * @brief Frees memory allocated for equipment.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeEquipments(EquipmentNode* head) {
    EquipmentNode* temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}