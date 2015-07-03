//////////////////////////////////////////////////////////////////////////////
///                                                                        ///
/// This file is part of the VDR mpv plugin and licensed under AGPLv3      ///
///                                                                        ///
/// See the README file for copyright information                          ///
///                                                                        ///
//////////////////////////////////////////////////////////////////////////////

#include "status.h"

cMpvStatus::cMpvStatus(cMpvPlayer *player)
{
  Volume = cDevice::CurrentVolume();
  Player = player;
}

void cMpvStatus::SetVolume(int volume, bool absolute)
{
  if (absolute)
    Volume = volume;
  else
    Volume += volume;

  Player->SetVolume(Volume/2.55);
}
