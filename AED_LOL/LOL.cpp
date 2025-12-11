#include "LOL.h"
#include <algorithm> // for std::find

LOL::LOL()
{
	// Initialize rankQueues for each rank
	rankQueues.resize(10);
	// Initialize roleQueues for each rank (10 ranks)
	roleQueues.resize(10);
}

// Creating matches for each rank

void LOL::createMatchForRank(const std::string& rank)
{
	static const std::vector<std::string> ranks = { "Iron", "Bronze", "Silver", "Gold", "Platinum", "Emerald", "Diamond", "Master", "Grandmaster", "Challenger" };
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	if (it != ranks.end())
	{
		int index = std::distance(ranks.begin(), it);
		if (index < rankQueues.size())
		{
			std::stack<Match>& matchStack = matchStacks[index];
			Match match;
			while (matchStack.size() < 1) // Create matches until there is at least one match in the stack
			{
				// Fill the match with players from the rank queue
				while (!match.isValid() && !rankQueues[index].empty())
				{
					Player player = rankQueues[index].top();
					rankQueues[index].pop();
					match.insertPlayer(player);
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
		file << player; // Usar el operador << sobrecargado
	}
	file.close();
}