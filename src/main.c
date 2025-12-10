#include "neuron/neuron.h"

#define TRAINING_SIZE 8

const double training_data[TRAINING_SIZE][2] = {
    {23, 4},
    {18, 3},
    {8, 2},
    {200, 30},
    {8, 150},
    {30, 350},
    {34634, 465},
    {345, 34634}
};

const bool labels[TRAINING_SIZE] = {true, true, true, true, false, false, false, false};

int main(void) {
    srand(time(NULL));
    system("clear");

    int epochs;
    printf("Hello, I am Neuron. Today, I will decide whether the values belong to the ring or to the pen.\n");
    printf("How many training sessions should I conduct?\n> ");
    
    while (scanf("%d", &epochs) != 1 || epochs <= 0 || getchar() != '\n') {
    	printf("Wrong. Please try again:\t");
    	while (getchar() != '\n');
    }

    Neuron neuron = init_neuron(2, 0.02);

    printf("Start weights: w1=%.4f, w2=%.4f, bias=%.4f\n\n", neuron.weights[0], neuron.weights[1], neuron.bias);
    printf("The training is starting.\n");
    
    for (int epoch = 0; epoch < epochs; epoch++) {
        int correct_predictions = 0;

        for (int i = 0; i < TRAINING_SIZE; i++) {
            double result = activate(&neuron, training_data[i]);
            bool predicted = (result > 0.0);

            if (predicted == labels[i]) {
                correct_predictions++;
            } else {
                train_step(&neuron, training_data[i], labels[i]);
            }
        }
        if (correct_predictions == TRAINING_SIZE) {
            printf("\033[32m %d - Training...\033[0m \n", epoch);
        }
        else {
            printf("\033[31m %d - Training...\033[0m \n", epoch);
        }
    }

    printf("\nFinal weights: w1=%.4f, w2=%.4f, bias=%.4f\n\n", neuron.weights[0], neuron.weights[1], neuron.bias);

    for (int i = 0; i < TRAINING_SIZE; i++) {
        double result = activate(&neuron, training_data[i]);
        bool predicted = (result > 0.0);

        printf("Data [%.0f, %.0f] | Prediction: %s | Expected: %s | Result: %.4f %s |\n",
               training_data[i][0], training_data[i][1],
               predicted ? "ring" : "pen",
               labels[i] ? "ring" : "pen",
               result,
               predicted == labels[i] ? "\033[32mCORRECT\033[0m" : "\033[31mWRONG\033[0m");
    }

    free_neuron(&neuron);
    return 0;
}
