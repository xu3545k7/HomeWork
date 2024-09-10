#ifndef DEVICE_H
#define DEVICE_H

#include <vector>

class Device {
public:
    virtual bool getOutput() = 0;  // 純虛擬函式
    virtual void addInputPins(const std::vector<Device*>& devices) = 0;  // 新增純虛擬函式
    virtual void addOutputPin(Device* output) = 0; // 新增純虛擬函式
    virtual ~Device() = default;
};

#endif
