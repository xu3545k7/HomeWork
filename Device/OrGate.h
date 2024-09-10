#include "Device.h"

class OrGate : public Device {
    std::vector<Device*> inputs;
    std::vector<Device*> outputs; 
    
public:
    OrGate(const std::vector<Device*>& in);  // ??©ú¡A¤£??
    virtual ~OrGate() override;

    bool getOutput()  override;
    void addInputPins(const std::vector<Device*>& devices);
    void addOutputPin(Device* device) override;
    void setInputs(const std::vector<Device*>& inputs);
};
