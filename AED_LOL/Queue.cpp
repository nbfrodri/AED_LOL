#include "Queue.h"
#include <iostream>

Queue::Queue()
{
	// Initialize vectors for 5 roles: T=0, J=1, M=2, A=3, S=4
	mainRolesQueue.resize(5);
	secondaryRolesQueue.resize(5);
}

int getRoleIndex(char role)
{
	switch (role)
	{
	case 'T': return 0;
	case 'J': return 1;
	case 'M': return 2;
	case 'A': return 3;
	case 'S': return 4;
	default: return -1;
	}
}

void Queue::enqueuePlayerToRoleQueue(const Player& player)
{
	char mainRole = player.getPrimaryRole();
	char secondaryRole = player.getSecondaryRole();

	int mainRoleIndex = getRoleIndex(mainRole);
	int secondaryRoleIndex = getRoleIndex(secondaryRole);

	if (mainRoleIndex != -1)
	{
		mainRolesQueue[mainRoleIndex].push(player);
	}
	
	if (secondaryRoleIndex != -1)
	{
		secondaryRolesQueue[secondaryRoleIndex].push(player);
	}
}

Player Queue::getPlayerForRole(char role)
{
	int roleIndex = getRoleIndex(role);
	if (roleIndex == -1)
	{
		throw std::invalid_argument("Invalid role");
	}

	// First try to get from main role queue
	if (!mainRolesQueue[roleIndex].empty())
	{
		Player player = mainRolesQueue[roleIndex].top();
		mainRolesQueue[roleIndex].pop();
		removePlayerFromQueues(player); // Remove from secondary queue as well
		return player;
	}
	// If main queue is empty, try secondary queue
	else if (!secondaryRolesQueue[roleIndex].empty())
	{
		Player player = secondaryRolesQueue[roleIndex].top();
		secondaryRolesQueue[roleIndex].pop();
		removePlayerFromQueues(player); // Remove from other queues as well
		return player;
	}
	
	throw std::runtime_error("No players available for role");
}

bool Queue::hasPlayersForRole(char role) const
{
	int roleIndex = getRoleIndex(role);
	if (roleIndex == -1) return false;
	
	bool hasMainRole = !mainRolesQueue[roleIndex].empty();
	bool hasSecondaryRole = !secondaryRolesQueue[roleIndex].empty();
	
	return hasMainRole || hasSecondaryRole;
}

int Queue::getPlayersCountForRole(char role) const
{
	int roleIndex = getRoleIndex(role);
	if (roleIndex == -1) return 0;
	
	return mainRolesQueue[roleIndex].size() + secondaryRolesQueue[roleIndex].size();
}

void Queue::removePlayerFromQueues(const Player& player)
{
	// Remove from all main role queues
	for (int i = 0; i < 5; ++i)
	{
		std::priority_queue<Player> tempQueue;
		while (!mainRolesQueue[i].empty())
		{
			Player tempPlayer = mainRolesQueue[i].top();
			mainRolesQueue[i].pop();
			if (tempPlayer.getId() != player.getId())
			{
				tempQueue.push(tempPlayer);
			}
		}
		mainRolesQueue[i] = tempQueue;
	}
	
	// Remove from all secondary role queues
	for (int i = 0; i < 5; ++i)
	{
		std::priority_queue<Player> tempQueue;
		while (!secondaryRolesQueue[i].empty())
		{
			Player tempPlayer = secondaryRolesQueue[i].top();
			secondaryRolesQueue[i].pop();
			if (tempPlayer.getId() != player.getId())
			{
				tempQueue.push(tempPlayer);
			}
		}
		secondaryRolesQueue[i] = tempQueue;
	}
}

void Queue::displayRoleQueue(char role, bool isPrimary) const
{
	int roleIndex = getRoleIndex(role);
	if (roleIndex == -1)
	{
		std::cout << "Invalid role!" << std::endl;
		return;
	}

	const std::priority_queue<Player>* queueToDisplay;
	if (isPrimary)
	{
		queueToDisplay = &mainRolesQueue[roleIndex];
	}
	else
	{
		queueToDisplay = &secondaryRolesQueue[roleIndex];
	}
	
	std::priority_queue<Player> tempQueue = *queueToDisplay;
	std::cout << "Players in " << (isPrimary ? "Primary" : "Secondary") << " Role Queue for Role " << role << ":\n";
	
	if (tempQueue.empty())
	{
		std::cout << "No players in this queue.\n";
		return;
	}
	
	while (!tempQueue.empty())
	{
		const Player& player = tempQueue.top();
		player.displayInfo();
		std::cout << "-----------------------\n";
		tempQueue.pop();
	}
}

bool Queue::isEmpty() const
{
	for (size_t i = 0; i < 5; ++i)
	{
		if (!mainRolesQueue[i].empty() || !secondaryRolesQueue[i].empty())
		{
			return false;
		}
	}
	return true;
}

int Queue::getTotalPlayers() const
{
	int total = 0;
	for (size_t i = 0; i < 5; ++i)
	{
		total += mainRolesQueue[i].size();
	}
	return total;
}

void Queue::clearAllQueues()
{
	// Clear all main role queues
	for (auto& queue : mainRolesQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}
	
	// Clear all secondary role queues
	for (auto& queue : secondaryRolesQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}
}