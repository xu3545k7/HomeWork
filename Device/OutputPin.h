#ifndef OUTPUTPIN_H
#define OUTPUTPIN_H

#include "Device.h"

class OutputPin : public Device {
    std::vector<Device*> connectedDevices;
public:
    OutputPin(const std::vector<Device*>& devices);
    OutputPin(); 
    ~OutputPin();
    bool getOutput() override;
    void addInputPins(const std::vector<Device*>& devices);
    void addOutputPin(Device* device) override;
};

#endif // OUTPUTPIN_H
