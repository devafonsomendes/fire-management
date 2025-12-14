/**
 * @file input.c
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Implementation of user input reading and validation functions.
 */

#include <stdio.h> // Provides standard input and output functions (e.g., printf, scanf)
#include <string.h> // Provides functions for string manipulation (e.g., strcpy, strlen)

#include "input.h"

#define INVALID_VALUE "O valor inserido é inválido."

/**
 * @brief Clears the input buffer to prevent read errors.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * @brief Reads an integer within a specific range.
 *
 * @param minValue Minimum acceptable value.
 * @param maxValue Maximum acceptable value.
 * @param message Message to display to the user.
 * @return The validated integer entered by the user.
 */
int getInt(int minValue, int maxValue, char *message) {
    int value;
    printf("%s", message);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf("%s", message);
    }
    cleanInputBuffer();
    return value;
}

/**
 * @brief Reads a float within a specific range.
 *
 * @param minValue Minimum acceptable value.
 * @param maxValue Maximum acceptable value.
 * @param message Message to display to the user.
 * @return The validated float entered by the user.
 */
float getFloat(float minValue, float maxValue, char *message) {
    float value;
    printf("%s", message);
    while (scanf("%f", &value) != 1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf("%s", message);
    }
    cleanInputBuffer();
    return value;
}

/**
 * @brief Reads a double within a specific range.
 *
 * @param minValue Minimum acceptable value.
 * @param maxValue Maximum acceptable value.
 * @param message Message to display to the user.
 * @return The validated double entered by the user.
 */
double getDouble(double minValue, double maxValue, char *message) {
    double value;
    printf("%s", message);
    while (scanf("%lf", &value) != 1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf("%s", message);
    }
    cleanInputBuffer();
    return value;
}

/**
 * @brief Reads a single character.
 *
 * @param message Message to display to the user.
 * @return The character entered by the user.
 */
char getChar(char *message) {
    char value;
    printf("%s", message);
    value = getchar();
    cleanInputBuffer();
    return value;
}

/**
 * @brief Reads a string with a maximum length.
 *
 * @param string Buffer where the string will be stored.
 * @param length Maximum length of the string to read.
 * @param message Message to display to the user.
 */
void getString(char *string, unsigned int length, char *message) {
    printf("%s", message);
    if (fgets(string, length, stdin) != NULL) {
        unsigned int len = strlen(string);
        if (len > 0 && string[len - 1] == '\n') {
            string[len - 1] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}