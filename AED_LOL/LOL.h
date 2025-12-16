#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <stack>

#include "Player.h"
#include "Queue.h"
#include "Match.h"

class LOL
{
private:
	std::vector<Player> players; // Vector to store all players
	std::vector<std::priority_queue<Player>> rankQueues; // Priority queues for each rank (10 ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger)
	char role1Priority;
	char role2Priority;
	std::vector<Queue> roleQueues; // Vector of Queue objects for each rank (10 ranks)
	std::vector<std::queue<Match>> matchQueues; // Queues for each rank to store the matches once they are fully created

	// Helper methods

	// Métodos auxiliares para createMatchForRank
	int getRankIndex(const std::string& rank); // Get index of rank in the ranks vector
	Match createSingleMatch(const std::string& rank, Queue& roleQueue); // Create a single match for a specific rank
	bool fillRoleInMatch(Match& match, char role, Queue& roleQueue, std::vector<int>& playersAddedToMatch); // Fill a specific role in the match
	Player* getValidPlayerForRole(char role, Queue& roleQueue, const std::vector<int>& playersAlreadyInMatch); // Get a valid player for a specific role, avoiding players already in the match
	Player* findOriginalPlayer(int playerId); // Find the original player object by ID
public:
	LOL();

	// Processing matches

	void processAllMatches(); // Calls the processMatchResults method on each match, also matches should save in the players history when implemented

	// Creating matches for each rank

	void createMatchForRank(const std::string& rank); // Create matches for a specific rank
	void createAllMatches(); // Create matches for all ranks

	// Add players to roleQueues based on their rank and roles, starting from Iron to Challenger

	void addPlayerToRoleQueue(const Player& player); // Add a single player to the appropriate role queue
	void addAllPlayersToRoleQueues(); // Add all players to their respective role queues

	// Update priorities of all players

	void updateAllPlayersPriorities(); // Update priorities for all players based on current role priorities

	// Enqueue players into their respective rank queues

	void enqueuePlayerToRankQueue(const Player& player); // Enqueue a single player to the appropriate rank queue
	void enqueueAllPlayersToRankQueues(); // Enqueue all players to their respective rank queues

	// Getters for role priorities

	char getRole1Priority() const;
	char getRole2Priority() const;

	// Get the 2 roles with less players

	std::pair<char, char> getTwoLeastPopularRoles() const; // Returns a pair of chars representing the two roles with the least number of players queued
	void assignRolePriorities(); // Assigns role1Priority and role2Priority based on the least popular roles

	// To filter and display top players (with algorithms)

	void displayTopPlayersByWinRateWithMinMatch(int minMatch, int top) const;
	void displayTopPlayersByELO(int top) const;
	void displayTopPlayersByRoleAndWinRate(char role, int minMatch, int top) const;
	void displayTopPlayersByRoleAndELO(char role, int top) const;
	
	// Display player match history
	void displayPlayerMatchHistory(int playerId) const; // Display match history for a specific player
	
	// Queue time management
	void assignRandomQueueTimes();
	
	// Simulation methods
	void simulateMatchmakingSeason(int iterations);
	void clearAllQueues(); // Clear all queues between iterations
	
	// File operations
	void loadPlayersFromFile(const std::string& filename);
	void savePlayersToFile(const std::string& filename) const;
};