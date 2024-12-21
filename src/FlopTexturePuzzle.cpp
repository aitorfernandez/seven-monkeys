//
//  FlopTexturePuzzle.cpp
//  SevenMonkeys
//

#include "FlopTexturePuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

FlopTexturePuzzle::FlopTexturePuzzle()
{
    CCLOG("// FlopTexturePuzzle %x Constructor", (int)(long)this);

    mvpDeck = new Deck();
    mvpFlopEval = new FlopEvaluator();
}

FlopTexturePuzzle::~FlopTexturePuzzle()
{
    CCLOG("// FlopTexturePuzzle %x Destructor", (int)(long)this);

    CC_SAFE_DELETE(mvpDeck);
    CC_SAFE_DELETE(mvpFlopEval);

    mvCards.clear();
    mvCards.shrink_to_fit();
}

bool FlopTexturePuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    this->scheduleUpdate();

    return true;
}

void FlopTexturePuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {
        deal();
        setWaitingPuzzle(true);
        scheduleHelpPlayer();
    }
}

void FlopTexturePuzzle::deal()
{
    Game::instance().getSoundManager().playDealSound();

    mvpDeck->placeCards();
    mvpDeck->shuffle();

    addCommunityCards();

    mvSuit = mvpFlopEval->evalSuit(mvCards);
    mvMatch = mvpFlopEval->evalMatch(mvCards);
    mvConnect = mvpFlopEval->evalConnect(mvCards);

    addTokens();

    if (UserDefault::getInstance()->getIntegerForKey("mode") > EASY)
        showPlayerMessage();

    mvCards.clear();
}

void FlopTexturePuzzle::addCommunityCards()
{
    for (size_t i = 0; i < 5; ++i) {

        cocos2d::Sprite* sprite;

        if (i > 2) {
            sprite = Sprite::createWithSpriteFrameName("BackCard.png");
        }
        else {
            int card = mvpDeck->dealCard();

            mvCards.push_back(card);

            sprite = Sprite::createWithSpriteFrameName(gHumanizeCards[card] + ".png");
        }

        sprite->setOpacity(0);
        sprite->setNormalizedPosition(Vec2(.3f + (i * .1f), .47f));

        this->addChild(sprite, kZOrderPuzzle::communityCards);

        sprite->runAction(FadeIn::create(.25f * i));
    }
}

void FlopTexturePuzzle::addTokens()
{
    std::vector<int> s { 0, 1, 3 };
    std::vector<int> m { 0, 1, 3 };
    std::vector<int> c { 0, 1, 2, 3 }; // 4 };

    s.erase(std::remove(s.begin(), s.end(), mvSuit), s.end());
    m.erase(std::remove(m.begin(), m.end(), mvMatch), m.end());
    c.erase(std::remove(c.begin(), c.end(), mvConnect), c.end());

    Rand::shuffle(s);
    Rand::shuffle(m);
    Rand::shuffle(c);

    int rndPos = randInt(2);
    s.insert((std::begin(s) + rndPos), mvSuit);

    rndPos = randInt(2);
    m.insert((std::begin(m) + rndPos), mvMatch);

    rndPos = randInt(2);
    c.insert((std::begin(c) + rndPos), mvConnect);

    std::vector<int> tokensValue { s[0], s[1], m[0], m[1], c[0], c[1] };

    for (short i = 0; i < mtpTokens.size(); ++i) {
        std::string filename;

        if (i < 2) {
            filename = "FlopTextureSuitToken";
            if (tokensValue[i] == mvSuit)
                mtpTokens[i]->setCorrect(true);
        }
        else if (i < 4) {
            filename = "FlopTextureMatchToken";
            if (tokensValue[i] == mvMatch)
                mtpTokens[i]->setCorrect(true);
        }
        else if (i < 6) {
            filename = "FlopTextureConnectToken";
            if (tokensValue[i] == mvConnect)
                mtpTokens[i]->setCorrect(true);
        }

        auto spriteName = filename + std::to_string(tokensValue[i]) + ".png";

        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setOpacity(0);
        sprite->setNormalizedPosition(mtpTokens[i]->getPosition());

        this->addChild(sprite, kZOrderPuzzle::tokens, i);

        sprite->runAction(FadeIn::create(.25f * i));

        if (mtpTokens[i]->isCorrect()) {
            mtRightAnswer = i;
        }
    }

    tokensValue.clear();
    tokensValue.shrink_to_fit();

    s.clear();
    s.shrink_to_fit();

    m.clear();
    m.shrink_to_fit();

    c.clear();
    c.shrink_to_fit();
}

void FlopTexturePuzzle::showPlayerMessage()
{
    std::string playerMessage = "Select " + std::to_string(UserDefault::getInstance()->getIntegerForKey("mode")) + "flop characteristics.";

    auto sword = Sprite::createWithSpriteFrameName("sword.png");

    sword->setNormalizedPosition(Vec2(.6f, .08f));
    sword->setOpacity(0);

    this->addChild(sword);

    auto label = Label::createWithTTF(playerMessage, "fonts/OpenSans-ExtraBold.ttf", 10);

    label->setNormalizedPosition(Vec2(.5f, .075f));
    label->setOpacity(0);

    this->addChild(label);

    auto action = Sequence::create(
                                   FadeIn::create(.25f),
                                   DelayTime::create(2.f),
                                   FadeOut::create(.25f),
                                   RemoveSelf::create(true),
                                   nullptr);

    sword->runAction(action);
    label->runAction(action->clone());
}
