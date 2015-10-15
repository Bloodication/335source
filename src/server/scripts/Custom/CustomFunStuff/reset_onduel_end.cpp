// quadral

class Reset_OnDuelEnd : public PlayerScript
{
public:
    Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    // Call the script after the 3s countdown
    void OnDuelStart(Player * player, Player * plTarget)
    {
        // Clear both players cooldowns
        player->RemoveArenaSpellCooldowns();
        plTarget->RemoveArenaSpellCooldowns();
        player->RemoveAura(10278);             // Hand of Protection
        plTarget->RemoveAura(10278);
        player->RemoveAura(498);               // Divine Protection
        plTarget->RemoveAura(498);
        player->RemoveAura(642);               // Divine Shield
        plTarget->RemoveAura(642);
        player->RemoveAura(41425);             // Remove Hypothermia Debuff
        plTarget->RemoveAura(41425);
        player->RemoveAura(25771);             // Remove Forbearance Debuff
        plTarget->RemoveAura(25771);
        player->RemoveAura(57724);             // Remove Sated Debuff
        plTarget->RemoveAura(57724);
        player->RemoveAura(57723);             // Remove Exhaustion Debuff
        plTarget->RemoveAura(57723);
        player->RemoveAura(66233);             // Remove Ardent Defender Debuff
        plTarget->RemoveAura(66233);
        player->RemoveAura(61987);             // Avenging Wrath Marker
        plTarget->RemoveAura(61987);
        player->RemoveAura(11196);             // Remove Recently Bandaged Debuff
        plTarget->RemoveAura(11196);
        player->SetHealth(player->GetMaxHealth());
        player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
        plTarget->SetHealth(plTarget->GetMaxHealth());
        plTarget->SetPower(POWER_MANA,  plTarget->GetMaxPower(POWER_MANA));
        player->SetPower(POWER_RAGE, 0);       // Remove Rage and Runic Power
        plTarget->SetPower(POWER_RAGE, 0);
        player->SetPower(POWER_RUNIC_POWER, 0);
        plTarget->SetPower(POWER_RUNIC_POWER, 0);
        //player->CastSpell(player, 46705, true);     // Honorless Target
        //plTarget->CastSpell(plTarget, 46705, true); // Honorless Target
    }
};

void AddSC_Reset()
{
    new Reset_OnDuelEnd;
}
