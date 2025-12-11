#pragma once

#include <stack> // Biblioteca para usar pilas (stacks)
#include <string>
#include <iostream>
#include <sstream>

// Forward declaration to avoid circular dependency
class Match;

// Both winRate and history will be calculated/created when the program runs, not stored in files.

struct MatchResult
{
	int matchId;
	bool won; // true if won, false if lost
	int eloChange; // positive for wins, negative for losses
	std::string opponentRank; // rank of the match
};

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

	// Match history
	std::stack<MatchResult> matchHistory; // Stack to store match history
	int totalMatches; // Total number of matches played
	int totalWins; // Total number of wins

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
	int getTotalMatches() const;
	int getTotalWins() const;
	
	// Match history methods
	void addMatchResult(int matchId, bool won, int eloChange, const std::string& matchRank);
	void calculateWinRate(); // Calculate win rate based on match history
	void displayMatchHistory() const; // Display recent match history
	const std::stack<MatchResult>& getMatchHistory() const;

	// Setters
	void setRank(const std::string& rank);
	void setElo(int elo);
	void setWinRate(double winRate);
	void setTotalMatches(int total);
	void setTotalWins(int wins);
	void setTimeQueued(double timeQueued);

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