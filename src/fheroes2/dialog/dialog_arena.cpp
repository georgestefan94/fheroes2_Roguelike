/***************************************************************************
 *   fheroes2: https://github.com/ihhub/fheroes2                           *
 *   Copyright (C) 2019 - 2026                                             *
 *                                                                         *
 *   Free Heroes2 Engine: http://sourceforge.net/projects/fheroes2         *
 *   Copyright (C) 2009 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.   
     // Modified by InfernoGeo (2026-10-27):
    // Added roguelike-inspired level-up reward functionality.*
 ***************************************************************************/

#include <cstdint>
#include <string>

#include "cursor.h"
#include "dialog.h" // IWYU pragma: associated
#include "game_assets.h"
#include "game_hotkeys.h"
#include "icn.h"
#include "image.h"
#include "localevent.h"
#include "math_base.h"
#include "screen.h"
#include "settings.h"
#include "skill.h"
#include "translations.h"
#include "ui_button.h"
#include "ui_dialog.h"
#include "ui_text.h"
#include "spell_storage.h"
#include "heroes.h"
#include "ui_language.h"

namespace
{
    void InfoSkillClear( const fheroes2::Rect & rect1, const fheroes2::Rect & rect2, const fheroes2::Rect & rect3 )
    {
        fheroes2::Display & display = fheroes2::Display::instance();

        fheroes2::Blit( Assets::getImage( ICN::XPRIMARY, 0 ), display, rect1.x, rect1.y );
        fheroes2::Blit( Assets::getImage( ICN::XPRIMARY, 1 ), display, rect2.x, rect2.y );
        fheroes2::Blit( Assets::getImage( ICN::XPRIMARY, 2 ), display, rect3.x, rect3.y );
    }

    void InfoArtifactClear( int art1, int art2, int art3, const fheroes2::Rect & rect1, const fheroes2::Rect & rect2, const fheroes2::Rect & rect3 )
    {
        fheroes2::Display & display = fheroes2::Display::instance();

        fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, art1 ), display, rect1.x, rect1.y );
        fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, art2 ), display, rect2.x, rect2.y );
        fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, art3 ), display, rect3.x, rect3.y );
    }

    void InfoSpellClear( int spell1, int spell2, int spell3, const fheroes2::Rect & rect1, const fheroes2::Rect & rect2, const fheroes2::Rect & rect3 )
    {
        fheroes2::Display & display = fheroes2::Display::instance();

        fheroes2::Blit( Assets::getImage( ICN::SPELLS, spell1 ), display, rect1.x, rect1.y );
        fheroes2::Blit( Assets::getImage( ICN::SPELLS, spell2 ), display, rect2.x, rect2.y );
        fheroes2::Blit( Assets::getImage( ICN::SPELLS, spell3 ), display, rect3.x, rect3.y );
    }

    void InfoSkillSelect( int skill, const fheroes2::Rect & rect1, const fheroes2::Rect & rect2, const fheroes2::Rect & rect3 )
    {
        fheroes2::Display & display = fheroes2::Display::instance();

        switch ( skill ) {
        case Skill::Primary::ATTACK:
            fheroes2::Blit( Assets::getImage( ICN::XPRIMARY, 4 ), display, rect1.x, rect1.y );
            break;
        case Skill::Primary::DEFENSE:
            fheroes2::Blit( Assets::getImage( ICN::XPRIMARY, 5 ), display, rect2.x, rect2.y );
            break;
        case Skill::Primary::POWER:
            fheroes2::Blit( Assets::getImage( ICN::XPRIMARY, 6 ), display, rect3.x, rect3.y );
            break;
        default:
            break;
        }
    }

    void InfoArtifactSelect( int selectedArtifactID, int art1, int art2, int art3, const fheroes2::Rect & rect1, const fheroes2::Rect & rect2,
                             const fheroes2::Rect & rect3 )
    {
        //fheroes2::Display & display = fheroes2::Display::instance();

        //fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, artifactID ), display, rect1.x, rect1.y );

        fheroes2::Display & display = fheroes2::Display::instance();

        switch ( selectedArtifactID ) {
        case Skill::Primary::ATTACK:
            fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, art1 ), display, rect1.x, rect1.y );
            break;
        case Skill::Primary::DEFENSE:
            fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, art2 ), display, rect2.x, rect2.y );
            break;
        case Skill::Primary::POWER:
            fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, art3 ), display, rect3.x, rect3.y );
            break;
        default:
            break;
        }
    }

    void InfoSpellSelect( int selectedSpellID, int spell1, int spell2, int spell3, const fheroes2::Rect & rect1, const fheroes2::Rect & rect2,
                             const fheroes2::Rect & rect3 )
    {
        // fheroes2::Display & display = fheroes2::Display::instance();

        // fheroes2::Blit( Assets::getImage( ICN::ARTIFACT, artifactID ), display, rect1.x, rect1.y );

        fheroes2::Display & display = fheroes2::Display::instance();

        switch ( selectedSpellID ) {
        case Skill::Primary::ATTACK:
            fheroes2::Blit( Assets::getImage( ICN::SPELLS, spell1 ), display, rect1.x, rect1.y );
            break;
        case Skill::Primary::DEFENSE:
            fheroes2::Blit( Assets::getImage( ICN::SPELLS, spell2 ), display, rect2.x, rect2.y );
            break;
        case Skill::Primary::POWER:
            fheroes2::Blit( Assets::getImage( ICN::SPELLS, spell3 ), display, rect3.x, rect3.y );
            break;
        default:
            break;
        }
    }

    int InfoSkillNext( int skill )
    {
        switch ( skill ) {
        case Skill::Primary::ATTACK:
            return Skill::Primary::DEFENSE;
        case Skill::Primary::DEFENSE:
            return Skill::Primary::POWER;
        default:
            break;
        }

        return Skill::Primary::UNKNOWN;
    }

    int InfoSkillPrev( int skill )
    {
        switch ( skill ) {
        case Skill::Primary::POWER:
            return Skill::Primary::DEFENSE;
        case Skill::Primary::DEFENSE:
            return Skill::Primary::ATTACK;
        default:
            break;
        }

        return Skill::Primary::UNKNOWN;
    }
}

int Dialog::SelectSkillFromArena()
{
    fheroes2::Display & display = fheroes2::Display::instance();
    const int system = Settings::Get().isEvilInterfaceEnabled() ? ICN::SYSTEME : ICN::SYSTEM;

    // setup cursor
    const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    fheroes2::Text title( _( "Arena" ), fheroes2::FontType::normalYellow() );

    fheroes2::Text textbox(
        _( "You enter the arena and face a pack of vicious lions. You handily defeat them, to the wild cheers of the crowd. Impressed by your skill, the aged trainer of gladiators agrees to train you in a skill of your choice." ),
        fheroes2::FontType::normalWhite() );
    const fheroes2::Sprite & sprite = Assets::getImage( ICN::XPRIMARY, 0 );
    const int spacer = 10;

    const Dialog::FrameBox box( title.height( fheroes2::boxAreaWidthPx ) + textbox.height( fheroes2::boxAreaWidthPx ) + 2 * spacer + sprite.height() + 15, true );

    const fheroes2::Rect & box_rt = box.GetArea();
    fheroes2::Point dst_pt( box_rt.x, box_rt.y );

    title.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    dst_pt.y += title.height( fheroes2::boxAreaWidthPx ) + spacer;

    textbox.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    dst_pt.y += textbox.height( fheroes2::boxAreaWidthPx ) + spacer;

    int res = Skill::Primary::ATTACK;

    const int spacingX = ( box_rt.width - sprite.width() * 3 ) / 4;

    fheroes2::Rect rect1( dst_pt.x + spacingX, dst_pt.y, sprite.width(), sprite.height() );
    fheroes2::Rect rect2( rect1.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );
    fheroes2::Rect rect3( rect2.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    InfoSkillClear( rect1, rect2, rect3 );
    InfoSkillSelect( res, rect1, rect2, rect3 );

    // info texts
    const int32_t skillTextWidth = 60;

    fheroes2::Text text( Skill::Primary::String( Skill::Primary::ATTACK ), fheroes2::FontType::smallWhite() );
    dst_pt.x = rect1.x + ( rect1.width - skillTextWidth ) / 2;
    dst_pt.y = rect1.y + rect1.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    text.set( Skill::Primary::String( Skill::Primary::DEFENSE ), fheroes2::FontType::smallWhite() );
    dst_pt.x = rect2.x + ( rect2.width - skillTextWidth ) / 2;
    dst_pt.y = rect2.y + rect2.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    text.set( Skill::Primary::String( Skill::Primary::POWER ), fheroes2::FontType::smallWhite() );
    dst_pt.x = rect3.x + ( rect3.width - skillTextWidth ) / 2;
    dst_pt.y = rect3.y + rect3.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    // buttons
    dst_pt.x = box_rt.x + ( box_rt.width - Assets::getImage( system, 1 ).width() ) / 2;
    dst_pt.y = box_rt.y + box_rt.height - Assets::getImage( system, 1 ).height();
    fheroes2::Button buttonOk( dst_pt.x, dst_pt.y, system, 1, 2 );

    LocalEvent & le = LocalEvent::Get();

    buttonOk.draw();
    display.render();

    // message loop
    while ( le.HandleEvents() ) {
        bool redraw = false;

        buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) && Skill::Primary::UNKNOWN != InfoSkillPrev( res ) ) {
            res = InfoSkillPrev( res );
            redraw = true;
        }
        else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) && Skill::Primary::UNKNOWN != InfoSkillNext( res ) ) {
            res = InfoSkillNext( res );
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect1 ) ) {
            res = Skill::Primary::ATTACK;
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect2 ) ) {
            res = Skill::Primary::DEFENSE;
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect3 ) ) {
            res = Skill::Primary::POWER;
            redraw = true;
        }
        else if ( le.isMouseRightButtonPressedInArea( rect1 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::ATTACK, "" ).showPopup( Dialog::ZERO );
        }
        else if ( le.isMouseRightButtonPressedInArea( rect2 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::DEFENSE, "" ).showPopup( Dialog::ZERO );
        }
        else if ( le.isMouseRightButtonPressedInArea( rect3 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::POWER, "" ).showPopup( Dialog::ZERO );
        }

        if ( redraw ) {
            InfoSkillClear( rect1, rect2, rect3 );
            InfoSkillSelect( res, rect1, rect2, rect3 );
            display.render();
        }

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) )
            break;
    }

    return res;
}

int Dialog::SelectSkillOnLevelUp()
{
    fheroes2::Display & display = fheroes2::Display::instance();
    const int system = Settings::Get().isEvilInterfaceEnabled() ? ICN::SYSTEME : ICN::SYSTEM;

    // setup cursor
    const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    fheroes2::Text title( _( "Primary Skill Gift" ), fheroes2::FontType::normalYellow() );

    fheroes2::Text textbox(
        _( "Upon leveling up, the Gods have blessed your hero with the choice to increase 1 of 3 primary skills. Choose wisely!" ),
        fheroes2::FontType::normalWhite() );
    const fheroes2::Sprite & sprite = Assets::getImage( ICN::XPRIMARY, 0 );
    const int spacer = 10;

    const Dialog::FrameBox box( title.height( fheroes2::boxAreaWidthPx ) + textbox.height( fheroes2::boxAreaWidthPx ) + 2 * spacer + sprite.height() + 15, true );

    const fheroes2::Rect & box_rt = box.GetArea();
    fheroes2::Point dst_pt( box_rt.x, box_rt.y );

    title.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    dst_pt.y += title.height( fheroes2::boxAreaWidthPx ) + spacer;

    textbox.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    dst_pt.y += textbox.height( fheroes2::boxAreaWidthPx ) + spacer;

    int res = Skill::Primary::ATTACK;

    const int spacingX = ( box_rt.width - sprite.width() * 3 ) / 4;

    fheroes2::Rect rect1( dst_pt.x + spacingX, dst_pt.y, sprite.width(), sprite.height() );
    fheroes2::Rect rect2( rect1.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );
    fheroes2::Rect rect3( rect2.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    InfoSkillClear( rect1, rect2, rect3 );
    InfoSkillSelect( res, rect1, rect2, rect3 );

    // info texts
    const int32_t skillTextWidth = 60;

    fheroes2::Text text( Skill::Primary::String( Skill::Primary::ATTACK ), fheroes2::FontType::smallWhite() );
    dst_pt.x = rect1.x + ( rect1.width - skillTextWidth ) / 2;
    dst_pt.y = rect1.y + rect1.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    text.set( Skill::Primary::String( Skill::Primary::DEFENSE ), fheroes2::FontType::smallWhite() );
    dst_pt.x = rect2.x + ( rect2.width - skillTextWidth ) / 2;
    dst_pt.y = rect2.y + rect2.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    text.set( Skill::Primary::String( Skill::Primary::POWER ), fheroes2::FontType::smallWhite() );
    dst_pt.x = rect3.x + ( rect3.width - skillTextWidth ) / 2;
    dst_pt.y = rect3.y + rect3.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    // buttons
    dst_pt.x = box_rt.x + ( box_rt.width - Assets::getImage( system, 1 ).width() ) / 2;
    dst_pt.y = box_rt.y + box_rt.height - Assets::getImage( system, 1 ).height();
    fheroes2::Button buttonOk( dst_pt.x, dst_pt.y, system, 1, 2 );

    LocalEvent & le = LocalEvent::Get();

    buttonOk.draw();
    display.render();

    // message loop
    while ( le.HandleEvents() ) {
        bool redraw = false;

        buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) && Skill::Primary::UNKNOWN != InfoSkillPrev( res ) ) {
            res = InfoSkillPrev( res );
            redraw = true;
        }
        else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) && Skill::Primary::UNKNOWN != InfoSkillNext( res ) ) {
            res = InfoSkillNext( res );
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect1 ) ) {
            res = Skill::Primary::ATTACK;
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect2 ) ) {
            res = Skill::Primary::DEFENSE;
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect3 ) ) {
            res = Skill::Primary::POWER;
            redraw = true;
        }
        else if ( le.isMouseRightButtonPressedInArea( rect1 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::ATTACK, "" ).showPopup( Dialog::ZERO );
        }
        else if ( le.isMouseRightButtonPressedInArea( rect2 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::DEFENSE, "" ).showPopup( Dialog::ZERO );
        }
        else if ( le.isMouseRightButtonPressedInArea( rect3 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::POWER, "" ).showPopup( Dialog::ZERO );
        }

        if ( redraw ) {
            InfoSkillClear( rect1, rect2, rect3 );
            InfoSkillSelect( res, rect1, rect2, rect3 );
            display.render();
        }

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) )
            break;
    }

    return res;
}


int Dialog::SelectSkillOnLevelUpWithHero( Heroes & hero )
{
    fheroes2::Display & display = fheroes2::Display::instance();

    const Settings & conf = Settings::Get();
    const bool isEvilInterface = conf.isEvilInterfaceEnabled();
    const int system = isEvilInterface ? ICN::SYSTEME : ICN::SYSTEM;

    // Setup cursor.
    const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    fheroes2::Text title( _( "Primary Skill Gift" ), fheroes2::FontType::normalYellow() );

    fheroes2::Text textbox( _( "Upon leveling up, the Gods have blessed your hero with the choice to increase 1 of 3 primary skills. Choose wisely!" ),
                            fheroes2::FontType::normalWhite() );

    const fheroes2::Sprite & sprite = Assets::getImage( ICN::XPRIMARY, 0 );

    const int spacer = 10;

    // -------------------------------------------------------
    // Button sprites
    // -------------------------------------------------------

    const fheroes2::Sprite & buttonOkImage = Assets::getImage( system, 1 );

    const int icnHeroes = isEvilInterface ? ICN::EVIL_ARMY_BUTTON : ICN::GOOD_ARMY_BUTTON;

    const fheroes2::Sprite & heroButtonImage = Assets::getImage( icnHeroes, 0 );

    const int buttonSpacing = 20;

    const int buttonRowHeight = std::max( buttonOkImage.height(), heroButtonImage.height() );

    // -------------------------------------------------------
    // Dialog frame
    // -------------------------------------------------------

    const int dialogHeight = title.height( fheroes2::boxAreaWidthPx ) + textbox.height( fheroes2::boxAreaWidthPx ) + 2 * spacer + sprite.height() + 15 + buttonRowHeight;

    const Dialog::FrameBox box( dialogHeight, true );

    const fheroes2::Rect & box_rt = box.GetArea();

    fheroes2::Point dst_pt( box_rt.x, box_rt.y );

    // Draw title.
    title.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );

    dst_pt.y += title.height( fheroes2::boxAreaWidthPx ) + spacer;

    // Draw description.
    textbox.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );

    dst_pt.y += textbox.height( fheroes2::boxAreaWidthPx ) + spacer;

    // Default selected skill.
    int res = Skill::Primary::ATTACK;

    // -------------------------------------------------------
    // Primary skill positions
    // -------------------------------------------------------

    const int spacingX = ( box_rt.width - sprite.width() * 3 ) / 4;

    const fheroes2::Rect rect1( box_rt.x + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    const fheroes2::Rect rect2( rect1.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    const fheroes2::Rect rect3( rect2.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    InfoSkillClear( rect1, rect2, rect3 );
    InfoSkillSelect( res, rect1, rect2, rect3 );

    // -------------------------------------------------------
    // Primary skill names
    // -------------------------------------------------------

    const int32_t skillTextWidth = 60;

    fheroes2::Text text( Skill::Primary::String( Skill::Primary::ATTACK ), fheroes2::FontType::smallWhite() );

    const auto drawSkillNames = [&]() {
        text.set( Skill::Primary::String( Skill::Primary::ATTACK ), fheroes2::FontType::smallWhite() );

        text.draw( rect1.x + ( rect1.width - skillTextWidth ) / 2, rect1.y + rect1.height + 7, skillTextWidth, display );

        text.set( Skill::Primary::String( Skill::Primary::DEFENSE ), fheroes2::FontType::smallWhite() );

        text.draw( rect2.x + ( rect2.width - skillTextWidth ) / 2, rect2.y + rect2.height + 7, skillTextWidth, display );

        text.set( Skill::Primary::String( Skill::Primary::POWER ), fheroes2::FontType::smallWhite() );

        text.draw( rect3.x + ( rect3.width - skillTextWidth ) / 2, rect3.y + rect3.height + 7, skillTextWidth, display );
    };

    drawSkillNames();

    // -------------------------------------------------------
    // Center Hero + OK buttons
    // -------------------------------------------------------

    const int totalButtonWidth = heroButtonImage.width() + buttonSpacing + buttonOkImage.width();

    const int buttonStartX = box_rt.x + ( box_rt.width - totalButtonWidth ) / 2;

    const int buttonRowY = box_rt.y + box_rt.height - buttonRowHeight;

    const int heroButtonX = buttonStartX;

    const int heroButtonY = buttonRowY + ( buttonRowHeight - heroButtonImage.height() ) / 2;

    const int buttonOkX = buttonStartX + heroButtonImage.width() + buttonSpacing;

    const int buttonOkY = buttonRowY + ( buttonRowHeight - buttonOkImage.height() ) / 2;

    fheroes2::Button buttonOk( buttonOkX, buttonOkY, system, 1, 2 );

    fheroes2::ButtonSprite buttonHero
        = fheroes2::makeButtonWithBackground( heroButtonX, heroButtonY, Assets::getImage( icnHeroes, 0 ), Assets::getImage( icnHeroes, 1 ), display );

    LocalEvent & le = LocalEvent::Get();

    buttonOk.draw();
    buttonHero.draw();

    display.render();

    // -------------------------------------------------------
    // Event loop
    // -------------------------------------------------------

    while ( le.HandleEvents() ) {
        bool redraw = false;

        // Button pressed states.
        buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

        buttonHero.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonHero.area() ) );

        // ---------------------------------------------------
        // View Hero
        // ---------------------------------------------------

        if ( le.MouseClickLeft( buttonHero.area() ) ) {
            le.reset();

            hero.OpenDialog( false, true, true, true, true, false, fheroes2::getLanguageFromAbbreviation( conf.getGameLanguage() ) );

            display.render();
            continue;
        }

        // ---------------------------------------------------
        // Hero button tooltip
        // ---------------------------------------------------

        if ( le.isMouseRightButtonPressedInArea( buttonHero.area() ) ) {
            fheroes2::showStandardTextMessage( "", _( "View Hero" ), Dialog::ZERO );

            display.render();
        }

        // ---------------------------------------------------
        // Keyboard navigation
        // ---------------------------------------------------

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) && Skill::Primary::UNKNOWN != InfoSkillPrev( res ) ) {
            res = InfoSkillPrev( res );
            redraw = true;
        }
        else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) && Skill::Primary::UNKNOWN != InfoSkillNext( res ) ) {
            res = InfoSkillNext( res );
            redraw = true;
        }

        // ---------------------------------------------------
        // Mouse selection
        // ---------------------------------------------------

        else if ( le.MouseClickLeft( rect1 ) ) {
            res = Skill::Primary::ATTACK;
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect2 ) ) {
            res = Skill::Primary::DEFENSE;
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect3 ) ) {
            res = Skill::Primary::POWER;
            redraw = true;
        }

        // ---------------------------------------------------
        // Right-click skill information
        // ---------------------------------------------------

        else if ( le.isMouseRightButtonPressedInArea( rect1 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::ATTACK, "" ).showPopup( Dialog::ZERO );

            display.render();
        }
        else if ( le.isMouseRightButtonPressedInArea( rect2 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::DEFENSE, "" ).showPopup( Dialog::ZERO );

            display.render();
        }
        else if ( le.isMouseRightButtonPressedInArea( rect3 ) ) {
            fheroes2::PrimarySkillDialogElement( Skill::Primary::POWER, "" ).showPopup( Dialog::ZERO );

            display.render();
        }

        // ---------------------------------------------------
        // Redraw selected skill
        // ---------------------------------------------------

        if ( redraw ) {
            InfoSkillClear( rect1, rect2, rect3 );
            InfoSkillSelect( res, rect1, rect2, rect3 );

            drawSkillNames();

            buttonOk.draw();
            buttonHero.draw();

            display.render();
        }

        // ---------------------------------------------------
        // Confirm skill selection
        // ---------------------------------------------------

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) ) {
            break;
        }
    }

    return res;
}


fheroes2::FontType highlight(int res, int art)
{
    if ( res == art )
        return fheroes2::FontType::smallYellow();

    return fheroes2::FontType::smallWhite();
}

int Dialog::SelectArtifactOnLevelUp(int artifactLevel)
{
    Artifact::ArtLevel level = Artifact::ART_LEVEL_4_OR_BELOW;

    if (artifactLevel == 3)
    {
        level = Artifact::ART_ULTIMATE;
    }
    else if (artifactLevel == 1)
    {
        level = Artifact::ART_LEVEL_7_OR_BELOW;
    }
    else if ( artifactLevel == 2 ) {
        level = Artifact::ART_LEVEL_ALL_NORMAL;
    }

    //inferno
    // fix right click on options and white border
    fheroes2::Display & display = fheroes2::Display::instance();
    const int system = Settings::Get().isEvilInterfaceEnabled() ? ICN::SYSTEME : ICN::SYSTEM;

    // setup cursor
    const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    fheroes2::Text title( _( "Artifact Gift" ), fheroes2::FontType::normalYellow() );

    fheroes2::Text textbox(
        _( "Upon leveling up, the Gods have blessed your hero with the choice to receive 1 of 3 artifacts. Choose wisely!" ),
        fheroes2::FontType::normalWhite() );
    const fheroes2::Sprite & sprite = Assets::getImage( ICN::ARTIFACT, 0 );
    const int spacer = 20; //change back to 10 if needed

    Artifact art1 = Artifact::Rand( level );
    Artifact art2 = art1;
    Artifact art3 = art1;

    while ( art1.GetID() == art2.GetID() ) {
        art2 = Artifact::Rand( level );
    }

    while ( art2.GetID() == art3.GetID() || art3.GetID() == art1.GetID() ) {
        art3 = Artifact::Rand( level );
    }

    //if (ultimateArtifact)
    //{
    //    art1 = Artifact::Rand( Artifact::ART_ULTIMATE );
    //    art2 = art1;
    //    art3 = art1;

    //    while ( art1.GetID() == art2.GetID() )
    //    {
    //        art2 = Artifact::Rand( Artifact::ART_ULTIMATE );
    //    }

    //    art3 = art2;

    //    while ( art2.GetID() == art3.GetID() || art3.GetID() == art1.GetID() )
    //    {
    //        art3 = Artifact::Rand( Artifact::ART_ULTIMATE );
    //    }
    //}

    int maxArtNameSize = std::max({
        static_cast<int>( std::strlen( art1.GetName() ) ), static_cast<int>( std::strlen( art2.GetName() ) ), static_cast<int>( std::strlen( art3.GetName() ) ) } );

    const Dialog::FrameBox box( title.height( fheroes2::boxAreaWidthPx ) + textbox.height( fheroes2::boxAreaWidthPx ) + 2 * spacer + sprite.height() + 15 + maxArtNameSize,
                                true );

    const fheroes2::Rect & box_rt = box.GetArea();
    fheroes2::Point dst_pt( box_rt.x, box_rt.y );

    title.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    dst_pt.y += title.height( fheroes2::boxAreaWidthPx ) + spacer;

    textbox.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    dst_pt.y += textbox.height( fheroes2::boxAreaWidthPx ) + spacer;

    int res = art1.GetID();

    const int spacingX = ( box_rt.width - sprite.width() * 3 ) / 4;

    fheroes2::Rect rect1( dst_pt.x + spacingX, dst_pt.y, sprite.width(), sprite.height() );
    fheroes2::Rect rect2( rect1.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );
    fheroes2::Rect rect3( rect2.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    InfoArtifactClear( art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 ); 
    InfoArtifactSelect( res, art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 ); // this had rect2 and rect3, maybe switch back

    // info texts
    const int32_t skillTextWidth = 60;

    fheroes2::Text text( art1.GetName(), highlight(res, art1.GetID()) );
    dst_pt.x = rect1.x + ( rect1.width - skillTextWidth ) / 2;
    dst_pt.y = rect1.y + rect1.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    text.set( art2.GetName(), highlight( res, art2.GetID() ) );
    dst_pt.x = rect2.x + ( rect2.width - skillTextWidth ) / 2;
    dst_pt.y = rect2.y + rect2.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    text.set( art3.GetName(), highlight( res, art3.GetID() ) );
    dst_pt.x = rect3.x + ( rect3.width - skillTextWidth ) / 2;
    dst_pt.y = rect3.y + rect3.height + 5;
    text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display ); // here

    // buttons
    dst_pt.x = box_rt.x + ( box_rt.width - Assets::getImage( system, 1 ).width() ) / 2;
    dst_pt.y = box_rt.y + box_rt.height - Assets::getImage( system, 1 ).height();
    fheroes2::Button buttonOk( dst_pt.x, dst_pt.y, system, 1, 2 );

    LocalEvent & le = LocalEvent::Get();

    buttonOk.draw();
    display.render();

    // message loop
    while ( le.HandleEvents() ) {
        bool redraw = false;

        buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) && Skill::Primary::UNKNOWN != InfoSkillPrev( res ) ) {
            res = InfoSkillPrev( res );
            redraw = true;
        }
        else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) && Skill::Primary::UNKNOWN != InfoSkillNext( res ) ) {
            res = InfoSkillNext( res );
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect1 ) ) {
            res = art1.GetID();
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect2 ) ) {
            res = art2.GetID();
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect3 ) ) {
            res = art3.GetID();
            redraw = true;
        }
        else if ( le.isMouseRightButtonPressedInArea( rect1 ) ) {
            //fheroes2::PrimarySkillDialogElement( Skill::Primary::ATTACK, "" ).showPopup( Dialog::ZERO );
            fheroes2::ArtifactDialogElement( art1 ).showPopup( Dialog::ZERO );
        }
        else if ( le.isMouseRightButtonPressedInArea( rect2 ) ) {
            //fheroes2::PrimarySkillDialogElement( Skill::Primary::DEFENSE, "" ).showPopup( Dialog::ZERO );
            fheroes2::ArtifactDialogElement( art2 ).showPopup( Dialog::ZERO );
        }
        else if ( le.isMouseRightButtonPressedInArea( rect3 ) ) {
            //fheroes2::PrimarySkillDialogElement( Skill::Primary::POWER, "" ).showPopup( Dialog::ZERO );
            fheroes2::ArtifactDialogElement( art3 ).showPopup( Dialog::ZERO );
        }

        if ( redraw ) {
            InfoArtifactClear( art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 );
            InfoArtifactSelect( res, art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 );

            text.set( art1.GetName(), highlight( res, art1.GetID() ) );
            dst_pt.x = rect1.x + ( rect1.width - skillTextWidth ) / 2;
            dst_pt.y = rect1.y + rect1.height + 5;
            text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

            text.set( art2.GetName(), highlight( res, art2.GetID() ) );
            dst_pt.x = rect2.x + ( rect2.width - skillTextWidth ) / 2;
            dst_pt.y = rect2.y + rect2.height + 5;
            text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

            text.set( art3.GetName(), highlight( res, art3.GetID() ) );
            dst_pt.x = rect3.x + ( rect3.width - skillTextWidth ) / 2;
            dst_pt.y = rect3.y + rect3.height + 5;
            text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display ); // here

            display.render();
        }

        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) )
            break;
    }

    return res;
}


int Dialog::SelectArtifactOnLevelUpWithHero( int artifactLevel, Heroes & hero )
{
    Artifact::ArtLevel level = Artifact::ART_LEVEL_4_OR_BELOW;

    if ( artifactLevel == 3 ) {
        level = Artifact::ART_ULTIMATE;
    }
    else if ( artifactLevel == 1 ) {
        level = Artifact::ART_LEVEL_7_OR_BELOW;
    }
    else if ( artifactLevel == 2 ) {
        level = Artifact::ART_LEVEL_ALL_NORMAL;
    }

    fheroes2::Display & display = fheroes2::Display::instance();

    const Settings & conf = Settings::Get();
    const bool isEvilInterface = conf.isEvilInterfaceEnabled();
    const int system = isEvilInterface ? ICN::SYSTEME : ICN::SYSTEM;

    const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    fheroes2::Text title( _( "Artifact Gift" ), fheroes2::FontType::normalYellow() );

    fheroes2::Text textbox( _( "Upon leveling up, the Gods have blessed your hero with the choice to receive 1 of 3 artifacts. Choose wisely!" ),
                            fheroes2::FontType::normalWhite() );

    const fheroes2::Sprite & sprite = Assets::getImage( ICN::ARTIFACT, 0 );

    const int spacer = 20;

    // Generate three different artifacts.
    Artifact art1 = Artifact::Rand( level );
    Artifact art2 = art1;
    Artifact art3 = art1;

    while ( art1.GetID() == art2.GetID() ) {
        art2 = Artifact::Rand( level );
    }

    while ( art2.GetID() == art3.GetID() || art3.GetID() == art1.GetID() ) {
        art3 = Artifact::Rand( level );
    }

    const int maxArtNameSize = std::max(
        { static_cast<int>( std::strlen( art1.GetName() ) ), static_cast<int>( std::strlen( art2.GetName() ) ), static_cast<int>( std::strlen( art3.GetName() ) ) } );

    // Button sprites.
    const fheroes2::Sprite & buttonOkImage = Assets::getImage( system, 1 );

    const int icnHeroes = isEvilInterface ? ICN::EVIL_ARMY_BUTTON : ICN::GOOD_ARMY_BUTTON;

    const fheroes2::Sprite & heroButtonImage = Assets::getImage( icnHeroes, 0 );

    const int buttonSpacing = 20;
    const int buttonRowHeight = std::max( buttonOkImage.height(), heroButtonImage.height() );

    // Allow space for the hero and OK buttons.
    const int dialogHeight
        = title.height( fheroes2::boxAreaWidthPx ) + textbox.height( fheroes2::boxAreaWidthPx ) + 2 * spacer + sprite.height() + 15 + maxArtNameSize + buttonRowHeight;

    const Dialog::FrameBox box( dialogHeight, true );

    const fheroes2::Rect & box_rt = box.GetArea();

    fheroes2::Point dst_pt( box_rt.x, box_rt.y );

    // Draw title.
    title.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );

    dst_pt.y += title.height( fheroes2::boxAreaWidthPx ) + spacer;

    // Draw description.
    textbox.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );

    dst_pt.y += textbox.height( fheroes2::boxAreaWidthPx ) + spacer;

    // Default selection.
    int res = art1.GetID();

    // Artifact positions.
    const int spacingX = ( box_rt.width - sprite.width() * 3 ) / 4;

    const fheroes2::Rect rect1( dst_pt.x + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    const fheroes2::Rect rect2( rect1.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    const fheroes2::Rect rect3( rect2.x + sprite.width() + spacingX, dst_pt.y, sprite.width(), sprite.height() );

    // Draw artifacts.
    InfoArtifactClear( art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 );

    InfoArtifactSelect( res, art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 );

    // Draw artifact names.
    const int32_t skillTextWidth = 60;

    fheroes2::Text text( art1.GetName(), highlight( res, art1.GetID() ) );

    const auto drawArtifactNames = [&]() {
        text.set( art1.GetName(), highlight( res, art1.GetID() ) );

        text.draw( rect1.x + ( rect1.width - skillTextWidth ) / 2, rect1.y + rect1.height + 7, skillTextWidth, display );

        text.set( art2.GetName(), highlight( res, art2.GetID() ) );

        text.draw( rect2.x + ( rect2.width - skillTextWidth ) / 2, rect2.y + rect2.height + 7, skillTextWidth, display );

        text.set( art3.GetName(), highlight( res, art3.GetID() ) );

        text.draw( rect3.x + ( rect3.width - skillTextWidth ) / 2, rect3.y + rect3.height + 7, skillTextWidth, display );
    };

    drawArtifactNames();

    // -------------------------------------------------------
    // Hero + OK buttons
    // -------------------------------------------------------

    const int totalButtonWidth = heroButtonImage.width() + buttonSpacing + buttonOkImage.width();

    const int buttonStartX = box_rt.x + ( box_rt.width - totalButtonWidth ) / 2;

    const int buttonRowY = box_rt.y + box_rt.height - buttonRowHeight;

    const int heroButtonX = buttonStartX;

    const int heroButtonY = buttonRowY + ( buttonRowHeight - heroButtonImage.height() ) / 2;

    const int buttonOkX = buttonStartX + heroButtonImage.width() + buttonSpacing;

    const int buttonOkY = buttonRowY + ( buttonRowHeight - buttonOkImage.height() ) / 2;

    fheroes2::Button buttonOk( buttonOkX, buttonOkY, system, 1, 2 );

    fheroes2::ButtonSprite buttonHero
        = fheroes2::makeButtonWithBackground( heroButtonX, heroButtonY, Assets::getImage( icnHeroes, 0 ), Assets::getImage( icnHeroes, 1 ), display );

    LocalEvent & le = LocalEvent::Get();

    buttonOk.draw();
    buttonHero.draw();

    display.render();

    // -------------------------------------------------------
    // Event loop
    // -------------------------------------------------------

    while ( le.HandleEvents() ) {
        bool redraw = false;

        buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

        buttonHero.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonHero.area() ) );

        // View hero without choosing an artifact.
        if ( le.MouseClickLeft( buttonHero.area() ) ) {
            le.reset();

            hero.OpenDialog( false, true, true, true, true, false, fheroes2::getLanguageFromAbbreviation( conf.getGameLanguage() ) );

            display.render();
            continue;
        }

        // Hero button tooltip.
        if ( le.isMouseRightButtonPressedInArea( buttonHero.area() ) ) {
            fheroes2::showStandardTextMessage( "", _( "View Hero" ), Dialog::ZERO );

            display.render();
        }

        // Keyboard selection.
        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) ) {
            if ( res == art1.GetID() ) {
                res = art3.GetID();
            }
            else if ( res == art2.GetID() ) {
                res = art1.GetID();
            }
            else {
                res = art2.GetID();
            }

            redraw = true;
        }
        else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) ) {
            if ( res == art1.GetID() ) {
                res = art2.GetID();
            }
            else if ( res == art2.GetID() ) {
                res = art3.GetID();
            }
            else {
                res = art1.GetID();
            }

            redraw = true;
        }

        // Mouse selection.
        else if ( le.MouseClickLeft( rect1 ) ) {
            res = art1.GetID();
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect2 ) ) {
            res = art2.GetID();
            redraw = true;
        }
        else if ( le.MouseClickLeft( rect3 ) ) {
            res = art3.GetID();
            redraw = true;
        }

        // Right-click artifact information.
        else if ( le.isMouseRightButtonPressedInArea( rect1 ) ) {
            fheroes2::ArtifactDialogElement( art1 ).showPopup( Dialog::ZERO );
            display.render();
        }
        else if ( le.isMouseRightButtonPressedInArea( rect2 ) ) {
            fheroes2::ArtifactDialogElement( art2 ).showPopup( Dialog::ZERO );
            display.render();
        }
        else if ( le.isMouseRightButtonPressedInArea( rect3 ) ) {
            fheroes2::ArtifactDialogElement( art3 ).showPopup( Dialog::ZERO );
            display.render();
        }

        // Redraw selection.
        if ( redraw ) {
            InfoArtifactClear( art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 );

            InfoArtifactSelect( res, art1.GetID(), art2.GetID(), art3.GetID(), rect1, rect2, rect3 );

            drawArtifactNames();

            buttonOk.draw();
            buttonHero.draw();

            display.render();
        }

        // Confirm artifact choice.
        if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) ) {
            break;
        }
    }

    return res;
}


int Dialog::SelectSpellOnLevelUp( SpellStorage knownSpells, int maxSpellLevel, Heroes &hero)
{
    //int randSpellLevel = ( std::rand() % maxSpellLevel ) + 1;

    std::vector<Spell> availableSpells;
    
    for (int i = 1; i <= Spell::SETWGUARDIAN; i++)
    {
        if (!knownSpells.isPresentSpell(i))
        {
            Spell newSpell = Spell( i );
            
            if ( newSpell.Level() <= maxSpellLevel ) 
            {
                availableSpells.push_back( i );
            }
        }
    }

    if (availableSpells.size() == 0)
    {
        return Spell::STONESKIN;
    }

    if ( availableSpells.size() == 1 ) {
        std::string msg = "Your hero learned ";
        msg += availableSpells[0].GetName();
        msg += " (the last spell he didn't know and is capable of understanding)";

        fheroes2::showStandardTextMessage( std::move( "Last Available Spell" ), std::move( msg ), Dialog::OK);
        return availableSpells[0].GetID();
    }

    if ( availableSpells.size() == 2 ) {
        int selection = rand() % 2;
        std::string msg = "Your hero learned ";
        msg += availableSpells[selection].GetName();
        msg += " (one of the 2 spells he didn't know and is capable of understanding)";

        fheroes2::showStandardTextMessage( std::move( "Learned Spell" ), std::move( msg ), Dialog::OK );
        return availableSpells[selection].GetID();
    }

    std::vector<Spell> pool = availableSpells;
    std::vector<Spell> result;

    for ( int i = 0; i < 3; i++ ) {
        int index = rand() % pool.size();

        result.push_back( pool[index] );
        pool.erase( pool.begin() + index );
    }

    // inferno
    //fheroes2::Display & display = fheroes2::Display::instance();
    //const int system = Settings::Get().isEvilInterfaceEnabled() ? ICN::SYSTEME : ICN::SYSTEM;

    //const CursorRestorer cursorRestorer( true, Cursor::POINTER );

    //// Text
    //fheroes2::Text title( _( "Spell Gift" ), fheroes2::FontType::normalYellow() );

    //fheroes2::Text textbox( _( "Upon leveling up, the Gods have blessed your hero with the choice to receive 1 of 3 new spells. Choose wisely!" ),
    //                        fheroes2::FontType::normalWhite() );

    //// Spells
    //Spell spell1( result[0] );
    //Spell spell2( result[1] );
    //Spell spell3( result[2] );

    //// Original sprites
    //const fheroes2::Sprite & scrollOriginal = Assets::getImage( ICN::TOWNWIND, 0 );

    //const fheroes2::Sprite & spellOriginal1 = Assets::getImage( ICN::SPELLS, spell1.IndexSprite() );
    //const fheroes2::Sprite & spellOriginal2 = Assets::getImage( ICN::SPELLS, spell2.IndexSprite() );
    //const fheroes2::Sprite & spellOriginal3 = Assets::getImage( ICN::SPELLS, spell3.IndexSprite() );

    //// Scaling: change 0.75 to 0.65 or 0.50 for smaller images
    //const double scale = 0.65;
    //const double scaleSpell = 1.0;

    //const auto scaledSpellSize = [scaleSpell]( int original ) { return std::max( 1, static_cast<int>( original * scaleSpell ) ); };
    //const auto scaledSize = [scale]( int original ) { return std::max( 1, static_cast<int>( original * scale ) ); };

    //// Allocate smaller images
    //fheroes2::Image scrollImage( scaledSize( scrollOriginal.width() ), scaledSize( scrollOriginal.height() ) );

    //fheroes2::Image spellImage1( scaledSpellSize( spellOriginal1.width() ), scaledSpellSize( spellOriginal1.height() ) );

    //fheroes2::Image spellImage2( scaledSpellSize( spellOriginal2.width() ), scaledSpellSize( spellOriginal2.height() ) );

    //fheroes2::Image spellImage3( scaledSpellSize( spellOriginal3.width() ), scaledSpellSize( spellOriginal3.height() ) );

    //// Resize sprites
    //fheroes2::Resize( scrollOriginal, scrollImage );
    //fheroes2::Resize( spellOriginal1, spellImage1 );
    //fheroes2::Resize( spellOriginal2, spellImage2 );
    //fheroes2::Resize( spellOriginal3, spellImage3 );

    //// Layout
    //const int spacer = 10;
    //const int scrollSpacing = 15;
    //const int sidePadding = 30;
    //const int skillTextWidth = 80;
    //const int spellNameHeight = 35;
    //const int bottomButtonSpace = 45;

    //const int scrollWidth = scrollImage.width();
    //const int scrollHeight = scrollImage.height();

    //const int requiredWidth = std::max( fheroes2::boxAreaWidthPx, scrollWidth * 3 + scrollSpacing * 2 + sidePadding * 2 );

    //const int requiredHeight = title.height( requiredWidth ) + textbox.height( requiredWidth ) + scrollHeight + spellNameHeight + bottomButtonSpace + spacer * 3;

    //// Resizable dialog
    //const Dialog::ResizableFrameBox box( requiredWidth, requiredHeight - 40, -1, true );

    //const fheroes2::Rect & box_rt = box.GetArea();

    //// Draw title and description
    //int currentY = box_rt.y;

    //title.draw( box_rt.x, currentY + 2, box_rt.width, display );
    //currentY += title.height( box_rt.width ) + spacer;

    //textbox.draw( box_rt.x, currentY + 2, box_rt.width, display );
    //currentY += textbox.height( box_rt.width ) + spacer;

    //// Selected spell
    //int res = spell1.GetID();

    //// Scroll positions
    //const int totalScrollWidth = scrollWidth * 3 + scrollSpacing * 2;

    //const int scrollStartX = box_rt.x + ( box_rt.width - totalScrollWidth ) / 2;

    //const int scrollY = currentY;

    //const int scrollX1 = scrollStartX;
    //const int scrollX2 = scrollX1 + scrollWidth + scrollSpacing;
    //const int scrollX3 = scrollX2 + scrollWidth + scrollSpacing;

    //// Scroll rectangles (clickable areas)
    //const fheroes2::Rect scrollRect1( scrollX1, scrollY, scrollWidth, scrollHeight );

    //const fheroes2::Rect scrollRect2( scrollX2, scrollY, scrollWidth, scrollHeight );

    //const fheroes2::Rect scrollRect3( scrollX3, scrollY, scrollWidth, scrollHeight );

    //// Center each spell on its scroll
    //const fheroes2::Rect rect1( scrollX1 + ( scrollWidth - spellImage1.width() ) / 2, scrollY + ( scrollHeight - spellImage1.height() ) / 2, spellImage1.width(),
    //                            spellImage1.height() );

    //const fheroes2::Rect rect2( scrollX2 + ( scrollWidth - spellImage2.width() ) / 2, scrollY + ( scrollHeight - spellImage2.height() ) / 2, spellImage2.width(),
    //                            spellImage2.height() );

    //const fheroes2::Rect rect3( scrollX3 + ( scrollWidth - spellImage3.width() ) / 2, scrollY + ( scrollHeight - spellImage3.height() ) / 2, spellImage3.width(),
    //                            spellImage3.height() );

    //// Draw scrolls and spells
    //const auto drawSpellImages = [&]() {
    //    // Scroll backgrounds
    //    fheroes2::Blit( scrollImage, display, scrollX1, scrollY );
    //    fheroes2::Blit( scrollImage, display, scrollX2, scrollY );
    //    fheroes2::Blit( scrollImage, display, scrollX3, scrollY );

    //    // Spell icons
    //    fheroes2::Blit( spellImage1, display, rect1.x, rect1.y );
    //    fheroes2::Blit( spellImage2, display, rect2.x, rect2.y );
    //    fheroes2::Blit( spellImage3, display, rect3.x, rect3.y );
    //};

    //// Draw spell names
    //const auto drawSpellNames = [&]() {
    //    fheroes2::Text text( spell1.GetName(), highlight( res, spell1.GetID() ) );

    //    text.draw( scrollRect1.x + ( scrollRect1.width - skillTextWidth ) / 2, scrollRect1.y + scrollRect1.height + 5, skillTextWidth, display );

    //    text.set( spell2.GetName(), highlight( res, spell2.GetID() ) );

    //    text.draw( scrollRect2.x + ( scrollRect2.width - skillTextWidth ) / 2, scrollRect2.y + scrollRect2.height + 5, skillTextWidth, display );

    //    text.set( spell3.GetName(), highlight( res, spell3.GetID() ) );

    //    text.draw( scrollRect3.x + ( scrollRect3.width - skillTextWidth ) / 2, scrollRect3.y + scrollRect3.height + 5, skillTextWidth, display );
    //};

    //// Initial drawing
    //drawSpellImages();
    //drawSpellNames();

    //// OK button
    //const fheroes2::Sprite & buttonImage = Assets::getImage( system, 1 );

    //const int buttonX = box_rt.x + ( box_rt.width - buttonImage.width() ) / 2;

    //const int buttonY = box_rt.y + box_rt.height - buttonImage.height();

    //fheroes2::Button buttonOk( buttonX, buttonY, system, 1, 2 );

    //LocalEvent & le = LocalEvent::Get();

    //buttonOk.draw();
    //display.render();

    //// Event loop
    //while ( le.HandleEvents() ) {
    //    bool redraw = false;

    //    buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

    //    if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) ) {
    //        if ( res == spell1.GetID() ) {
    //            res = spell3.GetID();
    //        }
    //        else if ( res == spell2.GetID() ) {
    //            res = spell1.GetID();
    //        }
    //        else {
    //            res = spell2.GetID();
    //        }

    //        redraw = true;
    //    }
    //    else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) ) {
    //        if ( res == spell1.GetID() ) {
    //            res = spell2.GetID();
    //        }
    //        else if ( res == spell2.GetID() ) {
    //            res = spell3.GetID();
    //        }
    //        else {
    //            res = spell1.GetID();
    //        }

    //        redraw = true;
    //    }
    //    else if ( le.MouseClickLeft( scrollRect1 ) ) {
    //        res = spell1.GetID();
    //        redraw = true;
    //    }
    //    else if ( le.MouseClickLeft( scrollRect2 ) ) {
    //        res = spell2.GetID();
    //        redraw = true;
    //    }
    //    else if ( le.MouseClickLeft( scrollRect3 ) ) {
    //        res = spell3.GetID();
    //        redraw = true;
    //    }

    //    if ( redraw ) {
    //        drawSpellImages();
    //        drawSpellNames();
    //        display.render();
    //    }

    //    if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) ) {
    //        break;
    //    }
    //}

    //return res;
// worked well above!

{
        const CursorRestorer cursorRestorer( true, Cursor::POINTER );

        fheroes2::Display & display = fheroes2::Display::instance();

        const Settings & conf = Settings::Get();
        const bool isEvilInterface = conf.isEvilInterfaceEnabled();

        const int system = isEvilInterface ? ICN::SYSTEME : ICN::SYSTEM;

        // -------------------------------------------------------
        // Text
        // -------------------------------------------------------

        const fheroes2::Text title( _( "Spell Gift" ), fheroes2::FontType::normalYellow() );

        const fheroes2::Text textbox( _( "Upon leveling up, the Gods have blessed your hero "
                                         "with the choice to receive 1 of 3 new spells. "
                                         "Choose wisely!" ),
                                      fheroes2::FontType::normalWhite() );

        // -------------------------------------------------------
        // Spells
        // -------------------------------------------------------

        const Spell spell1( result[0] );
        const Spell spell2( result[1] );
        const Spell spell3( result[2] );

        // -------------------------------------------------------
        // Original sprites
        // -------------------------------------------------------

        const fheroes2::Sprite & scrollOriginal = Assets::getImage( ICN::TOWNWIND, 0 );

        const fheroes2::Sprite & spellImage1 = Assets::getImage( ICN::SPELLS, spell1.IndexSprite() );

        const fheroes2::Sprite & spellImage2 = Assets::getImage( ICN::SPELLS, spell2.IndexSprite() );

        const fheroes2::Sprite & spellImage3 = Assets::getImage( ICN::SPELLS, spell3.IndexSprite() );

        // -------------------------------------------------------
        // Scale scrolls only
        // -------------------------------------------------------

        const double scrollScale = 0.75;

        const int scaledScrollWidth = std::max( 1, static_cast<int>( scrollOriginal.width() * scrollScale ) );

        const int scaledScrollHeight = std::max( 1, static_cast<int>( scrollOriginal.height() * scrollScale ) );

        fheroes2::Image scrollImage( scaledScrollWidth, scaledScrollHeight );

        fheroes2::Resize( scrollOriginal, scrollImage );

        const int scrollWidth = scrollImage.width();
        const int scrollHeight = scrollImage.height();

        // -------------------------------------------------------
        // Layout settings
        // -------------------------------------------------------

        const int spacer = 8;
        const int scrollSpacing = 7;
        const int sidePadding = 30;

        const int spellNameWidth = 100;
        const int spellNameHeight = 35;

        const int buttonSpacing = 20;
        const int buttonTopSpacing = 18;
        const int bottomPadding = 8;

        // Optional adjustments for visual centering
        const int spellOffsetX = 0;
        const int spellOffsetY = 0;

        // -------------------------------------------------------
        // Button sprites
        // -------------------------------------------------------

        const fheroes2::Sprite & buttonImage = Assets::getImage( system, 1 );

        const int icnHeroes = isEvilInterface ? ICN::EVIL_ARMY_BUTTON : ICN::GOOD_ARMY_BUTTON;

        const fheroes2::Sprite & heroButtonImage = Assets::getImage( icnHeroes, 0 );

        const int buttonRowHeight = std::max( buttonImage.height(), heroButtonImage.height() );

        // -------------------------------------------------------
        // Dialog dimensions
        // -------------------------------------------------------

        const int requiredWidth = std::max( fheroes2::boxAreaWidthPx, scrollWidth * 3 + scrollSpacing * 2 + sidePadding * 2 );

        const int textHeight = title.height( requiredWidth ) + textbox.height( requiredWidth ) + spacer * 2;

        const int requiredHeight = textHeight + scrollHeight + 5 + spellNameHeight + buttonTopSpacing + buttonRowHeight + bottomPadding - 40;

        const Dialog::ResizableFrameBox box( requiredWidth, requiredHeight, -1, true );

        const fheroes2::Rect & box_rt = box.GetArea();

        // -------------------------------------------------------
        // Title and description
        // -------------------------------------------------------

        int currentY = box_rt.y;

        title.draw( box_rt.x, currentY + 2, box_rt.width, display );

        currentY += title.height( box_rt.width ) + spacer;

        textbox.draw( box_rt.x, currentY + 2, box_rt.width, display );

        currentY += textbox.height( box_rt.width ) + spacer;

        // -------------------------------------------------------
        // Scroll positions
        // -------------------------------------------------------

        const int totalScrollWidth = scrollWidth * 3 + scrollSpacing * 2;

        const int scrollStartX = box_rt.x + ( box_rt.width - totalScrollWidth ) / 2;

        const int scrollY = currentY;

        const int scrollX1 = scrollStartX;
        const int scrollX2 = scrollX1 + scrollWidth + scrollSpacing;
        const int scrollX3 = scrollX2 + scrollWidth + scrollSpacing;

        const fheroes2::Rect scrollRect1( scrollX1, scrollY, scrollWidth, scrollHeight );

        const fheroes2::Rect scrollRect2( scrollX2, scrollY, scrollWidth, scrollHeight );

        const fheroes2::Rect scrollRect3( scrollX3, scrollY, scrollWidth, scrollHeight );

        // -------------------------------------------------------
        // Spell icon positions
        // -------------------------------------------------------

        const fheroes2::Rect rect1( scrollX1 + ( scrollWidth - spellImage1.width() ) / 2 + spellOffsetX,
                                    scrollY + ( scrollHeight - spellImage1.height() ) / 2 + spellOffsetY, spellImage1.width(), spellImage1.height() );

        const fheroes2::Rect rect2( scrollX2 + ( scrollWidth - spellImage2.width() ) / 2 + spellOffsetX,
                                    scrollY + ( scrollHeight - spellImage2.height() ) / 2 + spellOffsetY, spellImage2.width(), spellImage2.height() );

        const fheroes2::Rect rect3( scrollX3 + ( scrollWidth - spellImage3.width() ) / 2 + spellOffsetX,
                                    scrollY + ( scrollHeight - spellImage3.height() ) / 2 + spellOffsetY, spellImage3.width(), spellImage3.height() );

        // -------------------------------------------------------
        // Selected spell
        // -------------------------------------------------------

        int res = spell1.GetID();

        // -------------------------------------------------------
        // Drawing helpers
        // -------------------------------------------------------

        const auto drawSpellImages = [&]() {
            fheroes2::Blit( scrollImage, display, scrollX1, scrollY );
            fheroes2::Blit( scrollImage, display, scrollX2, scrollY );
            fheroes2::Blit( scrollImage, display, scrollX3, scrollY );

            fheroes2::Blit( spellImage1, display, rect1.x, rect1.y );

            fheroes2::Blit( spellImage2, display, rect2.x, rect2.y );

            fheroes2::Blit( spellImage3, display, rect3.x, rect3.y );
        };

        const auto drawSpellNames = [&]() {
            fheroes2::Text text( spell1.GetName(), highlight( res, spell1.GetID() ) );

            const int nameY = scrollY + scrollHeight + 5;

            text.draw( scrollX1 + ( scrollWidth - spellNameWidth ) / 2, nameY, spellNameWidth, display );

            text.set( spell2.GetName(), highlight( res, spell2.GetID() ) );

            text.draw( scrollX2 + ( scrollWidth - spellNameWidth ) / 2, nameY, spellNameWidth, display );

            text.set( spell3.GetName(), highlight( res, spell3.GetID() ) );

            text.draw( scrollX3 + ( scrollWidth - spellNameWidth ) / 2, nameY, spellNameWidth, display );
        };

        drawSpellImages();
        drawSpellImages();
        drawSpellImages();
        drawSpellNames();

        // -------------------------------------------------------
        // Center Hero + OK buttons together
        // -------------------------------------------------------

        const int totalButtonWidth = heroButtonImage.width() + buttonSpacing + buttonImage.width();

        const int buttonStartX = box_rt.x + ( box_rt.width - totalButtonWidth ) / 2;

        const int buttonRowY = box_rt.y + box_rt.height - buttonRowHeight - bottomPadding;

        const int heroButtonX = buttonStartX;

        const int heroButtonY = buttonRowY + ( buttonRowHeight - heroButtonImage.height() ) / 2;

        const int buttonX = buttonStartX + heroButtonImage.width() + buttonSpacing;

        const int buttonY = buttonRowY + ( buttonRowHeight - buttonImage.height() ) / 2;

        fheroes2::Button buttonOk( buttonX, buttonY, system, 1, 2 );

        fheroes2::ButtonSprite buttonHero
            = fheroes2::makeButtonWithBackground( heroButtonX, heroButtonY, Assets::getImage( icnHeroes, 0 ), Assets::getImage( icnHeroes, 1 ), display );

        // -------------------------------------------------------
        // Initial rendering
        // -------------------------------------------------------

        buttonOk.draw();
        buttonHero.draw();

        display.render();

        // -------------------------------------------------------
        // Event loop
        // -------------------------------------------------------

        LocalEvent & le = LocalEvent::Get();

        while ( le.HandleEvents() ) {
            bool redraw = false;

            buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

            buttonHero.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonHero.area() ) );

            // ---------------------------------------------------
            // View Hero
            // ---------------------------------------------------

            if ( le.MouseClickLeft( buttonHero.area() ) ) {
                le.reset();

                hero.OpenDialog( false, true, true, true, true, false, fheroes2::getLanguageFromAbbreviation( conf.getGameLanguage() ) );

                display.render();
                continue;
            }

            // ---------------------------------------------------
            // Hero button tooltip
            // ---------------------------------------------------

            if ( le.isMouseRightButtonPressedInArea( buttonHero.area() ) ) {
                fheroes2::showStandardTextMessage( "", _( "View Hero" ), Dialog::ZERO );

                display.render();
            }

            // ---------------------------------------------------
            // Keyboard selection
            // ---------------------------------------------------

            if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) ) {
                if ( res == spell1.GetID() ) {
                    res = spell3.GetID();
                }
                else if ( res == spell2.GetID() ) {
                    res = spell1.GetID();
                }
                else {
                    res = spell2.GetID();
                }

                redraw = true;
            }
            else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) ) {
                if ( res == spell1.GetID() ) {
                    res = spell2.GetID();
                }
                else if ( res == spell2.GetID() ) {
                    res = spell3.GetID();
                }
                else {
                    res = spell1.GetID();
                }

                redraw = true;
            }

            // ---------------------------------------------------
            // Mouse selection
            // ---------------------------------------------------

            else if ( le.MouseClickLeft( scrollRect1 ) ) {
                res = spell1.GetID();
                redraw = true;
            }
            else if ( le.MouseClickLeft( scrollRect2 ) ) {
                res = spell2.GetID();
                redraw = true;
            }
            else if ( le.MouseClickLeft( scrollRect3 ) ) {
                res = spell3.GetID();
                redraw = true;
            }

            // ---------------------------------------------------
            // Redraw selected spell
            // ---------------------------------------------------

            if ( redraw ) {
                drawSpellImages();
                drawSpellNames();

                buttonOk.draw();
                buttonHero.draw();

                display.render();
            }

            // ---------------------------------------------------
            // Confirm spell selection
            // ---------------------------------------------------

            if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) ) {
                break;
            }
        }

        return res;
    }

    //int maxArtNameSize = std::max( { static_cast<int>( std::strlen( spell1.GetName() ) ), static_cast<int>( std::strlen( spell2.GetName() ) ),
    //                                 static_cast<int>( std::strlen( spell3.GetName() ) ) } );

    //const Dialog::FrameBox box( title.height( fheroes2::boxAreaWidthPx ) + textbox.height( fheroes2::boxAreaWidthPx ) + 2 * spacer + sprite.height() + 15
    //                                + maxArtNameSize,
    //                            true );

    //const fheroes2::Rect & box_rt = box.GetArea();
    //fheroes2::Point dst_pt( box_rt.x, box_rt.y );

    //title.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    //dst_pt.y += title.height( fheroes2::boxAreaWidthPx ) + spacer;

    //textbox.draw( dst_pt.x, dst_pt.y + 2, fheroes2::boxAreaWidthPx, display );
    //dst_pt.y += textbox.height( fheroes2::boxAreaWidthPx ) + spacer;

    //int res = spell1.GetID();

    //const int spacingX = ( box_rt.width - scrollImage.width() * 3 ) / 4;

    //fheroes2::Rect rect1( dst_pt.x + spacingX, dst_pt.y, scrollImage.width(), scrollImage.height() );
    //fheroes2::Rect rect2( rect1.x + scrollImage.width() + spacingX, dst_pt.y, scrollImage.width(), scrollImage.height() );
    //fheroes2::Rect rect3( rect2.x + scrollImage.width() + spacingX, dst_pt.y, scrollImage.width(), scrollImage.height() );

    //// Draw the background centered behind all three spells
    //// Calculate spacing for 3 scrolls
    //const int spacingXScroll = ( box_rt.width - scrollImage.width() * 3 ) / 4;

    //// Position the 3 scrolls
    //const int scrollY = dst_pt.y;

    //const int scrollX1 = box_rt.x + spacingXScroll;
    //const int scrollX2 = scrollX1 + scrollImage.width() + spacingXScroll;
    //const int scrollX3 = scrollX2 + scrollImage.width() + spacingXScroll;

    //// Draw all 3 scroll backgrounds
    //fheroes2::Blit( scrollImage, display, scrollX1, scrollY );
    //fheroes2::Blit( scrollImage, display, scrollX2, scrollY );
    //fheroes2::Blit( scrollImage, display, scrollX3, scrollY );

    //InfoSpellClear( spell1.IndexSprite(), spell2.IndexSprite(), spell3.IndexSprite(), rect1, rect2, rect3 );
    //InfoSpellSelect( res, spell1.IndexSprite(), spell2.IndexSprite(), spell3.IndexSprite(), rect1, rect2, rect3 ); // this had rect2 and rect3, maybe switch back

    //// info texts
    //const int32_t skillTextWidth = 60;

    //fheroes2::Text text( spell1.GetName(), highlight( res, spell1.GetID() ) );
    //dst_pt.x = rect1.x + ( rect1.width - skillTextWidth ) / 2;
    //dst_pt.y = rect1.y + rect1.height + 5;
    //text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    //text.set( spell2.GetName(), highlight( res, spell2.GetID() ) );
    //dst_pt.x = rect2.x + ( rect2.width - skillTextWidth ) / 2;
    //dst_pt.y = rect2.y + rect2.height + 5;
    //text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    //text.set( spell3.GetName(), highlight( res, spell3.GetID() ) );
    //dst_pt.x = rect3.x + ( rect3.width - skillTextWidth ) / 2;
    //dst_pt.y = rect3.y + rect3.height + 5;
    //text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display ); // here

    //// buttons
    //dst_pt.x = box_rt.x + ( box_rt.width - Assets::getImage( system, 1 ).width() ) / 2;
    //dst_pt.y = box_rt.y + box_rt.height - Assets::getImage( system, 1 ).height();
    //fheroes2::Button buttonOk( dst_pt.x, dst_pt.y, system, 1, 2 );

    //LocalEvent & le = LocalEvent::Get();

    //buttonOk.draw();
    //display.render();

    //// message loop
    //while ( le.HandleEvents() ) {
    //    bool redraw = false;

    //    buttonOk.drawOnState( le.isMouseLeftButtonPressedAndHeldInArea( buttonOk.area() ) );

    //    if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_LEFT ) && Skill::Primary::UNKNOWN != InfoSkillPrev( res ) ) {
    //        res = InfoSkillPrev( res );
    //        redraw = true;
    //    }
    //    else if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_RIGHT ) && Skill::Primary::UNKNOWN != InfoSkillNext( res ) ) {
    //        res = InfoSkillNext( res );
    //        redraw = true;
    //    }
    //    else if ( le.MouseClickLeft( rect1 ) ) {
    //        res = spell1.GetID();
    //        redraw = true;
    //    }
    //    else if ( le.MouseClickLeft( rect2 ) ) {
    //        res = spell2.GetID();
    //        redraw = true;
    //    }
    //    else if ( le.MouseClickLeft( rect3 ) ) {
    //        res = spell3.GetID();
    //        redraw = true;
    //    }
    //    //else if ( le.isMouseRightButtonPressedInArea( rect1 ) ) {
    //    //    fheroes2::PrimarySkillDialogElement( Skill::Primary::ATTACK, "" ).showPopup( Dialog::ZERO );
    //    //    //fheroes2::SpellDialogElement( spell).showPopup( Dialog::ZERO );
    //    //}
    //    //else if ( le.isMouseRightButtonPressedInArea( rect2 ) ) {
    //    //    fheroes2::PrimarySkillDialogElement( Skill::Primary::DEFENSE, "" ).showPopup( Dialog::ZERO );
    //    //    //fheroes2::ArtifactDialogElement( art2 ).showPopup( Dialog::ZERO );
    //    //}
    //    //else if ( le.isMouseRightButtonPressedInArea( rect3 ) ) {
    //    //    fheroes2::PrimarySkillDialogElement( Skill::Primary::POWER, "" ).showPopup( Dialog::ZERO );
    //    //    //fheroes2::ArtifactDialogElement( art3 ).showPopup( Dialog::ZERO );
    //    //}

    //    if ( redraw ) {
    //        InfoSpellClear( spell1.IndexSprite(), spell2.IndexSprite(), spell3.IndexSprite(), rect1, rect2, rect3 );
    //        InfoSpellSelect( res, spell1.IndexSprite(), spell2.IndexSprite(), spell3.IndexSprite(), rect1, rect2, rect3 );

    //        text.set( spell1.GetName(), highlight( res, spell1.GetID() ) );
    //        dst_pt.x = rect1.x + ( rect1.width - skillTextWidth ) / 2;
    //        dst_pt.y = rect1.y + rect1.height + 5;
    //        text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    //        text.set( spell2.GetName(), highlight( res, spell2.GetID() ) );
    //        dst_pt.x = rect2.x + ( rect2.width - skillTextWidth ) / 2;
    //        dst_pt.y = rect2.y + rect2.height + 5;
    //        text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display );

    //        text.set( spell3.GetName(), highlight( res, spell3.GetID() ) );
    //        dst_pt.x = rect3.x + ( rect3.width - skillTextWidth ) / 2;
    //        dst_pt.y = rect3.y + rect3.height + 5;
    //        text.draw( dst_pt.x, dst_pt.y + 2, skillTextWidth, display ); // here

    //        display.render();
    //    }

    //    if ( Game::HotKeyPressEvent( Game::HotKeyEvent::DEFAULT_OKAY ) || le.MouseClickLeft( buttonOk.area() ) )
    //        break;
    //}

    //return res;
}