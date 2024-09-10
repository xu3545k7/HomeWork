
#include "LogicSimulator.h"


#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>

LogicSimulator::~LogicSimulator() {
    for (auto device : circuit) {
        delete device;
    }
    for (auto oPin : oPins) {
        delete oPin;
    }
}
bool LogicSimulator::load(const std::string& filePath) {
    

    
    std::ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    size_t numInputPins, numGates;
    if (!(file >> numInputPins >> numGates)) {
        return false;
    }

    iPins.resize(numInputPins);
    for (size_t i = 0; i < numInputPins; ++i) {
        iPins[i] = new InputPin(i);
    }

    // �M��Ū����ѤU������Ÿ�
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    for (size_t i = 0; i < numGates; ++i) {
        std::getline(file, line);
        
        // �M�z����M�B�~�Ů�Ÿ�
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        std::stringstream ss(line);
        int gateType;
        ss >> gateType;

        std::vector<std::string> inputs;
        std::string inputId;
        while (ss >> inputId && inputId != "0") {
            inputs.push_back(inputId);
        }

        gatesInfo.push_back({gateType, inputs});
        Device* gate = nullptr;

        switch (gateType) {
            case 1:
                gate = new AndGate({});
                break;
            case 2:
                gate = new OrGate({});
                break;
            case 3:
                gate = new NotGate(nullptr);
                break;
            default:
                return false;
        }

        circuit.push_back(gate);
    }

    for (size_t i = 0; i < gatesInfo.size(); ++i) {
        const std::vector<std::string>& inputs = std::get<1>(gatesInfo[i]);
        std::vector<Device*> resolvedInputs;

        //std::cerr << "Debug: Gate " << i + 1 << " receives inputs from: ";

        for (const auto& inputStr : inputs) {
            if (inputStr.find('.') != std::string::npos) {
                size_t dotPos = inputStr.find('.');
                std::string gatePart = inputStr.substr(0, dotPos);
                int gateId = std::stoi(gatePart);
                if (gateId < 1 || gateId > static_cast<int>(circuit.size())) {
                    //std::cerr << "Debug: Invalid gate ID in input: " << gateId << std::endl;
                    return false;
                }
                resolvedInputs.push_back(circuit[gateId - 1]);
                usedOutputs.insert(gateId - 1);  // �аO��gate����X�w�Q�ϥ�
                //std::cerr << "Gate " << gateId;
            } else {
                int inputId = std::stoi(inputStr);
                if (inputId < 0) {
                    // �s�����J�w�}
                    if (static_cast<size_t>(-inputId - 1) >= iPins.size()) {
                        //std::cerr << "Debug: Invalid input pin ID: " << inputId << std::endl;
                        return false;
                    }
                    resolvedInputs.push_back(iPins[-inputId - 1]);
                    //std::cerr << "InputPin " << -inputId;
                } else {
                    // �s�����L�h��
                    if (inputId < 1 || inputId > static_cast<int>(circuit.size())) {
                        //std::cerr << "Debug: Invalid gate ID in input: " << inputId << std::endl;
                        return false;
                    }

                    // �ˬd�O�_�s����ۤv
                    if (inputId - 1 == int(i)) {
                        std::cout << "Error: Logic gate cannot connect to itself." << std::endl;
                        
                        return false;  // ��^ false �H���� load
                    }

                    resolvedInputs.push_back(circuit[inputId - 1]);
                    usedOutputs.insert(inputId - 1);  // �аO�ӹh������X�w�Q�ϥ�
                    //std::cerr << "Gate " << inputId;
                }
            }
            //std::cerr << ", ";
        }

        //std::cerr << std::endl;

        switch (std::get<0>(gatesInfo[i])) {
            case 1:
                dynamic_cast<AndGate*>(circuit[i])->setInputs(resolvedInputs);
                //std::cerr << "Debug: AND gate " << i + 1 << " linked with " << resolvedInputs.size() << " inputs." << std::endl;
                break;
            case 2:
                dynamic_cast<OrGate*>(circuit[i])->setInputs(resolvedInputs);
                //std::cerr << "Debug: OR gate " << i + 1 << " linked with " << resolvedInputs.size() << " inputs." << std::endl;
                break;
            case 3:
                if (resolvedInputs.empty()) {
                    //std::cerr << "Debug: NOT gate " << i + 1 << " has no inputs." << std::endl;
                    return false;
                }
                dynamic_cast<NotGate*>(circuit[i])->setInputs(resolvedInputs[0]);
                //std::cerr << "Debug: NOT gate " << i + 1 << " linked with 1 input." << std::endl;
                break;
            default:
                //std::cerr << "Debug: Invalid gate type encountered during linking." << std::endl;
                break;
        }
    }
    
    // �ѧO�̲׿�X�h���G���ǿ�X���Q��L�h���ϥΪ��h��
    for (size_t i = 0; i < circuit.size(); ++i) {
        if (!usedOutputs.count(i)) {
            OutputPin* oPin = new OutputPin({circuit[i]});
            oPins.push_back(oPin);
            //std::cerr << "Debug: Gate " << i + 1 << " is an output gate and added to oPins." << std::endl;
        }
    }
    std::cerr << "Circuit: " << numInputPins << " input pins, " << oPins.size() << " output pins and " << numGates << " gates" << std::endl;
    return true;
}

std::string LogicSimulator::getSimulationResult(const std::vector<bool>& inputValues) {
    if (inputValues.size() != iPins.size()) {
        return "Error: Number of input values does not match number of input pins.";
    }
    std::stringstream result;
    for (size_t i = 0; i < iPins.size(); ++i) {
        iPins[i]->setValue(inputValues[i]);
        result << inputValues[i] << " ";
    }

    
    for (auto& oPin : oPins) {
        result << "| " << oPin->getOutput() << " ";
    }
    return result.str();
}

std::string LogicSimulator::getTruthTable() {
    std::stringstream result;
    size_t numInputs = iPins.size();
    size_t numRows = 1 << numInputs;

    for (size_t i = 0; i < numRows; ++i) {
        std::vector<bool> inputs(numInputs);
        for (size_t j = 0; j < numInputs; ++j) {
            inputs[j] = (i >> (numInputs - j - 1)) & 1;
        }

        
        result << getSimulationResult(inputs) << std::endl;
    }

    return result.str();
}

void LogicSimulator::addInputPin(Device* iPin) {
    iPins.push_back(static_cast<InputPin*>(iPin));
}

size_t LogicSimulator::getInputPinCount() const {
    return iPins.size();
}

void LogicSimulator::clearGates(){
    // �M�����e���q���M�޸}���
    for (auto device : circuit) {
        delete device;
    }
    circuit.clear();
    gatesInfo.clear();
    usedOutputs.clear();

    for (auto inputPin : iPins) {
        delete inputPin;
    }
    iPins.clear();

    for (auto outputPin : oPins) {
        delete outputPin;
    }
    oPins.clear();

    std::cerr << "All gates, input pins, and output pins have been cleared." << std::endl;
    std::cerr << "Current circuit size: " << circuit.size() << std::endl;
    std::cerr << "Current input pins size: " << iPins.size() << std::endl;
    std::cerr << "Current output pins size: " << oPins.size() << std::endl;
}
