#pragma once

#include <stack> // Biblioteca para usar pilas (stacks)
#include <string>
#include <iostream>
#include <sstream>

// Both winRate and history will be calculated/created when the program runs, not stored in files.

class Player
{
private:
	int id;
	std::string username;
	double timeQueued; // Time spent in queue (in seconds)
	std::string rank;
	int elo;
	double winRate; // Percentage of games won (calculated from match history)
	char roles[2]; // Will store the player's preferred roles (2 roles, first for primary, second for secondary)
	int priority; // Priority in the queue (higher priority gets matched first)

	// Variables for rank and ELO management
	std::string ranks[10] = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	int rankRanges[10] = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900 }; // ELO ranges for each rank

	// TODO: Add history of matches played when implementing game class
public:
	// Default constructor
	Player();
	// Parameterized constructor for creating a player with specific attributes and for reading from file
	Player(int id, const std::string& username, double timeQueued, int elo, char primaryRole, char secondaryRole);

	// Getters
	int getId() const;
	std::string getUsername() const;
	std::string getRank() const;
	int getElo() const;
	char getPrimaryRole() const;
	char getSecondaryRole() const;
	double getWinRate() const;
	double getTimeQueued() const;
	int getPriority() const;
	// TODO: Add getters for match history when implementing game class

	// Setters

	void setRank(const std::string& rank);
	void setElo(int elo);
	void setWinRate(double winRate);

	// Other methods

	void displayInfo() const; // Method to display player information
	void updateRank(); // Method to update rank based on ELO
	void calculatePriority(char rol1, char rol2); // Method to calculate priority based on time and roles

	// Operator overloads

	// for reading/writing player data to/from files
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	friend std::istream& operator>>(std::istream& is, Player& player);

	// For comparing players based on priority
	friend bool operator<(const Player& p1, const Player& p2);
};