/*
 * ProffieConfig, All-In-One Proffieboard Management Utility
 * Copyright (C) 2024 Ryan Ogurek
 *
 * main.cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <memory>
#include <ostream>
#include <unistd.h>
#include <wx/app.h>
#include <wx/frame.h>

#include "appcore/state.h"
#include "styles/bladestyle.h"
#include "styles/parse.h"
#include "test/uitest.h"

class ProffieConfig : public wxApp {
public:
    bool OnInit() override {
#   	ifdef __WXMSW__
        MSWEnableDarkMode();
        if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
            freopen("CONIN$", "r", stdin);
            std::ios::sync_with_stdio();
        }
#   	endif
#       ifdef __WXGTK__
        GTKSuppressDiagnostics();
#       endif

        chdir(argv[0].BeforeLast('/'));

        AppCore::init();
        // auto config{Config::readConfig("problemConfig.h")};
        // Config::writeConfig("test/problemConfig.h", *config);

        std::unique_ptr<BladeStyles::BladeStyle> style{BladeStyles::parseString(
                "// This is a line comment, lol!\n"
                "/* This is a block comment\n"
                "that spans multiple lines\n"
                "and is kinda scary\n"
                "*/\n"
                "StylePtr<Cylon<AudioFlicker<Blue, Black>, 20, 20, Green, 10, 200, 1000, DarkOrange>>()"
                )};
        auto styleStr{BladeStyles::asString(*style)};
        std::cout << styleStr.value() << std::endl;

        auto* testFrame{Test::init()};
        testFrame->Show();

        return true;
    }
};

wxIMPLEMENT_APP(ProffieConfig); // NOLINT
