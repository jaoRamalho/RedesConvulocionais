#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <iostream>
#include "ModulesNames.h" 
#include "Macros.hpp"
#include "ActivationFunctions.hpp"

class Neuron {
private:
    std::vector<int16_t> weights;
    int16_t bias;
    NameActivationFunction activationFunction;
    int16_t output;

public:
    Neuron(NameActivationFunction);
    ~Neuron();
    
    void setWeights(const std::vector<int16_t>& newWeights);
    void setBias(int16_t newBias);
    void setWeight(int index, int16_t weight);

    std::vector<int16_t> getWeights() const;
    int16_t getWeight(int index) const;
    int16_t getBias() const;
    int16_t getOutput() const;

    int16_t activate(const std::vector<int16_t>& inputs);
    void updateWeights(const std::vector<int16_t>& gradients, float learningRate); 
};


#endif // NEURON_HPP