#pragma once

#include <iostream>
#include <string>
#include "LOL.h"

class Menu
{
private:
    LOL lolSystem;
    
    // Helper methods for user input
    int getIntegerInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    char getCharInput(const std::string& prompt);
    void waitForEnter();
    void clearScreen();
    
public:
    Menu();
    
    // Main menu methods
    void run();
    void displayMainMenu();
    
    // Menu option handlers
    void handleSimulation();
    void handlePlayerHistory();
    void handleTopPlayersByELO();
    void handleTopPlayersByWinRate();
    void handleTopPlayersByRoleAndELO();
    void handleTopPlayersByRoleAndWinRate();
    void handleTopPlayersByRankAndWinRate();
    void handleTopPlayersByRankAndELO();
    void handleTopPlayersByRankRoleAndWinRate();
    void handleTopPlayersByRankRoleAndELO();
    void handleListAllPlayers();
    void handleListAllPlayersByRank();
    void handleListAllPlayersByRole();
};