// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015-2017 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32

#include <windows.h>

#else //_WIN32 -> OS X, LINUX

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#endif //_WIN32

static bool shouldContinue = true;

void signal_stop_processing(){
    printf("quitting...\n\n");
    shouldContinue = false;
}

#ifdef _WIN32

bool CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        signal_stop_processing();
        return(TRUE);
    default:
        return FALSE;
    }
}

#else //_WIN32 -> OSX, LINUX

static void signal_handler(int s) {
    signal_stop_processing();
}

#endif //_WIN32

static void set_key_handler()
{
#ifdef _WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);

#else //_WIN32 -> OS X, LINUX

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = &signal_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

#endif //_WIN32
}

#endif /* KEY_HANDLER_H */
