# KaraokeReplayY6
 Small ASI hook that patches audio start offsets in karaoke replay for Yakuza 6. Used for setting custom audio start offsets to help with custom karaoke modding. Other Dragon Engine Yakuza games store the audio offsets in db.par, so a similar patch is not needed.

# Installing
Unpack the [latest release zip](https://github.com/SutandoTsukai181/KaraokeReplayY6/releases/latest) into Yakuza 6 installation directory (next to the game's exe). Modify the audio offsets in KaraokeReplay.ini. Audio offsets are in seconds, and each offset corresponds to one of the karaoke songs in Yakuza 6.

If a mod uses this ASI as a dependency for modifying the offsets, use the KaraokeReplay.ini provided by that mod instead. If the mod doesn't have an ini file, change the values inside the ini provided with the ASI to the values specified by the mod.

# Building
Use [Premake](https://premake.github.io) to generate the solution files.

# Credits
Based on [CookiePLMonster](https://github.com/CookiePLMonster)'s SilentPatches and [ModUtils](https://github.com/CookiePLMonster/ModUtils). Also using [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader).

Special thanks to [Timo654](https://github.com/Timo654) for extensive testing, researching the game's karaoke system, and providing the memory patterns (basically everything).

Thanks to [jas0n098](https://github.com/jas0n098) for helping with debugging an issue that broke the hook.
