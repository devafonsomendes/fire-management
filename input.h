/**
* @file input.h
 * @author Afonso Mendes
 * @author Rodrigo Ferreira
 * @version 1.0
 *
 * @copyright Copyright (C) ESTG 2025. All Rights MIT Licensed.
 *
 * @brief Contains declarations for input validation functions to ensure robust user interaction.
 */

#ifndef INPUT_H
#define INPUT_H

/**
 * @brief Reads an integer within a specific range.
 *
 * @param minValue Minimum acceptable value.
 * @param maxValue Maximum acceptable value.
 * @param message Message to display to the user.
 * @return The validated integer entered by the user.
 */
int getInt(int minValue, int maxValue, char *message);

/**
 * @brief Reads a float within a specific range.
 *
 * @param minValue Minimum acceptable value.
 * @param maxValue Maximum acceptable value.
 * @param message Message to display to the user.
 * @return The validated float entered by the user.
 */
float getFloat(float minValue, float maxValue, char *message);

/**
 * @brief Reads a double within a specific range.
 *
 * @param minValue Minimum acceptable value.
 * @param maxValue Maximum acceptable value.
 * @param message Message to display to the user.
 * @return The validated double entered by the user.
 */
double getDouble(double minValue, double maxValue, char *message);

/**
 * @brief Reads a single character.
 *
 * @param message Message to display to the user.
 * @return The character entered by the user.
 */
char getChar(char *message);

/**
 * @brief Reads a string with a maximum length.
 *
 * @param string Buffer where the string will be stored.
 * @param length Maximum length of the string to read.
 * @param message Message to display to the user.
 */
void getString(char *string, unsigned int length, char *message);

/**
 * @brief Clears the input buffer to prevent read errors.
 */
void cleanInputBuffer();

#endif // INPUT_H