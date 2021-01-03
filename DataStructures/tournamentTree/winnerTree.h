// abstract class winner tree
// all methods are pure virtual functions

#ifndef WINNER_TREE_
#define WINNER_TREE_

template<typename T>
class winnerTree
{
public:
	virtual ~winnerTree() {}
	virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
					// create winner tree with thePlayer[1:theNumberOfPlayers]
	virtual int winner() const = 0;
					// return index of winner
	virtual void rePlay(int thePlayer) = 0;
					// replay matches following a change in thePlayer
};
#endif // !WINNER_TREE_
