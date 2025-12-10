#include "neuron/neuron.h"
#include "neuron/training.h"

void fake_loading(char* last_message);

int main(void) {
    srand(time(NULL));
    system("clear");

    int epochs, training_data_size;
    printf("\033[35mHello\033[0m, I am Neuron. Today, I will decide whether the values belong to the ring or to the pen.\n");
    printf("How many training sessions should I conduct?\n> ");
    
    while (scanf("%d", &epochs) != 1 || epochs < 0 || getchar() != '\n') {
    	printf("Incorrect data. Please try again:\t");
    	while (getchar() != '\n');
    }
    if (epochs == 0) {
        printf("\nExiting program.\n");
        return 0;
    }

    printf("How many training pairs should I create?\n> ");
    
    while (scanf("%d", &training_data_size) != 1 || training_data_size < 0 || getchar() != '\n') {
    	printf("Incorrect data. Please try again:\t");
    	while (getchar() != '\n');
    }
    if (training_data_size == 0) {
        printf("\nExiting program.\n");
        return 0;
    }

    double **training_data = generate_training_data(training_data_size);
    bool *labels = generate_training_labels(training_data, training_data_size);

    Neuron neuron = init_neuron(2, 0.02);

    printf("Start weights: w1=%.4f, w2=%.4f, bias=%.4f\n\n", neuron.weights[0], neuron.weights[1], neuron.bias);
    printf("The training is starting.\n");
    
    int correct_predictions_counter = 0;
    
    for (int epoch = 0; epoch < epochs; epoch++) {
        int correct_predictions = 0;

        for (int i = 0; i < training_data_size; i++) {
            double result = activate(&neuron, training_data[i]);
            bool predicted = (result > 0.0);

            if (predicted == labels[i]) {
                correct_predictions++;
            } else {
                train_step(&neuron, training_data[i], labels[i]);
            }
        }
        if (correct_predictions == training_data_size) {
            printf("\033[32m %d - Training...\033[0m \n", epoch);
            correct_predictions_counter++;
            if (correct_predictions_counter >= 2) {
                printf("\033[32m %d - Training completed successfully\033[0m \n", epoch);
                break;
            }
        }
        else {
            printf("\033[31m %d - Training...\033[0m \n", epoch);
            correct_predictions_counter = 0;
        }
    }

    printf("\nFinal weights: w1=%.4f, w2=%.4f, bias=%.4f\n\n", neuron.weights[0], neuron.weights[1], neuron.bias);

    for (int i = 0; i < training_data_size; i++) {
        double result = activate(&neuron, training_data[i]);
        bool predicted = (result > 0.0);

        char result_string[256];
        sprintf(result_string, 
            "Data [%.0f, %.0f] | Prediction: %s | Expected: %s | Result: %.4f %s |\n",
            training_data[i][0], 
            training_data[i][1], 
            predicted ? "ring" : "pen", 
            labels[i] ? "ring" : "pen", 
            result, 
            predicted == labels[i] ? "\033[32mCORRECT\033[0m" : "\033[31mWRONG\033[0m");
        printf("%s", result_string);
    }

    int user_input_radius = 1, user_input_width = 1;
    char last_message[256];

    while(user_input_radius != 0 || user_input_width != 0) {
        printf("\n\nPlease enter the following two values: the radius and width of the object,\n");
        printf("and I will decide whether the object is a ring or a pen. (Enter 0 0 to exit)\n");
        
        printf("> radius: ");
        while (scanf("%d", &user_input_radius) != 1 || user_input_radius < 0 || getchar() != '\n') {
            printf("Incorrect data. Please try again:\t");
            while (getchar() != '\n');
        }

        printf("> width: ");
        while (scanf("%d", &user_input_width) != 1 || user_input_width < 0 || getchar() != '\n') {
            printf("Incorrect data. Please try again:\t");
            while (getchar() != '\n');
        }

        if (user_input_radius == 0 && user_input_width == 0) {
            printf("\nExiting program.\n");
            break;
        }

        double user_training_data[2] = {(double)user_input_radius, (double)user_input_width};

        double result = activate(&neuron, user_training_data);
        bool predicted = (result > 0.0);
        
        sprintf(last_message, 
            "Data [%d, %d] | My answer is %s.\n",
            user_input_radius, 
            user_input_width, 
            predicted ? "\033[35mRING\033[0m" : "\033[35mPEN\033[0m");

        fake_loading(last_message);
    }

    free_neuron(&neuron);
    free_training_data(training_data, training_data_size);
    return 0;
}

void fake_loading(char* last_message) {
    char loading_message[] = "[=---------------------------]";
    int len = strlen(loading_message);
    
    printf("%s\n", last_message);
    
    for(int i = 1; i < len - 1; i++) {
        if (loading_message[i - 1] == '=') {
            loading_message[i] = '=';
        }
        
        printf("\r%s", loading_message);
        fflush(stdout);
        usleep(50000);
    }
    printf("\n");
}