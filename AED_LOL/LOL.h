#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

#include "Player.h"

// Matches will also be stored in a vector of stacks, one for each rank (only one stack per rank), the number of matches in each stack is dynamic
// When a new match is created and filled, the players will be popped from the rank queues (priority queues) according to their rank
// and added to the match. Once the match is completed, it will be pushed onto the corresponding rank stack.
// We will start by creating the matches for the highest rank (Challenger) and go downwards to Iron.
// Once all the matches are created and all the players are popped from the rank queues, the results will be processed, updating the players' ELO and win rates accordingly.

class LOL
{
private:
	std::vector<Player> players; // Vector to store all players
	std::vector<std::priority_queue<Player>> rankQueues; // Priority queues for each rank (10 ranks: Iron, Bronze, Silver, Gold, Platinum, Emerald, Diamond, Master, Grandmaster, Challenger)
	char role1Priority;
	char role2Priority;
public:
	LOL();

	// Update priorities of all players

	void updateAllPlayersPriorities();

	// Enqueue players into their respective rank queues

	void enqueuePlayerToRankQueue(const Player&	player);
	void enqueueAllPlayersToRankQueues();

	// Getters for role priorities

	char getRole1Priority() const;
	char getRole2Priority() const;

	// Get the 2 roles with less players

	std::pair<char, char> getTwoLeastPopularRoles() const;
	void assignRolePriorities();

	// Count methods

	int countAllPlayers() const;
	int countPlayersByRank(const std::string& rank) const;
	int countPlayersByRole(char role) const;
	int countPlayersByRankAndRole(const std::string& rank, char role) const;

	// Show methods

	void displayAllPlayers() const;
	void displayPlayersByRank(const std::string& rank) const;
	void displayPlayersByRole(char role) const;
	void displayPlayersByRankAndRole(const std::string& rank, char role) const;

	void displayRankQueue(std::string& rank) const;

	// File operations

	void loadPlayersFromFile(const std::string& filename);
	void savePlayersToFile(const std::string& filename) const;
};