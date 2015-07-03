//////////////////////////////////////////////////////////////////////////////
///                                                                        ///
/// This file is part of the VDR mpv plugin and licensed under AGPLv3      ///
///                                                                        ///
/// See the README file for copyright information                          ///
///                                                                        ///
//////////////////////////////////////////////////////////////////////////////

#include "playmenu.h"
#include "config.h"
#include "mpv_service.h"
#include "filebrowser.h"

//////////////////////////////////////////////////////////////////////////////
// cOsdMenu
//////////////////////////////////////////////////////////////////////////////

cPlayMenu::cPlayMenu(const char *title, int c0, int c1, int c2, int c3, int c4)
:cOsdMenu(title, c0, c1, c2, c3, c4)
{
  SetHasHotkeys();

  Add(new cOsdItem(hk(tr("Browse")), osUser1));
  Add(new cOsdItem(hk(tr("Play optical disc")), osUser2));
  Add(new cOsdItem(""));
  Add(new cOsdItem(""));
  Add(new cOsdItem(hk(tr("Play audio CD")), osUser5));
  Add(new cOsdItem(hk(tr("Play video DVD")), osUser6));

  if (cMpvFilebrowser::CurrentDir() != "")
  {
    AddSubMenu(new cMpvFilebrowser(MpvPluginConfig->BrowserRoot.c_str()));
  }
}

cPlayMenu::~cPlayMenu()
{
}

/**
** Handle play plugin menu key event.
**
** @param key  key event
*/
eOSState cPlayMenu::ProcessKey(eKeys key)
{
  eOSState state;

  // call standard function
  state = cOsdMenu::ProcessKey(key);

  switch (state)
  {
    case osUser1:
      AddSubMenu(new cMpvFilebrowser(MpvPluginConfig->BrowserRoot.c_str()));
      return osContinue; // restart with OSD browser

    case osUser2:
      Skins.Message(mtStatus,
      tr("Function not working yet, use 3 or 4"));
      return osContinue;

    case osUser5: // play audio cdrom
      PlayFile("cdda://");
      return osEnd;

    case osUser6: // play dvd
      PlayFile("dvdnav://menu");
      return osEnd;

    default:
      break;
  }
  return state;
}

int cPlayMenu::PlayFile(const char *Filename)
{
  cPlugin *p;
  p = cPluginManager::GetPlugin("mpv");
  if (p)
  {
    Mpv_StartPlayService_v1_0_t r;
      r.Filename = (char *)Filename;

    return p->Service("Mpv-StartPlayService_v1_0", &r);
  }

  return false;
}


