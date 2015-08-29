
#include "ScriptPCH.h"
#include "Chat.h"
#include <stdarg.h>
#include "GameObject.h"
#include "PoolMgr.h"
#include "ObjectAccessor.h"
#include "Transport.h"	
using namespace std;

// quadral ------------------------------------------>
class Guild_invite : public PlayerScript
{
public:
	Guild_invite() : PlayerScript("Guild_invite") {}

	void OnLogin(Player* pPlayer, bool /* OnLogin */ )
	{
			pPlayer->SetInGuild(1);
	}
};

void AddSC_Guild_invite()
{
	new Guild_invite();
}