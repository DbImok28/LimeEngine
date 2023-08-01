// Copyright (C) Pavel Jakushik - All rights reserved
// See the LICENSE file for copyright and licensing details.
// GitHub: https://github.com/RubyCircle/LimeEngine
#pragma once
#ifndef _WIN32_WINNT
	#define _WIN32_WINNT _WIN32_WINNT_WIN7 // Windows 7 or later
#endif
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS    // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOSYSMETRICS     // SM_*
#define NOMENUS          // MF_*
#define NOICONS          // IDI_*
#define NOSYSCOMMANDS    // SC_*
#define NORASTEROPS      // Binary and Tertiary raster ops
#define OEMRESOURCE      // OEM Resource values
#define NOATOM           // Atom Manager routines
#define NOCLIPBOARD      // Clipboard routines
#define NOCOLOR          // Screen colors
#define NOCTLMGR         // Control and Dialog routines
#define NODRAWTEXT       // DrawText() and DT_*
#define NOKERNEL         // All KERNEL defines and routines
#define NONLS            // All NLS defines and routines
#define NOMEMMGR         // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE       // typedef METAFILEPICT
#define NOMINMAX         // Macros min(a,b) and max(a,b)
#define NOOPENFILE       // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL         // SB_* and scrolling routines
#define NOSERVICE        // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND          // Sound driver routines
#define NOTEXTMETRIC     // typedef TEXTMETRIC and associated routines
#define NOWH             // SetWindowsHook and WH_*
#define NOCOMM           // COMM driver routines
#define NOKANJI          // Kanji support stuff.
#define NOHELP           // Help engine interface.
#define NOPROFILER       // Profiler interface.
#define NODEFERWINDOWPOS // DeferWindowPos routines
#define NOMCX            // Modem Configuration Extensions
/*
* NOVIRTUALKEYCODES - VK_ *
* NOWINMESSAGES     - WM_*, EM_*, LB_*, CB_*
* NOWINSTYLES       - WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
* NOSHOWWINDOW      - SW_*
* NOGDI             - All GDI defines and routines
* NOUSER            - All USER defines and routines
* NOMSG             - typedef MSG and associated routines
* NOWINOFFSETS      - GWL_*, GCL_*, associated routines
*/

#ifndef STRICT
	#define STRICT
#endif

#include <Windows.h>