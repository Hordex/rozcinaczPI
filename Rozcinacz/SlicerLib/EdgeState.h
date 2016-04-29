#pragma once
#include <iosfwd>

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

std::ostream& operator<<(std::ostream & os, EdgeState const state);