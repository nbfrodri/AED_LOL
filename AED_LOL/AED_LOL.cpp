#include <iostream>

#include "LOL.h"

int main()
{
	LOL lolSystem;

	// Load players from file
	lolSystem.loadPlayersFromFile("players.csv");
	lolSystem.assignRolePriorities(); // Assign role priorities based on least popular roles
	lolSystem.enqueueAllPlayersToRankQueues(); // Enqueue all players into their respective rank queues

	// Display players in the Challenger rank queue
	std::string rankToDisplay = "Challenger";
	lolSystem.displayRankQueue(rankToDisplay);

	// Show role priorities
	std::cout << "Role 1 Priority: " << lolSystem.getRole1Priority() << std::endl;
	std::cout << "Role 2 Priority: " << lolSystem.getRole2Priority() << std::endl;

	return 0;
}