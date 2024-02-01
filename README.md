# KrkrPatch

Auto load patch for krkr game.

### Usage
- Rename **`krkr-version.dll`** to **`version.dll`** then put into game root dir.

- Put patch files into **`unencrypted`** folder without directory structure.

    - (Optional) Pack **`unencrypted`** folder to **`unencrypted.xp3`** archive, use [GARbro](https://github.com/morkt/GARbro) or [Xp3Pack](https://github.com/arcusmaximus/KirikiriTools)

- Put **`unencrypted | unencrypted.xp3 | both(priority : folder > archive)`** & **`version.dll`** into game folder.

- Supports multiple patches : **`unencrypted, unencrypted2, unencrypted3...unencrypted9 (larger seq, higher priority)`**.

    - Picontinuous sequences are not necessary and dir & xp3 mixed supported, sample : **`unencrypted3, unencrypted5.xp3, unencrypted9`**.

# WafflePatch

Patch for waffle game to prevent crashes.

### Usage

- Rename **`waffle-version.dll`** to **`version.dll`** then put into game root dir.

# Merged
- [KrkrPatch](https://github.com/bynejake/KrkrPatch)
- [WafflePatch](https://github.com/bynejake/WafflePatch)
