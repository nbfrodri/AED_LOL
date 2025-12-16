#pragma once

#include "Player.h"
#include <cstdlib>
#include <vector>
#include <queue>

class Match
{
private:
	static int nextMatchId; // Static counter for unique match IDs
	int matchId;
	std::vector<Player*> players; // Pointers to allow modification of original players
	std::vector<char> assignedRoles; // To track assigned roles for players
	std::vector<bool> winners; // true if the player at the corresponding index won, false otherwise
	int eloWin;
	int eloLose;
	bool valid; // Ensures that the match has 10 players with all roles filled correctly
	std::string matchRank; // The rank tier this match belongs to
	bool winnersGenerated; // Flag to track if winners have been generated
public:
	Match();

	bool isValid() const; // Returns whether the match has 10 players
	void insertPlayerWithRole(Player* player, char assignedRole); // Insert player with specific assigned role

	void processMatchResults(); // Updates all players ELO based on the match results (winners vector), it only does this if the match is valid
	void generateWinners(); // Regenerate random winners for the match
	
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