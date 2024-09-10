#include "AndGate.h"

// 構造函數，接受輸入設備的向量
AndGate::AndGate(const std::vector<Device*>& in) : inputs(in), outputs() {
    this->inputs = in;
    this->outputs = {};

    if (outputs.empty()) {
        outputs.push_back(nullptr); 
    }
}


AndGate::~AndGate() {}

// 評估該AND門的輸出值
bool AndGate::getOutput()  {
    bool result = true;
    for (auto& input : inputs) {
        result = result && input->getOutput() ;
    }
    return result;
}

// 添加輸入引腳
void AndGate::addInputPins(const std::vector<Device*>& devices) {
    for (Device* device : devices) {
        inputs.push_back(device);
    }
}

// 添加輸出引腳
void AndGate::addOutputPin(Device* output) {
    outputs.push_back(output);
}

// 設置輸入引腳
void AndGate::setInputs(const std::vector<Device*>& inputs) {
    this->inputs = inputs;
}
