
#include "ScriptPCH.h"
#include "Chat.h"
#include <stdarg.h>
#include "GameObject.h"
#include "PoolMgr.h"
#include "ObjectAccessor.h"
#include "Transport.h"
using namespace std;
enum ForbiddenAreas
{
	AREA_MALL = 395,   // mall
};

// quadral ------------------------------------------>
class map_security : public PlayerScript
{
public:
	map_security() : PlayerScript("map_security") {}

	void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
	{
		switch (pPlayer->GetAreaId())
		{
		case AREA_MALL:
		{
			if (pPlayer->getLevel() <= 79)
			{
				pPlayer->SetPhaseMask(1, true);
			}
			else
			{
				pPlayer->SetPhaseMask(2, true);
			}



		}
		}
	}
};

void AddSC_Security_Scripts()
{
	new map_security();
}