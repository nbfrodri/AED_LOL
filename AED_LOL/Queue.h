#pragma once

#include "Player.h"
#include <queue>
#include <vector>

class Queue
{
private:
	std::vector<std::priority_queue<Player>> mainRolesQueue; // Priority queues for each role (5 roles: T, J, M, A, S) containing players with that primary role
	std::vector<std::priority_queue<Player>> secondaryRolesQueue; // Priority queues for each role (5 roles: T, J, M, A, S) containing players with that secondary role
public:
	Queue(); // Default constructor
	
	// Enqueue players into their respective role queues
	void enqueuePlayerToRoleQueue(const Player& player);

	// Get player from role queue with priority logic
	Player getPlayerForRole(char role); // Gets player prioritizing main role, then secondary
	bool hasPlayersForRole(char role) const; // Check if there are players available for a role
	
	// Remove player from both queues when taken
	void removePlayerFromQueues(const Player& player);

	// Display role queues
	void displayRoleQueue(char role, bool isPrimary) const;

	// Check if queues are empty
	bool isEmpty() const;
	int getTotalPlayers() const; // Get total number of players across all role queues
};