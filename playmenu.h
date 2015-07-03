//////////////////////////////////////////////////////////////////////////////
///                                                                        ///
/// This file is part of the VDR mpv plugin and licensed under AGPLv3      ///
///                                                                        ///
/// See the README file for copyright information                          ///
///                                                                        ///
//////////////////////////////////////////////////////////////////////////////

#ifndef __MPV_BROWSER_H
#define __MPV_BROWSER_H

#include <vdr/plugin.h>

class cPlayMenu:public cOsdMenu
{
  private:
  public:
    cPlayMenu(const char *, int = 0, int = 0, int = 0, int = 0, int = 0);
    virtual ~ cPlayMenu();
    virtual eOSState ProcessKey(eKeys);
    int PlayFile(const char *Filename);
};

#endif

