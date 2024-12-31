# KrkrPatch

Auto load patch for krkr game.

### Usage
- Rename **`krkr-version.dll`** to **`version.dll`** then put into game root dir.

- Put patch files into **`unencrypted`** folder without directory structure.

    - Multiple patches supported: **`unencrypted, unencrypted2~9 (larger seq, higher priority)`**.

    - Picontinuous sequences are not necessary, sample : **`unencrypted3, unencrypted7`**.

    - (Optional) Pack **`unencrypted`** folder to **`unencrypted.xp3`** archive **`(priority : folder > archive)`**.

        - use [**`GARbro`**](https://github.com/morkt/GARbro) or [**`Xp3Pack`**](https://github.com/arcusmaximus/KirikiriTools)

# WafflePatch

Patch for waffle game to prevent crashes.

### Usage

- Rename **`waffle-version.dll`** to **`version.dll`** then put into game root dir.

- (Optional) **`waffle-version-protected.dll`** & [**`version.json`**](https://github.com/bynejake/GalPatch/blob/main/WafflePatch/version.json)

    - For **`ProtectedExe (EnigmaProtector etc.)`** if memory patch needed.

    - Json sample for **`game : kanin, encoding : zh, font : Unifont`**.

# Merged
- [**`KrkrPatch`**](https://github.com/bynejake/KrkrPatch)
- [**`WafflePatch`**](https://github.com/bynejake/WafflePatch)
