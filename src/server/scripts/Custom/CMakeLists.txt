# Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
#  ${sources_Custom}
Custom/Transmog/Transmogrification.h
Custom/Transmog/Transmogrification.cpp
Custom/Transmog/Transmogrifier.cpp
Custom/1V1/npc_arena1v1.cpp
Custom/1V1/npc_arena1v1.h
Custom/PVP/arena_crystal.cpp
Custom/Arenaspectator/arena_spectator.cpp
Custom/CustomFunStuff/teleporter_npc.cpp
Custom/CustomRate/custom_rates.cpp
Custom/TransmogDisplayVendor/TransmogDisplayVendorConf.h
Custom/TransmogDisplayVendor/TransmogDisplayVendor.cpp
Custom/PVP/arenaladder.cpp
Custom/WorldChat/worldchat.cpp
Custom/CustomFunStuff/titles.cpp
Custom/CustomFunStuff/beastmaster.cpp
Custom/CustomFunStuff/enchanter.cpp
Custom/Killstreak/killstreak.cpp
Custom/CustomFunStuff/cooldowns_crystal.cpp
Custom/TemplateNPC/TemplateNPC.cpp
Custom/TemplateNPC/TemplateNPC.h
Custom/GuildHouses/guildmaster.cpp
Custom/CustomFunStuff/reset_onduel_end.cpp
Custom/CustomFunStuff/announce_login.cpp
Custom/CustomFunStuff/Bloodmoneyduels.cpp
Custom/CustomFunStuff/Boss_Announcer.cpp
Custom/CustomFunStuff/playertools.cpp
Custom/CustomFunStuff/professions.cpp
Custom/CustomFunStuff/Phased_duel.cpp
Custom/CustomFunStuff/druidformhackfix.cpp
Custom/CustomFunStuff/morpher_npc.cpp
Custom/3v3/npc_solo3v3.cpp
Custom/3v3/npc_solo3v3.h
Custom/GoMove/GOMove.cpp
Custom/Dementia/Arena_Anti-Draw.cpp
Custom/Reforging/Reforging.cpp
Custom/PVP/Glory.cpp
)

message("  -> Prepared: Custom")
