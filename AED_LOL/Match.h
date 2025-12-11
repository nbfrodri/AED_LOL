#pragma once

#include "Player.h"
#include <cstdlib>
#include <vector>

// Each match will store the players that participated, who won, and the ELO changes
// Also, all the roles should be filled (in total 10 players, 2 per role): T, J, M, A, S
// To ensure that 7/10 players have their primary role filled, the match creation function should prioritize adding players with their primary role first and then fill the remaining spots with secondary roles

class Match
{
private:
	std::vector<Player> players;
	std::vector<bool> winners; // true if the player at the corresponding index won, false otherwise
	int eloWin;
	int eloLose;
	bool valid; // Ensures that the match has 10 players with all roles filled correctly
public:
	Match();
};