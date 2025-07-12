#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Neuron.hpp"


class Network {

    class Layer {
    public:
        NameActivationFunction activationFunction;
        std::vector<Neuron> neurons;
        
        Layer(NameActivationFunction af) : activationFunction(af) { }
        void addNeuron(const Neuron& neuron) {  neurons.push_back(neuron); }
        Neuron& getNeuron(int index) { return neurons.at(index); }
        const std::vector<Neuron>& getNeurons() const { return neurons; }
        uint16_t size() const { return static_cast<int>(neurons.size()); }
    };

private:
    std::vector<Layer> hiddenLayers;
    
    Layer createLayer (int numNeurons, NameActivationFunction activationFunction);

public:
    Network();
    ~Network();


    int16_t crossEntropy(std::vector<int16_t> expectedOutputs, std::vector<int16_t> actualOutputs);
    int16_t errorCalculation(int16_t expectedOutput, int16_t actualOutput);
    void feedForward(const std::vector<int16_t> inputs);
    void backpropagate(const std::vector<int16_t> expectedOutputs);
    void addLayer(int numNeurons, NameActivationFunction activationFunction);
};



#endif // NETWORK_HPP