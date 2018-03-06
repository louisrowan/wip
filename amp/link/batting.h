#ifndef batting_cc
#define batting_cc

#include <iostream>
#include "master.h"

struct Player;

struct BattingLine {

    std::string id;
    std::string year;
    std::string G;
    std::string AB;
    std::string R;
    std::string H;
    std::string _2B;
    std::string _3B;
    std::string HR;
    std::string SB;
    std::string CS;
    std::string RBI;
    std::string BB;
    std::string K;
};

void readBattingData(std::string fileName, std::vector<Player>& players);

std::vector<Player> findBattingData(std::string fileName, std::vector<Player>& players, std::string, int);


#endif