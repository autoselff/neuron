#pragma once
#include "config.h"

/**
 * @brief Generates random training data for ring/pen classification
 * @param size Number of training samples to generate
 * @return Pointer to dynamically allocated 2D array of training data
 * @note Caller is responsible for freeing the returned memory
 * @details Generates data where:
 *          - Rings: small radius (5-250), small width (2-50)
 *          - Pens: either large radius or large width (100-50000)
 */
double** generate_training_data(int size);

/**
 * @brief Generates corresponding labels for training data based on generated patterns
 * @param data Pointer to 2D training data array
 * @param size Number of training samples
 * @return Pointer to dynamically allocated array of boolean labels
 * @note Caller is responsible for freeing the returned memory
 * @details Analyzes data to determine if each sample is a ring or pen:
 *          - Ring (true): both radius and width are small
 *          - Pen (false): either radius or width is large
 */
bool* generate_training_labels(double** data, int size);

/**
 * @brief Frees memory allocated for training data
 * @param data Pointer to 2D training data array
 * @param size Number of samples in the array
 */
void free_training_data(double** data, int size);