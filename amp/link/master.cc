#include <iostream>
#include <fstream>
#include <vector>
#include "master.h"


std::vector<std::string> splitLine(std::string str) {
    
    std::vector<std::string> ret;
    std::string current;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ',') {
            ret.push_back(current);
            current = "";
        }
        else {
            current += str[i];
        }
    }
    if (current.size() > 0) ret.push_back(current);

    return ret;
};

Player formatPlayerLine(std::vector<std::string> playerVector) {

    Player p;
    p.id = playerVector[0];
    p.birthYear = playerVector[1];
    p.birthCountry = playerVector[4];
    p.birthState = playerVector[5];
    p.birthCity = playerVector[6];
    p.deathYear = playerVector[7];
    p.firstName = playerVector[13];
    p.lastName = playerVector[14];
    p.fullName = playerVector[13] + " " + playerVector[14];
    p.height = playerVector[17];
    p.weight = playerVector[16];
    p.bats = playerVector[18];
    p.throws = playerVector[19];

    return p;

}

void readMasterData(std::string fileName, std::vector<Player>& players) {

    std::ifstream infile;
    infile.open(fileName);

    std::string headerLine;
    getline(infile, headerLine); // skip headers

    std::string playerLine;
    while (!infile.eof()) {
        getline(infile, playerLine);
        if (playerLine == "") break;
        std::vector<std::string> vec;
        vec = splitLine(playerLine);
        Player p = formatPlayerLine(vec);
        players.push_back(p);
    }
}
