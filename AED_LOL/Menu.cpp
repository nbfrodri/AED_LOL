#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu()
{
    // Load players when the menu is created
    std::cout << "Loading players from file...\n";
    lolSystem.loadPlayersFromFile("players.csv");
    std::cout << "Players loaded successfully!\n\n";
}

void Menu::run()
{
    int choice;
    
    do
    {
        displayMainMenu();
        choice = getIntegerInput("Enter your choice: ");
        
        switch (choice)
        {
        case 1:
            handleSimulation();
            break;
        case 2:
            handlePlayerHistory();
            break;
        case 3:
            handleTopPlayersByELO();
            break;
        case 4:
            handleTopPlayersByWinRate();
            break;
        case 5:
            handleTopPlayersByRoleAndELO();
            break;
        case 6:
            handleTopPlayersByRoleAndWinRate();
            break;
        case 7:
            handleTopPlayersByRankAndWinRate();
            break;
        case 8:
            handleTopPlayersByRankAndELO();
            break;
        case 9:
            handleTopPlayersByRankRoleAndWinRate();
            break;
        case 10:
            handleTopPlayersByRankRoleAndELO();
            break;
        case 11:
            handleListAllPlayers();
            break;
        case 12:
            handleListAllPlayersByRank();
            break;
        case 13:
            handleListAllPlayersByRole();
            break;
        case 14:
            std::cout << "Saving players to file...\n";
            lolSystem.savePlayersToFile("players.csv");
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            waitForEnter();
            break;
        }
        
    } while (choice != 14);
}

void Menu::displayMainMenu()
{
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "       LEAGUE OF LEGENDS SYSTEM       \n";
    std::cout << "========================================\n";
    std::cout << "1. Simulate Matchmaking Season\n";
    std::cout << "2. Show Player Match History\n";
    std::cout << "3. Show Top Players by ELO\n";
    std::cout << "4. Show Top Players by Win Rate\n";
    std::cout << "5. Show Top Players by Role and ELO\n";
    std::cout << "6. Show Top Players by Role and Win Rate\n";
    std::cout << "7. Show Top Players by Rank and Win Rate\n";
    std::cout << "8. Show Top Players by Rank and ELO\n";
    std::cout << "9. Show Top Players by Rank, Role and Win Rate\n";
    std::cout << "10. Show Top Players by Rank, Role and ELO\n";
    std::cout << "11. List All Players\n";
    std::cout << "12. List All Players by Rank\n";
    std::cout << "13. List All Players by Role\n";
    std::cout << "14. Exit\n";
    std::cout << "========================================\n";
}

void Menu::handleSimulation()
{
    clearScreen();
    std::cout << "=== SIMULATION ===\n";
    
    int iterations = getIntegerInput("Enter number of simulation iterations: ");
    
    std::cout << "\nRunning simulation with " << iterations << " iterations...\n";
    lolSystem.simulateMatchmakingSeason(iterations);
    
    std::cout << "\nSimulation completed! Saving data to file...\n";
    lolSystem.savePlayersToFile("players.csv");
    std::cout << "Data saved successfully!\n";
    
    waitForEnter();
}

void Menu::handlePlayerHistory()
{
    clearScreen();
    std::cout << "=== PLAYER MATCH HISTORY ===\n";
    
    int playerId = getIntegerInput("Enter player ID: ");
    
    std::cout << "\n";
    lolSystem.displayPlayerMatchHistory(playerId);
    
    waitForEnter();
}

void Menu::handleTopPlayersByELO()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY ELO ===\n";
    
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByELO(topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByWinRate()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY WIN RATE ===\n";
    
    int minMatches = getIntegerInput("Enter minimum number of matches: ");
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByWinRateWithMinMatch(minMatches, topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByRoleAndELO()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY ROLE AND ELO ===\n";
    
    std::cout << "Available roles: T (Top), J (Jungle), M (Mid), A (ADC), S (Support)\n";
    char role = getCharInput("Enter role: ");
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByRoleAndELO(role, topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByRoleAndWinRate()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY ROLE AND WIN RATE ===\n";
    
    std::cout << "Available roles: T (Top), J (Jungle), M (Mid), A (ADC), S (Support)\n";
    char role = getCharInput("Enter role: ");
    int minMatches = getIntegerInput("Enter minimum number of matches: ");
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByRoleAndWinRate(role, minMatches, topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByRankAndWinRate()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY RANK AND WIN RATE ===\n";
    
    std::cout << "Available ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger\n";
    std::string rank = getStringInput("Enter rank: ");
    int minMatches = getIntegerInput("Enter minimum number of matches: ");
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByRankAndWinRate(rank, minMatches, topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByRankAndELO()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY RANK AND ELO ===\n";
    
    std::cout << "Available ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger\n";
    std::string rank = getStringInput("Enter rank: ");
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByRankAndELO(rank, topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByRankRoleAndWinRate()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY RANK, ROLE AND WIN RATE ===\n";
    
    std::cout << "Available ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger\n";
    std::string rank = getStringInput("Enter rank: ");
    
    std::cout << "Available roles: T (Top), J (Jungle), M (Mid), A (ADC), S (Support)\n";
    char role = getCharInput("Enter role: ");
    
    int minMatches = getIntegerInput("Enter minimum number of matches: ");
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByRankRoleAndWinRate(rank, role, minMatches, topCount);
    
    waitForEnter();
}

void Menu::handleTopPlayersByRankRoleAndELO()
{
    clearScreen();
    std::cout << "=== TOP PLAYERS BY RANK, ROLE AND ELO ===\n";
    
    std::cout << "Available ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger\n";
    std::string rank = getStringInput("Enter rank: ");
    
    std::cout << "Available roles: T (Top), J (Jungle), M (Mid), A (ADC), S (Support)\n";
    char role = getCharInput("Enter role: ");
    
    int topCount = getIntegerInput("Enter number of top players to display: ");
    
    std::cout << "\n";
    lolSystem.displayTopPlayersByRankRoleAndELO(rank, role, topCount);
    
    waitForEnter();
}

void Menu::handleListAllPlayers()
{
    clearScreen();
    std::cout << "=== ALL PLAYERS ===\n";
    
    std::cout << "\n";
    lolSystem.displayAllPlayers();
    
    waitForEnter();
}

void Menu::handleListAllPlayersByRank()
{
    clearScreen();
    std::cout << "=== ALL PLAYERS BY RANK ===\n";
    
    std::cout << "Available ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger\n";
    std::string rank = getStringInput("Enter rank: ");
    
    std::cout << "\n";
    lolSystem.displayAllPlayersByRank(rank);
    
    waitForEnter();
}

void Menu::handleListAllPlayersByRole()
{
    clearScreen();
    std::cout << "=== ALL PLAYERS BY ROLE ===\n";
    
    std::cout << "Available roles: T (Top), J (Jungle), M (Mid), A (ADC), S (Support)\n";
    char role = getCharInput("Enter role: ");
    
    std::cout << "Do you want to filter by:\n";
    std::cout << "1. Primary role\n";
    std::cout << "2. Secondary role\n";
    int choice = getIntegerInput("Enter your choice (1 or 2): ");
    
    bool isPrimary = (choice == 1);
    
    std::cout << "\n";
    lolSystem.displayAllPlayersByRole(role, isPrimary);
    
    waitForEnter();
}

// Helper methods for user input

int Menu::getIntegerInput(const std::string& prompt)
{
    int value;
    std::cout << prompt;

    if (std::cin >> value)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
    else
    {
        std::cout << "Invalid input. Please enter a valid number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return getIntegerInput(prompt); // Llamada recursiva para reintentar
    }
}

std::string Menu::getStringInput(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

char Menu::getCharInput(const std::string& prompt)
{
    char input;
    std::cout << prompt;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

void Menu::waitForEnter()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::clearScreen()
{
    // Clear screen for Windows
    system("cls");
}