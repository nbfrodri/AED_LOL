#include "Player.h"
#include <iomanip>
#include <vector>

// Constructors

Player::Player() : id(0), username(""), timeQueued(0.0), rank("Iron"), elo(0), winRate(0.0), totalMatches(0), totalWins(0)
{
	roles[0] = 'U'; // U for Unassigned
	roles[1] = 'U';
	priority = 0; // Initial priority
	// matchHistory is automatically initialized as empty stack
}

Player::Player(int id, const std::string& username, double timeQueued, int elo, char primaryRole, char secondaryRole)
	: id(id), username(username), timeQueued(timeQueued), elo(elo), winRate(0.0), totalMatches(0), totalWins(0)
{
	priority = 0; // Initial priority
	roles[0] = primaryRole;
	roles[1] = secondaryRole;
	updateRank(); // Set rank based on initial ELO
	// matchHistory is automatically initialized as empty stack
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

int Player::getTotalMatches() const
{
	return totalMatches;
}

int Player::getTotalWins() const
{
	return totalWins;
}

const std::stack<MatchResult>& Player::getMatchHistory() const
{
	return matchHistory;
}

// Match history methods

void Player::addMatchResult(int matchId, bool won, int eloChange, const std::string& matchRank)
{
	MatchResult result;
	result.matchId = matchId;
	result.won = won;
	result.eloChange = eloChange;
	result.opponentRank = matchRank;
	
	matchHistory.push(result);
	
	// Use recursive method to recalculate win rate from entire history
	calculateWinRateRecursive();
}

void Player::calculateWinRate()
{
	if (totalMatches == 0)
	{
		winRate = 0.0;
	}
	else
	{
		winRate = (static_cast<double>(totalWins) / static_cast<double>(totalMatches)) * 100.0;
	}
}

// Recursive helper function to count wins/losses from match history stack
std::pair<int, int> countWinsLossesRecursive(std::stack<MatchResult> historyStack)
{
	// Base case: if stack is empty
	if (historyStack.empty())
	{
		return {0, 0}; // {wins, totalMatches}
	}
	
	// Get the top match result
	MatchResult currentMatch = historyStack.top();
	historyStack.pop();
	
	// Recursively process the rest of the stack
	auto [wins, matches] = countWinsLossesRecursive(historyStack);
	
	// Add current match to the count
	if (currentMatch.won)
	{
		return {wins + 1, matches + 1};
	}
	else
	{
		return {wins, matches + 1};
	}
}

void Player::calculateWinRateRecursive()
{
	if (matchHistory.empty())
	{
		winRate = 0.0;
		totalMatches = 0;
		totalWins = 0;
	}
	else
	{
		// Use recursive function to calculate wins and total matches
		auto [wins, matches] = countWinsLossesRecursive(matchHistory);
		
		totalWins = wins;
		totalMatches = matches;
		
		if (totalMatches > 0)
		{
			winRate = (static_cast<double>(totalWins) / static_cast<double>(totalMatches)) * 100.0;
		}
		else
		{
			winRate = 0.0;
		}
	}
}

void Player::displayMatchHistory() const
{
	std::cout << "Match History for " << username << " (Last 20 matches):\n";
	std::cout << "==================================================\n";
	
	if (matchHistory.empty())
	{
		std::cout << "No matches played yet.\n";
		return;
	}
	
	// Create a temporary stack to display history without modifying the original
	std::stack<MatchResult> tempHistory = matchHistory;
	std::vector<MatchResult> recentMatches;
	
	// Get the last 5 matches
	int count = 0;
	while (!tempHistory.empty() && count < 20)
	{
		recentMatches.push_back(tempHistory.top());
		tempHistory.pop();
		count++;
	}
	
	// Display matches (most recent first)
	for (const auto& match : recentMatches)
	{
		std::cout << "Match ID: " << match.matchId
				  << " | " << (match.won ? "WIN" : "LOSS")
				  << " | ELO Change: " << (match.eloChange >= 0 ? "+" : "") << match.eloChange
				  << " | Rank: " << match.opponentRank << "\n";
	}
	
	std::cout << "==================================================\n";
	std::cout << "Total Matches: " << totalMatches << " | Total Wins: " << totalWins 
			  << " | Win Rate: " << std::fixed << std::setprecision(1) << winRate << "%\n";
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

void Player::setTotalMatches(int total)
{
	this->totalMatches = total;
}

void Player::setTotalWins(int wins)
{
	this->totalWins = wins;
}

void Player::setTimeQueued(double timeQueued)
{
	this->timeQueued = timeQueued;
}

// Other methods

void Player::displayInfo() const
{
	std::cout << "Player ID: " << id << "\n";
	std::cout << "Username: " << username << "\n";
	std::cout << "Rank: " << rank << "\n";
	std::cout << "ELO: " << elo << "\n";
	std::cout << "Win Rate: " << std::fixed << std::setprecision(1) << winRate << "%\n";
	std::cout << "Primary Role: " << roles[0] << "\n";
	std::cout << "Secondary Role: " << roles[1] << "\n";
	std::cout << "Time Queued: " << timeQueued << " seconds\n";
	std::cout << "Priority: " << priority << "\n";
	std::cout << "Total Matches: " << totalMatches << " | Total Wins: " << totalWins << "\n";
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
	os << player.id << "," << player.username << "," << player.timeQueued << "," 
	   << player.elo << "," << player.roles[0] << "," << player.roles[1];
	return os;
}

std::istream& operator>>(std::istream& is, Player& player)
{
	std::string line;
	if (std::getline(is, line))
	{
		std::istringstream ss(line);
		std::string token;
		
		// Read basic player data (original format)
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
		
		// Match statistics are NOT read from file - they start fresh each session
		player.totalMatches = 0;
		player.totalWins = 0;
		player.calculateWinRate(); // Will be 0.0 since no matches yet
		
		player.updateRank(); // Update rank based on ELO
	}
	return is;
}

bool operator<(const Player& p1, const Player& p2)
{
	return p1.getPriority() < p2.getPriority(); // Higher priority value means higher priority
}