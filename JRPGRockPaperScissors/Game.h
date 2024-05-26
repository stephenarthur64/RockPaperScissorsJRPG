/// <summary>
/// author Stephen Arthur C00295678
/// 01/03/24
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Gobals.h"
#include "Player.h"
#include <ctime>
#include <cstdlib>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	Enemy jackFrost;
	Player myPlayer;



private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void playerActions();
	void enemyActions();
	void setupFontAndText();
	void setupStats();
	void setupStatBars();
	void updateText();
	void setupSprite();
	void setupButtons();
	void resetEnemy();
	void resetGame();
	void damageCalc(int t_typeAttacker, int t_typeDefender, int t_attackStr, int t_defenderDef);
	int criticalMissHit();
	void checkButtonBorders(sf::Window& t_window);
	void checkMouseLocation(sf::Window& t_window);


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_enemyStats; // Text for enemy stats
	sf::Text m_playerStats; //Text for player stats
	sf::Text m_fightText; // Text for fight button
	sf::Text m_blockText; // Text for block button
	sf::Text m_fleeText; // Text for flee button
	sf::Text m_enemyTurn; // Text for during the enemy's turn
	sf::Text m_okayText; //Text for the okay button
	sf::Text m_gameOverText; //Text for game over
	sf::Text m_tryAgainText; //Text for try again option
	sf::Text m_quitGameText; //Text for quit game option
	sf::Text m_missCrit; //Text for when the Player lands a crit or miss
	sf::Text m_backInstructions; //Text to tell Player how to quit FIGHT menu

	sf::Sprite m_damageFire; //Sprite for damage taken graphic
	sf::Texture m_fireTexture;//Texture for damage taken graphic
	sf::Sprite m_damageImage; //Image for when the Player Damages the enemy
	sf::Texture m_rockTexture; //Texture for Rock attacks
	sf::Texture m_scissorsTexture; //Texture for scissors attacks
	sf::Texture m_paperTexture; //Texture for paper attacks

	sf::RectangleShape m_background; //used to colour background
	sf::RectangleShape m_fight; // Rectangle for FIGHT button
	sf::RectangleShape m_block; // Rectangle for BLOCK button
	sf::RectangleShape m_flee; //Rectangle for FLEE button
	sf::RectangleShape m_fightBack; //Rectangle for behing FIGHT button
	sf::RectangleShape m_blockBack; //Rectangle for behing BLOCK button
	sf::RectangleShape m_fleeBack; //Rectangle for behing FLEE button
	sf::RectangleShape m_buttonBack; //Rectangle for behind the buttons
	sf::RectangleShape m_tryAgainBack; //Rectangle for behind the Retry button
	sf::RectangleShape m_okayBack; //Rectangle for behind the Okay button
	sf::RectangleShape m_quitBack; //Rectangle for behind the Quit button
	sf::RectangleShape m_okayButton; //Button to progress text
	sf::RectangleShape m_enemyHp; // bar for enemy hp
	sf::RectangleShape m_enemyHpBack; //bar for the back of enemyHp
	sf::RectangleShape m_enemyStr; // bar for enemy str
	sf::RectangleShape m_enemyDef; // bar for enemy def
	sf::RectangleShape m_playerHp; //bar for player hp
	sf::RectangleShape m_playerHpBack; //bar for the back of player hp
	sf::RectangleShape m_playerStr; //bar for player str
	sf::RectangleShape m_playerDef; //Bar for player def
	sf::RectangleShape m_tryAgain; //Rectangle for the try again button
	sf::RectangleShape m_quit; //Rectangle for quit button

	std::string m_enemyDamage; //Damage enemy has dealt (used for text in enemy turn)

	sf::Vector2i mouseLocation; //Vector for mouse location

	int m_ticks{ 0 }; //Increases every frame in order to count seconds

	bool m_canFight = true; //bool for if the player can fight
	bool m_fleeCheck = false; //did player flee from enemy
	bool m_blockCheck = false; //did the player select block
	bool m_fightCheck = false; //did player select fight
	bool m_rockCheck = false; //did player choose rock
	bool m_paperCheck = false; //did player choose paper
	bool m_scissorsCheck = false; //did player choose scissors
	bool m_okayCheck = true; //did player click okay
	bool m_tryAgainCheck = false; //did the player click restart
	bool respawnEnemy{ false }; //bool for if the enemy needs to be respawned
	bool m_playerTurn{ true }; //bool for if it is the player's turn
	bool m_playerDamaged{ false };//bool for if player has been damaged
	bool m_graphics{ true };//bool to activate graphics
	bool m_enemyDamaged{ false };//bool for if enemy has been damaged
	bool m_gameOver{ false };//bool for if the game is in game over state
	bool m_mouseFight{ false };//is mouse hovered over fight button?
	bool m_mouseBlock{ false };//is mouse hovered over block button?
	bool m_mouseFlee{ false };//is mouse hovered over flee button?
	bool m_mouseTryAgain{ false };//is moused hoverd over try again button?
	bool m_mouseQuit{ false };//is mouse hovered over quit button?
	bool m_mouseOkay{ false };//is mouse hovered over okay button?
	bool m_crit{ false };//did the attacker land a critical hit?
	bool m_miss{ false };//did the attack miss?
	bool m_fightMenu{ false };//is the FIGHT menu open? (for instructions)
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

