//quadral

#include "ScriptPCH.h"
#include "Battleground.h"

class FastArenaCrystal : public GameObjectScript
{
public:

	FastArenaCrystal()
		: GameObjectScript("FastArenaCrystal") { }

	bool OnGossipHello(Player* player, GameObject* go)
	{
		if (Battleground *bg = player->GetBattleground())
		{
			if (!bg->IsChallenge())
			{
				if (bg->isArena() && bg->GetArenaType() == ARENA_TYPE_5v5) // 1v1
					player->GetSession()->SendAreaTriggerMessage("Players marked as ready: %u/2", bg->ClickFastStart(player, go));

				if (bg->isArena() && bg->GetArenaType() == ARENA_TYPE_2v2) // 2v2
					player->GetSession()->SendAreaTriggerMessage("Players marked as ready: %u/4", bg->ClickFastStart(player, go));

				if (bg->isArena() && bg->GetArenaType() == ARENA_TYPE_3v3) // 3v3
					player->GetSession()->SendAreaTriggerMessage("Players marked as ready: %u/6", bg->ClickFastStart(player, go));
			}
		}
		return false;
	}
};

void AddSC_fast_arena_start()
{
	new FastArenaCrystal();
}
