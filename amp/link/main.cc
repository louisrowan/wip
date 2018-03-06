#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
// #include "salary.h"
#include "master.h"
#include "batting.h"



int main (int argc, char** argv){

    if (argc < 3) {
        std::cout << "provide a stat and min amount" << std::endl;
        return 1;
    }

    // std::vector<Player> players = readData("salaries.csv");
    // printSalaryByYear(players);
    // printTeamByYear(players, "BOS", 2003);
    // printPlayerByYear(players, "garcino01");

    std::vector<Player> players;
    readMasterData("master.csv", players);
    // readBattingData("batting.csv", players);

    findBattingData("batting.csv", players, argv[1], std::stoi(argv[2]));

    std::cout << argc << " | " << argv[0] << std::endl;


    return 0;
}












