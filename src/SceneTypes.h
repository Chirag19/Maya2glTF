#pragma once
#include "BasicTypes.h"

// <0 means an invalid index
typedef __int32 Index;

/** Maya uses strings to identify color and texture-coordinate sets. We use indices */
typedef int SetIndex;

typedef Float3 Position;
typedef Float3 Normal;
typedef Float2 TexCoord;
typedef Float4 Color;

typedef std::vector<Position> PositionVector;
typedef std::vector<Normal> NormalVector;
typedef std::vector<TexCoord> TexCoordVector;
typedef std::vector<Color> ColorVector;
typedef std::vector<Index> IndexVector;

enum PrimitiveKind
{
	// TODO: Support other primitives
	TRIANGLE_LIST
};

enum Limitations
{
	MAX_TEXTURES_PER_VERTEX = 4,
	MAX_SKIN_INFLUENCES_PER_VERTEX = 4,
};

namespace Semantic
{
	enum Kind
	{
		POSITION,
		NORMAL,
		COLOR,
		TEXCOORD,
		COUNT,
	};

	inline Kind from(int s)
	{
		assert(s >= 0 && s < COUNT);
		return static_cast<Kind>(s);
	}

	// Get the number of components per semantic 
	inline size_t dimension(const Kind s)
	{
		switch (s)
		{
		case POSITION:	return array_size<Position>::size;
		case NORMAL:	return array_size<Normal>::size;
		case COLOR:		return array_size<Color>::size;
		case TEXCOORD:	return array_size<TexCoord>::size;
		default: assert(false); return 0;
		}
	}

	inline const char* name(const Kind s)
	{
		switch (s)
		{
		case POSITION:	return "POSITION";
		case NORMAL:	return "NORMAL";
		case COLOR:		return "COLOR";
		case TEXCOORD:	return "TEXCOORD";
		default: assert(false); return "UNKNOWN";
		}
	}

	inline std::string attributeName(const Kind s, const int setIndex)
	{
		switch (s)
		{
		case POSITION:	return std::string("POSITION");
		case NORMAL:	return std::string("NORMAL");
		case COLOR:		return std::string("COLOR_") + std::to_string(setIndex);
		case TEXCOORD:	return std::string("TEXCOORD_") + std::to_string(setIndex);
		default: assert(false); return "UNKNOWN";
		}
	}
}