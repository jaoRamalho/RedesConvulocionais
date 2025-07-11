#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Neuron.hpp"


class Network {

    class Layer {
    public:
        std::vector<Neuron> neurons;
        ActivationFunctions activationFunction;
    };

private:
    Layer outputLayer;
    std::vector<Layer> hiddenLayers;
    
    Layer createLayer (int numNeurons, ActivationFunctions activationFunction);

public:
    Network();
    ~Network();

    void feedForward(const std::vector<int16_t> inputs);
    void backpropagate(const std::vector<int16_t> expectedOutputs);
};



#endif // NETWORK_HPP