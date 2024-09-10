#ifndef ANDGATE_H
#define ANDGATE_H

#include "Device.h"

class AndGate : public Device {
    std::vector<Device*> inputs;
    std::vector<Device*> outputs;  

public:
    AndGate(const std::vector<Device*>& in);
    virtual ~AndGate() override;
    
    bool getOutput()  override;
    void addInputPins(const std::vector<Device*>& devices);  
    void addOutputPin(Device* output) override; 
    void setInputs(const std::vector<Device*>& inputs);
    
};

#endif
