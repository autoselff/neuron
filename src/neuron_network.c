#include "neuron_network.h"
#include <time.h>

NeuronNetwork init_network(int input_size, double accuracy) {
    NeuronNetwork network;
    network.input_size = input_size;
    network.accuracy = accuracy;
    
    network.weights = (double*)malloc(input_size * sizeof(double));
    
    if (network.weights == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < input_size; i++) {
        network.weights[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
    }
    
    network.bias = (double)rand() / RAND_MAX * 2.0 - 1.0;
    
    printf("Successfully initialized neural network.\n");
    printf("Input size: %d, Accuracy: %.4f\n", input_size, accuracy);
    
    return network;
}

/**
 * Jeżeli result jest większy od 0 to oznaczać to będzie że dane przedstawiają obrączkę.
 * Natomiast jeżeli wynik będzie mniejszy od 0 to będzie to oznaczać długopis.
 */
double activate(NeuronNetwork* network, double* inputs) {
    double result = 0.0;

    for (int i = 0; i < network->input_size; i++) {
        result += (inputs[i] * network->weights[i]);
    }
    
    result += network->bias;
    return result;
}

void train_step(NeuronNetwork* network, double* inputs, bool expected_answer) {
    double result = activate(network, inputs);
    bool predicted_answer = (result > 0.0);

    if (predicted_answer != expected_answer) {
        double multiplier = expected_answer ? 1.0 : -1.0;
        
        for (int i = 0; i < network->input_size; i++) {
            network->weights[i] += inputs[i] * network->accuracy * multiplier;
        }
        
        network->bias += network->accuracy * multiplier;
    }
}

void free_network(NeuronNetwork* network) {
    if (network != NULL) {
        free(network->weights);
        network->weights = NULL;
        network->input_size = 0;
    }
}