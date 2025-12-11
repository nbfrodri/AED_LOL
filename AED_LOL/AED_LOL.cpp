#include <iostream>

#include "LOL.h"

int main()
{
	LOL lolSystem;

	// Load players from file
	lolSystem.loadPlayersFromFile("players.csv");
	lolSystem.assignRolePriorities(); // Assign role priorities based on least popular roles
	lolSystem.enqueueAllPlayersToRankQueues(); // Enqueue all players into their respective rank queues
	lolSystem.addAllPlayersToRoleQueues(); // Add all players to role queues

	// Display the Top role queue for a specific rank (Challenger)
	lolSystem.displayRoleQueue("Iron", 'T', true); // true indicates primary role
	// Display the Top role secondary queue for a specific rank (Challenger)
	lolSystem.displayRoleQueue("Iron", 'T', false); // false indicates secondary role

	return 0;
}