# GalPatch
patch for krkr and waffle game.

# KrkrPatch

Load patch for krkr game.

## Usage
- Download [latest release](https://github.com/bynejake/KrkrPatch/releases/latest), rename **`version-(debug/release).dll`** to **`version.dll`**.

- Put patch files into **`unencrypted`** folder without directory structure.

    - (Optional) Pack **`unencrypted`** folder to **`unencrypted.xp3`** archive, use [GARbro](https://github.com/morkt/GARbro) or [Xp3Pack](https://github.com/arcusmaximus/KirikiriTools)

- Put **`unencrypted | unencrypted.xp3 | both(priority : folder > archive)`** & **`version.dll`** into game folder.

- Supports multiple patches : **`unencrypted, unencrypted2, unencrypted3...unencrypted9 (larger seq, higher priority)`**.

    - Picontinuous sequences are not necessary and dir & xp3 mixed supported, sample : **`unencrypted3, unencrypted5.xp3, unencrypted9`**.

## Log

Auto write log into **`version.log`**(only debug version)

# WafflePatch

Patch for waffle game to prevent crashes.

## Usage
- Download [latest release](https://github.com/bynejake/KrkrPatch/releases/latest).

- Put **`version.dll`** into game root dir.
