/// <summary>
/// @author Stephen Arthur C00295678
/// @date March 2024
/// </summary>

#include "Player.h"
#include <iostream>


/// <summary>
/// Player Constructor
/// </summary>
Player::Player()
{
	m_hp = 100;
	m_str = (rand() % 51) + 50;
	m_def = (rand() % 51) + 50;
	setupSprite();
}

void Player::setupSprite()
{
	
}

/// <summary>
/// Returns the current strength value of the Player
/// </summary>
int Player::getStr()
{
	return m_str;
}

/// <summary>
/// Returns the current Defence value of the Player
/// </summary>
int Player::getDef()
{
	return m_def;
}

/// <summary>
/// Returns the current health of the Player
/// </summary>
int Player::getHp()
{
	return m_hp;
}

/// <summary>
/// Updates the Player's stats display with
/// their new current values
/// </summary>
std::string Player::updateStats()
{
	std::string message = std::to_string(m_str) + " :Str\n" + std::to_string(m_def)+ " :Def\n" + std::to_string(m_hp) + " :Hp\n";

	return message;
}

/// <summary>
/// Sets a new value for Player strength
/// </summary>
void Player::setStr(int t_newStr)
{
	m_str = t_newStr;
}

/// <summary>
/// Sets a new value for Player defence
/// </summary>
void Player::setDef(int t_newDef)
{
	m_def = t_newDef;
}

/// <summary>
/// Sets a new value for Player health
/// </summary>
void Player::setHp(int t_newHp)
{
	m_hp = t_newHp;
	std::cout << "set hp";
}

/// <summary>
/// Returns the Player's current type i.e Rock, Paper or Scissors
/// </summary>
int Player::getType()
{
	return m_playerType;
}

/// <summary>
/// Sets the attack type of the Player, i.e Rock, Paper or Scissors
/// </summary>
void Player::setType(int t_newType)
{
	m_playerType = t_newType;
	std::cout << " type " << t_newType << std::endl;
}

/// <summary>
/// Returns the percentage of total health the Player has, used for health bar
/// </summary>
float Player::percentageHp()
{
	return m_hp / 100.0f;
}

/// <summary>
/// Returns the percentage of total strength the Player has, used for stat bar
/// </summary>
float Player::percentageStr()
{
	return m_str / 100.0f;
}

/// <summary>
/// Returns the percentage of total defence the Player has, used for stat bar
/// </summary>
float Player::percentageDef()
{
	return m_def / 100.0f;
}
