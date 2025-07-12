#ifndef ACTIVATE_FUNCTIONS_HPP
#define ACTIVATE_FUNCTIONS_HPP

#include "Macros.hpp"

enum NameActivationFunction : uint8_t {
    SIGMOID = 0,
    TANH = 1,
    RELU = 2, 
    SOFTMAX = 3
};

class ActivationFunctions {
public:
    static int16_t sigmoid(int32_t x);
    static int16_t tanh(int32_t x);
    static int16_t relu(int32_t x);
    static int16_t softmax(int32_t x);
   
    static int16_t activationFunction(int32_t x, NameActivationFunction activationFunction);
};


#endif // ACTIVATE_FUNCTIONS_HPP