#include "Player.h"

Player::Player(int color, bool *tempIsCheck, bool *tempCheckMat, bool *tempWillBeCheck) : playerColor(color), isCheck(tempIsCheck), checkMat(tempCheckMat), willBeCheck(tempWillBeCheck)
{}

void Player::deleteFirstPossibleMove()
{
	PossibleMoves.pop_front();
}

Player::~Player()
{}