//by SymbolixDEV https://github.com/SymbolixDEV

class Morpher_Npc : public CreatureScript
{
    public:
    Morpher_Npc() : CreatureScript("Morpher_Npc") { }
 
    bool OnGossipHello(Player * pPlayer, Creature * pCreature)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        pPlayer->ADD_GOSSIP_ITEM(8, "Blood Elf Female", GOSSIP_SENDER_MAIN, 4);
        pPlayer->ADD_GOSSIP_ITEM(8, "Blood Elf Male", GOSSIP_SENDER_MAIN, 5);
        pPlayer->ADD_GOSSIP_ITEM(8, "Gnome Female", GOSSIP_SENDER_MAIN, 6);
        pPlayer->ADD_GOSSIP_ITEM(8, "Gnome Male", GOSSIP_SENDER_MAIN, 7);
        pPlayer->ADD_GOSSIP_ITEM(8, "Human Female", GOSSIP_SENDER_MAIN, 8);
        pPlayer->ADD_GOSSIP_ITEM(8, "Human Male", GOSSIP_SENDER_MAIN, 9);
        pPlayer->ADD_GOSSIP_ITEM(8, "Tauren Female", GOSSIP_SENDER_MAIN, 10);
        pPlayer->ADD_GOSSIP_ITEM(8, "Tauren Male", GOSSIP_SENDER_MAIN, 11);
        pPlayer->ADD_GOSSIP_ITEM(8, "Undead Pirate", GOSSIP_SENDER_MAIN, 12);
        pPlayer->ADD_GOSSIP_ITEM(8, "Ethereal", GOSSIP_SENDER_MAIN, 13);
        pPlayer->ADD_GOSSIP_ITEM(8, "Mad Scientist)", GOSSIP_SENDER_MAIN, 14);
        pPlayer->ADD_GOSSIP_ITEM(8, "Vrykul", GOSSIP_SENDER_MAIN, 15);
        pPlayer->ADD_GOSSIP_ITEM(8, "Necromancer", GOSSIP_SENDER_MAIN, 16);
        pPlayer->ADD_GOSSIP_ITEM(8, "Skeletal Mage", GOSSIP_SENDER_MAIN, 17);
        pPlayer->ADD_GOSSIP_ITEM(8, "Frost Troll", GOSSIP_SENDER_MAIN, 18);
        pPlayer->ADD_GOSSIP_ITEM(8, "Blood Elf Demon Girl", GOSSIP_SENDER_MAIN, 19);
        pPlayer->ADD_GOSSIP_ITEM(8, "Human 19 Twink", GOSSIP_SENDER_MAIN, 20);
        pPlayer->ADD_GOSSIP_ITEM(8, "Undead 19 Twink", GOSSIP_SENDER_MAIN, 21);
        pPlayer->PlayerTalkClass->SendGossipMenu(9452, pCreature->GetGUID());
        return true;
    }
       
    bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            pPlayer->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {

            case 4:
                pPlayer->SetDisplayId(20370);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Female Blood Elf.", LANG_UNIVERSAL, pPlayer);
                break;

            case 5:
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Male Blood Elf.", LANG_UNIVERSAL, pPlayer);
                break;

            case 6:
                pPlayer->DestroyItemCount(45624, 25, true);
                pPlayer->SetDisplayId(20320);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Gnome Female.", LANG_UNIVERSAL, pPlayer);
                break;

            case 7:
                pPlayer->SetDisplayId(20580);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Gnome Male.", LANG_UNIVERSAL, pPlayer);
                break;

            case 8:
                pPlayer->SetDisplayId(19724);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Human Female.", LANG_UNIVERSAL, pPlayer);
                break;

            case 9:
                pPlayer->SetDisplayId(19723);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Human Male.", LANG_UNIVERSAL, pPlayer);
                break;

            case 10:
                pPlayer->SetDisplayId(20584);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Tauren Female.", LANG_UNIVERSAL, pPlayer);
                break;

            case 11:
                pPlayer->DestroyItemCount(45624, 25, true);
                pPlayer->SetDisplayId(20319);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Tauren Male", LANG_UNIVERSAL, pPlayer);
                break;

            case 12:
                pPlayer->SetDisplayId(25042);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Undead Pirate", LANG_UNIVERSAL, pPlayer);
                break;

            case 13:
                pPlayer->SetDisplayId(24942);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Ethereal", LANG_UNIVERSAL, pPlayer);
                break;

            case 14:
                pPlayer->SetDisplayId(23875);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Mad Scientist", LANG_UNIVERSAL, pPlayer);
                break;

            case 15:
                pPlayer->SetDisplayId(22634);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Vrykul", LANG_UNIVERSAL, pPlayer);
                break;

            case 16:
                pPlayer->SetDisplayId(24793);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Necromancer", LANG_UNIVERSAL, pPlayer);
                break;

            case 17:
                pPlayer->SetDisplayId(24495);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.7f);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Skeletal Mage", LANG_UNIVERSAL, pPlayer);
                break;

            case 18:
                pPlayer->SetDisplayId(24938);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Frost Troll", LANG_UNIVERSAL, pPlayer);
                break;

            case 19:
                pPlayer->SetDisplayId(24930);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a BELF Demon Girl", LANG_UNIVERSAL, pPlayer);
                break;

            case 20:
                pPlayer->SetDisplayId(29796);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Human 19 Twink", LANG_UNIVERSAL, pPlayer);
                break;

            case 21:
                pPlayer->SetDisplayId(29795);
                pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->Whisper("You have been Morphed into a Undead 19 Twink", LANG_UNIVERSAL, pPlayer);
                break;
                }
            }
            
            return true;
        }
};
void AddSC_Morpher_Npc()
{
    new Morpher_Npc();
}
