#include "salary.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

Player getMax(const std::vector<Player>& players) {

    Player max;
    for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
        if (it->salary > max.salary) {
            max = *it;
        }
    }
    return max;
}

double getAverage(const std::vector<Player>& players) {

    double total = 0;
    for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
        total += it->salary;
    }
    return total/players.size();
}

Player findById(const std::vector<Player>& players, int id) {

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


void printPlayerVector(const std::vector<Player>& players, std::vector<std::string> fields) {

    for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {

        if (std::find(fields.begin(), fields.end(), "name") != fields.end()) {
            std::cout << it->name;
        }
        if (std::find(fields.begin(), fields.end(), "year") != fields.end()) {
            std::cout << " | " << it->year;
        }
        if (std::find(fields.begin(), fields.end(), "team") != fields.end()) {
            std::cout << " | " << it->team;
        }
        if (std::find(fields.begin(), fields.end(), "salary") != fields.end()) {
            std::cout << " | " << it->salary;
        }
        std::cout << std::endl;
    }
}




void printSalaryByYear(const std::vector<Player>& players) {

    std::map<int, std::vector<Player> > salByYear;

    std::vector<Player>::const_iterator it;

    for (it = players.begin(); it != players.end(); ++it) {

        int year = it->year;

        std::map<int, std::vector<Player> >::iterator iter = salByYear.find(year);

        if (iter == salByYear.end() ) {
            std::vector<Player> newYear;
            salByYear[year] = newYear;
        }

        salByYear[year].push_back(*it);
    }


    for (std::map<int, std::vector<Player> >::const_iterator it = salByYear.begin(); it != salByYear.end(); ++it) {
        std::vector<Player> salaries;
        salaries = it->second;
        double average = getAverage(salaries);
        std::cout << "average for " << it->first << ": " << formatBigNum(average) << std::endl;
    }

}


void printTeamByYear(const std::vector<Player>& players, std::string team, int year) {

    std::vector<Player> ret;

    bool found = false;
    for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
        if (it->team == team && it->year == year) {
            ret.push_back(*it);
            found = true;
        }
        else if (found) {
            break;
        }
    }

    for (std::vector<Player>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
        std::cout << it->name << ": " << formatBigNum(it->salary) << std::endl;
    }
}


void printPlayerByYear(const std::vector<Player>& players, std::string name) {

    std::vector<Player> ret;

    for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
        if (it->name == name) {
            ret.push_back(*it);
        }
    }

    for (std::vector<Player>::const_iterator it = ret.begin(); it != ret.end(); ++it) {
        std::cout << it->name << ": " << it->year << " " << formatBigNum(it->salary) << std::endl;
    }

    std::vector<std::string> fields = {"name", "year", "salary"};
    printPlayerVector(ret, fields);
}