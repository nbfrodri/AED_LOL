#include "Queue.h"
#include <iostream>

Queue::Queue()
{
	// Initialize vectors for 5 roles: T=0, J=1, M=2, A=3, S=4
	mainRolesQueue.resize(5);
	secondaryRolesQueue.resize(5);
}

void Queue::enqueuePlayerToRoleQueue(const Player& player)
{
	// Queue[] is indexed as T=0, J=1, M=2, A=3, S=4
	char mainRole = player.getPrimaryRole();
	char secondaryRole = player.getSecondaryRole();

	int mainRoleIndex = -1;
	int secondaryRoleIndex = -1;

	switch (mainRole)
	{
	case 'T':
		mainRoleIndex = 0;
		break;
	case 'J':
		mainRoleIndex = 1;
		break;
	case 'M':
		mainRoleIndex = 2;
		break;
	case 'A':
		mainRoleIndex = 3;
		break;
	case 'S':
		mainRoleIndex = 4;
		break;
	default:
		return; // Invalid role
	}

	switch (secondaryRole)
	{
	case 'T':
		secondaryRoleIndex = 0;
		break;
	case 'J':
		secondaryRoleIndex = 1;
		break;
	case 'M':
		secondaryRoleIndex = 2;
		break;
	case 'A':
		secondaryRoleIndex = 3;
		break;
	case 'S':
		secondaryRoleIndex = 4;
		break;
	default:
		return; // Invalid role
	}
	
	// Enqueue player into the appropriate role queues
	mainRolesQueue[mainRoleIndex].push(player);
	secondaryRolesQueue[secondaryRoleIndex].push(player);
}

void Queue::displayRoleQueue(char role, bool isPrimary) const
{
	int roleIndex = -1;
	switch (role)
	{
	case 'T':
		roleIndex = 0;
		break;
	case 'J':
		roleIndex = 1;
		break;
	case 'M':
		roleIndex = 2;
		break;
	case 'A':
		roleIndex = 3;
		break;
	case 'S':
		roleIndex = 4;
		break;
	default:
		std::cout << "Invalid role!" << std::endl;
		return; // Invalid role
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