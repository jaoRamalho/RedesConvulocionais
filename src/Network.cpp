#include "Network.hpp"


Network::Network() {


}


Network::~Network() {


}

Network::Layer Network::createLayer(int numNeurons, NameActivationFunction activationFunction) {
    Layer newLayer(activationFunction);
    for (int i = 0; i < numNeurons; ++i) {
        Neuron neuron(activationFunction);
        newLayer.addNeuron(neuron);
    }
    return newLayer;
}

void Network::feedForward(const std::vector<int16_t> inputs) {
}

void Network::backpropagate(const std::vector<int16_t> expectedOutputs) {

}

void Network::addLayer(int numNeurons, NameActivationFunction activationFunction){
    Layer newLayer = createLayer(numNeurons, activationFunction);
    hiddenLayers.push_back(newLayer);   
}
