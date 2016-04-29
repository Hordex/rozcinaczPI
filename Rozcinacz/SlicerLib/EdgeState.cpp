#include <ostream>
#include "EdgeState.h"


inline std::ostream& operator<<(std::ostream & os, EdgeState const state)
{
	switch (state) {
	case Free:
		os << "Free";
		break;
	case Locked:
		os << "Locked";
		break;
	case Deleted:
		os << "Deleted";
	}
	return os;
}
