#include "neuron.h"

Neuron init_neuron(int input_size, double accuracy) {
    Neuron neuron;
    neuron.input_size = input_size;
    neuron.accuracy = accuracy;
    
    neuron.weights = (double*)malloc(input_size * sizeof(double));
    
    if (neuron.weights == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < input_size; i++) {
        neuron.weights[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
    }
    
    neuron.bias = (double)rand() / RAND_MAX * 2.0 - 1.0;
    
    printf("Successfully initialized neuron.\n");
    printf("Input size: %d, Accuracy: %.4f\n", input_size, accuracy);
    
    return neuron;
}

double activate(Neuron* neuron, double* inputs) {
    double result = 0.0;

    for (int i = 0; i < neuron->input_size; i++) {
        result += (inputs[i] * neuron->weights[i]);
    }
    
    result += neuron->bias;
    return result;
}

void train_step(Neuron* neuron, double* inputs, bool expected_answer) {
    // Get current prediction
    double result = activate(neuron, inputs);
    bool predicted_answer = (result > 0.0);

    // Only update if prediction is wrong
    if (predicted_answer != expected_answer) {
        // Determine direction of update: +1 for ring, -1 for pen
        double multiplier = expected_answer ? 1.0 : -1.0;
        
        // Update each weight: w[i] = w[i] + input[i] * learning_rate * direction
        for (int i = 0; i < neuron->input_size; i++) {
            neuron->weights[i] += inputs[i] * neuron->accuracy * multiplier;
        }
        
        // Update bias: bias = bias + learning_rate * direction
        neuron->bias += neuron->accuracy * multiplier;
    }
}

void free_neuron(Neuron* neuron) {
    if (neuron != NULL) {
        free(neuron->weights);
        neuron->weights = NULL;
        neuron->input_size = 0;
    }
}