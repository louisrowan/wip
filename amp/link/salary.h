#ifndef salary_cc
#define salary_cc

#include <iostream>

struct Player {
    int id;
    int year;
    std::string team;
    std::string league;
    std::string name;
    int salary;
};

Player getMax(const std::vector<Player>&);

Player findById(const std::vector<Player>&, int);

std::string formatBigNum(int);

double getAverage(const std::vector<Player>&);

void printPlayerVector(const std::vector<Player>&, std::vector<std::string>);

void printSalaryByYear(const std::vector<Player>&);

void printTeamByYear(const std::vector<Player>&, std::string, int); 
void printPlayerByYear(const std::vector<Player>&, std::string);

#endif