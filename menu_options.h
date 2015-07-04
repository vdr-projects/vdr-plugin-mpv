#ifndef __MPV_MENU_OPTIONS
#define __MPV_MENU_OPTIONS

#include <string>
#include <vdr/plugin.h>
#include "player.h"

using std::string;

class cMpvMenuOptions:public cOsdMenu
{
  private:
    cMpvPlayer *player;
    void ShowOptions();

  public:
    cMpvMenuOptions(cMpvPlayer *Player);
    ~cMpvMenuOptions();
    virtual eOSState ProcessKey(eKeys Key);
};

class cMpvMenuChapters:public cOsdMenu
{
  private:
    cMpvPlayer *player;

    void AddItem(string Title, int Number);

  public:
    cMpvMenuChapters(cMpvPlayer *Player);
    virtual eOSState ProcessKey(eKeys Key);
};

class cMpvMenuChapterItem:public cOsdItem
{
  private:
    int number;

  public:
    cMpvMenuChapterItem(string Title, int Number);
    int Number() { return number; }
};

#endif

