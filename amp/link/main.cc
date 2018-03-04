#include <iostream>
#include <fstream>
#include <vector>
#include <map>


struct Player {
    int id;
    int year;
    std::string team;
    std::string league;
    std::string name;
    int salary;
};


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


void printPlayer(const Player& p) {
    std::cout << std::endl;
    std::cout << "id: " << p.id << std::endl;
    std::cout << "year: " << p.year << std::endl;
    std::cout << "team: " << p.team << std::endl;
    std::cout << "name: " << p.name << std::endl;
    std::cout << "salary: " << p.salary << std::endl;
    std::cout << std::endl;
    return;

}


Player findById(std::vector<Player> players, int id) {

    std::vector<Player>::const_iterator it;
    for (it = players.begin(); it != players.end(); ++it) {
        if (it-> id == id) {
            return *it;
        }
    }
}

std::string formatBigNum(int i) {

    std::string str = std::to_string(i);
    std::string newString;

    int count = 0;
    for (int index = str.size() - 1; index > -1; --index) {
        if (count == 3) {
            newString += ",";
            count = 0;
        }
        newString += str[index];
        ++count;
    }

    std::string ret;
    for (int i = newString.size() - 1; i > -1; --i) {
        ret += newString[i];
    }


    return ret;
}


void printSalaryByYear(std::vector<Player> players) {

    std::map<int, std::vector<int> > salByYear;

    std::vector<Player>::const_iterator it;

    for (it = players.begin(); it != players.end(); ++it) {

        int year = it->year;

        std::map<int, std::vector<int> >::iterator iter = salByYear.find(year);

        if (iter == salByYear.end() ) {
            std::vector<int> newYear;
            salByYear[year] = newYear;
        }

        salByYear[year].push_back(it->salary);
    }


    for (std::map<int, std::vector<int> >::const_iterator it = salByYear.begin(); it != salByYear.end(); ++it) {
        std::vector<int> salaries;
        salaries = it->second;
        double sal = 0;
        int count = 0;
        for (std::vector<int>::const_iterator i = salaries.begin(); i != salaries.end(); ++i) {

            sal += *i;
            ++count;
        }
        int average = (sal/count);
        std::cout << "average for " << it->first << ": " << formatBigNum(average) << std::endl;
    }

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

    printPlayer(max);
    
    printSalaryByYear(players);


    return 0;
}














