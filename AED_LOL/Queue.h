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

	// Display role queues
	void displayRoleQueue(char role, bool isPrimary) const;
};