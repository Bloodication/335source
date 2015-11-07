/**************************************************/
/***           GLORY POINTS SYSTEM              ***/
/**************************************************/
void Player::RewardGlory(int amount, int source)
{   
    //Only change glory if we are assure that it never drops below zero.
    if ((_gloryPoints + amount) >= 0)
        _gloryPoints += amount;

    char const* glorySource;
    switch (source)
    {
        case PVP_HK: glorySource = "an honorable kill"; 
        break;

        case PVP_BG: glorySource = "winning a battleground";
        break;

        case PVP_ARENA: glorySource = "winning an arena";
        break;

        default: glorySource = "an unknown reason";
        break;
    }

    if (!CanRankUp())
        ChatHandler(GetSession()).PSendSysMessage("|CFF1CB619 Yor received %u Glory for %s. You need %u Glory to reach next rank|r", amount, glorySource, PointsUntilNextRank());
}

bool Player::CanRankUp()
{
    bool rankedUp = false; //Used to check if a player has ranked up

    if (_gloryPoints >= GLORY_RANK_1 && (!HasTitle(TITLE_SCOUT) && !HasTitle(TITLE_PRIVATE)))
    {
        RewardGloryRank(1);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_2 && (!HasTitle(TITLE_GRUNT) && !HasTitle(TITLE_CORPORAL)))
    {
        RewardGloryRank(2);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_3 && (!HasTitle(TITLE_SERGEANT_H) && !HasTitle(TITLE_SERGEANT_A)))
    {
        RewardGloryRank(3);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_4 && (!HasTitle(TITLE_SENIOR_SERGEANT) && !HasTitle(TITLE_MASTER_SERGEANT)))
    {
        RewardGloryRank(4);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_5 && (!HasTitle(TITLE_FIRST_SERGEANT) && !HasTitle(TITLE_SERGEANT_MAJOR)))
    {
        RewardGloryRank(5);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_6 && (!HasTitle(TITLE_STONE_GUARD) && !HasTitle(TITLE_KNIGHT)))
    {
        RewardGloryRank(6);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_7 && (!HasTitle(TITLE_BLOOD_GUARD) && !HasTitle(TITLE_KNIGHT_LIEUTENANT)))
    {
        RewardGloryRank(7);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_8 && (!HasTitle(TITLE_LEGIONNAIRE) && !HasTitle(TITLE_KNIGHT_CAPTAIN)))
    {
        RewardGloryRank(8);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_9 && (!HasTitle(TITLE_CENTURION) && !HasTitle(TITLE_KNIGHT_CHAMPION)))
    {
        RewardGloryRank(9);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_10 && (!HasTitle(TITLE_CHAMPION) && !HasTitle(TITLE_LIEUTENANT_COMMANDER)))
    {
        RewardGloryRank(10);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_11 && (!HasTitle(TITLE_LIEUTENANT_GENERAL) && !HasTitle(TITLE_COMMANDER)))
    {
        RewardGloryRank(11);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_12 && (!HasTitle(TITLE_GENERAL) && !HasTitle(TITLE_MARSHAL)))
    {
        RewardGloryRank(12);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_13 && (!HasTitle(TITLE_WARLORD) && !HasTitle(TITLE_FIELD_MARSHAL)))
    {
        RewardGloryRank(13);
        rankedUp = true;
    }

    if (_gloryPoints >= GLORY_RANK_14 && (!HasTitle(TITLE_HIGH_WARLORD) && !HasTitle(TITLE_GRAND_MARSHAL)))
    {
        RewardGloryRank(14);
        rankedUp = true;
    }

    if (rankedUp)
        return true;

    return false;
}

void Player::RewardGloryRank(int rank)
{
    CharTitlesEntry const* titleInfo;
    for (int itr = 1; itr <= 14; itr++)
    {
        if (itr == rank)
        {
            if (GetTeam() == ALLIANCE)
            {
                //Alliance ranks start from 1-14
                titleInfo = sCharTitlesStore.LookupEntry(rank);
                SetTitle(titleInfo);
                GetSession()->SendAreaTriggerMessage("Congratulations! You have been promoted to a new rank!");
            }
            else
            {
                //Horde Ranks start from 15-28
                titleInfo = sCharTitlesStore.LookupEntry(rank+14);
                SetTitle(titleInfo);
                GetSession()->SendAreaTriggerMessage("Congratulations! You have been promoted to a new rank!");
            }
        }
    }
    SaveToDB();
}

uint32 Player::PointsUntilNextRank()
{
    if (_gloryPoints < GLORY_RANK_1 && (!HasTitle(TITLE_SCOUT) && !HasTitle(TITLE_PRIVATE)))
        return GLORY_RANK_1 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_2 && (!HasTitle(TITLE_GRUNT) && !HasTitle(TITLE_CORPORAL)))
        return GLORY_RANK_2 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_3 && (!HasTitle(TITLE_SERGEANT_H) && !HasTitle(TITLE_SERGEANT_A)))
        return GLORY_RANK_3 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_4 && (!HasTitle(TITLE_SENIOR_SERGEANT) && !HasTitle(TITLE_MASTER_SERGEANT)))
        return GLORY_RANK_4 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_5 && (!HasTitle(TITLE_FIRST_SERGEANT) && !HasTitle(TITLE_SERGEANT_MAJOR)))
        return GLORY_RANK_5 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_6 && (!HasTitle(TITLE_STONE_GUARD) && !HasTitle(TITLE_KNIGHT)))
        return GLORY_RANK_6 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_7 && (!HasTitle(TITLE_BLOOD_GUARD) && !HasTitle(TITLE_KNIGHT_LIEUTENANT)))
        return GLORY_RANK_7 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_8 && (!HasTitle(TITLE_LEGIONNAIRE) && !HasTitle(TITLE_KNIGHT_CAPTAIN)))
        return GLORY_RANK_8 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_9 && (!HasTitle(TITLE_CENTURION) && !HasTitle(TITLE_KNIGHT_CHAMPION)))
        return GLORY_RANK_9 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_10 && (!HasTitle(TITLE_CHAMPION) && !HasTitle(TITLE_LIEUTENANT_COMMANDER)))
        return GLORY_RANK_10 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_11 && (!HasTitle(TITLE_LIEUTENANT_GENERAL) && !HasTitle(TITLE_COMMANDER)))
        return GLORY_RANK_11 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_12 && (!HasTitle(TITLE_GENERAL) && !HasTitle(TITLE_MARSHAL)))
        return GLORY_RANK_12 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_13 && (!HasTitle(TITLE_WARLORD) && !HasTitle(TITLE_FIELD_MARSHAL)))
        return GLORY_RANK_13 - _gloryPoints;

    if (_gloryPoints < GLORY_RANK_14 && (!HasTitle(TITLE_HIGH_WARLORD) && !HasTitle(TITLE_GRAND_MARSHAL)))
        return GLORY_RANK_14 - _gloryPoints;

    return 0;
}

void Player::_LoadGlory(int amount)
{
    if (amount < 0)
        amount = 0;

    _gloryPoints = amount;
   ChatHandler(GetSession()).PSendSysMessage("|CFF1CB619 You have %u Glory|r", _gloryPoints);
}