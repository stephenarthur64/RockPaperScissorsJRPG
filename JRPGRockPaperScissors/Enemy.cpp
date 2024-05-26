/// <summary>
/// @author Stephen Arthur C00295678
/// @date March 2024
/// </summary>

#include "Enemy.h"
#include <iostream>

/// <summary>
/// Enemy constructor
/// </summary>
Enemy::Enemy()
{
	setupEnemy();
	randomStats();


}

/// <summary>
/// Sets up the randomised stats of the Enemy
/// </summary>
void Enemy::randomStats()
{
	m_hp = (rand() % 101) + 30;
	m_maxHp = m_hp;
	m_str = (rand() % 101) + 20;
	m_def = (rand() % 101) + 20;

	if (m_str < 30 && m_def < 100)
	{
		m_def += 20;
	}
	if (m_def < 30 && m_str < 100)
	{
		m_str += 20;
	}
	if (m_str > 100 && m_def >= 50)
	{
		m_def -= 30;
	}
	if (m_def > 100 && m_str >= 50)
	{
		m_str -= 30;
	}
	m_enemyType = (rand() % 3);
	setupIcon(m_enemyType);

}

/// <summary>
/// Returns the current strength of the Enemy
/// </summary>
int Enemy::getStr()
{
	return m_str;
}

/// <summary>
/// Returns the current defence of the Enemy
/// </summary>
int Enemy::getDef()
{
	return m_def;
}

/// <summary>
/// Returns the current health of the Enemy
/// </summary>
int Enemy::getHp()
{
	return m_hp;
}

/// <summary>
/// Returns the current location of the Enemy sprite
/// </summary>
sf::Vector2f Enemy::getLocation()
{
	return m_location;
}

/// <summary>
/// Sets the value for Enemy strength
/// </summary>
void Enemy::setStr(int t_newStr)
{
	m_str = t_newStr;
}

/// <summary>
/// Sets the value for Enemy defence
/// </summary>
void Enemy::setDef(int t_newDef)
{
	m_def = t_newDef;
}

/// <summary>
/// Sets the value for  Enemy health
/// </summary>
void Enemy::setHp(int t_newHp)
{
	m_hp = t_newHp;
}

/// <summary>
/// Returns the Enemy's sprite
/// </summary>
sf::Sprite Enemy::getSprite()
{
	return m_enemySprite;
}

/// <summary>
/// Returns the sprite for the type icon
/// </summary>
sf::Sprite Enemy::getIcon()
{
	return m_typeIcon;
}

/// <summary>
/// Sets up the type icon
/// </summary>
void Enemy::setupIcon(int t_type)
{
	if (ROCK == t_type)
	{
		m_typeIcon.setTexture(m_rockTexture);
		m_typeIcon.setScale(0.1, 0.1);
	}
	if (PAPER == t_type)
	{
		m_typeIcon.setTexture(m_paperTexture);
		m_typeIcon.setScale(0.1, 0.1);
	}
	if (SCISSORS == t_type)
	{
		m_typeIcon.setTexture(m_scissorsTexture);
		m_typeIcon.setScale(0.17, 0.17);
	}
}

/// <summary>
/// Sets up the Enemy sprite
/// </summary>
void Enemy::setupEnemy()
{
	if (!m_enemyTexture.loadFromFile("ASSETS\\IMAGES\\JackFrostSheet.png"))
	{
		std::cout << "Enemy texture error\n";
	}
	m_enemySprite.setTexture(m_enemyTexture);
	m_enemySprite.setTextureRect(sf::IntRect(0, 0, 34, 50));
	m_enemySprite.setPosition(m_location);
	m_enemySprite.setScale(4, 4);

	if (!m_rockTexture.loadFromFile("ASSETS\\IMAGES\\rock_icon.png"))
	{
		std::cout << "rock texture\n";
	}
	if (!m_paperTexture.loadFromFile("ASSETS\\IMAGES\\paper_icon.png"))
	{
		std::cout << "paper texture\n";
	}
	if (!m_scissorsTexture.loadFromFile("ASSETS\\IMAGES\\scissors_icon.png"))
	{
		std::cout << "scissors texture\n";
	}
	m_typeIcon.setPosition(m_iconLocation);
}

/// <summary>
/// Updates the stat display with the Enemy's current stats
/// </summary>
std::string Enemy::updateStats()
{
	std::string message = "Str: " + std::to_string(m_str) + "\n Def: " + std::to_string(m_def) + "\n Hp: " + std::to_string(m_hp);

	return message;
}

/// <summary>
/// Returns the Enemy's current type
/// </summary>
int Enemy::getType()
{
	return m_enemyType;
}

/// <summary>
/// Returns the percentage of total health the Enemy currently has,
/// used for health bar
/// </summary>
float Enemy::percentageHp()
{
	return (m_hp / m_maxHp);
}

/// <summary>
/// Returns the percentage of total strength the Enemy currently has,
/// used for stat bar
/// </summary>
float Enemy::percentageStr()
{
	return (m_str / 120.0f);
}

/// <summary>
/// Returns the percentage of total defence the Enemy currently has,
/// used for stat bar
/// </summary>
float Enemy::percentageDef()
{
	return (m_def / 120.0f);
}

/// <summary>
/// Animates the Enemy sprite
/// </summary>
void Enemy::animateEnemy()
{
	int frame;
	const int ROWS = 2;
	const int COLS = 9;
	int row = 0;
	int column;
	const float FRAME_WIDTH = 32;
	const int FRAME_HEIGHT = 50;

	m_enemyFrameCounter += m_enemyFrameIncriment;
	frame = static_cast<int>(m_enemyFrameCounter);

	if (frame >= ENEMY_FRAME)
	{
		frame = 0;
		m_enemyFrameCounter = 0.0f;
	}
	

	if (frame != m_enemyFrame)
	{
		m_enemyFrame = frame;
		column = frame % COLS;
		if (column >= 6)
		{
			row = 1;
		}
		
		m_enemySprite.setTextureRect(sf::IntRect(column * FRAME_WIDTH, FRAME_HEIGHT * row, FRAME_WIDTH, FRAME_HEIGHT));
	}
}

/// <summary>
/// Animates the Enemy sprite when the enemy is damaged
/// </summary>
void Enemy::animateDamageEnemy()
{
	int frame;
	const int ROWS = 4;
	const int COLS = 3;
	float row = 4.5;
	int column;
	const float FRAME_WIDTH = 44;
	const int FRAME_HEIGHT = 50;

	m_enemyFrameCounter += m_enemyFrameIncriment;
	frame = static_cast<int>(m_enemyFrameCounter);

	if (frame >= ENEMY_FRAME)
	{
		frame = 0;
		m_enemyFrameCounter = 0.0f;
	}


	if (frame != m_enemyFrame)
	{
		m_enemyFrame = frame;
		column = frame % COLS;
		

		m_enemySprite.setTextureRect(sf::IntRect(column * FRAME_WIDTH, FRAME_HEIGHT * row, FRAME_WIDTH, FRAME_HEIGHT));
	}
}



