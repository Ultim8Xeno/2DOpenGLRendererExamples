#pragma once
#ifdef DEBUG
#define ASSERT(x) if (!(x)) {__debugbreak();}	// Works in visual studio only
#else
#define ASSERT(x) x
#endif // DEBUG