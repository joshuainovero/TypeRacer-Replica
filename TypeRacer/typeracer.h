#pragma once
#define CURL_STATICLIB
#define NOMINMAX
#include <SFML/Graphics.hpp>
#include <fstream>
#include <curl/curl.h>
#include <json/json.h>
#include <cstdint>
#include <memory>
#include <string>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <thread>
#include <string>
#include <ctime>
#include <array>
#include <cmath>

class TypeRacer {
public:
	TypeRacer();
	void run();

private:
	sf::RenderWindow* window;
	sf::Clock* clock = nullptr;
	sf::Clock* clockCountdown = nullptr;
	sf::Cursor cursor;
	sf::Event sfEvent;
	sf::Font font, fontBold;
	sf::Text inputTxt, preInputTxt;
	sf::Text wpmTxt;
	sf::Text countdownTxtMsg, countdownTxtSec;
	sf::RectangleShape inputBar;
	sf::RectangleShape inputBorder;
	sf::RectangleShape borderQuote;
	std::vector<sf::Text> sfQuoteVec;
	std::string currWord;
	std::vector<std::string> currentQuote;
	sf::Vector2i mousePos;
	uint32_t wordTyped = 0;
	uint32_t currIndexQuote = 0;
	uint32_t wpm = 0;
	sf::Text yourSpeedTxt, timeTxt, accuracyTxt;
	sf::Text title, author;
	std::array<std::string, 2> about;
	uint32_t minutesPassed = 0, secondsPassed = 0, tempSecondsPassed = 0;

	/*Quote Marker*/
	sf::Text marker;
	uint32_t cIndexQuote = 0;
	uint32_t uiIndexQuote = 0;
	uint32_t posIndex = 0;
	uint32_t wrongWordCount = 0;
	float accuracyPercentage = 100.0f;
	float penaltyIncr = 0.0f;
	std::string lineChecker = "";
	std::string currWrongWord;

	/*Start button properties*/
	sf::Texture startBtnTexture, startBtnHoverTexture;
	sf::Sprite startBtnSprite;
	std::array<int, 4> startBtnRanges;
	bool onHover = false;

	/*Main menu button properties*/
	sf::Texture menuBtnTexture;
	sf::Sprite menuBtnSprite;
	std::array<int, 4> menuBtnRanges;
	bool onHoverMenuBtn = false;

	/*Results panel*/
	sf::Texture resultPanelTexture;
	sf::Sprite resultPanelSprite;
	std::array<int, 4> tryAgainRanges;
	bool resultsTriggered = false;

	uint32_t states = 0; //0 - menu, 1 - inRace
	int countdownSeconds = 10, tempSeconds;

private:
	void updateSFMLEvents();
	void update();
	void render();
	void fetchQuoteAPI();
	void displayQuote();
	void dispQuoteMarker();
	void menu();
	void inRace();
	void wpmDisplay();
	void subStrChecker();
	void stateManager();
	void reset();
	void dumpJsonData(Json::Value& newData);
	Json::Value getDataJson();

	// Button Events
	bool startBtnInRange();
	bool tryAgainInRange();
	bool menuBtnInRange();
};

