#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    double* weights;
    double bias;
    double accuracy;
    int input_size;
} Neuron;

Neuron init_neuron(int input_size, double accuracy);
double activate(Neuron* neuron, double* inputs);
void train_step(Neuron* neuron, double* inputs, bool expected_answer);
void free_neuron(Neuron* neuron);