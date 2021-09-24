/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "../SDL_sysurl.h"

#include <string.h>
#if defined(__SNC__)
#include <apputil.h>
#include <kernel.h>
#else
#include <psp2/apputil.h>
#endif

int
SDL_SYS_OpenURL(const char *url)
{
    SceAppUtilInitParam init_param;
    SceAppUtilBootParam boot_param;
    SceAppUtilWebBrowserParam browser_param;
    SDL_zero(init_param);
    SDL_zero(boot_param);
    sceAppUtilInit(&init_param, &boot_param);
    SDL_zero(browser_param);
#if defined(__SNC__)
	browser_param.wbstr = url;
	browser_param.wbstrLength = strlen(url);
	browser_param.launchMode = SCE_APPUTIL_WEBBROWSER_LAUNCH_APP_MODAL;
	if (sceAppUtilLaunchWebBrowser(&browser_param) < 0) {
		browser_param.launchMode = SCE_APPUTIL_WEBBROWSER_LAUNCH_APP_NORMAL;
		sceAppUtilLaunchWebBrowser(&browser_param);
	}
#else
    browser_param.str = url;
    browser_param.strlen = strlen(url);
	sceAppUtilLaunchWebBrowser(&browser_param);
#endif
    return 0;
}

/* vi: set ts=4 sw=4 expandtab: */

