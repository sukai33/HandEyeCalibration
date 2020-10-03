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
#ifndef ASTRA_DEFINES_H
#define ASTRA_DEFINES_H

#ifdef  __cplusplus
    #define ASTRA_BEGIN_DECLS extern "C" {
    #define ASTRA_END_DECLS   }
#else
    #define ASTRA_BEGIN_DECLS
    #define ASTRA_END_DECLS
#endif

#if defined (_MSC_VER)
    #define ASTRA_EXPORT __declspec(dllexport)
    #define ASTRA_IMPORT __declspec(dllimport)
    #define ASTRA_PUBLIC
    #define ASTRA_LOCAL
    #define ASTRA_CALLBACK __cdecl
#else
    #if __GNUC__ >= 4 || defined (__clang__)
        #define ASTRA_PUBLIC __attribute__ ((visibility ("default")))
        #define ASTRA_LOCAL  __attribute__ ((visibility ("hidden")))
        #define ASTRA_EXPORT ASTRA_PUBLIC
        #define ASTRA_IMPORT
        #if defined(__x86_64__) || defined(__ANDROID__)
            #define ASTRA_CALLBACK
        #else
            #define ASTRA_CALLBACK __attribute__ ((__cdecl__))
        #endif
    #else
        #define ASTRA_PUBLIC
        #define ASTRA_LOCAL
        #define ASTRA_EXPORT
        #define ASTRA_IMPORT
        #define ASTRA_CALLBACK
    #endif
#endif

#ifndef ASTRA_API
    #ifdef ASTRA_BUILD
        #define ASTRA_API ASTRA_PUBLIC ASTRA_EXPORT
    #else
        #define ASTRA_API ASTRA_IMPORT
    #endif
#endif

#ifndef ASTRA_API_EX
    #ifdef ASTRA_BUILD_EX
        #define ASTRA_API_EX ASTRA_EXPORT
    #else
        #define ASTRA_API_EX ASTRA_IMPORT
    #endif
#endif

#endif /* ASTRA_DEFINES_H */
