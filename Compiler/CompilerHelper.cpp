#include "CompilerHelper.h"
#include "Pe.h"

void CompilerHelper::Analyze()
{
    if (static constexpr auto PATTERN_BORLAND = "Borland"; Pe::FindData(PATTERN_BORLAND, strlen(PATTERN_BORLAND), TRUE))
        CompilerType = CompilerType::Borland;
    else
        CompilerType = CompilerType::Msvc;
}
