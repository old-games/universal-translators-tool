#include "pch.h"
#include "uttypes.h"


const int BPP::ColourNumber[BPP::bppNum] =
{
	2,
	4,
	16,
	256,
	65536,
	16777216,
	16777216
};

const int BPP::Bits[BPP::bppNum] =
{
	1,
	2,
	4,
	8,
	16,
	24,
	32
};

const wxString BPP::Names[BPP::bppNum] =
{
	"Monochrome",
	"CGA",
	"EGA",
	"VGA",
	"High color",
	"True color",
	"True color with alpha"
};


size_t BPP::PaletteSize( int n )
{
	wxASSERT( n < bppNum );
	return ColourNumber[n] * sizeof(Pixel);
}

