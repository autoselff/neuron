cmake_minimum_required(VERSION 3.10)
project(neuron C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} 
    src/main.c
    src/neuron/neuron.h
    src/neuron/neuron.c
    src/neuron/training.h
    src/neuron/training.c
)