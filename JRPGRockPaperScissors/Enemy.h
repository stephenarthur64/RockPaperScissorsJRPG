/// <summary>
/// @author Stephen Arthur C00295678
/// @date March 2024
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include "Gobals.h"

class Enemy
{
	int m_str; //Strength of enemy
	int m_def; //Defence of enemy
	int m_hp; //Health of enemy
	float m_maxHp; //Maximum health of enemy
	sf::Vector2f m_location{320.0f, 175.0f}; //Location of enemy
	sf::Vector2f m_iconLocation{450.0f, 200.0f}; //location of type icon
	sf::Sprite m_enemySprite; //Sprite for enemy
	sf::Texture m_enemyTexture; //Texture for enemy
	sf::Sprite m_typeIcon; //Sprite for type icon
	sf::Texture m_rockTexture; //Texture for rock icon
	sf::Texture m_paperTexture; //Texture for paper icon
	sf::Texture m_scissorsTexture; // texture for scissors icon
	int m_enemyType; //current enemy type
	int m_enemyFrame = -1;
	const int ENEMY_FRAME = 15;
	float m_enemyFrameCounter = 0.0f;
	float m_enemyFrameIncriment = 0.2f;

public:
	Enemy();
	void randomStats();
	int getStr();
	int getDef();
	int getHp();
	sf::Vector2f getLocation();
	void setStr(int t_newStr);
	void setDef(int t_newDef);
	void setHp(int t_newHp);
	sf::Sprite getSprite();
	sf::Sprite getIcon();
	void setupIcon(int t_type);
	void setupEnemy();
	std::string updateStats();
	int getType();
	float percentageHp();
	float percentageStr();
	float percentageDef();
	void animateEnemy();
	void animateDamageEnemy();


};