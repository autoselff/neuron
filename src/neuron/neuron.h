#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
 * @struct Neuron
 * @brief Represents a simple perceptron neural network unit
 * 
 * @var Neuron::weights
 * Array of weight values for each input feature
 * 
 * @var Neuron::bias
 * Bias term added to the weighted sum during activation
 * 
 * @var Neuron::accuracy
 * Learning rate that controls the step size during training
 * 
 * @var Neuron::input_size
 * Number of input features the neuron processes
 */
typedef struct {
    double* weights;
    double bias;
    double accuracy;
    int input_size;
} Neuron;

/**
 * @brief Initializes a new neuron with random weights and bias
 * @param input_size Number of input features the neuron will process
 * @param accuracy Learning rate for training (step size for weight updates)
 * @return Initialized Neuron structure with random weights between -1 and 1
 */
Neuron init_neuron(int input_size, double accuracy);

/**
 * @brief Computes the activation output of the neuron
 * @details Calculates weighted sum of inputs plus bias.
 *          If result > 0: predicts "ring"
 *          If result < 0: predicts "pen"
 * @param neuron Pointer to the neuron structure
 * @param inputs Array of input values to process
 * @return Activation result (positive for ring, negative for pen)
 */
double activate(Neuron* neuron, double* inputs);

/**
 * @brief Performs one training step using the perceptron learning rule
 * @details Updates weights and bias if the prediction is incorrect.
 *          Uses gradient descent with the specified learning rate (accuracy).
 * @param neuron Pointer to the neuron to train
 * @param inputs Array of input values for this training example
 * @param expected_answer True if input should be classified as "ring", false for "pen"
 */
void train_step(Neuron* neuron, double* inputs, bool expected_answer);

/**
 * @brief Frees allocated memory for the neuron
 * @details Releases the dynamically allocated weights array and resets structure
 * @param neuron Pointer to the neuron to free
 */
void free_neuron(Neuron* neuron);