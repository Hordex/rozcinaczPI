#pragma once
#include <ostream>

/// <summary>
/// Enum for edge states
/// </summary>
enum EdgeState
{
	/// <summary>
	/// Edge can be modified
	/// </summary>
	Free,
	/// <summary>
	/// Edge exists but cannot be modified
	/// </summary>
	Locked,
	/// <summary>
	/// Edge is deleted
	/// </summary>
	Deleted
};

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