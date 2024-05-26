/// <summary>
/// @author Stephen Arthur C00295678
/// @date March 2024
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDE, SCREEN_HEIGHT, 32U }, "JRPG Rock Paper Scissors Demo" },
	m_exitGame{false} //when true game will exit
{


	setupFontAndText(); // load font 
	setupStats(); 
	setupSprite(); // load texture
	setupButtons();
	setupStatBars();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}

		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			checkButtonBorders(m_window);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::BackSpace == t_event.key.code)
	{
		m_fightCheck = false;
	}
	if (sf::Keyboard::F1 == t_event.key.code)
	{
		m_graphics = !m_graphics;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_playerTurn && !m_gameOver)
	{
		playerActions();
	}

	if (!m_playerTurn)
	{
		m_ticks++;
	}

	if (!m_playerTurn && !m_gameOver && m_ticks >= 120)
	{
		m_ticks = 0;
		m_enemyDamaged = false;
		enemyActions();
	}
	checkMouseLocation(m_window);
	if (jackFrost.getHp() < 0)
	{
		resetEnemy();
	}
	if (myPlayer.getHp() < 0)
	{
		m_enemyDamaged = false;
		m_gameOver = true;
		m_okayCheck = true;
		//std::cout << "game over\n";
		if (m_tryAgainCheck)
		{
			resetGame();
			m_tryAgainCheck = false;
		}
	}
	if (!m_enemyDamaged)
	{
		jackFrost.animateEnemy();
	}
	if (m_enemyDamaged && !m_miss)
	{
		jackFrost.animateDamageEnemy();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	//Background
	m_window.draw(m_background);
	//Enemy Sprite display
	m_window.draw(jackFrost.getSprite());
	//Update text values for stats
	updateText();
	//Stats for Player and Enemy
	m_window.draw(m_enemyStats);
	m_window.draw(m_playerStats);
	//Box behind buttons
	m_window.draw(m_buttonBack);
	
	//Back button instructions
	if (m_fightCheck)
	{
		m_window.draw(m_backInstructions);
	}

	//Button hightlights
	if(m_mouseFight && !m_gameOver)
	{
		m_window.draw(m_fightBack);
	}
	if (m_mouseBlock && !m_gameOver)
	{
		m_window.draw(m_blockBack);
	}
	if (m_mouseFlee && !m_gameOver)
	{
		m_window.draw(m_fleeBack);
	}
	
	if (m_playerTurn && !m_blockCheck && !m_gameOver) //If default screen
	{
		//Fight button
		m_window.draw(m_fight);
		m_window.draw(m_fightText);
		//Block button
		m_window.draw(m_block);
		m_window.draw(m_blockText);
		//Flee button
		m_window.draw(m_flee);
		m_window.draw(m_fleeText);
	}
	//Type icon for Enemy type
	m_window.draw(jackFrost.getIcon());
	//If Player hasn't pressed Okay button
	if (!m_okayCheck)
	{
		//Enemy turn info
		m_window.draw(m_enemyTurn);
		//Okay button
		if (m_mouseOkay)
		{
			m_window.draw(m_okayBack);
		}
		m_window.draw(m_okayButton);
		m_window.draw(m_okayText);
	}
	if (m_graphics) //if graphics enabled
	{
		//Enemy stat display
		m_window.draw(m_enemyHpBack);
		m_window.draw(m_enemyHp);
		m_window.draw(m_enemyStr);
		m_window.draw(m_enemyDef);
		//Player stat display
		m_window.draw(m_playerHpBack);
		if (!m_gameOver) //Prevents health bar going backwards
		{
			m_window.draw(m_playerHp);
		}
		m_window.draw(m_playerStr);
		m_window.draw(m_playerDef);

	}
	if (m_playerDamaged && !m_miss)
	{
		//Damage on player graphic
		m_window.draw(m_damageFire);
	}
	//Displays the crit or miss message
	if (m_miss || m_crit)
	{
		m_window.draw(m_missCrit);
	}
	if (m_gameOver)
	{
		//Button highlights
		checkMouseLocation(m_window);
		if (m_mouseTryAgain)
		{
			m_window.draw(m_tryAgainBack);
		}
		if (m_mouseQuit)
		{
			m_window.draw(m_quitBack);
		}
		//Retry button
		m_window.draw(m_tryAgain);
		//Quit button
		m_window.draw(m_quit);
		//Text for Game Over screen
		m_window.draw(m_gameOverText);
		m_window.draw(m_tryAgainText);
		m_window.draw(m_quitGameText);
	}
	//Displays the graphic for when the player attacks the enemy
	if (!m_playerTurn && m_enemyDamaged && !m_miss)
	{
		m_window.draw(m_damageImage);
	}
	
	m_window.display();
}

/// <summary>
/// Manages the actions the Player can take on their turn
/// </summary>
void Game::playerActions()
{
	checkMouseLocation(m_window);
	m_playerDamaged = false;
	m_enemyDamaged = false;
	m_miss = false;
	m_crit = false;
	if (!m_blockCheck)
	{
		if (m_fleeCheck)
		{
			resetEnemy();
			m_fleeCheck = false;
		}
		if (myPlayer.getType() < 3)
		{
			std::cout << "player dam " << myPlayer.getType() << std::endl;;
			damageCalc(myPlayer.getType(), jackFrost.getType(), myPlayer.getStr(), jackFrost.getDef());
			myPlayer.setType(4);
			std::cout << "player dam " << myPlayer.getType() << std::endl;;
			m_playerTurn = false;
		}
	}
	if (m_blockCheck)
	{
		m_playerTurn = false;
		m_blockCheck = false;
	}
}

/// <summary>
/// Manages the actions the enemy can take on their turn
/// </summary>
void Game::enemyActions()
{
	m_miss = false;
	m_crit = false;
	m_mouseFight = false;
	m_mouseBlock = false;
	m_mouseFlee = false;
	m_okayCheck = false;
	if (!m_playerDamaged)
	{
		std::cout << "enemy dam" << m_playerDamaged << std::endl;
		damageCalc(jackFrost.getType(), myPlayer.getType(), jackFrost.getStr(), myPlayer.getDef());
	}
	m_playerDamaged = true;
	if (m_okayCheck)
	{
		m_canFight = true;
	}

}

/// <summary>
/// load the font and setup text messages for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_fightText.setFont(m_ArialBlackfont);
	m_fightText.setString("FIGHT");
	m_fightText.setPosition(70, 450);
	m_fightText.setCharacterSize(47U);
	m_fightText.setFillColor(sf::Color::White);

	m_blockText.setFont(m_ArialBlackfont);
	m_blockText.setString("BLOCK");
	m_blockText.setPosition(320, 450);
	m_blockText.setCharacterSize(47U);
	m_blockText.setFillColor(sf::Color::White);

	m_fleeText.setFont(m_ArialBlackfont);
	m_fleeText.setString("FLEE");
	m_fleeText.setPosition(570, 450);
	m_fleeText.setCharacterSize(47U);
	m_fleeText.setFillColor(sf::Color::White);

	m_enemyTurn.setFont(m_ArialBlackfont);
	m_enemyTurn.setCharacterSize(40U);
	m_enemyTurn.setPosition(0, BUTTON_Y - 50);

	m_okayText.setFont(m_ArialBlackfont);
	m_okayText.setString("Okay");
	m_okayText.setOrigin(100, 0);
	m_okayText.setCharacterSize(40U);
	m_okayText.setPosition(440, 535);

	m_gameOverText.setFont(m_ArialBlackfont);
	m_gameOverText.setString("Game Over!");
	m_gameOverText.setCharacterSize(60U);
	m_gameOverText.setPosition(220, 20);
	m_gameOverText.setOutlineColor(sf::Color::Black);
	m_gameOverText.setOutlineThickness(5);
	m_gameOverText.setFillColor(sf::Color::Red);

	m_tryAgainText.setFont(m_ArialBlackfont);
	m_tryAgainText.setString("Restart");
	m_tryAgainText.setCharacterSize(45U);
	m_tryAgainText.setPosition(TRY_AGAIN_X + 7, TRY_AGAIN_Y + 10);
	m_tryAgainText.setOutlineColor(sf::Color::Black);
	m_tryAgainText.setOutlineThickness(2);

	m_quitGameText.setFont(m_ArialBlackfont);
	m_quitGameText.setString("Quit");
	m_quitGameText.setCharacterSize(45U);
	m_quitGameText.setPosition(TRY_AGAIN_X + 7, TRY_AGAIN_Y + 110);
	m_quitGameText.setOutlineColor(sf::Color::Black);
	m_quitGameText.setOutlineThickness(2);

	m_missCrit.setFont(m_ArialBlackfont);
	m_missCrit.setCharacterSize(40U);
	m_missCrit.setPosition(600, 200);
	m_missCrit.setOutlineColor(sf::Color::Black);
	m_missCrit.setOutlineThickness(2);
	m_missCrit.setString("test");

	m_backInstructions.setFont(m_ArialBlackfont);
	m_backInstructions.setCharacterSize(20U);
	m_backInstructions.setPosition(470, BUTTON_Y - 30);
	m_backInstructions.setOutlineColor(sf::Color::Black);
	m_backInstructions.setOutlineThickness(2);
	m_backInstructions.setString("Press <backspace> to cancel");

}

/// <summary>
/// Sets up the stat displays of the Enemy and Player
/// </summary>
void Game::setupStats()
{
	m_enemyStats.setFont(m_ArialBlackfont);
	m_enemyStats.setString(jackFrost.updateStats());
	m_enemyStats.setOrigin(30.0f, 0.0f);
	m_enemyStats.setPosition(jackFrost.getLocation() - sf::Vector2f {275.0f, 125.0f});
	m_enemyStats.setCharacterSize(30U);
	m_enemyStats.setOutlineColor(sf::Color::Red);
	m_enemyStats.setFillColor(sf::Color::Black);
	m_enemyStats.setOutlineThickness(3.0f);

	m_playerStats.setFont(m_ArialBlackfont);
	m_playerStats.setString(myPlayer.updateStats());
	m_playerStats.setOrigin(30.0f, 0.0f);
	m_playerStats.setPosition(SCREEN_WIDE - 110, 50.0f);
	m_playerStats.setCharacterSize(30U);
	m_playerStats.setOutlineColor(sf::Color::Green);
	m_playerStats.setOutlineThickness(3.0f);

	
}

/// <summary>
/// Sets up the stat bars for the stats display for the Enemy and Player
/// </summary>
void Game::setupStatBars()
{
	m_enemyHp.setPosition(90, 140);
	m_enemyHp.setSize(sf::Vector2f{200.0f, 25.0f});
	m_enemyHp.setFillColor(sf::Color::Red);
	m_enemyHp.setOutlineThickness(5);
	m_enemyHp.setOutlineColor(sf::Color::Black);

	m_enemyHpBack.setPosition(90, 135);
	m_enemyHpBack.setSize(sf::Vector2f{210.0f, 35.0f});
	m_enemyHpBack.setFillColor(sf::Color::Black);

	m_enemyStr.setPosition(80, 55);
	m_enemyStr.setSize(sf::Vector2f{200.0f, 25.0f});
	m_enemyStr.setFillColor(sf::Color::Red);
	m_enemyStr.setOutlineThickness(5);
	m_enemyStr.setOutlineColor(sf::Color::Black);

	m_enemyDef.setPosition(100, 100);
	m_enemyDef.setFillColor(sf::Color::Red);
	m_enemyDef.setOutlineThickness(5);
	m_enemyDef.setOutlineColor(sf::Color::Black);

	m_playerHp.setOrigin(200.0f, 0.0f);
	m_playerHp.setPosition(720, 140);
	m_playerHp.setSize(sf::Vector2f{200.0f, 25.0f});
	m_playerHp.setScale(0.5, 1);
	m_playerHp.setFillColor(sf::Color::Green);
	m_playerHp.setOutlineThickness(5);
	m_playerHp.setOutlineColor(sf::Color::Black);

	m_playerHpBack.setPosition(720, 135);
	m_playerHpBack.setSize(sf::Vector2f{210.0f, 35.0f});
	m_playerHpBack.setFillColor(sf::Color::Black);
	m_playerHpBack.setOrigin(200.0f, 0.0f);

	m_playerStr.setPosition(705, 55);
	m_playerStr.setSize(sf::Vector2f{200.0f, 25.0f});
	m_playerStr.setFillColor(sf::Color::Green);
	m_playerStr.setOutlineThickness(5);
	m_playerStr.setOutlineColor(sf::Color::Black);
	m_playerStr.setOrigin(200.0f, 0.0f);

	m_playerDef.setPosition(700, 100);
	m_playerDef.setSize(sf::Vector2f{200.0f, 25.0f});
	m_playerDef.setFillColor(sf::Color::Green);
	m_playerDef.setOutlineThickness(5);
	m_playerDef.setOutlineColor(sf::Color::Black);
	m_playerDef.setOrigin(200.0f, 0.0f);
}
/// <summary>
/// Updates the stats displays and the moves the Player can use
/// </summary>
void Game::updateText()
{
	m_enemyStats.setString(jackFrost.updateStats());
	m_playerStats.setString(myPlayer.updateStats());

	if (m_fightCheck)
	{
		m_fightText.setString("ROCK");
		m_blockText.setString("PAPER");
		m_fleeText.setString("SCISSORS");
		m_fleeText.setCharacterSize(35U);
		m_fleeText.setPosition(553, 460);
	}
	if (!m_fightCheck)
	{
		m_fightText.setString("FIGHT");
		m_blockText.setString("BLOCK");
		m_fleeText.setString("FLEE");
		m_fleeText.setCharacterSize(47U);
		m_fleeText.setPosition(565, 450);
	}
	m_enemyTurn.setString("The enemy has dealt " + m_enemyDamage + " damage");

	//Update enemy stat bars
	m_enemyHp.setSize(sf::Vector2f{((jackFrost.percentageHp())) * 200.0f, 25.0f});
	m_enemyStr.setSize(sf::Vector2f{(jackFrost.percentageStr() * 200.0f), 25.0f});
	m_enemyDef.setSize(sf::Vector2f{(jackFrost.percentageDef() * 200.0f), 25.0f});

	//Update player stat bars
	m_playerHp.setScale(myPlayer.percentageHp(), 1);
	m_playerStr.setScale(myPlayer.percentageStr(), 1);
	m_playerDef.setScale(myPlayer.percentageDef(), 1);
	if (myPlayer.getHp() < 100)
	{
		m_playerHp.setPosition(705, 140);
		m_playerHpBack.setPosition(700, 135);
	}
	if (myPlayer.getHp() < 10)
	{
		m_playerHp.setPosition(688, 140);
		m_playerHpBack.setPosition(682, 135);
	}
	if (myPlayer.getHp() == 100)
	{
		m_playerHp.setPosition(720, 140);
		m_playerHpBack.setPosition(720, 135);
	}
	if (myPlayer.getType() == ROCK)
	{
		m_damageImage.setTexture(m_rockTexture);
	}
	else if (myPlayer.getType() == PAPER)
	{
		m_damageImage.setTexture(m_paperTexture);
	}
	else if (myPlayer.getType() == SCISSORS)
	{
		m_damageImage.setTexture(m_scissorsTexture);
	}

	if (m_crit)
	{
		m_missCrit.setString("Critical!");
	}
	if (m_miss)
	{
		m_missCrit.setString("Miss!");
	}
}

/// <summary>
/// load textures and setup associated sprites
/// Currently only damage sprite is setup here
/// </summary>
void Game::setupSprite()
{
	sf::Color colour {0, 91, 127, 255};
	m_background.setFillColor(colour);
//	m_background.setPosition(0, 0);
	m_background.setSize(sf::Vector2f{SCREEN_WIDE, SCREEN_HEIGHT});

	if (!m_fireTexture.loadFromFile("ASSETS\\IMAGES\\firedamage.png"))
	{
		std::cout << "fire error\n";
	}
	m_damageFire.setTexture(m_fireTexture);
	m_damageFire.setPosition(0, BUTTON_Y - 200);
	m_fireTexture.setRepeated(true);
	m_damageFire.setTextureRect(sf::IntRect(0, 0, 1000, 165));

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

	m_damageImage.setScale(0.25, 0.25);
	m_damageImage.setPosition(100.0f, 200.0f);
}

/// <summary>
/// Sets up the buttons for Player choices
/// </summary>
void Game::setupButtons()
{
	//Fight button
	m_fight.setPosition(FIGHT_LEFT, BUTTON_Y);
	m_fight.setSize(sf::Vector2f{BUTTON_WIDTH, BUTTON_HEIGHT});
	m_fight.setFillColor(sf::Color::Black);

	//Block button
	m_block.setPosition(BLOCK_LEFT, BUTTON_Y);
	m_block.setSize(sf::Vector2f{BUTTON_WIDTH, BUTTON_HEIGHT});
	m_block.setFillColor(sf::Color::Black);

	//Flee button
	m_flee.setPosition(FLEE_LEFT, BUTTON_Y);
	m_flee.setSize(sf::Vector2f{BUTTON_WIDTH, BUTTON_HEIGHT});
	m_flee.setFillColor(sf::Color::Black);

	//Fight highlight
	m_fightBack.setPosition(FIGHT_LEFT - 10, BUTTON_Y - 10);
	m_fightBack.setSize(sf::Vector2f{BUTTON_WIDTH + 20, BUTTON_HEIGHT + 20});
	m_fightBack.setFillColor(sf::Color::Yellow);

	//Block highlight
	m_blockBack.setPosition(BLOCK_LEFT - 10, BUTTON_Y - 10);
	m_blockBack.setSize(sf::Vector2f{BUTTON_WIDTH + 20, BUTTON_HEIGHT + 20});
	m_blockBack.setFillColor(sf::Color::Yellow);

	//Flee highlight
	m_fleeBack.setPosition(FLEE_LEFT - 10, BUTTON_Y - 10);
	m_fleeBack.setSize(sf::Vector2f{BUTTON_WIDTH + 20, BUTTON_HEIGHT + 20});
	m_fleeBack.setFillColor(sf::Color::Yellow);

	//Behind buttons box
	m_buttonBack.setPosition(0, BUTTON_Y - 50);
	m_buttonBack.setSize(sf::Vector2f{SCREEN_WIDE, SCREEN_HEIGHT - (BUTTON_Y - 50)});
	m_buttonBack.setFillColor(sf::Color::Blue);

	//Okay button
	m_okayButton.setPosition(OKAY_LEFT, OKAY_Y);
	m_okayButton.setSize(sf::Vector2f{BUTTON_WIDTH, BUTTON_HEIGHT});
	m_okayButton.setFillColor(sf::Color::Black);

	//Okay hightlight
	m_okayBack.setPosition(OKAY_LEFT - 10, OKAY_Y - 10);
	m_okayBack.setSize(sf::Vector2f{BUTTON_WIDTH + 20, BUTTON_HEIGHT + 20});
	m_okayBack.setFillColor(sf::Color::Yellow);

	//Try again button
	m_tryAgain.setPosition(TRY_AGAIN_X, TRY_AGAIN_Y);
	m_tryAgain.setSize(sf::Vector2f{200, 75});
	m_tryAgain.setFillColor(sf::Color::Blue);
	m_tryAgain.setOutlineColor(sf::Color::Black);
	m_tryAgain.setOutlineThickness(2);

	//Quit button
	m_quit.setPosition(TRY_AGAIN_X, TRY_AGAIN_Y + 100);
	m_quit.setSize(sf::Vector2f{200, 75});
	m_quit.setFillColor(sf::Color::Blue);
	m_quit.setOutlineColor(sf::Color::Black);
	m_quit.setOutlineThickness(2);

	//Try again highlight
	m_tryAgainBack.setPosition(TRY_AGAIN_X - 10, TRY_AGAIN_Y - 10);
	m_tryAgainBack.setSize(sf::Vector2f{220, 95});
	m_tryAgainBack.setFillColor(sf::Color::Yellow);

	//Quit button highlight
	m_quitBack.setPosition(TRY_AGAIN_X - 10, TRY_AGAIN_Y + 90);
	m_quitBack.setSize(sf::Vector2f{220, 95});
	m_quitBack.setFillColor(sf::Color::Yellow);

}

/// <summary>
/// Resets the Enemy when they die
/// </summary>
void Game::resetEnemy()
{
	jackFrost.randomStats();
}

/// <summary>
/// Resets the game when the Player retries
/// </summary>
void Game::resetGame()
{
	m_gameOver = false;
	myPlayer.setHp(100);
	resetEnemy();
	myPlayer.setStr((rand() % 51) + 50);
	myPlayer.setDef((rand() % 51) + 50);
	m_playerTurn = true;
}

/// <summary>
/// Calculates the damage dealt by an attacker,
/// comparing attacker strength vs defender defence, then
/// setting the new reduced hp of defender
/// </summary>
void Game::damageCalc(int t_typeAttacker, int t_typeDefender, int t_attackStr, int t_defenderDef)
{
	float damage = 0;
	int weakMod = 1;
	int modifier;


	int randNum = (rand() % 6) + 5;

	switch (t_typeAttacker)
	{
	case ROCK:
		if (ROCK == t_typeDefender)
		{
			weakMod = 1;
		}
		else if (PAPER == t_typeDefender)
		{
			weakMod = 0.5;
		}
		else
		{
			weakMod = 2;
		}
		break;
	case PAPER:
		if (ROCK == t_typeDefender)
		{
			weakMod = 2;
		}
		else if (PAPER == t_typeDefender)
		{
			weakMod = 1;
		}
		else
		{
			weakMod = 0.5;
		}
		break;
	case SCISSORS:
		if (ROCK == t_typeDefender)
		{
			weakMod = 0.5;
		}
		else if (PAPER == t_typeDefender)
		{
			weakMod = 2;
		}
		else
		{
			weakMod = 1;
		}
		break;
	default:
		break;
	}
	
	damage = weakMod * ((t_attackStr / t_defenderDef) + randNum);
	if (damage < 1)
	{
		damage = 1;
	}
	damage *= criticalMissHit();


	if (m_playerTurn)
	{
		jackFrost.setHp(jackFrost.getHp() - damage);
		m_enemyDamaged = true;
		m_fightCheck = false;
		myPlayer.setType(4);
	}
	else
	{
		if (m_blockCheck)
		{
			damage *= 0.5;
		}
		myPlayer.setHp(myPlayer.getHp() - damage);
		m_enemyDamage = std::to_string((int)damage);
	}
}

/// <summary>
/// Generates a random number to determine if the attack misses,
/// hits normally or lands a critical hit
/// </summary>
int Game::criticalMissHit()
{
	int result;
	int randNum;

	randNum = (rand() % 20) + 1;

	if (5 >= randNum)
	{
		result = MISS;
		m_miss = true;
	}
	else if (15 <= randNum)
	{
		result = CRIT;
		m_crit = true;
	}
	else
	{
		result = HIT;
	}

	return result;
}

/// <summary>
/// Checks where the mouse button was clicked,
/// used to manage the various button options for Player
/// </summary>
void Game::checkButtonBorders(sf::Window& t_window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		mouseLocation = (sf::Mouse::getPosition(t_window));
		//For fighting buttons
		if (mouseLocation.y > BUTTON_Y && mouseLocation.y < BUTTON_FLOOR)
		{
			if (mouseLocation.x > FIGHT_LEFT && mouseLocation.x < FIGHT_RIGHT)
			{
				if (!m_fightCheck)
				{
					std::cout << "fight yup\n";
					m_fightCheck = true;
				}
				else
				{
					std::cout << "Rock yup\n";
					myPlayer.setType(ROCK);
					m_canFight = false;
				}
			}
			if (mouseLocation.x > BLOCK_LEFT && mouseLocation.x < BLOCK_RIGHT)
			{
				if (!m_fightCheck)
				{
					std::cout << "block yup\n";
					m_blockCheck = true;
				}
				else
				{
					std::cout << "Paper yup\n";
					myPlayer.setType(PAPER);
					m_canFight = false;

				}
			}
			if (mouseLocation.x > FLEE_LEFT && mouseLocation.x < FLEE_RIGHT)
			{
				if (!m_fightCheck)
				{
					std::cout << "flee yup\n";
					m_fleeCheck = true;
				}
				else
				{
					std::cout << "Scissors yup\n";
					myPlayer.setType(SCISSORS);
					m_canFight = false;
				}
			}
		} // end fight buttons
		if (!m_playerTurn && !m_okayCheck)
		{
			if (mouseLocation.y > OKAY_Y && mouseLocation.y < OKAY_FLOOR)
			{
				if (mouseLocation.x > OKAY_LEFT && mouseLocation.x < OKAY_RIGHT)
				{
					std::cout << "okay yup\n";
					m_okayCheck = true;
					m_playerTurn = true;
				}
			}
		}// end okay check
		if (m_gameOver)
		{
			if (mouseLocation.y > TRY_AGAIN_Y && mouseLocation.y < TRY_AGAIN_Y + 75)
			{
				if (mouseLocation.x > 300 && mouseLocation.x < 500)
				{
					std::cout << "Try again yup\n";
					m_tryAgainCheck = true;
				}
			}
			if (mouseLocation.y > TRY_AGAIN_Y + 100 && mouseLocation.y < TRY_AGAIN_Y + 175)
			{
				if (mouseLocation.x > 300 && mouseLocation.x < 500)
				{
					std::cout << "exit yup\n";
					t_window.close();
				}
			}
		}// end game over


	}// end button pressed
	
}

/// <summary>
/// Checks where the mouse currently is, used for
/// highlighted buttons
/// </summary>
void Game::checkMouseLocation(sf::Window& t_window)
{
	sf::Vector2i mouseLocation;

	mouseLocation = (sf::Mouse::getPosition(t_window));

	if (m_playerTurn)
	{
		if (mouseLocation.y > BUTTON_Y && mouseLocation.y < BUTTON_FLOOR)
		{
			if (mouseLocation.x > FIGHT_LEFT && mouseLocation.x < FIGHT_RIGHT)
			{
				m_mouseFight = true;
			}
			else
			{
				m_mouseFight = false;
			}
			if (mouseLocation.x > BLOCK_LEFT && mouseLocation.x < BLOCK_RIGHT)
			{
				m_mouseBlock = true;
			}
			else
			{
				m_mouseBlock = false;
			}
			if (mouseLocation.x > FLEE_LEFT && mouseLocation.x < FLEE_RIGHT)
			{
				m_mouseFlee = true;
			}
			else
			{
				m_mouseFlee = false;
			}
		}
		else
		{
			m_mouseFight = false;
			m_mouseBlock = false;
			m_mouseFlee = false;
		}
	}
	if (m_gameOver)
	{
		if (mouseLocation.y > TRY_AGAIN_Y && mouseLocation.y < TRY_AGAIN_Y + 75)
		{
			if (mouseLocation.x > 300 && mouseLocation.x < 500)
			{
				m_mouseTryAgain = true;
			}

		}
		else
		{
			m_mouseTryAgain = false;
		}
		if (mouseLocation.y > TRY_AGAIN_Y + 100 && mouseLocation.y < TRY_AGAIN_Y + 175)
		{
			if (mouseLocation.x > 300 && mouseLocation.x < 500)
			{
				m_mouseQuit = true;
			}
		}
		else
		{
			m_mouseQuit = false;
		}
	}
	if (!m_okayCheck)
	{
		if (mouseLocation.y > OKAY_Y && mouseLocation.y < OKAY_FLOOR)
		{
			if (mouseLocation.x > OKAY_LEFT && mouseLocation.x < OKAY_RIGHT)
			{
				m_mouseOkay = true;
			}
		}
		else
		{
			m_mouseOkay = false;
		}
	}
}

