#pragma once

#include "Player.h"
#include <cstdlib>
#include <vector>
#include <queue>

// Each match will store the players that participated, who won, and the ELO changes
// Also, all the roles should be filled (in total 10 players, 2 per role): T, J, M, A, S
// To ensure that 7/10 players have their primary role filled, the match creation function should prioritize adding players with their primary role first and then fill the remaining spots with secondary roles

class Match
{
private:
	static int nextMatchId; // Static counter for unique match IDs
	int matchId;
	std::vector<Player*> players; // Changed to pointers to allow modification of original players
	std::vector<char> assignedRoles; // NEW: Track what role each player is assigned in this match
	std::vector<bool> winners; // true if the player at the corresponding index won, false otherwise
	int eloWin;
	int eloLose;
	bool valid; // Ensures that the match has 10 players with all roles filled correctly
	std::string matchRank; // The rank tier this match belongs to
	bool winnersGenerated; // Flag to track if winners have been generated
public:
	Match();

	bool isValid() const; // Returns whether the match has 10 players
	void insertPlayer(Player* player); // Inserts a player into the match (the players vector)
	void insertPlayerWithRole(Player* player, char assignedRole); // Insert player with specific assigned role

	void processMatchResults(); // Updates all players ELO based on the match results (winners vector), it only does this if the match is valid
	void generateWinners(); // Regenerate random winners for the match

	void showMatchInfo() const; // Displays information about the match and its players
	
	// Getters for accessing match data
	const std::vector<Player*>& getPlayers() const;
	const std::vector<bool>& getWinners() const;
	int getEloWin() const;
	int getEloLose() const;
	int getMatchId() const;
	const std::string& getMatchRank() const;
	
	// Setters
	void setMatchRank(const std::string& rank);
};