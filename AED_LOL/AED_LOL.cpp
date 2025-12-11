#include <iostream>

#include "LOL.h"

int main()
{
	LOL lolSystem;

	// Load players from file
	lolSystem.loadPlayersFromFile("players.csv");
	
	// Assign role priorities based on least popular roles
	lolSystem.assignRolePriorities();
	
	// Enqueue all players into their respective rank queues
	lolSystem.enqueueAllPlayersToRankQueues();
	
	// Add all players to role queues
	lolSystem.addAllPlayersToRoleQueues();

	// Create matches for all ranks
	lolSystem.createAllMatches();
		
	// Process all match results (this will automatically save to file)
	lolSystem.processAllMatches();
	
	// Assign new random queue times to all players
	lolSystem.assignRandomQueueTimes();

	// Save updated player data back to file
	lolSystem.savePlayersToFile("players.csv");

	// Display match history for a specific player (example: player ID 1)
	std::cout << "=== PLAYER MATCH HISTORY EXAMPLE ===\n";
	lolSystem.displayPlayerMatchHistory(3);
	
	return 0;
}