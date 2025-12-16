#include <iostream>

#include "LOL.h"

int main()
{
	LOL lolSystem;

	// Load players from file (si reduces el número de jugadores, las iteraciones se harán más rápido)
	lolSystem.loadPlayersFromFile("players.csv");
	
	// Run simulation for multiple iterations
	int simulationIterations = 5; // Change to 1 for debugging
	lolSystem.simulateMatchmakingSeason(simulationIterations);

	// Save final updated player data back to file
	lolSystem.savePlayersToFile("players.csv");
	
	// Display final statistics
	std::cout << "=== FINAL PLAYER STATISTICS ===\n";

	// Display first top x players by ELO
	lolSystem.displayTopPlayersByELO(10);

	// Display top WR players with a minimum of matches played
	int minMatches = 1;
	int topPlayers = 10;
	lolSystem.displayTopPlayersByWinRateWithMinMatch(minMatches, topPlayers);

	// Display match history for a specific player (example: player ID 1)
	std::cout << "=== PLAYER MATCH HISTORY EXAMPLE ===\n";
	lolSystem.displayPlayerMatchHistory(1);
	
	return 0;
}