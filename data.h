/**
 * @file data.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.2
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Defines the core data structures (structs) and enumerations used across the entire system.
 * This file serves as the central data model for Firefighters, Occurrences, Equipment, and Interventions.
 */

#ifndef DATA_H
#define DATA_H

// Constants
#define MAX_STRING 100
#define FILE_FIREFIGHTERS "firefighters.bin"
#define FILE_OCCURRENCES "occurrences.bin"
#define FILE_EQUIPMENTS "equipments.bin"
#define FILE_INTERVENTIONS "interventions.bin"

// Enumerations

/**
 * @brief Represents the type of an occurrence environment.
 */
typedef enum {
    FOREST,
    URBAN,
    INDUSTRIAL
} OccurrenceType;

/**
 * @brief Represents the priority level of an occurrence.
 */
typedef enum {
    LOW,
    NORMAL,
    HIGH
} Priority;

/**
 * @brief Represents the lifecycle status of an occurrence.
 * @note OCCURRENCE_INACTIVE is used for soft-delete (history preservation).
 */
typedef enum {
    REPORTED,
    IN_PROGRESS,
    RESOLVED,
    OCCURRENCE_INACTIVE
} OccurrenceStatus;

/**
 * @brief Represents the availability status of a firefighter.
 */
typedef enum {
    AVAILABLE,
    BUSY,
    FIREFIGHTER_INACTIVE
} FirefighterStatus;

/**
 * @brief Represents the operational status of equipment.
 */
typedef enum {
    OPERATIONAL,
    IN_USE,
    MAINTENANCE,
    EQUIPMENT_INACTIVE
} EquipmentStatus;

/**
 * @brief Represents the status of an operational intervention.
 */
typedef enum {
    IN_PLANNING,
    RUNNING,
    FINISHED,
    INTERVENTION_INACTIVE
} InterventionStatus;

// Structures

/**
 * @brief Structure to represent Date and Time.
 */
typedef struct {
    int day, month, year;
    int hour, minute;
} DateTime;

/**
 * @brief Structure representing a Firefighter entity.
 */
typedef struct {
    int id;
    char name[MAX_STRING];
    char specialty[MAX_STRING];
    FirefighterStatus status;
    int totalInterventions;
    int totalResponseTime;
} Firefighter;

/**
 * @brief Linked List Node for Firefighters.
 * Implements a dynamic list to store firefighter data.
 */
typedef struct FirefighterNode {
    Firefighter data;
    struct FirefighterNode* next;
} FirefighterNode;

/**
 * @brief Structure representing an Occurrence (Incident).
 */
typedef struct {
    int id;
    char location[MAX_STRING];
    DateTime timestamp;
    DateTime endedAt;
    OccurrenceType type;
    Priority priority;
    OccurrenceStatus status;
} Occurrence;

/**
 * @brief Linked List Node for Occurrences.
 */
typedef struct OccurrenceNode {
    Occurrence data;
    struct OccurrenceNode* next;
} OccurrenceNode;

/**
 * @brief Structure representing Equipment.
 */
typedef struct {
    int id;
    char designation[MAX_STRING];
    char type[MAX_STRING];
    EquipmentStatus status;
} Equipment;

/**
 * @brief Linked List Node for Equipment.
 */
typedef struct EquipmentNode {
    Equipment data;
    struct EquipmentNode* next;
} EquipmentNode;

/**
 * @brief Structure representing an Intervention.
 * Links an Occurrence to the resources (Firefighter/Equipment) assigned to it.
 */
typedef struct {
    int id;
    int idOccurrence;
    DateTime start;
    DateTime end;
    InterventionStatus status;
    int assignedFirefighterId;
} Intervention;

/**
 * @brief Linked List Node for Interventions.
 */
typedef struct InterventionNode {
    Intervention data;
    struct InterventionNode* next;
} InterventionNode;

#endif // DATA_H