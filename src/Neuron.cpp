#include "Neuron.hpp"


Neuron::Neuron(std::vector<int16_t> initialWeights, int16_t initialBias = 0, ActivationFunction func = SIGMOID)
: weights(initialWeights), bias(initialBias), activationFunction(func), output(0)
{


}


Neuron::~Neuron() {


}   

void Neuron::setWeights(const std::vector<int16_t>& newWeights) {
    weights = newWeights;
}

void Neuron::setBias(int16_t newBias) {
    bias = newBias;
}

void Neuron::setWeight(int index, int16_t weight) {
    if (index >= 0 && index < weights.size()) {
        weights[index] = weight;
    } else {
        std::cerr << "Index out of bounds" << std::endl;
    }
}

std::vector<int16_t> Neuron::getWeights() const {
    return weights;
}

int16_t Neuron::getWeight(int index) const {
    if (index >= 0 && index < weights.size()) {
        return weights[index];
    } else {
        std::cerr << "Index out of bounds" << std::endl;
        return 0; // or throw an exception
    }
}

int16_t Neuron::getBias() const {
    return bias;
}

int16_t Neuron::getOutput() const {
    return output;
}

int16_t Neuron::activate(const std::vector<int16_t>& inputs) const {
    if (inputs.size() != weights.size()) {
        std::cerr << "Input size does not match weights size" << std::endl;
        return 0; // or throw an exception
    }

    int16_t sum = bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * weights[i];
    }

    switch (activationFunction) {
        case SIGMOID:
            return sigmoid(sum);
        case TANH:
            return tanh(sum);
        case RELU:
            return relu(sum);
        case LEAKY_RELU:
            return leakyRelu(sum);
        default:
            std::cerr << "Unknown activation function" << std::endl;
            return 0; // or throw an exception
    }
}

int16_t Neuron::sigmoid(int16_t x) const {
    return static_cast<int16_t>((1 / (1 + std::exp(-x))) * 32767); // Scale to int16_t range
}

int16_t Neuron::tanh(int16_t x) const {
    return static_cast<int16_t>(std::tanh(x) * 32767); // Scale to int16_t range
}

int16_t Neuron::relu(int16_t x) const {
    return (x > 0) ? x : 0;
}

int16_t Neuron::leakyRelu(int16_t x) const {
    return (x > 0) ? x : static_cast<int16_t>(0.01 * x);
}



