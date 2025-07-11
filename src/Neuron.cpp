#include "Neuron.hpp"
#include "Log.hpp"

Neuron::Neuron(NameActivationFunction func = SIGMOID) : 
activationFunction(func), output(0) {
    
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
        logPrintf(Error, MODULE_NEURON, "Index out of bounds in setWeight: %d", index);
    }
}

std::vector<int16_t> Neuron::getWeights() const {
    return weights;
}

int16_t Neuron::getWeight(int index) const {
    if (index >= 0 && index < weights.size()) {
        return weights[index];
    } else {
        logPrintf(Error, MODULE_NEURON, "Index out of bounds in getWeight: %d", index);
        return 0; // or throw an exception
    }
}

int16_t Neuron::getBias() const {
    return bias;
}

int16_t Neuron::getOutput() const {
    return output;
}

int16_t Neuron::activate(const std::vector<int16_t>& inputs) {
    if (inputs.size() != weights.size()) {
        logPrintf(Error, MODULE_NEURON, "Input size does not match weights size: %zu vs %zu", inputs.size(), weights.size());
        return 0; // or throw an exception
    }

    int64_t sum = bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * weights[i];
    }

    // Apply the activation function
    output = ActivationFunctions::activationFunction(sum, activationFunction);
}

void Neuron::updateWeights(const std::vector<int16_t>& gradients, float learningRate) {
    if (gradients.size() != weights.size()) {
        logPrintf(Error, MODULE_NEURON, "Gradients size does not match weights size: %zu vs %zu", gradients.size(), weights.size());
        return; // or throw an exception
    }

    for (size_t i = 0; i < weights.size(); ++i) {
        weights[i] -= static_cast<int16_t>(learningRate * gradients[i]);
    }
}



