#include "OrGate.h"

OrGate::OrGate(const std::vector<Device*>& in): inputs(in){}  // ??放在cpp文件中

OrGate::~OrGate() {}

bool OrGate::getOutput()  {
    bool result = false;
    for (auto& input : inputs) {
        result = result || input->getOutput() ;
    }
    return result;
}

void OrGate::addInputPins(const std::vector<Device*>& devices) {
    for (Device* device : devices) {
        inputs.push_back(device);
    }
}

void OrGate::addOutputPin(Device* device) {
    outputs.push_back(device);
}

void OrGate::setInputs(const std::vector<Device*>& inputs) {
    this->inputs = inputs;
}
