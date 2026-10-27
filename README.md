# fheroes2: Roguelike Level-Up Rewards

An unofficial, independently maintained modification of the [fheroes2](https://github.com/ihhub/fheroes2) engine for **Heroes of Might and Magic II** 
Made by [InfernoGeo](https://www.youtube.com/@InfernoGeoHeroes)

This mod adds **roguelike-inspired rewards when heroes level up**, including opportunities to choose skills, artifacts, and spells. It focuses on giving hero progression more variety and interesting choices.

## Download for Windows

**[Download fheroes2 Roguelike v0.1 Alpha — Windows 64-bit ZIP](https://github.com/georgestefan94/fheroes2_Roguelike/releases/download/v0.1.0-alpha/fheroes2-Roguelike-v0.1Win.zip)**

No Visual Studio or compiling required. Players must provide Heroes of Might and Magic II game data from their own legally obtained copy. See [installation instructions](#how-to-download-and-play) below.

I modified the fheroes2 code to make these changes:
- after a hero levels up, they get to choose 1 of 3 Artifacts, Primary Skills and Spells (if they can learn and don't have them already)
- when a hero gets to level 10, they get to choose an Ultimate Artifact instead (if there is no room, the lowest rated artifact will be replaced, no magic book obviously)
- if a hero doesn't have a spell book, they'll receive one when they level up the first time
- Mysticism now replenishes more mana, 15, 25, 40 per day OR 10%, 20%, 30% of the total mana, whichever is higher
- all factions start with Mysticism, Barbarians and Knights with Basic, others with Advanced
- Eagle Eye never shows up when leveling up
- AI heroes have a chance to increase their Knowledge by 1 when leveling up (separate from the other gifts) (Might heroes 50%, Magic 33%)
- Everyone has a low chance of leveling up Wisdom and nobody starts with it, but the AI heroes ignore Wisdom requirements when getting a random spell
 after leveling up

The artifact choices will depend on the hero's level:
- treasure artifacts for Levels 2, 3 and 4
- treasure or minor artifacts for Levels 5, 6 and 7
- ultimate artifacts at Level 10
- treasure, minor or major artifacts for all the other Levels

AI advantages:
- Wisdom requirements are ignored when getting a free spell (after leveling up)
- the AI has a 50% chance to get a Major Artifact at each level

[NOTE] Right now the AI doesn't really 'choose' stuff, but rather it gets random things, but those are in general the better ones. In the future I'll add a proper choosing logic, but I wanted to just make sure it works, then I'll improve it.

## How to download and play

### Windows 64-bit — ready-to-run build

1. Download the [Windows v0.1 Alpha ZIP](https://github.com/georgestefan94/fheroes2_Roguelike/releases/download/v0.1.0-alpha/fheroes2-Roguelike-v0.1Win.zip) and extract it.
2. Open your legally obtained **Heroes of Might and Magic II** installation folder.
3. Copy its `DATA`, `ANIM`, `MAPS`, and `MUSIC` folders (whichever are available) into the extracted mod folder, **beside `fheroes2.exe`**. Merge the existing `maps` folder if Windows asks.
4. Double-click `fheroes2.exe` to play.

If Windows complains about missing Microsoft Visual C++ runtime DLLs, install the [Microsoft Visual C++ Redistributable for x64](https://aka.ms/vs/17/release/vc_redist.x64.exe).

### Build from source

The modified engine's source code is available in this GitHub repository. Developers can choose **Code → Download ZIP** or clone the repository and follow the [fheroes2 build instructions](docs/DEVELOPMENT.md). Windows builds may require running `script/windows/install_packages.bat` to install dependencies.

**No original commercial Heroes II images, music, or game data are included in the ready-to-run download or source repository.** The release ZIP contains the compiled open-source engine and supporting files, not a standalone copy of Heroes II.

## Credits and license

This project is based on the open-source **fheroes2** engine created by the [fheroes2 contributors](https://github.com/ihhub/fheroes2). This is an unofficial fork and is not an official release of fheroes2.

The engine source code and modifications are distributed under the **GNU General Public License v2.0**; see the repository's [LICENSE](LICENSE) and retained source-file notices. Original Heroes II game assets are separate and remain subject to their owners' rights.

---

## About the original fheroes2 project

The following is the original fheroes2 project README, retained for upstream documentation and attribution. Its download links, community contacts, and donation information refer to the **original fheroes2 project**, not specifically to this mod.

# fheroes2

**fheroes2** is a recreation of the Heroes of Might and Magic II game engine.

This open source multiplatform project, written from scratch, is designed to reproduce the original game with significant
improvements in gameplay, graphics and logic (including support for high-resolution graphics, improved AI, numerous fixes
and user interface improvements), breathing new life into one of the most addictive turn-based strategy games.

You can find a complete list of all of our changes and enhancements in [**this page**](docs/GAME_IMPROVEMENTS.md).

<p align="center">
    <img src="docs/images/screenshots/screenshot_world_map.webp" width="820" alt="Screenshot of the world map">
</p>

<p align="center">
    <img src="docs/images/screenshots/screenshot_battle.webp" width="410" alt="Screenshot of the battle screen">
    <img src="docs/images/screenshots/screenshot_castle.webp" width="410" alt="Screenshot of the castle screen">
</p>

## Download and Install

Please follow the [**installation guide**](docs/INSTALL.md) to download and install fheroes2.

[![Github Downloads](https://img.shields.io/github/downloads/ihhub/fheroes2/total.svg)](https://github.com/ihhub/fheroes2/releases)

## Copyright

All rights for the original game and its resources belong to former The 3DO Company. These rights were transferred to Ubisoft.
We do not encourage and do not support any form of illegal usage of the original game. We strongly advise to purchase the original
game on [**GOG**](https://www.gog.com) or [**Ubisoft Store**](https://store.ubi.com) platforms. Alternatively, you can download a
free demo version of the game. Please refer to the [**installation guide**](docs/INSTALL.md) for more information.

## License

This project is licensed under the [**GNU General Public License v2.0**](https://github.com/ihhub/fheroes2/blob/master/LICENSE).

Initially, the project was developed on [**sourceforge**](https://sourceforge.net/projects/fheroes2/).

## Contribution and Development

This repository is a place for everyone. If you want to contribute, please read more to learn [**how you can contribute**](docs/FAQ.md#q-how-can-i-contribute-to-the-project).

### Developing fheroes2 engine

To build the project from source, please follow [**this guide**](docs/DEVELOPMENT.md).

[![Build Status](https://github.com/ihhub/fheroes2/actions/workflows/push.yml/badge.svg)](https://github.com/ihhub/fheroes2/actions)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=ihhub_fheroes2&metric=bugs)](https://sonarcloud.io/dashboard?id=ihhub_fheroes2)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=ihhub_fheroes2&metric=code_smells)](https://sonarcloud.io/dashboard?id=ihhub_fheroes2)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=ihhub_fheroes2&metric=duplicated_lines_density)](https://sonarcloud.io/dashboard?id=ihhub_fheroes2)

To assist with the graphical asset efforts of the project, please look at our [**graphical artist guide**](docs/GRAPHICAL_ASSETS.md).

If you would like to help translating the project, please read the [**translation guide**](docs/TRANSLATION.md).

### Developing fheroes2 documentation site

To build the [website](https://ihhub.github.io/fheroes2/) from source, please follow
[**this guide**](docs/WEBSITE_LOCAL_DEV.md).

## Donation

We accept donations via [**Patreon**](https://www.patreon.com/fheroes2), [**PayPal**](https://www.paypal.com/paypalme/fheroes2) or [**Boosty**](https://boosty.to/fheroes2).
All donations will be used only for the future project development as we do not consider this project as a source of income by any means.

[![Patreon Donate](https://img.shields.io/badge/Donate-Patreon-green.svg)](https://www.patreon.com/fheroes2)
[![Paypal Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/fheroes2)
[![Boosty Donate](https://img.shields.io/badge/Donate-Boosty-green.svg)](https://boosty.to/fheroes2)

## Contacts

Follow us on social networks: [**Facebook**](https://www.facebook.com/groups/fheroes2) or [**VK**](https://vk.com/fheroes2).
We also have a [**Discord**](https://discord.gg/xF85vbZ) server to discuss the development of the project.

[![Facebook](https://img.shields.io/badge/Facebook-blue.svg)](https://www.facebook.com/groups/fheroes2)
[![VK](https://img.shields.io/badge/VK-blue.svg)](https://vk.com/fheroes2)
[![Discord](https://img.shields.io/discord/733093692860137523.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/xF85vbZ)

## Frequently Asked Questions (FAQ)

You can find answers to the most commonly asked questions on our [**F.A.Q. page**](docs/FAQ.md).
