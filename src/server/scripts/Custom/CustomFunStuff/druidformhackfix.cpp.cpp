#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "SpellScript.h"
#include "Player.h"

enum Spells
{
    SPELL_CATFORM = 768,
    SPELL_DIREBEAR = 21178,
    SPELL_BEARFORM = 5487,
    SPELL_MOONKIN = 24858
};

class spell_ex_24858 : public SpellScriptLoader
{
public:
    spell_ex_24858() : SpellScriptLoader("spell_ex_24858") { }

    class spell_ex_24858_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ex_24858_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MOONKIN))
                return false;
            return true;
        }

        bool Load()
        {
            if (Unit* caster = GetCaster())
                if (caster->GetTypeId() == TYPEID_PLAYER)
                    return true;
            return false;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            if (caster->GetTeamId() == TEAM_HORDE)
                caster->SetDisplayId(43789);
            if (caster->GetTeamId() == TEAM_ALLIANCE)
                caster->SetDisplayId(43787);
        };

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_ex_24858_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ex_24858_AuraScript();
    }
};

class spell_ex_5487 : public SpellScriptLoader
{
public:
    spell_ex_5487() : SpellScriptLoader("spell_ex_5487") { }

    class spell_ex_5487_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ex_5487_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_BEARFORM))
                return false;
            return true;
        }

        bool Load()
        {
            if (Unit* caster = GetCaster())
                if (caster->GetTypeId() == TYPEID_PLAYER)
                    return true;
            return false;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            if (caster->GetTeamId() == TEAM_HORDE)
                caster->SetDisplayId(43742);
            if (caster->GetTeamId() == TEAM_ALLIANCE)
                caster->SetDisplayId(43743);
        };

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_ex_5487_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ex_5487_AuraScript();
    }
};

class spell_ex_21178 : public SpellScriptLoader
{
public:
    spell_ex_21178() : SpellScriptLoader("spell_ex_21178") { }

    class spell_ex_21178_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ex_21178_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DIREBEAR))
                return false;
            return true;
        }

        bool Load()
        {
            if (Unit* caster = GetCaster())
                if (caster->GetTypeId() == TYPEID_PLAYER)
                    return true;
            return false;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            if (caster->GetTeamId() == TEAM_HORDE)
                caster->SetDisplayId(43742);
            if (caster->GetTeamId() == TEAM_ALLIANCE)
                caster->SetDisplayId(43743);
        };

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_ex_21178_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ex_21178_AuraScript();
    }
};

class spell_ex_768 : public SpellScriptLoader
{
public:
    spell_ex_768() : SpellScriptLoader("spell_ex_768") { }

    class spell_ex_768_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ex_768_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_CATFORM))
                return false;
            return true;
        }

        bool Load()
        {
            if (Unit* caster = GetCaster())
                if (caster->GetTypeId() == TYPEID_PLAYER)
                    return true;
            return false;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            if (caster->GetTeamId() == TEAM_HORDE)
                caster->SetDisplayId(43775);
            if (caster->GetTeamId() == TEAM_ALLIANCE)
                caster->SetDisplayId(43765);
        };

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_ex_768_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ex_768_AuraScript();
    }
};

void AddSC_DruidHax()
{
    new spell_ex_768;
    new spell_ex_21178;
    new spell_ex_5487;
    new spell_ex_24858;
}