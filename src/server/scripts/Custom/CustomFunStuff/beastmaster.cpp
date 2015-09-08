
#include "Pet.h"
     
class Beastmaster_NPC : public CreatureScript
{
    public:
		Beastmaster_NPC() : CreatureScript("Beastmaster_NPC") {}
     
    void CreatePet(Player *player, Creature * m_creature, uint32 entry) {
     
            if(player->getClass() != CLASS_HUNTER) 
			{
                player->PlayerTalkClass->SendCloseGossip();
                return;
            }
     
            if(player->GetPet()) 
			{
                player->PlayerTalkClass->SendCloseGossip();
                return;
            }
     
            Creature *creatureTarget = m_creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY()+2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
            if(!creatureTarget) return;
           
            Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
			
            if (!pet)
			    return;
     
            // kill original creature
            creatureTarget->setDeathState(JUST_DIED);
            creatureTarget->RemoveCorpse();
            creatureTarget->SetHealth(0);                       // just for nice GM-mode view
     
            pet->SetPower(POWER_HAPPINESS, 1048000);
     
            pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
            pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
     
            // prepare visual effect for levelup
            pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
            pet->GetMap()->AddToMap(pet->ToCreature());
            // visual effect for levelup for lulz
            pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());
                   
            pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
            if (!pet->InitStatsForLevel(player->getLevel()))
                pet->UpdateAllStats();
         
            // caster has pet now
            player->SetMinion(pet, true);
     
            pet->SavePetToDB(PET_SAVE_AS_CURRENT);
            pet->InitTalentForLevel();
            player->PetSpellInitialize();
           
            //inform that has da pet
            player->PlayerTalkClass->SendCloseGossip();
        }
     
        bool OnGossipHello(Player * player, Creature * m_creature)
        {
            if (player->getClass() != CLASS_HUNTER)
            {
                return true;
            }
            player->ADD_GOSSIP_ITEM(4, "Normal Pet.", GOSSIP_SENDER_MAIN, 30);
            if (player->CanTameExoticPets())
            {
                player->ADD_GOSSIP_ITEM(4, "Exotic Pet.", GOSSIP_SENDER_MAIN, 50);
            }
            player->ADD_GOSSIP_ITEM(4, "Stable your pet.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
           // player->ADD_GOSSIP_ITEM(4, "Pet Food.", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
            player->ADD_GOSSIP_ITEM(4, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
            player->SEND_GOSSIP_MENU(60022, m_creature->GetGUID());
            return true;
        }
     
        bool OnGossipSelect(Player * player, Creature * m_creature, uint32 sender, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();
			
            switch (action)
            {
            case 100:
                OnGossipHello(player, m_creature);
            break;
     
            case 150:
                player->CLOSE_GOSSIP_MENU();
            break;
           
			case 30:
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bat:26:26:-15:0|t|r Bat", GOSSIP_SENDER_MAIN, 18);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_bear:26:26:-15:0|t|r Bear.", GOSSIP_SENDER_MAIN, 1);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_boar:26:26:-15:0|t|r Boar", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_cat:26:26:-15:0|t|r Cat.", GOSSIP_SENDER_MAIN, 4);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_vulture:26:26:-15:0|t|r Vulture.", GOSSIP_SENDER_MAIN, 5);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_crab:26:26:-15:0|t|r Crab.", GOSSIP_SENDER_MAIN, 6);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_crocolisk:26:26:-15:0|t|r Cocolisk.", GOSSIP_SENDER_MAIN, 7);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_dragonhawk:26:26:-15:0|t|r Dragonhawk.", GOSSIP_SENDER_MAIN, 17);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_gorilla:26:26:-15:0|t|r Gorilla", GOSSIP_SENDER_MAIN, 8);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wolf:26:26:-15:0|t|r Wolf.", GOSSIP_SENDER_MAIN, 9);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_hyena:26:26:-15:0|t|r Hyena.", GOSSIP_SENDER_MAIN, 10);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_moth:26:26:-15:0|t|r Moth.", GOSSIP_SENDER_MAIN, 11);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_owl:26:26:-15:0|t|r Owl.", GOSSIP_SENDER_MAIN, 12);
				player->ADD_GOSSIP_ITEM(4, "Next Page", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(2, "Main Menu.", GOSSIP_SENDER_MAIN, 100);
				player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
				break;

			case 31:
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_raptor:26:26:-15:0|t|r Raptor.", GOSSIP_SENDER_MAIN, 20);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_ravager:26:26:-15:0|t|r Ravager.", GOSSIP_SENDER_MAIN, 19);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_tallstrider:26:26:-15:0|t|r Tallstrider.", GOSSIP_SENDER_MAIN, 13);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_scorpid:26:26:-15:0|t|r Scorpid.", GOSSIP_SENDER_MAIN, 414);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_spider:26:26:-15:0|t|r Spider", GOSSIP_SENDER_MAIN, 16);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_cobrastrikes:26:26:-15:0|t|r Cobra.", GOSSIP_SENDER_MAIN, 21);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_turtle:26:26:-15:0|t|r Turtle.", GOSSIP_SENDER_MAIN, 15);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_wasp:26:26:-15:0|t|r Wasp.", GOSSIP_SENDER_MAIN, 93);
				player->ADD_GOSSIP_ITEM(4, "<- Back.", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(2, "<- Main Menu.", GOSSIP_SENDER_MAIN, 100);
				player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
				break;

			case 50:
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_chimera:26:26:-15:0|t|r Chimera.", GOSSIP_SENDER_MAIN, 51);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_corehound:26:26:-15:0|t|r Corehound", GOSSIP_SENDER_MAIN, 52);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_devilsaur:26:26:-15:0|t|r Devilsaur.", GOSSIP_SENDER_MAIN, 53);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_rhino:26:26:-15:0|t|r Rhino.", GOSSIP_SENDER_MAIN, 54);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_silithid:26:26:-15:0|t|r Silithd ", GOSSIP_SENDER_MAIN, 55);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_hunter_pet_worm:26:26:-15:0|t|r Worm.", GOSSIP_SENDER_MAIN, 56);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Ability_druid_catform:26:26:-15:0|t|r Loque'nahak.", GOSSIP_SENDER_MAIN, 57);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_nature_spiritwolf:26:26:-15:0|t|r Spirit wolf.", GOSSIP_SENDER_MAIN, 58);
				player->ADD_GOSSIP_ITEM(6, "|cff00ff00|TInterface\\icons\\Spell_shadow_spectralsight:26:26:-15:0|t|r Spirit beast.", GOSSIP_SENDER_MAIN, 59);
				player->ADD_GOSSIP_ITEM(4, "Normal Menu.", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(2, "Main Menu.", GOSSIP_SENDER_MAIN, 100);
				player->SEND_GOSSIP_MENU(1, m_creature->GetGUID());
				break;
         
                case GOSSIP_OPTION_STABLEPET:
                    player->GetSession()->SendStablePet(m_creature->GetGUID());
                break;
                case GOSSIP_OPTION_VENDOR:
                    player->GetSession()->SendListInventory(m_creature->GetGUID());
                break;
                case 51: //chimera
                    CreatePet(player, m_creature, 21879);
                break;
                case 52: //core hound
                    CreatePet(player, m_creature, 21108);
                break;
                case 53: //Devilsaur
                    CreatePet(player, m_creature, 20931);
                break;
                case 54: //rhino
                    CreatePet(player, m_creature, 30445);
                break;
                case 55: //silithid
                    CreatePet(player, m_creature, 5460);
                break;
                case 56: //Worm
                    CreatePet(player, m_creature, 30148);
                break;
                case 57: //Loque'nahak
                    CreatePet(player, m_creature, 32517);
                break;
                case 58: //Skoll
                    CreatePet(player, m_creature, 35189);
                break;
                case 59: //Gondria
                    CreatePet(player, m_creature, 33776);
                break;
                case 16: //Spider
                    CreatePet(player, m_creature, 2349);
                break;
                case 17: //Dragonhawk
                    CreatePet(player, m_creature, 27946);
                break;
                case 18: //Bat
                    CreatePet(player, m_creature, 28233);
                break;
                case 19: //Ravager
                    CreatePet(player, m_creature, 17199);
                break;
                case 20: //Raptor
                    CreatePet(player, m_creature, 14821);
                break;
                case 21: //Serpent
                    CreatePet(player, m_creature, 28358);
                break;
                case 1: //bear
                    CreatePet(player, m_creature, 29319);
                break;
                case 2: //Boar
                    CreatePet(player, m_creature, 29996);
                break;
                case 93: //Bug
                    CreatePet(player, m_creature, 28085);
                break;
                case 4: //cat
                    CreatePet(player, m_creature, 28097);
                break;
                case 5: //carrion
                    CreatePet(player, m_creature, 26838);
                break;
                case 6: //crab
                    CreatePet(player, m_creature, 24478);
                break;  
                case 7: //crocolisk
                    CreatePet(player, m_creature, 1417);
                break;  
                case 8: //gorila
                    CreatePet(player, m_creature, 28213);
                break;
                case 9: //hound
                    CreatePet(player, m_creature, 29452);
                break;
                case 10: //hynea
                    CreatePet(player, m_creature, 13036);
                break;
                case 11: //Moth
                    CreatePet(player, m_creature, 27421);
                break;
                case 12: //owl
                    CreatePet(player, m_creature, 23136);
                break;
                case 13: //strider
                    CreatePet(player, m_creature, 22807);
                break;
                case 414: //scorpid
                    CreatePet(player, m_creature, 9698);
                break;
                case 15: //turtle
                    CreatePet(player, m_creature, 25482);
                break;
            }
            return true;
        }
};
     
void AddSC_Beastmaster_NPC()
{
    new Beastmaster_NPC;
}
