#include "ActivationFunctions.hpp"
#include "Log.hpp"
#include <math.h>

int16_t ActivationFunctions::sigmoid(int32_t x) {
    return static_cast<int16_t>((1 / (1 + expf(-x))) * MAX_INT16); // Scale to int16_t range
}

int16_t ActivationFunctions::tanh(int32_t x) {
    return static_cast<int16_t>(tanhf(x) * MAX_INT16); // Scale to int16_t range
}

int16_t ActivationFunctions::relu(int32_t x) {
    return (x > 0) ? static_cast<int16_t>(x >> 16)  : 0; // Scale to int16_t range, assuming x is in the range of int32_t
}

int16_t ActivationFunctions::softmax(int32_t x) {
    return 0;
}

int16_t ActivationFunctions::activationFunction(int32_t x, NameActivationFunction activationFunction) {
    switch (activationFunction) {
        case SIGMOID:
            return sigmoid(x); 
        case TANH:
            return tanh(x);
        case RELU:
            return relu(x);
        case SOFTMAX:
            return softmax(x);
        default:
            logPrintf(Error, MODULE_NEURON, "Unknown activation function: %d", activationFunction);
            return 0; // or throw an exception
    }
}