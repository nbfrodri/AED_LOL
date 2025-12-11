#include <iostream>

#include "LOL.h"

int main()
{
	LOL lolSystem;

	// Load players from file
	lolSystem.loadPlayersFromFile("players.csv");
	
	// Run simulation for multiple iterations
	int simulationIterations = 50; // Change this to simulate different numbers of seasons
	lolSystem.simulateMatchmakingSeason(simulationIterations);

	// Save final updated player data back to file
	lolSystem.savePlayersToFile("players.csv");
	
	// Display final statistics
	std::cout << "=== FINAL PLAYER STATISTICS ===\n";

	// Display first top 10 players by ELO

	lolSystem.displayTopPlayersByELO(10);

	// Display top 10 WR players that minimum have 10 matches played

	int minMatches = 10;
	int topPlayers = 10;
	lolSystem.displayTopPlayersByWinRateWithMinMatch(minMatches, topPlayers);

	// Display match history for a specific player (example: player ID 3)
	std::cout << "=== PLAYER MATCH HISTORY EXAMPLE ===\n";
	lolSystem.displayPlayerMatchHistory(891);
	
	return 0;
}