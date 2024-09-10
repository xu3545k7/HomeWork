#include "TextUI.h"
#include <iostream>


void TextUI::displayMenu() {
    std::cout << "1. Load logic circuit file" << std::endl;
    std::cout << "2. Simulation" << std::endl;
    std::cout << "3. Display truth table" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void TextUI::processCommand() {
    int command;
    while (true) {
        displayMenu();
        std::cout << "Command: ";
        std::cin >> command;

        if (command == 1) {
            std::string filePath;
            std::cout << "Please key in a file path: ";
            std::cin >> filePath;

            simulator.clearGates();// 清除資料
            
            if (!simulator.load(filePath)) {
                std::cout << "File not found or format error. Please try again." << std::endl;
            } else {
                std::cout << "File loaded successfully.\n";
            }
        } else if (command == 2) {
            std::vector<bool> inputValues(simulator.getInputPinCount());
            for (size_t i = 0; i < inputValues.size(); ++i) {
                int val = 0;
                std::cout << "Please key in value for Input Pin " << i + 1 << " : ";
                std::cin >> val;
                while(val != 0 && val != 1){
                    std::cout << "The value of input pin must be 0/1 ";
                    std::cout << "Please key in value for Input Pin " << i + 1 << " : ";
                    std::cin >> val;
                }
                inputValues[i] = (val != 0);// 轉bool
            }
            std::cout << "Simulation result: " << std::endl;
            std::cout << "i i i | o: " << std::endl;
            std::cout << "1 2 3 | 1: " << std::endl;
            std::cout << "------+--  " << std::endl;
            std::cout << simulator.getSimulationResult(inputValues) << std::endl;
        } else if (command == 3) {
            std::cout << "Circuit Truth table: " << std::endl;
            std::cout << "i i i | o: " << std::endl;
            std::cout << "1 2 3 | 1: " << std::endl;
            std::cout << "------+--  " << std::endl;
            std::cout << simulator.getTruthTable();
        }  else if (command == 4) {
            std::cout << "Goodbye, thanks for using LS. " << std::endl;
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
}

