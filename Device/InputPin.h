#ifndef INPUTPIN_H
#define INPUTPIN_H

#include <stddef.h>
#include "Device.h"

class InputPin : public Device {
    size_t index;
    bool value;
public:
    InputPin(size_t idx);
    InputPin(size_t idx, bool initialValue);  // «Øºc¤l
    bool getOutput()  override;
    void setValue(bool val);
    void addInputPins(const std::vector<Device*>& devices)override;
    void addOutputPin(Device* device) override;
};

#endif 
