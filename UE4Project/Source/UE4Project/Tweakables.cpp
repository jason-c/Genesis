#include "Tweakables.h"

UTweakables::UTweakables()
{
	for (int i = 0; i < (int)EBlockType::Count; i++)
	{
		BlockTypes[i].Type = (EBlockType)i;
	}
}
