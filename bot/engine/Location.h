#ifndef LOCATION_H_
#define LOCATION_H_

#include <cstdlib>
#include <iostream>
#include "../debug.h"

enum FWDirection {
	N,  // Norte, arriba
	E,  // Este, derecha
	S,  // Sur, abajo
	W,  // Oeste, izquierda
	IMPOSSIBLE, // Imposible, error, no hay dirección...
};

/*
		constants
*/
const int TDIRECTIONS = 4;
const char CDIRECTIONS[4] = {'N', 'E', 'S', 'W'};
const int DIRECTIONS[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };      //{N, E, S, W}
const FWDirection FDIRECTIONS[4] = {N, E, S, W};
const FWDirection OPPOSITE[4] = {S, W, N, E};

/*
		struct for representing locations in the grid.
*/
struct Location
{
	int row, col;

	Location()
	{
		row = col = 0;
	};

	Location(int r, int c)
	{
		row = r;
		col = c;
	};

	Location(const int *posFromArray)
	{
		this->col = posFromArray[0];
		this->row = posFromArray[1];
	}

	Location(const int *pos, const int *dir)
	{
		this->col = pos[0] + dir[0];
		this->row = pos[1] + dir[1];
	}

	Location(const int *pos, const FWDirection dir)
	{
		if (dir != IMPOSSIBLE)
		{
			this->col = pos[1] + DIRECTIONS[dir][1];
			this->row = pos[0] + DIRECTIONS[dir][0];
		}
		else
		{
			this->col = -1;
			this->row = -1;
		}
	}

	Location(const Location &pos, FWDirection dir)
	{
		if (dir != IMPOSSIBLE)
		{
			this->col = pos.col + DIRECTIONS[dir][1];
			this->row = pos.row + DIRECTIONS[dir][0];
		}
		else
		{
			this->col = -1;
			this->row = -1;
		}
	}

	bool canWalkTo(FWDirection fd);
	void walkTo(FWDirection fd);
	void wrap();

	int to1D(size_t cols) const {
		return col + row * cols;
	}

	Location operator+(const Location &other) const
	{
		Location result(*this);
		result.col += other.col;
		result.row += other.row;
		return result;
	}

	Location operator-(const Location &other) const 
	{
		Location result(*this);
		result.col -= other.col;
		result.row -= other.row;
		return result;
	}

	int operator*(const Location & other) const {
		return col * other.col + row * other.row;
	}

	Location operator*(int other) const {
		return Location(this->row * other, this->col * other);
	}

	bool operator==(const Location & other) const {
		return other.row == row && other.col == col;
	}

	bool operator!=(const Location & other) const {
		return !operator==(other);
	}

	// TODO: Mejora si se cambia por el orden Z
	bool operator <(const Location & other) const {
		if (this->row < other.row) {
			return true;
		} else if (this->row > other.row) {
			return false;
		}
		return this->col < other.col;
	}

	FWDirection direction() const {
		FWDirection dir = IMPOSSIBLE;
		int m = 0;
		for (int i = 0; i < TDIRECTIONS; i++) {
			FWDirection d = FDIRECTIONS[i];
			Location l(DIRECTIONS[i]);
			if (this->operator*(l) > m) {
				m = this->operator*(l);
				dir = d;
			}
		}
		return dir;
	}
};

std::ostream & operator<<(std::ostream & o, const Location & l);

namespace std
{
		template<> struct hash<Location>
		{
				typedef Location argument_type;
				typedef std::size_t result_type;
				result_type operator()(argument_type const& s) const noexcept
				{
						result_type const h1 ( std::hash<int>{}(s.row) );
						result_type const h2 ( std::hash<int>{}(s.col) );
						return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
				}
		};
}

#endif //LOCATION_H_
