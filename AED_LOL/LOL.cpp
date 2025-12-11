#include "LOL.h"
#include <algorithm> // for std::find and std::sort
#include <iomanip>   // for std::setprecision
#include <cstdlib>   // for std::rand and std::srand
#include <ctime>     // for std::time

LOL::LOL()
{
	// Initialize rankQueues for each rank
	rankQueues.resize(10);
	// Initialize roleQueues for each rank (10 ranks)
	roleQueues.resize(10);
	// Initialize matchStacks for each rank (10 ranks)
	matchStacks.resize(10);
}

void LOL::displayPlayersByRankAndRole(const std::string& rank, char role) const
{
	for (const auto& player : players)
	{
		if (player.getRank() == rank && (player.getPrimaryRole() == role || player.getSecondaryRole() == role))
		{
			player.displayInfo();
			std::cout << "-----------------------\n";
		}
	}
}

void LOL::displayRankQueue(std::string& rank) const
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	if (it != ranks.end())
	{
		int index = std::distance(ranks.begin(), it);
		if (index < rankQueues.size())
		{
			std::priority_queue<Player> tempQueue = rankQueues[index]; // Copiar la cola para no modificar la original
			while (!tempQueue.empty())
			{
				const Player& player = tempQueue.top();
				player.displayInfo();
				std::cout << "-----------------------\n";
				tempQueue.pop();
			}
		}
		else
		{
			std::cout << "No players in the " << rank << " queue.\n";
		}
	}
	else
	{
		std::cout << "Invalid rank: " << rank << std::endl;
	}
}

void LOL::displayRoleQueue(const std::string& rank, char role, bool isPrimary) const
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	if (it != ranks.end())
	{
		int index = std::distance(ranks.begin(), it);
		if (index < roleQueues.size())
		{
			std::cout << "Role Queue for Rank: " << rank << "\n";
			roleQueues[index].displayRoleQueue(role, isPrimary);
		}
		else
		{
			std::cout << "No role queues found for rank: " << rank << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid rank: " << rank << std::endl;
	}
}

void LOL::displayMatchesForRank(const std::string& rank) const
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	if (it != ranks.end())
	{
		int index = std::distance(ranks.begin(), it);
		if (index < matchStacks.size())
		{
			std::cout << "\n========================================\n";
			std::cout << "        MATCHES FOR RANK: " << rank << "\n";
			std::cout << "========================================\n";
			std::cout << "Number of matches: " << matchStacks[index].size() << "\n\n";
			
			if (matchStacks[index].empty())
			{
				std::cout << "No matches found for this rank.\n";
				std::cout << "========================================\n\n";
				return;
			}
			
			// Create a copy of the stack to iterate through it
			std::stack<Match> tempStack = matchStacks[index];
			int matchNumber = 1;
			
			while (!tempStack.empty())
			{
				const Match& match = tempStack.top();
				std::cout << "MATCH #" << matchNumber << ":\n";
				displayMatchInfo(match);
				tempStack.pop();
				matchNumber++;
			}
			
			std::cout << "========================================\n";
			std::cout << "End of matches for " << rank << " rank\n";
			std::cout << "========================================\n\n";
		}
		else
		{
			std::cout << "No matches found for rank: " << rank << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid rank: " << rank << std::endl;
	}
}

void LOL::displayMatchInfo(const Match& match) const
{
	match.showMatchInfo();
}

void LOL::displayPlayerMatchHistory(int playerId) const
{
	for (const auto& player : players)
	{
		if (player.getId() == playerId)
		{
			player.displayMatchHistory();
			return;
		}
	}
	std::cout << "Player with ID " << playerId << " not found.\n";
}

void LOL::displayPlayersWithHighestWinRate(int topCount) const
{
	// Create a copy of players vector for sorting
	std::vector<Player> sortedPlayers = players;
	
	// Sort by win rate (descending) and then by total matches (minimum 1 match played)
	std::sort(sortedPlayers.begin(), sortedPlayers.end(), 
		[](const Player& a, const Player& b) {
			// Players with no matches go to the end
			if (a.getTotalMatches() == 0 && b.getTotalMatches() == 0) return false;
			if (a.getTotalMatches() == 0) return false;
			if (b.getTotalMatches() == 0) return true;
			
			// Sort by win rate (higher first)
			return a.getWinRate() > b.getWinRate();
		});
	
	std::cout << "\n========================================\n";
	std::cout << "TOP " << topCount << " PLAYERS BY WIN RATE\n";
	std::cout << "========================================\n";
	
	int count = 0;
	for (const auto& player : sortedPlayers)
	{
		if (count >= topCount) break;
		if (player.getTotalMatches() == 0) continue; // Skip players with no matches
		
		std::cout << (count + 1) << ". " << player.getUsername() 
				  << " | Win Rate: " << std::fixed << std::setprecision(1) << player.getWinRate() << "%"
				  << " | Matches: " << player.getTotalMatches()
				  << " | Wins: " << player.getTotalWins()
				  << " | Rank: " << player.getRank()
				  << " | ELO: " << player.getElo() << "\n";
		count++;
	}
	
	if (count == 0)
	{
		std::cout << "No players have played any matches yet.\n";
	}
	
	std::cout << "========================================\n\n";
}

void LOL::assignRandomQueueTimes()
{
	std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator
	
	for (auto& player : players)
	{
		// Generate random double between 1.0 and 400.0
		double randomTime = 1.0 + static_cast<double>(std::rand()) / RAND_MAX * 399.0;
		player.setTimeQueued(randomTime);
	}
	
	std::cout << "Random queue times assigned to all players (1.0 - 400.0 seconds).\n";
}

// File operations

void LOL::loadPlayersFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file for reading: " << filename << std::endl;
		return;
	}
	Player* player = new Player(); // Crear un solo objeto Player para reutilizar
	while (file >> *player) // Usar el operador >> sobrecargado
	{
		players.push_back(*player); // Agregar una copia del player al vector
		player = new Player(); // Crear un nuevo objeto Player para la siguiente lectura
	}
	delete player; // Limpiar el último player no utilizado
	file.close();
}

void LOL::savePlayersToFile(const std::string& filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file for writing: " << filename << std::endl;
		return;
	}
	for (const auto& player : players)
	{
		file << player << "\n"; // Agregar salto de línea después de cada player
	}
	file.close();
}

void LOL::createMatchForRank(const std::string& rank)
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	if (it != ranks.end())
	{
		int index = std::distance(ranks.begin(), it);
		if (index < roleQueues.size())
		{
			Queue& currentRoleQueue = roleQueues[index];
			std::priority_queue<Player>& currentRankQueue = rankQueues[index];
			
			// Create matches while we have at least 10 players in the rank queue
			while (currentRankQueue.size() >= 10)
			{
				Match match;
				match.setMatchRank(rank); // Set the match rank
				std::vector<char> roles = {'T', 'J', 'M', 'A', 'S'};
				
				// Try to fill the match with 2 players per role (10 total)
				for (char role : roles)
				{
					int playersNeededForRole = 2;
					
					while (playersNeededForRole > 0 && currentRoleQueue.hasPlayersForRole(role))
					{
						try
						{
							Player player = currentRoleQueue.getPlayerForRole(role);
							
							// Find the original player in the players vector to get a pointer
							Player* originalPlayer = nullptr;
							for (auto& p : players)
							{
								if (p.getId() == player.getId())
								{
									originalPlayer = &p;
									break;
								}
							}
							
							if (originalPlayer != nullptr)
							{
								match.insertPlayer(originalPlayer);
								
								// Remove player from rank queue as well
								std::vector<Player> tempPlayers;
								bool playerFound = false;
								
								while (!currentRankQueue.empty() && !playerFound)
								{
									Player tempPlayer = currentRankQueue.top();
									currentRankQueue.pop();
									
									if (tempPlayer.getId() != player.getId())
									{
										tempPlayers.push_back(tempPlayer);
									}
									else
									{
										playerFound = true;
									}
								}
								
								// Put back the other players
								for (const auto& p : tempPlayers)
								{
									currentRankQueue.push(p);
								}
							}
							
							playersNeededForRole--;
						}
						catch (const std::exception&)
						{
							// No more players available for this role
							break;
						}
					}
				}
				
				// If we have a valid match (10 players), add it to the match stack
				if (match.isValid())
				{
					matchStacks[index].push(match);
				}
				else
				{
					// If we couldn't create a complete match, break the loop
					break;
				}
			}
		}
	}
}

void LOL::createAllMatches()
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	for (const auto& rank : ranks)
	{
		createMatchForRank(rank);
	}
}

void LOL::processAllMatches()
{
	for (auto& matchStack : matchStacks)
	{
		// Process all matches in each stack
		std::stack<Match> tempStack;
		
		// Move matches to temp stack for processing
		while (!matchStack.empty())
		{
			Match match = matchStack.top();
			matchStack.pop();
			
			// Process the match results
			match.processMatchResults();
			
			// Store in temp stack
			tempStack.push(match);
		}
		
		// Move back to original stack (optional, depending on whether you want to keep processed matches)
		while (!tempStack.empty())
		{
			matchStack.push(tempStack.top());
			tempStack.pop();
		}
	}
	
	// Save updated player data to file after processing all matches
	std::cout << "Saving updated player data to file...\n";
	savePlayersToFile("players.csv");
	std::cout << "Player data saved successfully.\n";
}

// Add players to roleQueues based on their rank and roles, starting from Iron to Challenger

void LOL::addPlayerToRoleQueue(const Player& player)
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), player.getRank()); // Iterator that finds the rank of the player in the ranks vector
	if (it != ranks.end()) // If rank found
	{
		int index = std::distance(ranks.begin(), it); // Calculate index based on position in ranks vector (for example, Iron = 0, Bronze = 1, etc.)
		if (roleQueues.size() <= index)
		{
			roleQueues.resize(index + 1); // Resize the roleQueues vector if necessary (needed if for example no players of a certain rank have been added yet)
		}
		roleQueues[index].enqueuePlayerToRoleQueue(player); // Add player to the appropriate role queue
	}
}

void LOL::addAllPlayersToRoleQueues()
{
	for (const auto& player : players)
	{
		addPlayerToRoleQueue(player);
	}
}

// Update priorities of all players

void LOL::updateAllPlayersPriorities()
{
	for (auto& player : players)
	{
		player.calculatePriority(role1Priority, role2Priority);
	}
}

// Enqueue players into their respective rank queues

void LOL::enqueuePlayerToRankQueue(const Player& player)
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), player.getRank()); // Iterator that finds the rank of the player in the ranks vector
	if (it != ranks.end()) // If rank found
	{
		int index = std::distance(ranks.begin(), it); // Calculate index based on position in ranks vector (for example, Iron = 0, Bronze = 1, etc.)
		if (rankQueues.size() <= index)
		{
			rankQueues.resize(index + 1); // Resize the rankQueues vector if necessary (needed if for example no players of a certain rank have been added yet)
		}
		rankQueues[index].push(player); // Enqueue player to the appropriate rank queue
	}
}

void LOL::enqueueAllPlayersToRankQueues()
{
	for (const auto& player : players)
	{
		enqueuePlayerToRankQueue(player);
	}
}

// Getters for role priorities

char LOL::getRole1Priority() const
{
	return role1Priority;
}

char LOL::getRole2Priority() const
{
	return role2Priority;
}

// Get the 2 roles with less players

std::pair<char, char> LOL::getTwoLeastPopularRoles() const
{
	std::vector<char> roles = { 'T', 'J', 'M', 'A', 'S' }; // Top, Jungle, Mid, ADC, Support
	std::vector<int> roleCounts(roles.size(), 0); // Initialize counts to 0
	// Count players for each role
	for (const auto& player : players)
	{
		for (size_t i = 0; i < roles.size(); ++i)
		{
			if (player.getPrimaryRole() == roles[i] || player.getSecondaryRole() == roles[i])
			{
				roleCounts[i]++;
			}
		}
	}
	// Find the two roles with the least players
	int firstMinIndex = -1;
	int secondMinIndex = -1;
	for (size_t i = 0; i < roleCounts.size(); ++i)
	{
		if (firstMinIndex == -1 || roleCounts[i] < roleCounts[firstMinIndex])
		{
			secondMinIndex = firstMinIndex;
			firstMinIndex = i;
		}
		else if (secondMinIndex == -1 || roleCounts[i] < roleCounts[secondMinIndex])
		{
			secondMinIndex = i;
		}
	}
	return { roles[firstMinIndex], roles[secondMinIndex] };
}

void LOL::assignRolePriorities()
{
	auto [role1, role2] = getTwoLeastPopularRoles();
	role1Priority = role1;
	role2Priority = role2;
	updateAllPlayersPriorities();
}

// Count methods

int LOL::countAllPlayers() const
{
	return players.size();
}

int LOL::countPlayersByRank(const std::string& rank) const
{
	int count = 0;
	for (const auto& player : players)
	{
		if (player.getRank() == rank)
		{
			count++;
		}
	}
	return count;
}

int LOL::countPlayersByRole(char role) const
{
	int count = 0;
	for (const auto& player : players)
	{
		if (player.getPrimaryRole() == role || player.getSecondaryRole() == role)
		{
			count++;
		}
	}
	return count;
}

int LOL::countPlayersByRankAndRole(const std::string& rank, char role) const
{
	int count = 0;
	for (const auto& player : players)
	{
		if (player.getRank() == rank && (player.getPrimaryRole() == role || player.getSecondaryRole() == role))
		{
			count++;
		}
	}
	return count;
}

// Show methods

void LOL::displayAllPlayers() const
{
	for (const auto& player : players)
	{
		player.displayInfo();
		std::cout << "-----------------------\n";
	}
}

void LOL::displayPlayersByRank(const std::string& rank) const
{
	for (const auto& player : players)
	{
		if (player.getRank() == rank)
		{
			player.displayInfo();
			std::cout << "-----------------------\n";
		}
	}
}

void LOL::displayPlayersByRole(char role) const
{
	for (const auto& player : players)
	{
		if (player.getPrimaryRole() == role || player.getSecondaryRole() == role)
		{
			player.displayInfo();
			std::cout << "-----------------------\n";
		}
	}
}