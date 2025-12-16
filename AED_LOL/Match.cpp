#include "Match.h"
#include <ctime>
#include <iostream>
#include <iomanip>

// Static member definition
int Match::nextMatchId = 1;

Match::Match() : matchId(nextMatchId++), valid(false), matchRank(""), winnersGenerated(false)
{
	// Using random, establish a random number between 15 and 30 for eloWin and eloLose
	eloWin = rand() % 16 + 15;
	eloLose = rand() % 16 + 15;

	// Initialize winners vector but don't populate it yet
	winners.resize(10, false);
	// Initialize assigned roles vector
	assignedRoles.resize(10, 'U'); // U for Unassigned
}

void Match::generateWinners()
{
	if (players.size() != 10) return;
	
	// Clear previous winners (set it all to false)
	for (size_t i = 0; i < winners.size(); ++i)
	{
		winners[i] = false;
	}
	
	// Seed random number generator with current time + match ID for better randomness
	srand(static_cast<unsigned int>(time(0)) + matchId);
	
	// Randomly set 5 players as winners
	int winsAssigned = 0;
	while (winsAssigned < 5)
	{
		int randomIndex = rand() % 10;
		if (!winners[randomIndex])
		{
			winners[randomIndex] = true;
			winsAssigned++;
		}
	}
	
	winnersGenerated = true;
}

bool Match::isValid() const
{
	bool result = players.size() == 10 && valid; // Must have 10 players and valid roles
	return result;
}

void Match::insertPlayerWithRole(Player* player, char assignedRole)
{
	if (players.size() < 10)
	{
		// Check if player is already in the match
		for (const auto& existingPlayer : players)
		{
			if (existingPlayer->getId() == player->getId())
			{
				std::cout << "Warning: Player " << player->getUsername() << " (ID: " << player->getId() << ") already in match " << matchId << std::endl;
				return; // Don't add duplicate player
			}
		}
		
		players.push_back(player);
		assignedRoles[players.size() - 1] = assignedRole; // Assign the specific role
		
		if (players.size() == 10)
		{
			// Check if all roles are filled correctly using ASSIGNED roles
			std::vector<int> roleCounts(5, 0); // T, J, M, A, S
			
			for (size_t i = 0; i < players.size(); ++i)
			{
				char assignedRoleForPlayer = assignedRoles[i];
				
				switch (assignedRoleForPlayer)
				{
				case 'T': roleCounts[0]++; break;
				case 'J': roleCounts[1]++; break;
				case 'M': roleCounts[2]++; break;
				case 'A': roleCounts[3]++; break;
				case 'S': roleCounts[4]++; break;
				default:
					std::cout << "WARNING: Player " << players[i]->getUsername() << " has invalid assigned role: " << assignedRoleForPlayer << "\n";
				}
			}
			
			// Check if we have exactly 2 players per role
			char roleNames[] = {'T', 'J', 'M', 'A', 'S'};
			bool allRolesFilled = true;
			
			for (int i = 0; i < 5; ++i)
			{
				if (roleCounts[i] == 2)
				{
				}
				else
				{
					allRolesFilled = false;
				}
			}
			
			valid = allRolesFilled;
		}
	}
	else
	{
		std::cout << "Warning: Cannot add player to match " << matchId << " - already has 10 players" << std::endl;
	}
}

void Match::processMatchResults()
{
	if (!isValid()) return; // Only process if match is valid
	
	// Generate fresh winners for this match if not already done
	if (!winnersGenerated)
	{
		generateWinners();
	}
		
	// Update each player's ELO based on whether they won or lost
	for (size_t i = 0; i < players.size(); ++i)
	{
		Player* player = players[i];
		bool playerWon = winners[i];
		int eloChange = 0;
		
		// Store old rank for comparison
		std::string oldRank = player->getRank();
		int oldElo = player->getElo();
		
		if (playerWon)
		{
			// Winner gains ELO
			int newElo = player->getElo() + eloWin;
			player->setElo(newElo);
			eloChange = eloWin;
		}
		else
		{
			// Loser loses ELO
			int newElo = player->getElo() - eloLose;
			if (newElo < 0) newElo = 0; // Ensure ELO doesn't go below 0
			player->setElo(newElo);
			eloChange = -eloLose;
		}
		
		// Update rank based on new ELO
		player->updateRank();
		
		// Add match result to player's history
		player->addMatchResult(matchId, playerWon, eloChange, matchRank);
	}
	
}

// Getters implementation
const std::vector<Player*>& Match::getPlayers() const
{
	return players;
}

const std::vector<bool>& Match::getWinners() const
{
	return winners;
}

int Match::getEloWin() const
{
	return eloWin;
}

int Match::getEloLose() const
{
	return eloLose;
}

int Match::getMatchId() const
{
	return matchId;
}

const std::string& Match::getMatchRank() const
{
	return matchRank;
}

void Match::setMatchRank(const std::string& rank)
{
	matchRank = rank;
}