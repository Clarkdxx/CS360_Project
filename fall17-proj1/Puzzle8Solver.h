#ifndef PUZZLE_8_SOLVER_H
#define PUZZLE_8_SOLVER_H

#include <string>

void WeightedAStar(std::string puzzle, double w, int & cost, int & expansions);

double GetF(int g, int h, double w);

bool IsGoal(std::string str);
#endif
