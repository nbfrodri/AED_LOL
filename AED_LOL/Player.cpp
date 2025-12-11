#include "Player.h"

// Constructors

Player::Player() : id(0), username(""), timeQueued(0.0), rank("Iron"), elo(0), winRate(0.0)
{
	roles[0] = 'U'; // U for Unassigned
	roles[1] = 'U';
	priority = 0; // Initial priority
	// TODO: Initialize match history when implementing game class
}

Player::Player(int id, const std::string& username, double timeQueued, int elo, char primaryRole, char secondaryRole)
	: id(id), username(username), timeQueued(timeQueued), elo(elo), winRate(0.0)
{
	priority = 0; // Initial priority
	roles[0] = primaryRole;
	roles[1] = secondaryRole;
	updateRank(); // Set rank based on initial ELO
	// TODO: Initialize match history when implementing game class
}

// Getters

int Player::getId() const
{
	return id;
}

std::string Player::getUsername() const
{
	return username;
}

std::string Player::getRank() const
{
	return rank;
}

int Player::getElo() const
{
	return elo;
}

char Player::getPrimaryRole() const
{
	return roles[0];
}

char Player::getSecondaryRole() const
{
	return roles[1];
}

double Player::getWinRate() const
{
	return winRate;
}

double Player::getTimeQueued() const
{
	return timeQueued;
}

int Player::getPriority() const
{
	return priority;
}

// Setters

void Player::setRank(const std::string& rank)
{
	this->rank = rank;
}

void Player::setElo(int elo)
{
	this->elo = elo;
}

void Player::setWinRate(double winRate)
{
	this->winRate = winRate;
}

// Other methods

void Player::displayInfo() const
{
	std::cout << "Player ID: " << id << "\n";
	std::cout << "Username: " << username << "\n";
	std::cout << "Rank: " << rank << "\n";
	std::cout << "ELO: " << elo << "\n";
	std::cout << "Win Rate: " << winRate << "%\n";
	std::cout << "Primary Role: " << roles[0] << "\n";
	std::cout << "Secondary Role: " << roles[1] << "\n";
	std::cout << "Time Queued: " << timeQueued << " seconds\n";
	std::cout << "Priority: " << priority << "\n";
	// TODO: Display match history when implementing game class
}

void Player::updateRank()
{
	for (int i = 9; i >= 0; --i) // Start from highest rank
	{
		if (elo >= rankRanges[i]) // Check if ELO is within the range for this rank
		{
			rank = ranks[i];
			return;
		}
	}
}

void Player::calculatePriority(char rol1, char rol2)
{
	priority = static_cast<int>(timeQueued); // Base priority on time queued
	// Increase priority if player's roles match the desired roles
	if (roles[0] == rol1 || roles[1] == rol1)
	{
		priority += 30; // Bigger boost for matching primary role (+half minute equivalent)
	}
	if (roles[0] == rol2 || roles[1] == rol2)
	{
		priority += 15; // Smaller boost for matching secondary role (+15 seconds equivalent)
	}
}

// Operator overloads

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	os << player.id << "," << player.username << "," << player.timeQueued << "," << player.elo << "," << player.roles[0] << "," << player.roles[1];
	return os;
}

std::istream& operator>>(std::istream& is, Player& player)
{
	std::string line;
	if (std::getline(is, line))
	{
		std::istringstream ss(line);
		std::string token;
		std::getline(ss, token, ',');
		player.id = std::stoi(token);
		std::getline(ss, token, ',');
		player.username = token;
		std::getline(ss, token, ',');
		player.timeQueued = std::stod(token);
		std::getline(ss, token, ',');
		player.elo = std::stoi(token);
		std::getline(ss, token, ',');
		player.roles[0] = token[0];
		std::getline(ss, token, ',');
		player.roles[1] = token[0];
		player.updateRank(); // Update rank based on ELO
	}
	return is;
}

bool operator<(const Player& p1, const Player& p2)
{
	return p1.getPriority() < p2.getPriority(); // Higher priority value means higher priority
}