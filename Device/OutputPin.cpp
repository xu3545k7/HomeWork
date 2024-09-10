#include "OutputPin.h"
#include <iostream>

OutputPin::OutputPin(const std::vector<Device*>& devices) : connectedDevices(devices) {}

OutputPin::OutputPin() : connectedDevices() {}  

OutputPin::~OutputPin() {}

bool OutputPin::getOutput()  {
    if (!connectedDevices.empty()) {
        return connectedDevices[0]->getOutput(); // Return the first connected device's evaluation
    } else {
        std::cerr << "Debug: OutputPin has no connected device." << std::endl;
        return false;
    }
}

void OutputPin::addInputPins(const std::vector<Device*>& devices) {
    (void)devices;
}

void OutputPin::addOutputPin(Device* device) {
    connectedDevices.push_back(device);
}

