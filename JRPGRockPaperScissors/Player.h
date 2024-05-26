/// <summary>
/// @author Stephen Arthur C00295678
/// @date March 2024
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include "Gobals.h"

class Player {

	int m_hp; //Player's health
	int m_str; //Player's strength
	int m_def; //player's defence
	int m_playerType{ 3 }; //Type of Player's attack

	

public:

	Player();
	void setupSprite();
	int getStr();
	int getDef();
	int getHp();
	std::string updateStats();
	void setStr(int t_newStr);
	void setDef(int t_newDef);
	void setHp(int t_newHp);
	int getType();
	void setType(int t_newType);
	float percentageHp();
	float percentageStr();
	float percentageDef();
};