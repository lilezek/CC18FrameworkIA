#ifndef PATH_H
#define PATH_H

#include <vector>
#include "../engine/Location.h"

struct Step {
    Location point;
    FWDirection origin;
    int distance;

    bool operator ==(const Step & other) const {
        return point == other.point;
    }
};

namespace std
{
    template<> struct hash<Step>
    {
        typedef Step argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const noexcept
        {
            return std::hash<Location>{}(s.point);
        }
    };

}

typedef std::vector<Step> Path;

std::ostream & operator<<(std::ostream & o, const Path & p);

#endif