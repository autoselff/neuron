#include "training.h"

double** generate_training_data(int size) {
    double** data = (double**)malloc(size * sizeof(double*));
    
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size; i++) {
        data[i] = (double*)malloc(2 * sizeof(double));
        
        if (data[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(data[j]);
            }
            free(data);
            exit(EXIT_FAILURE);
        }
        
        if (i < size / 2) {
            data[i][0] = (double)(rand() % 246 + 5);
            data[i][1] = (double)(rand() % 49 + 2);
        } 
        else {
            if (rand() % 2 == 0) {
                data[i][0] = (double)(rand() % 49900 + 100);
                data[i][1] = (double)(rand() % 49 + 2);
            } else {
                data[i][0] = (double)(rand() % 246 + 5);
                data[i][1] = (double)(rand() % 49900 + 100);
            }
        }
    }
    
    return data;
}

bool* generate_training_labels(double** data, int size) {
    bool* labels = (bool*)malloc(size * sizeof(bool));
    
    if (labels == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size; i++) {
        if (data[i][0] < 300 && data[i][1] < 100) {
            labels[i] = true;
        }
        else {
            labels[i] = false;
        }
    }
    
    return labels;
}

void free_training_data(double** data, int size) {
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            free(data[i]);
        }
        free(data);
    }
}
