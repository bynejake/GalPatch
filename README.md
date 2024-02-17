# KrkrPatch

Auto load patch for krkr game.

### Usage
- Rename **`krkr-version.dll`** to **`version.dll`** then put into game root dir.

- Put patch files into **`unencrypted`** folder without directory structure.

    - (Optional) Pack **`unencrypted`** folder to **`unencrypted.xp3`** archive, use [GARbro](https://github.com/morkt/GARbro) or [Xp3Pack](https://github.com/arcusmaximus/KirikiriTools)

- Put **`unencrypted | unencrypted.xp3 | both(priority : folder > archive)`** into game root dir.

- Supports multiple patches : **`unencrypted, unencrypted2~9 (larger seq, higher priority)`**.

    - Picontinuous sequences are not necessary, sample : **`unencrypted3.xp3, unencrypted7`**.

# WafflePatch

Patch for waffle game to prevent crashes.

### Usage

- Rename **`waffle-version.dll`** to **`version.dll`** then put into game root dir.

# Merged
- [KrkrPatch](https://github.com/bynejake/KrkrPatch)
- [WafflePatch](https://github.com/bynejake/WafflePatch)
