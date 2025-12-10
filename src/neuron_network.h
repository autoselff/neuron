#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double* weights;
    double bias;
    double accuracy;
    int input_size;
} NeuronNetwork;

NeuronNetwork init_network(int input_size, double accuracy);
double activate(NeuronNetwork* network, double* inputs);
void train_step(NeuronNetwork* network, double* inputs, bool expected_answer);
void free_network(NeuronNetwork* network);