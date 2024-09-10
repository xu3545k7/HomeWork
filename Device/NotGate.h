#ifndef NOTGATE_H
#define NOTGATE_H

#include "Device.h"

class NotGate : public Device {
    Device* input;
    std::vector<Device*> outputs;  
public:
    NotGate(Device* in);
    bool getOutput() override;
    void addInputPins(const std::vector<Device*>& devices) override;
    void addOutputPin(Device* device) override;
    void setInputs( Device* input);
};



#endif // NOTGATE_H
