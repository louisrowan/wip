#ifndef master_cc
#define master_cc

#include <iostream>
#include <vector>
#include "batting.h"

struct BattingLine;

struct Player {
    std::string id;
    std::string birthYear;
    std::string birthCountry;
    std::string birthState;
    std::string birthCity;
    std::string deathYear;
    std::string firstName;
    std::string lastName;
    std::string fullName;
    std::string height;
    std::string weight;
    std::string bats;
    std::string throws;
    std::vector<BattingLine> battingStats;
};

std::vector<std::string> splitLine(std::string);

void readMasterData(std::string, std::vector<Player>&);


#endif