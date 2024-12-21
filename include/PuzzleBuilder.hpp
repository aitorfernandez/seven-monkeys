//
//  PuzzleBuilder.hpp
//  SevenMonkeys
//

#ifndef PuzzleBuilder_hpp
#define PuzzleBuilder_hpp

#include "SevenMonkeys.hpp"

#include "Builder.hpp"

#include "BackgroundLayer.hpp"
#include "FairyLayer.hpp"
#include "HUDLayer.hpp"
#include "CountDownLayer.hpp"

#include "PuzzleLayer.hpp"

#include "Player.hpp"
#include "Token.hpp"

#include "PokerHandsPuzzle.hpp"
#include "OrderPuzzle.hpp"
#include "BestHandPuzzle.hpp"
#include "OutsPuzzle.hpp"
#include "FlopTexturePuzzle.hpp"
#include "OddsPuzzle.hpp"
#include "PreFlopPuzzle.hpp"

USING_NS_CC;

class PuzzleBuilder : public Builder
{
private:

    rapidjson::Document mvDocument;

public:

    PuzzleBuilder(const std::string &filename)
    {
        CCLOG("// PuzzleBuilder %x Constructor", (int)(long)this);

        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
        std::string json = FileUtils::getInstance()->getStringFromFile(fullPath);

        mvDocument.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(json.c_str());
    }

    virtual ~PuzzleBuilder()
    {
        CCLOG("// PuzzleBuilder %x Destructor", (int)(long)this);
    }

    void addBackground()
    {
        auto backgroundLayer = BackgroundLayer::create(mvDocument["background"].GetString());
        mtpPuzzleScene->addLayer(backgroundLayer);
    }

    void addPuzzle(const short puzzle)
    {
        PuzzleLayer *puzzleLayer;

        switch (puzzle) {
            case (0): {
                puzzleLayer = PokerHandsPuzzle::create();
                puzzleLayer->setPokerHandsTouch();
            }
            break;
            case (1): {
                puzzleLayer = OrderPuzzle::create();
                puzzleLayer->setOrderTouch();
            }
            break;
            case (2): {
                puzzleLayer = BestHandPuzzle::create();
                puzzleLayer->setBestHandTouch();
            }
            break;
            case (3): {
                puzzleLayer = OutsPuzzle::create();
                puzzleLayer->setOutsTouch();
            }
            break;
            case (4): {
                puzzleLayer = OddsPuzzle::create();
                puzzleLayer->setOddsTouch();
            }
            break;
            case (5): {
                puzzleLayer = FlopTexturePuzzle::create();
                puzzleLayer->setFlopTextureTouch();
            }
            break;
            case (6): {
                puzzleLayer = PreFlopPuzzle::create();
                puzzleLayer->setPreFlopTouch();
            }
            break;
        }

        const char* mode = Game::instance().getHumanizeMode(UserDefault::getInstance()->getIntegerForKey("mode"));

        const rapidjson::Value& puzzleLevel = mvDocument["puzzle"][mode];

        if (puzzleLevel.HasMember("players")) {
            const rapidjson::Value& players = puzzleLevel["players"];

            for (rapidjson::SizeType i = 0; i < players.Size(); i++) {

                // Player per position
                auto player = new Player();

                if (players[i].HasMember("sticker")) {
                    player->mPositions.sticker = Vec2(
                                                      players[i]["sticker"][0].GetDouble(),
                                                      players[i]["sticker"][1].GetDouble());
                }

                if (players[i].HasMember("btn")) {
                    player->mPositions.btn = Vec2(
                                                  players[i]["btn"][0].GetDouble(),
                                                  players[i]["btn"][1].GetDouble());
                }

                if (players[i].HasMember("blinds")) {
                    player->mPositions.blinds = Vec2(
                                                     players[i]["blinds"][0].GetDouble(),
                                                     players[i]["blinds"][1].GetDouble());
                }

                if (players[i].HasMember("stack")) {
                    player->mPositions.stack = Vec2(
                                                    players[i]["stack"][0].GetDouble(),
                                                    players[i]["stack"][1].GetDouble());
                }

                puzzleLayer->pushPlayer(player);
            }
        }

        if (puzzleLevel.HasMember("tokens")) {
            const rapidjson::Value& tokens = puzzleLevel["tokens"];

            for (rapidjson::SizeType i = 0; i < tokens.Size(); i++) {
                auto token = new Token();

                token->setPosition(Vec2(
                                        tokens[i][0].GetDouble(),
                                        tokens[i][1].GetDouble()));

                puzzleLayer->pushToken(token);
            }
        }

        mtpPuzzleScene->addLayer(puzzleLayer);
    }

    void addFairy()
    {
        const rapidjson::Value& messages = mvDocument["messages"];

        auto fairyLayer = FairyLayer::create();

        for (rapidjson::SizeType i = 0; i < messages.Size(); i++)
            fairyLayer->addMessage(messages[i].GetString());

        mtpPuzzleScene->addLayer(fairyLayer);
    }

    void addHUD()
    {
        const char* mode = Game::instance().getHumanizeMode(UserDefault::getInstance()->getIntegerForKey("mode"));

        float puzzleTime = mvDocument["puzzle"][mode]["time"].GetDouble();

        int firstLevel = mvDocument["puzzle"][mode]["firstLevel"].GetInt();
        int lastLevel = mvDocument["puzzle"][mode]["lastLevel"].GetInt();

        float penalty = mvDocument["puzzle"][mode]["penalty"].GetDouble();

        auto hudLayer = HUDLayer::create(puzzleTime, firstLevel, lastLevel, penalty);
        mtpPuzzleScene->addLayer(hudLayer);
    }

    void addCountDown()
    {
        auto countDownLayer = CountDownLayer::create();
        mtpPuzzleScene->addLayer(countDownLayer);
    }
};

#endif /* PuzzleBuilder_hpp */
