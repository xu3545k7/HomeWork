#include "InputPin.h"

InputPin::InputPin(size_t idx) : index(idx), value(false) {
    this->index = idx;
    this->value = false;
}

InputPin::InputPin(size_t idx, bool initialValue) : index(idx), value(initialValue) {}  

bool InputPin::getOutput()  {
    return value;
}

void InputPin::setValue(bool val) {
    value = val;
}
void InputPin::addInputPins(const std::vector<Device*>& devices){
    (void)devices;
}

void InputPin::addOutputPin(Device* device){
    (void)device;
}
