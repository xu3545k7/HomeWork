#include "NotGate.h"

NotGate::NotGate(Device* in) : input(in) {
    this->input = in;
    this->outputs = {};
}

bool NotGate::getOutput()  {
    return !input->getOutput() ;
}

void NotGate::addInputPins(const std::vector<Device*>& devices) {
    (void)devices;
}

void NotGate::addOutputPin(Device* output) {
    outputs.push_back(output);
}

void NotGate::setInputs(Device* input) {
    this->input = input;
}
