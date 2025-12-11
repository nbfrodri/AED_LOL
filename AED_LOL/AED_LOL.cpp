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
	std::cout << "Creating matches...\n";
	lolSystem.createAllMatches();
	std::cout << "Matches created successfully.\n\n";
	
	// Display detailed match information for specific ranks
	std::cout << "=== DISPLAYING DETAILED MATCH INFORMATION ===\n";
	lolSystem.displayMatchesForRank("Master");
	
	// Process all match results (this will automatically save to file)
	std::cout << "Processing match results...\n";
	lolSystem.processAllMatches();
	std::cout << "All matches processed and player data saved.\n\n";
	
	// Display match history for a specific player (example: player ID 1)
	std::cout << "=== PLAYER MATCH HISTORY EXAMPLE ===\n";
	lolSystem.displayPlayerMatchHistory(1);
	
	return 0;
}