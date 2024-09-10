#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H

#include "../Device/Device.h"
#include "../Device/InputPin.h"
#include "../Device/OutputPin.h"
#include "../Device/AndGate.h"
#include "../Device/NotGate.h"
#include "../Device/OrGate.h"

#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>


class LogicSimulator {
    std::vector<Device*> circuit;
    std::vector<InputPin*> iPins;
    std::vector<OutputPin*> oPins;
    std::vector<std::tuple<int, std::vector<std::string>>> gatesInfo;
    std::unordered_set<int> usedOutputs;
public:
    ~LogicSimulator();
    bool load(const std::string& filePath);
    std::string getSimulationResult(const std::vector<bool>& inputValues);
    std::string getTruthTable();
    void addInputPin(Device* iPin);
    size_t getInputPinCount() const;
    void clearGates();
};

#endif // LOGICSIMULATOR_H
