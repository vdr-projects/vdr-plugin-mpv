//////////////////////////////////////////////////////////////////////////////
///                                                                        ///
/// This file is part of the VDR mpv plugin and licensed under AGPLv3      ///
///                                                                        ///
/// See the README file for copyright information                          ///
///                                                                        ///
//////////////////////////////////////////////////////////////////////////////

#ifndef __MPV_STATUS_H
#define __MPV_STATUS_H

#include <vdr/status.h>
#include "player.h"

class cMpvStatus:public cStatus
{
  private:
    int Volume; // current volume
    cMpvPlayer *Player;

  public:
    cMpvStatus(cMpvPlayer *player);

  protected:
    virtual void SetVolume(int volume, bool absolute); // volume changed
};

#endif

