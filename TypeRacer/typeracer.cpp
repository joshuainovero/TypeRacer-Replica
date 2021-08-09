#include "typeracer.h"

TypeRacer::TypeRacer() {
    window = new sf::RenderWindow(sf::VideoMode(1100, 600), "Type Racer", sf::Style::Close);
 
    font.loadFromFile("Fonts/Lato-Regular.ttf");
    fontBold.loadFromFile("Fonts/Lato-Bold.ttf");

    inputTxt.setFont(font);
    inputTxt.setFillColor(sf::Color::Black);
    inputTxt.setCharacterSize(24);
    inputTxt.setPosition(sf::Vector2f(120.0f, window->getSize().y - 115));

    preInputTxt.setFont(font);
    preInputTxt.setFillColor(sf::Color(153, 153, 153));
    preInputTxt.setCharacterSize(24);
    preInputTxt.setPosition(sf::Vector2f(120.0f, window->getSize().y - 115));
    preInputTxt.setString("Type the above text here when the race begins");
    
    wpmTxt.setFont(fontBold);
    wpmTxt.setFillColor(sf::Color(99, 142, 142));
    wpmTxt.setCharacterSize(20);
    wpmTxt.setPosition(sf::Vector2f(window->getSize().x-120, 0.0f));
    wpmTxt.setString("WPM:");

    countdownTxtMsg.setFont(font);
    countdownTxtMsg.setFillColor(sf::Color::Black);
    countdownTxtMsg.setCharacterSize(24);
    countdownTxtMsg.setPosition(sf::Vector2f(420.0f, 10.0f));
    countdownTxtMsg.setString("Get ready to type!     :     ");

    countdownTxtSec.setFont(fontBold);
    countdownTxtSec.setFillColor(sf::Color::Black);
    countdownTxtSec.setCharacterSize(35);
    float cdTxtMsgWidth = countdownTxtMsg.findCharacterPos(countdownTxtMsg.getString().getSize() - 1).x - countdownTxtMsg.findCharacterPos(0).x;
    countdownTxtSec.setPosition(sf::Vector2f(countdownTxtMsg.findCharacterPos(0).x + cdTxtMsgWidth, 3.0f));

    inputBar.setSize(sf::Vector2f(900.0f, 40.0f));
    inputBar.setFillColor(sf::Color::White);
    inputBar.setOutlineColor(sf::Color(199, 213, 221));
    inputBar.setOutlineThickness(1);
    inputBar.setPosition(sf::Vector2f(100.0f, window->getSize().y - 120));

    inputBorder.setSize(sf::Vector2f(930.0f, 80.0f));
    inputBorder.setFillColor(sf::Color(246, 251, 255));
    inputBorder.setOutlineColor(sf::Color(199, 213, 217));
    inputBorder.setOutlineThickness(1.3f);
    inputBorder.setOrigin(sf::Vector2f(inputBorder.getSize().x/(float)2, inputBorder.getSize().y/(float)2));
    inputBorder.setPosition(sf::Vector2f(window->getSize().x/(float)2, 500.0f));

    borderQuote.setSize(sf::Vector2f(950,350));
    borderQuote.setFillColor(sf::Color(246, 251, 255));
    borderQuote.setOutlineColor(sf::Color(199, 213, 217));
    borderQuote.setOutlineThickness(1.3f);
    borderQuote.setOrigin(sf::Vector2f(borderQuote.getSize().x/(float)2, borderQuote.getSize().y/(float)2));
    borderQuote.setPosition(sf::Vector2f(window->getSize().x/(float)2, 240.0f));

    marker.setFont(font);
    marker.setFillColor(sf::Color(153,204,0));
    marker.setStyle(sf::Text::Underlined);
    marker.setCharacterSize(24);

    startBtnTexture.loadFromFile("Resources/img/StartButton.png");
    startBtnHoverTexture.loadFromFile("Resources/img/StartButtonHover.png");
    startBtnSprite.setTexture(startBtnTexture);
    startBtnSprite.setOrigin(sf::Vector2f(startBtnTexture.getSize().x/2.0f, startBtnTexture.getSize().y/2.0f));
    startBtnSprite.setPosition(sf::Vector2f(window->getSize().x/2.0f, window->getSize().y/2.0f));
    startBtnRanges[0] = 406;
    startBtnRanges[1] = startBtnRanges[0] + 289;
    startBtnRanges[2] = 252;
    startBtnRanges[3] = startBtnRanges[2] + 78;

    resultPanelTexture.loadFromFile("Resources/img/Results.png");
    resultPanelSprite.setTexture(resultPanelTexture);
    resultPanelSprite.setOrigin(sf::Vector2f(resultPanelTexture.getSize().x/2.0f, resultPanelTexture.getSize().y/2.0f));
    resultPanelSprite.setPosition(sf::Vector2f(window->getSize().x/2.0f, window->getSize().y/2.0f));
    tryAgainRanges[0] = 627;
    tryAgainRanges[1] = tryAgainRanges[0] + 186;
    tryAgainRanges[2] = 318;
    tryAgainRanges[3] = tryAgainRanges[2] + 44;

    yourSpeedTxt.setFont(fontBold);
    yourSpeedTxt.setCharacterSize(21);
    yourSpeedTxt.setFillColor(sf::Color::White);
    yourSpeedTxt.setPosition(sf::Vector2f(485.0f, 280.0f));

    timeTxt.setFont(fontBold);
    timeTxt.setCharacterSize(21);
    timeTxt.setFillColor(sf::Color::White);
    timeTxt.setPosition(sf::Vector2f(485.0f, 342.0f));

    accuracyTxt.setFont(fontBold);
    accuracyTxt.setCharacterSize(21);
    accuracyTxt.setFillColor(sf::Color::White);
    accuracyTxt.setPosition(sf::Vector2f(485.0f, 406.0f));

    title.setFont(font);
    title.setCharacterSize(21);
    title.setFillColor(sf::Color::White);

    author.setFont(font);
    author.setCharacterSize(18);
    author.setFillColor(sf::Color(148, 184, 210));

}

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

void TypeRacer::fetchQuoteAPI() {
    const std::string url("https://joshuainovero.github.io/public-json-api/typeracer.json"); //JSON file from URL

    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;
        Json::Value jsonData;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            /*std::cout << jsonData.toStyledString() << std::endl;*/
            
            uint32_t randIndexQuote = rand() % 707;
            int bb = 0;
            std::string parsedQuote = jsonData["quotes"][randIndexQuote]["quote"].asString();
            std::string parsedAbout = jsonData["quotes"][randIndexQuote]["about"].asString();
            parsedAbout = parsedAbout.substr(std::string("- from").length() + 1);

            uint32_t materialIndex;
            if (parsedAbout.find("a book") != std::string::npos)
                materialIndex = parsedAbout.find("a book");
            else if (parsedAbout.find("a movie") != std::string::npos)
                materialIndex = parsedAbout.find("a movie");
            else if (parsedAbout.find("a poem") != std::string::npos)
                materialIndex = parsedAbout.find("a poem");
            else if (parsedAbout.find("a song") != std::string::npos)
                materialIndex = parsedAbout.find("a song");

            about[0] = parsedAbout.substr(0, materialIndex - 2);
            about[1] = parsedAbout.substr(materialIndex); 

            std::string tempStr;
            for (size_t i = 0; i < parsedQuote.length(); ++i) {
                if (parsedQuote[i] == ' ' || i == parsedQuote.length() - 1) {
                    if (i == parsedQuote.length() - 1)
                        tempStr.push_back(parsedQuote[i]);
                    currentQuote.push_back(tempStr);
                    tempStr.clear();
                }
                else {
                    tempStr.push_back(parsedQuote[i]);
                }
            }

            std::string tempLine = "";
            sf::Text tempText;
            tempText.setFont(font);
            tempText.setFillColor(sf::Color::Black);
            tempText.setCharacterSize(24);
            for (size_t i = 0; i < currentQuote.size(); ++i) {
                std::string checkExceed = tempLine + currentQuote[i];
                if (checkExceed.length() > 79) {
                    tempText.setString(tempLine);
                    sfQuoteVec.push_back(tempText);
                    tempLine = "";
                    tempLine += currentQuote[i] + " ";
                }
                else {
                    tempLine += currentQuote[i] + " ";
                }
            }
            if (tempLine.size() != 0) {
                tempText.setString(tempLine);
                sfQuoteVec.push_back(tempText);
            }

        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
    
    }
}

void TypeRacer::wpmDisplay() {
        wpm = (float)wordTyped / ((float)clock->getElapsedTime().asSeconds() / (float)60);
        wpmTxt.setString("WPM: " + std::to_string((int)wpm));
    
}

void TypeRacer::inRace() {
    if (sfQuoteVec.empty()) {
        fetchQuoteAPI();
    }
    window->draw(borderQuote);
    window->draw(inputBorder);
    window->draw(inputBar);
    window->draw(inputTxt);
    window->draw(wpmTxt);
    displayQuote();

    if (clockCountdown == nullptr) {
        std::cout << "Created new clock countdown" << std::endl;
        clockCountdown = new sf::Clock();
    }

    if (countdownSeconds >= 0) {
        if ((int)clockCountdown->getElapsedTime().asSeconds() != tempSeconds) {
            tempSeconds = (int)clockCountdown->getElapsedTime().asSeconds();
            countdownSeconds--;
            if (countdownSeconds == 5) {
                countdownTxtMsg.setString("It's the final countdown!     :     ");
                countdownTxtMsg.setPosition(sf::Vector2f(353.0f, 10.0f));
            }
        }
        if (countdownSeconds < 10) {
            countdownTxtSec.setString("0" + std::to_string(countdownSeconds));
        } else
            countdownTxtSec.setString(std::to_string(countdownSeconds));
        window->draw(countdownTxtMsg);
        window->draw(countdownTxtSec);
        window->draw(preInputTxt);
    }
    else {
        if (clock == nullptr) {
            delete clockCountdown;
            clock = new sf::Clock();
            std::cout << "Created new clock" << std::endl;
        }
        if (!resultsTriggered) {
            if ((int)clock->getElapsedTime().asSeconds() != tempSecondsPassed) {
                secondsPassed++;
                tempSecondsPassed++;
                if (secondsPassed == 60) {
                    secondsPassed = 0;
                    minutesPassed++;
                }
            }
            
            dispQuoteMarker();
            subStrChecker();
            wpmDisplay();
        }

        if (cIndexQuote == sfQuoteVec.size()) {
            if (!resultsTriggered) {
                title.setString(about[0]);
                title.setPosition(sf::Vector2f((int)(window->getSize().x/2.0f), (int)205.0f));
                title.setOrigin((int)(title.getLocalBounds().left + title.getLocalBounds().width / 2.0f),
                (int)(title.getLocalBounds().top + title.getLocalBounds().height / 2.0f));

                author.setString(about[1]);
                author.setPosition(sf::Vector2f((int)(window->getSize().x / 2.0f), (int)230.0f));
                author.setOrigin((int)(author.getLocalBounds().left + author.getLocalBounds().width / 2.0f),
                (int)(author.getLocalBounds().top + author.getLocalBounds().height / 2.0f));

                yourSpeedTxt.setString(std::to_string(wpm) + " wpm");
                if (secondsPassed < 10)
                    timeTxt.setString(std::to_string(minutesPassed) + ":" + "0" + std::to_string(secondsPassed));
                else
                    timeTxt.setString(std::to_string(minutesPassed) + ":" + std::to_string(secondsPassed));
                std::string formattedAccuracy = std::to_string(accuracyPercentage).substr(0, std::to_string(accuracyPercentage).find('.') + 2);
                accuracyTxt.setString(formattedAccuracy + "%");
                resultsTriggered = true;
            }
            window->draw(resultPanelSprite);
            window->draw(title);
            window->draw(author);
            window->draw(yourSpeedTxt);
            window->draw(timeTxt);
            window->draw(accuracyTxt);

            if (tryAgainInRange()) {
                if (!onHover) {
                    cursor.loadFromSystem(sf::Cursor::Hand);
                    window->setMouseCursor(cursor);
                    onHover = true;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    reset();
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    window->setMouseCursor(cursor);
                }
            }
            else {
                if (onHover) {
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    window->setMouseCursor(cursor);
                    onHover = false;
                }
            }
            //reset();
            //states = 0;
        }
    }
}

void TypeRacer::menu() {
    window->draw(startBtnSprite);
    if (startBtnInRange()) {
        if (startBtnSprite.getTexture() != &startBtnHoverTexture)
            startBtnSprite.setTexture(startBtnHoverTexture);
        if (!onHover) {
            cursor.loadFromSystem(sf::Cursor::Hand);
            window->setMouseCursor(cursor);
            onHover = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            states = 1;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window->setMouseCursor(cursor);
            onHover = false;
        }

    }
    else {
        if (startBtnSprite.getTexture() != &startBtnTexture)
            startBtnSprite.setTexture(startBtnTexture);
        if (onHover) {
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window->setMouseCursor(cursor);
            onHover = false;
        }
    }
}

void TypeRacer::displayQuote() {
    sf::Vector2f quotePos(110.0f, 85.0f);
    for (size_t i = 0; i < sfQuoteVec.size(); ++i) {
        sfQuoteVec[i].setPosition(sf::Vector2f(quotePos.x, quotePos.y));
        window->draw(sfQuoteVec[i]);
        quotePos.y += 35;
    }
}

void TypeRacer::dispQuoteMarker() {
    std::vector<std::string> quoteForMarker;
    std::string tmpStr;
    if (cIndexQuote != sfQuoteVec.size()) {
        std::string onString = sfQuoteVec[cIndexQuote].getString();

        for (size_t i = 0; i < onString.length(); ++i) {

            if (onString[i] == ' ' || i == onString.length() - 1) {
                quoteForMarker.push_back(tmpStr);
                tmpStr.clear();
            }
            else {
                tmpStr.push_back(onString[i]);
            }
        }
    }

    for (size_t i = 0; i < uiIndexQuote; ++i) {
        posIndex++;
        for (size_t k = 0; k < quoteForMarker[i].size(); ++k) {
            posIndex++;
        }
    }
    if (cIndexQuote != sfQuoteVec.size()) {
        sf::Vector2f pos = sfQuoteVec[cIndexQuote].findCharacterPos(posIndex);
        marker.setString(currentQuote[currIndexQuote]);
        marker.setPosition(pos.x, pos.y);
        posIndex = 0;
        window->draw(marker);
    }
}

void TypeRacer::updateSFMLEvents() {
    while (window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed)
            window->close();
        else if (sfEvent.type == sf::Event::TextEntered) {
            if (states == 1 && clock != nullptr && !resultsTriggered) {
                if (sfEvent.text.unicode == 8 && currWord.size() != 0) {
                    currWord.pop_back();
                }
                else if (sfEvent.text.unicode == 32) {
                    if (currWord == currentQuote[currIndexQuote]) {
                        lineChecker += currWord + " ";
                        currWord.clear();
                        currIndexQuote++;
                        uiIndexQuote++;
                        wordTyped++;
                        if (lineChecker.length() == sfQuoteVec[cIndexQuote].getString().getSize()) {
                            cIndexQuote++;
                            lineChecker = "";
                            uiIndexQuote = 0;

                        }
                    }
                }
                else {
                    if (sfEvent.text.unicode != 8) {
                        currWord.push_back((char)sfEvent.text.unicode);
                    }
                }
                inputTxt.setString(currWord);

            }
        }
    }
}

void TypeRacer::update() {
    mousePos = sf::Mouse::getPosition(*window);
    updateSFMLEvents();
}

void TypeRacer::render() {
    window->clear(sf::Color::White);
    if (states == 0) {
        menu();
    }
    else if (states == 1)
        inRace();

    window->display();

}

void TypeRacer::subStrChecker() {

    if (cIndexQuote != sfQuoteVec.size()) {
        if (currentQuote[currIndexQuote].find(currWord) != 0) {
            if (currWord != currWrongWord && currWrongWord.find(currWord) == std::string::npos) {
                inputBar.setFillColor(sf::Color(208, 131, 131));
                currWrongWord = currWord;
                wrongWordCount++;
                if (accuracyPercentage >= 1.0f) {
                    if (wrongWordCount <= 1) {
                        accuracyPercentage -= 0.7f + penaltyIncr;
                        penaltyIncr += 0.1f;
                        if (accuracyPercentage < 1.0f) {
                            accuracyPercentage = 1.0f;
                        }
                    }
                    else
                        accuracyPercentage -= 0.1f;
                }
            }
        }
        else {
            if (!currWrongWord.empty()) {
                wrongWordCount = 0;
                currWrongWord.clear();
            }
            inputBar.setFillColor(sf::Color::White);
        }
    }
}

void TypeRacer::run() {
    while (window->isOpen()) {
        update();
        render();

        //std::cout << mousePos.x << " : " << mousePos.y << std::endl;
        // 406
        // 252
    }
}

bool TypeRacer::startBtnInRange() {
    return (mousePos.x >= startBtnRanges[0] && mousePos.x <= startBtnRanges[1] &&
            mousePos.y >= startBtnRanges[2] && mousePos.y <= startBtnRanges[3]);
}

bool TypeRacer::tryAgainInRange() {
    return (mousePos.x >= tryAgainRanges[0] && mousePos.x <= tryAgainRanges[1] &&
        mousePos.y >= tryAgainRanges[2] && mousePos.y <= tryAgainRanges[3]);
}

void TypeRacer::reset() {
    sfQuoteVec.clear();
    currWord.clear();
    currentQuote.clear();
    currWrongWord.clear();
    wpmTxt.setString("WPM:");
    countdownTxtMsg.setString("Get ready to type!     :     ");
    countdownTxtMsg.setPosition(sf::Vector2f(420.0f, 10.0f));
    wordTyped = 0;
    wpm = 0;
    currIndexQuote = 0;
    cIndexQuote = 0;
    uiIndexQuote = 0;
    posIndex = 0;
    wrongWordCount = 0;
    lineChecker = "";
    accuracyPercentage = 100.0f;
    penaltyIncr = 0.0f;
    delete clock;
    clock = nullptr;
    clockCountdown = nullptr;
    resultsTriggered = false;
    countdownSeconds = 10;
    minutesPassed = 0;
    secondsPassed = 0;
    tempSecondsPassed = 0;
    std::cout << "Deleted clock" << std::endl;
}