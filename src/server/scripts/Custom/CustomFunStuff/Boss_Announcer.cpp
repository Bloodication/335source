

class Boss_Announcer : public PlayerScript
{
public:
Boss_Announcer() : PlayerScript ("Boss_Announcer") {}

void OnCreatureKill(Player* player, Creature* boss)
{

if (boss->isWorldBoss())
{
std::string plrname = player->GetName();
std::string bossname = boss->GetName();	
char msg[250];
snprintf(msg, 250, "|CFF7BBEF7[ Boss Announcer ]|r:|cffff0000 %s |r and his group killed world boss |CFF18BE00[%s]|r !!!",plrname.c_str(),bossname.c_str());
sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
}
}
};

void AddSC_Boss_Announcer()
{
new Boss_Announcer;
}