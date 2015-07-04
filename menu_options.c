#include "menu_options.h"

cMpvMenuOptions::cMpvMenuOptions(cMpvPlayer *Player)
:cOsdMenu(tr("Options"))
{
  SetDisplayMenu();
  player = Player;
  ShowOptions();
  Show();
  Display();
}

cMpvMenuOptions::~cMpvMenuOptions()
{
  dsyslog ("dekonstruktor\n");
}

void cMpvMenuOptions::ShowOptions()
{
  // display chapter select menu if the file has named named chapters
  if (player->NumChapters() && player->ChapterTitle(1) != "")
    Add(new cOsdItem(tr("Show chapters"), osUser1));

  // TODO if we are currently on a playlist display playlist menu
  
}

eOSState cMpvMenuOptions::ProcessKey(eKeys Key)
{
  eOSState State = cOsdMenu::ProcessKey(Key);

  if (!HasSubMenu())
  {
    switch (Key)
    {
      case kOk:
        AddSubMenu(new cMpvMenuChapters(player));
      break;

      default:
      break;
    }
  }

  return State;
}

cMpvMenuChapters::cMpvMenuChapters(cMpvPlayer *Player)
:cOsdMenu(tr("Chapters"))
{
  player = Player;
  for (int i=1; i<=player->NumChapters(); i++)
    AddItem(player->ChapterTitle(i), i);

  Display();
}

eOSState cMpvMenuChapters::ProcessKey(eKeys Key)
{
  eOSState State = cOsdMenu::ProcessKey(Key);
  if (State == osUnknown)
  {
    switch (Key)
    {
      case kOk:
        cMpvMenuChapterItem *item = (cMpvMenuChapterItem *) Get(Current());
        player->SetChapter(item->Number());
      return osEnd;
    }
  }

  return State;
}

void cMpvMenuChapters::AddItem(string Title, int Number)
{
  bool Current = false;
  if (player->ChapterTitle(player->CurrentChapter()) == Title)
    Current = true;
  Add(new cMpvMenuChapterItem(Title, Number), Current);
}

cMpvMenuChapterItem::cMpvMenuChapterItem(string Title, int Number)
{
  // TODO add number in front
  number = Number;
  SetText(Title.c_str());
}

