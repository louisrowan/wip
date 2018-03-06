#include <iostream>
#include <fstream>
#include <vector>
#include "batting.h"
#include "master.h"

BattingLine formatBattingLine(std::vector<std::string>& battingLine) {

    BattingLine b;
    b.id = battingLine[0];
    b.year = battingLine[1];
    b.G = battingLine[5];
    b.AB = battingLine[6];
    b.R = battingLine[7];
    b.H = battingLine[8];
    b._2B = battingLine[9];
    b._3B = battingLine[10];
    b.HR = battingLine[11];
    b.SB = battingLine[13];
    b.CS = battingLine[14];
    b.RBI = battingLine[12];
    b.BB = battingLine[15];
    b.K = battingLine[16];

    return b;
}


double findPlayerById(std::string id, std::vector<Player>& players) {

    if (players.size() == 1) return 0;

    double median = players.size()/2;
    if (players[median].id == id) {
        return median;
    }

    std::vector<Player> newArr;
    if (players[median].id > id) {
        for (int i = 0; i < median; ++i) {
            newArr.push_back(players[i]);
        }
        return findPlayerById(id, newArr);
    }

    for (int i = median; i < players.size(); ++i) {
        newArr.push_back(players[i]);
    }

    return median + findPlayerById(id, newArr);
}



// void readBattingData(std::string fileName, std::vector<Player>& players) {

//     std::ifstream infile;
//     infile.open(fileName);

//     std::string headerLine;
//     getline(infile, headerLine); // skip headers

//     std::string statLine;
//     while (!infile.eof()) {
//         getline(infile, statLine);
//         if (statLine == "") break;

//         std::vector<std::string> vec;
//         vec = splitLine(statLine);
//         BattingLine bl;
//         bl = formatBattingLine(vec);
//         std::string id = bl.id;
//         int index = findPlayerById(id, players);
//         Player p;
//         p = players[index];
//         p.battingStats.push_back(battingLine);
//         std::cout << "year " << vec[1] << " | name " << p.fullName << p.battingState[0].HR  << std::endl;
//     }


// }


std::string getProp (std::string propName, BattingLine battingLine) {

    if (propName == "G") return battingLine.G;
    else if (propName == "AB") return battingLine.AB;
    else if (propName == "R") return battingLine.R;
    else if (propName == "H") return battingLine.H;
    else if (propName == "_2B") return battingLine._2B;
    else if (propName == "_3B") return battingLine._3B;
    else if (propName == "HR") return battingLine.HR;
    else if (propName == "SB") return battingLine.SB;
    else if (propName == "CS") return battingLine.CS;
    else if (propName == "RBI") return battingLine.RBI;
    else if (propName == "BB") return battingLine.BB;
    else if (propName == "K") return battingLine.K;

    std::cout << "error in getProp " << propName << std::endl;
    return "0";
}

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


std::vector<Player> findBattingData(std::string fileName, std::vector<Player>& players, std::string statName, int stat) {

    std::vector<Player> _players;
    std::vector<BattingLine> _battingLines;

    std::ifstream infile;
    infile.open(fileName);

    std::string headerLine;
    getline(infile, headerLine); // skip headers

    std::string statLine;
    int count = 0;
    while (!infile.eof()) {
        getline(infile, statLine);
        if (statLine == "") break;

        std::vector<std::string> vec;
        vec = splitLine(statLine);
        BattingLine bl;
        bl = formatBattingLine(vec);

        std::string prop = getProp(statName, bl);

        if (prop != "" && std::stoi(prop) > stat) {
            double i = findPlayerById(bl.id, players);
            _players.push_back(players[i]);
            _battingLines.push_back(bl);
            if (++count > 50) {
                std::cout << " > 50 results " << std::endl;
                break;
            }
        }
    }

    int maxSize = 0;
    for (int i = 0; i < _players.size(); ++i) {
        if (_players[i].fullName.size() > maxSize) {
            maxSize = _players[i].fullName.size();
        }
    }
    
    for (int i = 0; i < _players.size(); ++i) {
        Player pl = _players[i];
        BattingLine bl = _battingLines[i];
        int padding = maxSize - pl.fullName.size();

        std::cout << bl.year << " | " << pl.fullName;
        for (int i = 0; i < padding; ++i) {
            std::cout << " ";
        }

        std::string prop = getProp(statName, bl);

        std::cout << " | "  << prop << std::endl;
    }
    return _players;
}


// struct BattingLine {

//     std::string year;
//     std::string G;
//     std::string AB;
//     std::string R;
//     std::string H;
//     std::string 2B;
//     std::string 3B;
//     std::string HR;
//     std::string SB;
//     std::string CS;
//     std::string RBI;
//     std::string BB;
//     std::string K;
// };