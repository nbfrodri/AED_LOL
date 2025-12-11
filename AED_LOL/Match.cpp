#include "Match.h"

Match::Match() : valid(false)
{
	srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

	// Using random, stablish a random number between 15 and 30 for eloWin and eloLose
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