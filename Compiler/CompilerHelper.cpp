#include "CompilerHelper.h"
#include "PE.h"

void CompilerHelper::Init()
{
	if (static constexpr auto PATTERN_BORLAND = "Borland"; PE::FindData(PATTERN_BORLAND, strlen(PATTERN_BORLAND), TRUE))
        CompilerType = CompilerType::Borland;
    else
        CompilerType = CompilerType::Msvc;
}
