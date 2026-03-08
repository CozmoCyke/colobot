/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2023, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

#include "ui/screen/screen_main_menu.h"

#include "app/app.h"

#include "common/edu_mode.h"
#include "common/logger.h"
#include "common/restext.h"

#include "level/parser/parser.h"

#include "sound/sound.h"

#include "ui/controls/button.h"
#include "ui/controls/control.h"
#include "ui/controls/group.h"
#include "ui/controls/interface.h"
#include "ui/controls/label.h"
#include "ui/controls/window.h"

#include "ui/screen/screen_setup.h"

namespace Ui
{

CScreenMainMenu::CScreenMainMenu()
{
}

void CScreenMainMenu::CreateInterface()
{
    CWindow*        pw;
    CLabel*         pl;
    CButton*        pb;
    CGroup*         pg;
    Math::Point     pos, ddim;
    std::string     name;

    m_inEduSpecialMissions = false;

    pos.x  = 0.35f;
    pos.y  = 0.10f;
    ddim.x = 0.30f;
    ddim.y = 0.80f;
    pw = m_interface->CreateWindows(pos, ddim, 10, EVENT_WINDOW5);

    GetResource(RES_TEXT, RT_TITLE_APPNAME, name);
    pw->SetName(name);

    pos.x  = 0.35f;
    pos.y  = 0.60f;
    ddim.x = 0.30f;
    ddim.y = 0.30f;
    pw->CreateGroup(pos, ddim, 5, EVENT_INTERFACE_GLINTl);  // orange corner
    pos.x  = 0.35f;
    pos.y  = 0.10f;
    ddim.x = 0.30f;
    ddim.y = 0.30f;
    pw->CreateGroup(pos, ddim, 4, EVENT_INTERFACE_GLINTr);  // blue corner

    ddim.x = 0.20f;
    pos.x = 0.40f;
    ddim.y = dim.y*2.0f;
    pos.y = oy+sy*9.5f;
    pg = pw->CreateGroup(pos, ddim, 23, EVENT_LABEL1);  // missions + freegame
    pg->SetState(STATE_SHADOW);
    ddim.y = dim.y*2.95f;
    pos.y = oy+sy*6.7f;
    pg = pw->CreateGroup(pos, ddim, 24, EVENT_LABEL1);  // exercises + challenges
    pg->SetState(STATE_SHADOW);
    ddim.y = dim.y*1.6f;
    pos.y = oy+sy*3.4f;
    pg = pw->CreateGroup(pos, ddim, 25, EVENT_LABEL1);  // change player + settings
    pg->SetState(STATE_SHADOW);
    ddim.y = dim.y*1.2f;
    pos.y = oy+sy*1.9f;
    pg = pw->CreateGroup(pos, ddim, 26, EVENT_LABEL1);  // quit
    pg->SetState(STATE_SHADOW);

    ddim.x = 0.12f;
    ddim.y = dim.y*0.8f;
    pos.x = 0.41f;
    pos.y = oy+sy*10.5f;

    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_MISSION);
    pb->SetState(STATE_SHADOW);

    ddim.x = 0.06f;
    pos.x = 0.53f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_PLUS);
    pb->SetState(STATE_SHADOW);

    ddim.x = 0.18f;
    pos.x = 0.41f;

    pos.y = oy+sy*9.6f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_FREE);
    pb->SetState(STATE_SHADOW);

    pos.y = oy+sy*8.6f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_TRAINER);
    pb->SetState(STATE_SHADOW);

    pos.y = oy+sy*7.7f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_DEFI);
    pb->SetState(STATE_SHADOW);

    pos.y = oy+sy*6.8f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_CODE_BATTLES);
    pb->SetState(STATE_SHADOW);

    pos.y = oy+sy*5.8f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_USER);
    pb->SetState(STATE_SHADOW);
    try
    {
        CLevelParser levelParser("levels/custom/config.txt");
        if (levelParser.Exists())
        {
            levelParser.Load();
            CLevelParserLine* line = levelParser.Get("Button");
            if (line->GetParam("name")->IsDefined())
                pb->SetName(line->GetParam("name")->AsString());
            if (line->GetParam("tooltip")->IsDefined())
                pb->SetTooltip(line->GetParam("tooltip")->AsString());
        }
    }
    catch (CLevelParserException& e)
    {
        GetLogger()->Error("Failed loading userlevel button name: %s\n", e.what());
    }

    ddim.y = dim.y*0.5f;
    pos.y = oy+sy*4.35f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_NAME);
    pb->SetState(STATE_SHADOW);

    ddim.y = dim.y*0.75f;
    pos.y = oy+sy*3.5f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_SETUP);
    pb->SetState(STATE_SHADOW);

    ddim.y = dim.y*1;
    pos.y = oy+sy*2.0f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_QUIT);
    pb->SetState(STATE_SHADOW);

    pos.x  = 0.40f;
    ddim.x = 0.20f;
    pos.y  =  26.0f/480.0f;
    ddim.y =  12.0f/480.0f;
    pg = pw->CreateGroup(pos, ddim, 1, EVENT_LABEL1);
    pg->SetState(STATE_SHADOW);
    pos.y -=  5.0f/480.0f;
    pl = pw->CreateLabel(pos, ddim, 0, EVENT_LABEL1, "TerranovaTeam");
    pl->SetFontType(Gfx::FONT_STUDIO);
    pl->SetFontSize(Gfx::FONT_SIZE_SMALL);

    // SatCom button
    pos.x = ox+sx*4.3f;
    pos.y = oy+sy*4.3f;
    ddim.x = dim.x*1.2f;
    ddim.y = dim.y*1.2f;
    pb = pw->CreateButton(pos, ddim, 128+60, EVENT_INTERFACE_SATCOM);
    pb->SetState(STATE_SHADOW);

    // Mods button
    pos.x  = 447.0f/640.0f;
    pos.y  = 313.0f/480.0f;
    ddim.x = 0.09f;
    pb = pw->CreateButton(pos, ddim, -1, EVENT_INTERFACE_MODS);
    pb->SetState(STATE_SHADOW);


    if (Edu::IsEnabled())
    {
        ApplyEduTopLevelLayout(pw);
    }

    SetBackground("textures/interface/interface.png");
    CreateVersionDisplay();
}

void CScreenMainMenu::ApplyEduTopLevelLayout(CWindow* window)
{
    auto setVisible = [&](EventType eventType, bool visible)
    {
        CControl* control = window->SearchControl(eventType);
        if (control == nullptr) return;
        control->SetState(STATE_VISIBLE, visible);
        control->SetState(STATE_ENABLE, visible);
    };

    m_inEduSpecialMissions = false;

    setVisible(EVENT_INTERFACE_MISSION, m_main->HasPlayableLevels(LevelCategory::Missions));
    setVisible(EVENT_INTERFACE_PLUS, m_main->HasPlayableLevels(LevelCategory::GamePlus));
    setVisible(EVENT_INTERFACE_CODE_BATTLES, m_main->HasPlayableLevels(LevelCategory::CodeBattles));

    setVisible(EVENT_INTERFACE_TRAINER, false);
    setVisible(EVENT_INTERFACE_DEFI, false);
    setVisible(EVENT_INTERFACE_FREE, false);

    const bool hasSpecialMissions = m_main->HasEduSpecialMissions();
    setVisible(EVENT_INTERFACE_USER, hasSpecialMissions);

    CButton* specialButton = static_cast<CButton*>(window->SearchControl(EVENT_INTERFACE_USER));
    if (specialButton != nullptr)
    {
        specialButton->SetName("Special Missions");
        specialButton->SetTooltip("Special Missions");
    }

    setVisible(EVENT_INTERFACE_MODS, m_main->CanAccessPackageManagement());
}

void CScreenMainMenu::ApplyEduSpecialMissionsLayout(CWindow* window)
{
    auto setButton = [&](EventType eventType, bool visible, EventType textEvent)
    {
        CButton* button = static_cast<CButton*>(window->SearchControl(eventType));
        if (button == nullptr) return;
        button->SetState(STATE_VISIBLE, visible);
        button->SetState(STATE_ENABLE, visible);
        std::string name;
        GetResource(RES_EVENT, textEvent, name);
        auto pos = name.find('\\');
        if (pos != std::string::npos)
        {
            name = name.substr(0, pos);
        }
        button->SetName(name);
    };

    m_inEduSpecialMissions = true;

    CControl* mission = window->SearchControl(EVENT_INTERFACE_MISSION);
    if (mission != nullptr)
    {
        mission->SetState(STATE_VISIBLE, false);
        mission->SetState(STATE_ENABLE, false);
    }
    CControl* plus = window->SearchControl(EVENT_INTERFACE_PLUS);
    if (plus != nullptr)
    {
        plus->SetState(STATE_VISIBLE, false);
        plus->SetState(STATE_ENABLE, false);
    }
    CControl* battles = window->SearchControl(EVENT_INTERFACE_CODE_BATTLES);
    if (battles != nullptr)
    {
        battles->SetState(STATE_VISIBLE, false);
        battles->SetState(STATE_ENABLE, false);
    }

    setButton(EVENT_INTERFACE_TRAINER, m_main->HasPlayableLevels(LevelCategory::Exercises), EVENT_INTERFACE_TRAINER);
    setButton(EVENT_INTERFACE_DEFI, m_main->HasPlayableLevels(LevelCategory::Challenges), EVENT_INTERFACE_DEFI);
    setButton(EVENT_INTERFACE_FREE, m_main->HasPlayableLevels(LevelCategory::FreeGame), EVENT_INTERFACE_FREE);
    setButton(EVENT_INTERFACE_USER, m_main->HasPlayableLevels(LevelCategory::CustomLevels), EVENT_INTERFACE_USER);
}

bool CScreenMainMenu::OpenEduSecondaryCategory(EventType eventType)
{
    LevelCategory category = LevelCategory::Max;

    if (eventType == EVENT_INTERFACE_TRAINER) category = LevelCategory::Exercises;
    if (eventType == EVENT_INTERFACE_DEFI) category = LevelCategory::Challenges;
    if (eventType == EVENT_INTERFACE_FREE) category = LevelCategory::FreeGame;
    if (eventType == EVENT_INTERFACE_USER) category = LevelCategory::CustomLevels;

    if (category == LevelCategory::Max || !m_main->HasPlayableLevels(category))
    {
        return false;
    }

    m_main->SetLevel(category, 0, 0);
    m_main->ChangePhase(PHASE_LEVEL_LIST);
    return true;
}

bool CScreenMainMenu::EventProcess(const Event &event)
{
    switch (event.type)
    {
        case EVENT_KEY_DOWN:
            if ( event.GetData<KeyEventData>()->key == KEY(ESCAPE) )
            {
                if (Edu::IsEnabled() && m_inEduSpecialMissions)
                {
                    CWindow* window = static_cast<CWindow*>(m_interface->SearchControl(EVENT_WINDOW5));
                    if (window != nullptr)
                    {
                        ApplyEduTopLevelLayout(window);
                    }
                }
                else
                {
                    m_sound->Play(SOUND_TZOING);
                    m_main->ChangePhase(PHASE_QUIT_SCREEN);
                }
                return false;
            }
            return true;
            break;

        case EVENT_INTERFACE_QUIT:
            m_sound->Play(SOUND_TZOING);
            m_main->ChangePhase(PHASE_QUIT_SCREEN);
            break;

        case EVENT_INTERFACE_TRAINER:
            if (Edu::IsEnabled() && m_inEduSpecialMissions)
            {
                OpenEduSecondaryCategory(event.type);
                break;
            }
            m_main->SetLevel(LevelCategory::Exercises, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_DEFI:
            if (Edu::IsEnabled() && m_inEduSpecialMissions)
            {
                OpenEduSecondaryCategory(event.type);
                break;
            }
            m_main->SetLevel(LevelCategory::Challenges, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_MISSION:
            m_main->SetLevel(LevelCategory::Missions, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_FREE:
            if (Edu::IsEnabled() && m_inEduSpecialMissions)
            {
                OpenEduSecondaryCategory(event.type);
                break;
            }
            m_main->SetLevel(LevelCategory::FreeGame, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_CODE_BATTLES:
            m_main->SetLevel(LevelCategory::CodeBattles, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_PLUS:
            m_main->SetLevel(LevelCategory::GamePlus, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_USER:
            if (Edu::IsEnabled())
            {
                if (m_inEduSpecialMissions)
                {
                    OpenEduSecondaryCategory(event.type);
                    return false;
                }

                CWindow* window = static_cast<CWindow*>(m_interface->SearchControl(EVENT_WINDOW5));
                if (window != nullptr)
                {
                    ApplyEduSpecialMissionsLayout(window);
                }
                return false;
            }

            m_main->SetLevel(LevelCategory::CustomLevels, 0, 0);
            m_main->ChangePhase(PHASE_LEVEL_LIST);
            break;

        case EVENT_INTERFACE_SETUP:
            m_main->ChangePhase(CScreenSetup::GetTab());
            break;

        case EVENT_INTERFACE_NAME:
            m_main->ChangePhase(PHASE_PLAYER_SELECT);
            break;

        case EVENT_INTERFACE_SATCOM:
            m_main->ChangePhase(PHASE_SATCOM);
            break;

        case EVENT_INTERFACE_MODS:
            if (m_main->CanAccessPackageManagement())
                m_main->ChangePhase(PHASE_MOD_LIST);
            break;

        default:
            return true;
    }
    return false;
}

} // namespace Ui
