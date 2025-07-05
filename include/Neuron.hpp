#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdint>


enum ActivationFunction {
    SIGMOID,
    TANH,
    RELU,
    LEAKY_RELU
};

class Neuron {
private:
    std::vector<int16_t> weights;
    int16_t bias;
    ActivationFunction activationFunction;
    int16_t output;

public:
    Neuron(std::vector<int16_t> initialWeights, int16_t initialBias, ActivationFunction func);
    ~Neuron();
    
    void setWeights(const std::vector<int16_t>& newWeights);
    void setBias(int16_t newBias);
    void setWeight(int index, int16_t weight);

    std::vector<int16_t> getWeights() const;
    int16_t getWeight(int index) const;
    int16_t getBias() const;
    int16_t getOutput() const;

    int16_t activate(const std::vector<int16_t>& inputs) const;
    
    int16_t sigmoid(int16_t x) const;
    int16_t tanh(int16_t x) const;
    int16_t relu(int16_t x) const;
    int16_t leakyRelu(int16_t x) const;
};


#endif // NEURON_HPP