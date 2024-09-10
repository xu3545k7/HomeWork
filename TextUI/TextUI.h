#ifndef TEXTUI_H
#define TEXTUI_H

#include "../LogicSimulator/LogicSimulator.h"

class TextUI {
    LogicSimulator simulator;
public:
    void displayMenu();
    void processCommand();
};

#endif // TEXTUI_H
