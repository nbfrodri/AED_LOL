#include "Match.h"
#include <ctime>
#include <iostream>
#include <iomanip>

// Static member definition
int Match::nextMatchId = 1;

Match::Match() : matchId(nextMatchId++), valid(false), matchRank("")
{
	srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

	// Using random, establish a random number between 15 and 30 for eloWin and eloLose
	eloWin = rand() % 16 + 15;
	eloLose = rand() % 16 + 15;

	// We also initialize the positions in the winners vector to false and then randomly set 5 of them to true
	winners.resize(10, false);
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
}

bool Match::isValid() const
{
	return players.size() == 10 && valid;
}

void Match::insertPlayer(Player* player)
{
	if (players.size() < 10)
	{
		players.push_back(player);
		if (players.size() == 10)
		{
			// Check if all roles are filled correctly
			std::vector<int> roleCounts(5, 0); // T, J, M, A, S
			for (const auto& p : players)
			{
				char primaryRole = p->getPrimaryRole();
				switch (primaryRole)
				{
				case 'T': roleCounts[0]++; break;
				case 'J': roleCounts[1]++; break;
				case 'M': roleCounts[2]++; break;
				case 'A': roleCounts[3]++; break;
				case 'S': roleCounts[4]++; break;
				}
			}
			
			// Check if we have exactly 2 players per role
			bool allRolesFilled = true;
			for (int count : roleCounts)
			{
				if (count != 2)
				{
					allRolesFilled = false;
					break;
				}
			}
			
			valid = allRolesFilled;
		}
	}
}

void Match::processMatchResults()
{
	if (!isValid()) return;
	
	for (size_t i = 0; i < players.size(); ++i)
	{
		Player* player = players[i];
		bool playerWon = winners[i];
		int eloChange = 0;
		
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

void Match::showMatchInfo() const
{
	std::cout << "========== MATCH INFORMATION ==========\n";
	std::cout << "Match ID: " << matchId << "\n";
	std::cout << "Match Rank: " << matchRank << "\n";
	std::cout << "Match Status: " << (isValid() ? "VALID" : "INVALID") << "\n";
	std::cout << "Players in Match: " << players.size() << "/10\n";
	std::cout << "ELO Win: +" << eloWin << " | ELO Loss: -" << eloLose << "\n";
	std::cout << "=======================================\n";
	
	if (players.empty())
	{
		std::cout << "No players in this match.\n";
		return;
	}
	
	// Group players by role for better display
	std::vector<std::vector<Player*>> playersByRole(5);
	std::vector<char> roleNames = {'T', 'J', 'M', 'A', 'S'};
	std::vector<std::string> roleFullNames = {"Top", "Jungle", "Mid", "ADC", "Support"};
	
	for (size_t i = 0; i < players.size(); ++i)
	{
		Player* player = players[i];
		char role = player->getPrimaryRole();
		int roleIndex = -1;
		
		switch (role)
		{
		case 'T': roleIndex = 0; break;
		case 'J': roleIndex = 1; break;
		case 'M': roleIndex = 2; break;
		case 'A': roleIndex = 3; break;
		case 'S': roleIndex = 4; break;
		}
		
		if (roleIndex != -1)
		{
			playersByRole[roleIndex].push_back(player);
		}
	}
	
	// Display players by role
	for (size_t roleIdx = 0; roleIdx < 5; ++roleIdx)
	{
		std::cout << "\n" << roleFullNames[roleIdx] << " (" << roleNames[roleIdx] << "):";
		if (playersByRole[roleIdx].empty())
		{
			std::cout << " No players assigned\n";
		}
		else
		{
			std::cout << "\n";
			for (size_t playerIdx = 0; playerIdx < playersByRole[roleIdx].size(); ++playerIdx)
			{
				Player* player = playersByRole[roleIdx][playerIdx];
				
				// Find this player's index in the original players vector to check if they won
				bool isWinner = false;
				for (size_t i = 0; i < players.size(); ++i)
				{
					if (players[i]->getId() == player->getId())
					{
						isWinner = (i < winners.size()) ? winners[i] : false;
						break;
					}
				}
				
				std::cout << "  " << (playerIdx + 1) << ". " << player->getUsername()
						  << " (ID: " << player->getId() 
						  << ", ELO: " << player->getElo()
						  << ", Rank: " << player->getRank()
						  << ", WR: " << std::fixed << std::setprecision(1) << player->getWinRate() << "%"
						  << ") - " << (isWinner ? "WINNER" : "LOSER") << "\n";
			}
		}
	}
	std::cout << "=======================================\n\n";
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