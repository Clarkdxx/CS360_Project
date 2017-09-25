#ifndef STATE_8_PUZZLE_H
#define STATE_8_PUZZLE_H

#include <string>
#include <cassert>
#include <iostream>
#include <vector>

// Represents an 8-puzzle state as a 3x3 array of chars. Each char can take values in range '0'-'9' (chars, not integers).
// '0' represents the blank tile.
// Provides GetKey to uniquely represent the puzzle as an integer (for hashing).
// You can extend this class to generate successors and get heuristic distance to '012345678', which is always the goal state.

class Puzzle8State {
public:
	Puzzle8State(std::string s) {
		assert(s.length() == 9);
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				tiles[r][c] = s[r*3 + c];
        closed = false;
        opened = false;
	}

	// Key generated as an integer for the hash function in Puzzle8StateManager.
	int GetKey() {
		int key = 0;
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				key = key*10 + int(tiles[r][c] - '0');
		return key;
	}

	// Return the linearized form as a string. (You don't need to use this.)
	std::string GetLinearizedForm () {
		std::string s = "";
		for (int r = 0; r < 3; r++)
			for (int c = 0; c < 3; c++)
				s += tiles[r][c];
		return s;
	}

	// Print the puzzle in a 3x3 layout. (You don't need to use this.)
	void Print(std::ostream & out = std::cout) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				out<<tiles[r][c]<<" ";
			}
			out<<std::endl;
		}
		out<<GetKey()<<std::endl;
	}
    
    void SetClosed()
    {
        closed = true;
    }
    
    bool GetClosed()
    {
        return closed;
    }
    
    void SetOpened()
    {
        opened = true;
    }
    
    bool GetOpened()
    {
        return opened;
    }
    
    //calculate heuristic distance
    int GetHeuristic()
    {
        int distance = 0;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if (tiles[r][c] == '1')
                {
                    distance += r + std::abs(c - 1);
                }
                else if (tiles[r][c] == '2')
                {
                    distance += r + std::abs(c - 2);
                }
                else if (tiles[r][c] == '3')
                {
                    distance += std::abs(r - 1) + c;
                }
                else if (tiles[r][c] == '4')
                {
                    distance += std::abs(r - 1) + std::abs(c - 1);
                }
                else if (tiles[r][c] == '5')
                {
                    distance += std::abs(r - 1) + std::abs(c - 2);
                }
                else if (tiles[r][c] == '6')
                {
                    distance += std::abs(r - 2) + c;
                }
                else if (tiles[r][c] == '7')
                {
                    distance += std::abs(r - 2) + std::abs(c - 1);
                }
                else if (tiles[r][c] == '8')
                {
                    distance += std::abs(r - 2) + std::abs(c - 2);
                }
            }
        }
        return distance;
    }
    
    //Successors
    std::vector<Puzzle8State> GetSuccessors()
    {
        std::vector<Puzzle8State> successors;
        int idxR = 0, idxC = 0;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if(tiles[r][c] == '0')
                {
                    idxR = r;
                    idxC = c;
                }
            }
        }
        int idx0 = idxR * 3 + idxC;
        if(idxR - 1 >= 0)   //we have something above
        {
            int idxSwap = (idxR - 1) * 3 + idxC;
            std::string currState = GetLinearizedForm ();
            std::swap(currState[idx0], currState[idxSwap]);
            successors.push_back(Puzzle8State(currState));
        }
        if(idxR + 1 <= 2)   //we have something below
        {
            int idxSwap = (idxR + 1) * 3 + idxC;
            std::string currState = GetLinearizedForm ();
            std::swap(currState[idx0], currState[idxSwap]);
            successors.push_back(Puzzle8State(currState));
        }
        if(idxC - 1 >= 0)   //we have something left
        {
            int idxSwap = (idxR) * 3 + idxC - 1;
            std::string currState = GetLinearizedForm ();
            std::swap(currState[idx0], currState[idxSwap]);
            successors.push_back(Puzzle8State(currState));
        }
        if(idxC + 1 <= 2)   //we have something right
        {
            int idxSwap = (idxR) * 3 + idxC + 1;
            std::string currState = GetLinearizedForm();
            std::swap(currState[idx0], currState[idxSwap]);
            successors.push_back(Puzzle8State(currState));
        }
        return successors;
    }

private:

	// tiles[r][c] is the tile (or blank) at row r (0-2) and column c (0-2)
	// 0th row is the top row, and 0th column is the leftmost column.
	char tiles[3][3];
    bool closed, opened;
};

#endif
