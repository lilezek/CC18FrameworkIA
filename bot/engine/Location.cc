#include "Location.h"
#include "State.h"

std::ostream &operator<<(std::ostream &o, const Location &l)
{
	return o << l.row << ", " << l.col;
}

bool Location::canWalkTo(FWDirection fd)
{
	State &s = State::getSingleton();
	if (fd == IMPOSSIBLE)
	{
		return false;
	}
	return s.canMoveTo(*this, fd);
}

void Location::walkTo(FWDirection fd)
{
	State &s = State::getSingleton();
	s.makeMove(*this, fd);
}

void Location::wrap()
{
	State &s = State::getSingleton();
	col = (col + s.cols) % s.cols;
	row = (row + s.rows) % s.rows;
}