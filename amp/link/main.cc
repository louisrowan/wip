#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "salary.h"



Player createPlayer(std::string& str, int id) {

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
    ret.push_back(current);

    Player p;
    p.id = id;
    p.year = std::stoi(ret[0]);
    p.team = ret[1];
    p.league = ret[2];
    p.name = ret[3];
    p.salary = std::stoi(ret[4]);

    return p;
};

std::vector<Player> readData(std::string file) {

    std::ifstream infile;
    infile.open(file);

    std::vector<Player> players;

    std::string line;
    bool seenHeader = false;

    int id = 0;
    while (!infile.eof()) {
        getline(infile, line);
        if (line == "") break;
        if (!seenHeader) seenHeader = true;
        else {
            Player p;
            p = createPlayer(line, id++);
            players.push_back(p);
        }
    }

    return players;
}







int main (){

    std::vector<Player> players = readData("data.csv");

    Player max;
    std::vector<Player>::const_iterator it;

    for (it = players.begin(); it != players.end(); ++it) {
        if (it->salary > max.salary) {
            max = *it;
        }
    }
    
    // printSalaryByYear(players);

    // printTeamByYear(players, "BOS", 2003);

    printPlayerByYear(players, "garcino01");


    return 0;
}














