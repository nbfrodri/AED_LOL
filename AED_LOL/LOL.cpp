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
	// Initialize matchQueues for each rank (10 ranks)
	matchQueues.resize(10);
}

void LOL::displayTopPlayersByWinRateWithMinMatch(int minMatch, int top) const {
	std::vector<Player> filteredPlayers;
	
	// Filter players with at least minMatch played
	for (const auto& player : players)
	{
		if (player.getTotalMatches() >= minMatch)
		{
			filteredPlayers.push_back(player);
		}
	}
	
	// Sort filtered players by win rate in descending order
	std::sort(filteredPlayers.begin(), filteredPlayers.end(), [](const Player& a, const Player& b) {
		return a.getWinRate() > b.getWinRate();
	});
	
	std::cout << "\n========================================\n";
	std::cout << "TOP " << top << " PLAYERS BY WIN RATE (MIN " << minMatch << " MATCHES)\n";
	std::cout << "========================================\n";
	
	for (int i = 0; i < top && i < filteredPlayers.size(); ++i)
	{
		const auto& player = filteredPlayers[i];
		std::cout << (i + 1) << ". ";
		player.displayInfo();
		std::cout << "-----------------------\n";
	}
	
	std::cout << "========================================\n\n";
}

void LOL::displayTopPlayersByELO(int top) const {
	std::vector<Player> sortedPlayers = players;
	std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player& a, const Player& b) {
		return a.getElo() > b.getElo(); // Sort in descending order of ELO
	});
	std::cout << "\n========================================\n";
	std::cout << "TOP " << top << " PLAYERS BY ELO\n";
	std::cout << "========================================\n";
	for (int i = 0; i < top && i < sortedPlayers.size(); ++i)
	{
		const auto& player = sortedPlayers[i];
		std::cout << (i + 1) << ". ";
		player.displayInfo();
		std::cout << "-----------------------\n";
	}
	std::cout << "========================================\n\n";
}

void LOL::displayAllPlayersByELO() const {
	std::vector<Player> sortedPlayers = players;
	std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player& a, const Player& b) {
		return a.getElo() > b.getElo(); // Sort in descending order of ELO
	});
	for (const auto& player : sortedPlayers)
	{
		player.displayInfo();
		std::cout << "-----------------------\n";
	}
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
		if (index < matchQueues.size())
		{
			std::cout << "\n========================================\n";
			std::cout << "        MATCHES FOR RANK: " << rank << "\n";
			std::cout << "========================================\n";
			std::cout << "Number of matches: " << matchQueues[index].size() << "\n\n";
			
			if (matchQueues[index].empty())
			{
				std::cout << "No matches found for this rank.\n";
				std::cout << "========================================\n\n";
				return;
			}
			
			// Create a copy of the queue to iterate through it
			std::queue<Match> tempQueue = matchQueues[index];
			int matchNumber = 1;
			
			while (!tempQueue.empty())
			{
				const Match& match = tempQueue.front();
				std::cout << "MATCH #" << matchNumber << ":\n";
				displayMatchInfo(match);
				tempQueue.pop();
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

void LOL::displaySampleMatchFromIteration() const
{
	std::cout << "\n=== SAMPLE MATCH FROM THIS ITERATION ===\n";
	
	// Find the first non-empty match queue and display one match
	for (size_t rankIndex = 0; rankIndex < matchQueues.size(); ++rankIndex)
	{
		if (!matchQueues[rankIndex].empty())
		{
			// Get rank name
			static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
			
			std::queue<Match> tempQueue = matchQueues[rankIndex];
			const Match& sampleMatch = tempQueue.front();
			
			std::cout << "Sample from " << ranks[rankIndex] << " rank:\n";
			displayMatchInfo(sampleMatch);
			return;
		}
	}
	
	std::cout << "No matches found in this iteration.\n";
	std::cout << "=========================================\n\n";
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

void LOL::simulateMatchmakingSeason(int iterations)
{
	std::cout << "\n=== STARTING MATCHMAKING SIMULATION ===\n";
	std::cout << "Running " << iterations << " iteration(s) of matchmaking...\n\n";
	
	for (int i = 1; i <= iterations; ++i)
	{
		std::cout << "--- ITERATION " << i << " ---\n";
		
		// Clear all queues and match stacks from previous iteration
		clearAllQueues();
		std::cout << "All queues cleared for fresh start.\n";
		
		// Assign new random queue times to all players
		assignRandomQueueTimes();
		
		// Assign role priorities based on least popular roles
		assignRolePriorities();
		
		// Update priorities of all players
		updateAllPlayersPriorities();
		std::cout << "Player priorities updated.\n";

		// Enqueue all players into their respective rank queues
		enqueueAllPlayersToRankQueues();
		std::cout << "Players enqueued to rank queues.\n";
		
		// Add all players to role queues
		addAllPlayersToRoleQueues();
		std::cout << "Players added to role queues.\n";
		
		// Create matches for all ranks
		std::cout << "Creating matches for iteration " << i << "...\n";
		createAllMatches();
		std::cout << "Matches creation completed for iteration " << i << ".\n\n";
		
		// Process all match results
		std::cout << "=== PROCESSING MATCH RESULTS ===\n";
		processAllMatches();
		std::cout << "=== MATCH PROCESSING COMPLETE ===\n\n";
		
		std::cout << "Iteration " << i << " completed.\n";
		
		// Add separator between iterations (except for the last one)
		if (i < iterations)
		{
			std::cout << "\n";
		}
	}
	
	std::cout << "\n=== SIMULATION COMPLETED ===\n";
	std::cout << "All " << iterations << " iteration(s) completed successfully!\n";
	std::cout << "Final player data saved to file.\n\n";
}

void LOL::clearAllQueues()
{
	// Clear all rank queues (priority queues)
	for (auto& queue : rankQueues)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}
	
	// Clear all role queues
	for (auto& queue : roleQueues)
	{
		queue.clearAllQueues();
	}
	
	// Clear all match queues
	for (auto& queue : matchQueues)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}
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
			
			// Create matches while we have at least 10 players in the role queue
			int matchesCreated = 0;
			while (currentRoleQueue.getTotalPlayers() >= 10)
			{
				Match match;
				match.setMatchRank(rank);
				std::vector<char> roles = {'T', 'J', 'M', 'A', 'S'};
				std::vector<int> playersAddedToMatch;
				bool matchCreationFailed = false;
				
				// Try to fill the match with 2 players per role (10 total)
				for (char role : roles)
				{
					int playersNeededForRole = 2;
					int playersFoundForRole = 0;
					
					
					while (playersNeededForRole > 0 && currentRoleQueue.hasPlayersForRole(role))
					{
						try
						{
							Player player = currentRoleQueue.getPlayerForRole(role);
							
							// Check if this player is already in the match
							bool playerAlreadyAdded = false;
							for (int addedId : playersAddedToMatch)
							{
								if (addedId == player.getId())
								{
									playerAlreadyAdded = true;
									break;
								}
							}
							
							if (playerAlreadyAdded)
							{
								continue;
							}
							
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
								match.insertPlayerWithRole(originalPlayer, role); // Use new method with assigned role
								playersAddedToMatch.push_back(player.getId());
							}
							
							playersNeededForRole--;
						}
						catch (const std::exception& e)
						{
							std::cout << "        Exception getting player for role " << role << ": " << e.what() << "\n";
							break;
						}
					}
										
					// If we couldn't fill this role, mark match creation as failed
					if (playersNeededForRole > 0)
					{
						matchCreationFailed = true;
						break;
					}
				}
				
				// If we have a valid match (10 players), add it to the match queue
				if (match.isValid() && !matchCreationFailed && playersAddedToMatch.size() == 10)
				{
					match.generateWinners();
					matchQueues[index].push(match);
					matchesCreated++;
				}
				else
				{
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
		std::cout << "Matches created for rank: " << rank << "\n";
	}
}

void LOL::processAllMatches()
{
	int totalMatchesProcessed = 0;
	
	for (size_t rankIndex = 0; rankIndex < matchQueues.size(); ++rankIndex)
	{
		auto& matchQueue = matchQueues[rankIndex];
		
		if (!matchQueue.empty())
		{
			static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
			std::string rankName = (rankIndex < ranks.size()) ? ranks[rankIndex] : "Unknown";
			
			std::cout << "Processing " << matchQueue.size() << " matches for " << rankName << " rank...\n";
			
			// Process all matches in each queue
			std::queue<Match> tempQueue;
			int rankMatches = 0;
			
			// Move matches to temp queue for processing
			while (!matchQueue.empty())
			{
				Match match = matchQueue.front();
				matchQueue.pop();
				
				std::cout << "  Processing match " << match.getMatchId() << " with " << match.getPlayers().size() << " players\n";
				
				// Process the match results
				match.processMatchResults();
				rankMatches++;
				totalMatchesProcessed++;
				
				// Store in temp queue
				tempQueue.push(match);
			}
			
			// Move back to original queue
			while (!tempQueue.empty())
			{
				matchQueue.push(tempQueue.front());
				tempQueue.pop();
			}
			
			std::cout << "  Processed " << rankMatches << " matches for " << rankName << "\n\n";
		}
	}
	
	std::cout << "Total matches processed this iteration: " << totalMatchesProcessed << "\n";
	
	if (totalMatchesProcessed == 0)
	{
		std::cout << "WARNING: No matches were processed! Check match creation.\n";
	}
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

void LOL::displayRoleDistribution() const
{
	std::cout << "\n=== ROLE DISTRIBUTION BY RANK ===\n";
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	std::vector<char> roles = {'T', 'J', 'M', 'A', 'S'};
	
	bool hasAnyPlayers = false;
	
	for (size_t rankIndex = 0; rankIndex < ranks.size() && rankIndex < roleQueues.size(); ++rankIndex)
	{
		int totalPlayersInRank = roleQueues[rankIndex].getTotalPlayers();
		
		if (totalPlayersInRank > 0)
		{
			hasAnyPlayers = true;
			std::cout << ranks[rankIndex] << " rank (Total: " << totalPlayersInRank << " players):\n";
			
			for (char role : roles)
			{
				int count = roleQueues[rankIndex].getPlayersCountForRole(role);
				std::cout << "  Role " << role << ": " << count << " players";
				if (count >= 2) 
				{
					std::cout << " (sufficient for matches)";
				}
				else if (count == 1)
				{
					std::cout << " (needs 1 more)";
				}
				else
				{
					std::cout << " (needs 2 more)";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
		}
		else
		{
			std::cout << ranks[rankIndex] << " rank: No players\n";
		}
	}
	
	if (!hasAnyPlayers)
	{
		std::cout << "NO PLAYERS FOUND IN ANY ROLE QUEUES!\n";
		std::cout << "This suggests players are not being added to role queues properly.\n";
	}
	
	std::cout << "==================================\n";
}

// File operations// File operations