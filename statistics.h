/**
* @file statistics.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.2
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Contains declarations for Additional Functionality and Strategic Reports.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

#include "data.h"

/**
 * @brief ADDITIONAL FUNCTIONALITY: Operational Capacity Monitor.
 *
 * Displays a real-time dashboard showing the percentage of available resources (Human and Material).
 * It calculates the ratio of available vs. total resources and issues a critical alert
 * if the capacity drops below 20%.
 *
 * @param fHead Pointer to the head of the firefighter linked list.
 * @param eHead Pointer to the head of the equipment linked list.
 */
void showOperationalMonitor(FirefighterNode* fHead, EquipmentNode* eHead);

/**
 * @brief COMPLEX REPORT 1: Operational Efficiency Analysis.
 *
 * Calculates and displays the average resolution time (in minutes) for each type of incident
 * (Forest, Urban, Industrial), based on resolved occurrences with valid end dates.
 *
 * @param head Pointer to the head of the occurrence linked list.
 */
void reportOperationalEfficiency(OccurrenceNode* head);

/**
 * @brief COMPLEX REPORT 2: Equipment Usage and Strain Analysis.
 *
 * Analyzes the ratio of equipment in maintenance versus operational status to determine
 * if the fleet is overstrained. Provides strategic advice if the maintenance ratio exceeds 30%.
 *
 * @param head Pointer to the head of the equipment linked list.
 */
void reportEquipmentStrain(EquipmentNode* head);

#endif // STATISTICS_H