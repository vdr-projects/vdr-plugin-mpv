#include <vector>
#include <string>
#include <algorithm>

#include "filebrowser.h"
#include "mpv_service.h"

using std::string;
using std::vector;
using std::sort;

string cMpvFilebrowser::currentDir = "";
string cMpvFilebrowser::currentItem = "";

cMpvFilebrowser::cMpvFilebrowser(string RootDir)
:cOsdMenu("Filebrowser")
{
  rootDir = RootDir;
  if (currentDir == "")
    currentDir = rootDir;
  ShowDirectory(currentDir);
}

void cMpvFilebrowser::ShowDirectory(string Path)
{
  Clear();
  vector<string> Directories;
  vector<string> Files;

  DIR *hDir;
  struct dirent *Entry;

  hDir = opendir(Path.c_str());
  while ((Entry = readdir(hDir)) != NULL)
  {
    if (!Entry || Entry->d_name[0] == '.')
      continue;

    struct stat Stat;
    string Filename = Path + "/" + Entry->d_name;
    stat(Filename.c_str(), &Stat);

    if (S_ISDIR(Stat.st_mode))
      Directories.push_back(Entry->d_name);

    else if (S_ISREG(Stat.st_mode))
      Files.push_back(Entry->d_name);
  }
  closedir(hDir);

  sort(Directories.begin(), Directories.end());
  sort(Files.begin(), Files.end());

  for (unsigned int i=0; i<Directories.size(); i++)
    AddItem(Path, Directories[i], true);

  for (unsigned int i=0; i<Files.size(); i++)
    AddItem(Path, Files[i], false);

  string MenuTitle = "Filebrowser";
  if (rootDir != Path)
    MenuTitle += " (" + Path.substr(rootDir.size() + 1, string::npos) + ")";
  SetTitle(MenuTitle.c_str());
  SetHelp(NULL, NULL, "Shuffle", NULL);
  Display();
}

void cMpvFilebrowser::AddItem(string Path, string Text, bool IsDir)
{
  bool Current = false;
  if (currentItem == Text)
    Current = true;
  Add(new cMpvFilebrowserMenuItem(Path, Text, IsDir), Current);
}

eOSState cMpvFilebrowser::ProcessKey(eKeys Key)
{
  //TODO since we get more and more Keys we should use switch again
  if (Key == kOk)
  {
    cMpvFilebrowserMenuItem *item = (cMpvFilebrowserMenuItem *) Get(Current());
    string newPath = item->Path() + "/" + item->Text();
    if (item->IsDirectory())
    {
      currentDir = newPath;
      currentItem = "";
      ShowDirectory(newPath);
      return osContinue;
    }
    else
    {
      currentItem = item->Text();
      PlayFile(newPath);
      return osEnd;
    }
  }
  else if (Key == kBack)
  {
    // we reached our root, so don't go back further and let VDR handle this (close submenu)
    if (currentDir == rootDir)
      return cOsdMenu::ProcessKey(Key);
    currentItem = currentDir.substr(currentDir.find_last_of("/")+1, string::npos);
    currentDir = currentDir.substr(0,currentDir.find_last_of("/"));
    ShowDirectory(currentDir);
    return osContinue;
  }
  else if (Key == kLeft || Key == kRight || Key == kUp || Key == kDown)
  {
    // first let VDR handle those keys or we get the previous item
    eOSState State = cOsdMenu::ProcessKey(Key);
    cMpvFilebrowserMenuItem *item = (cMpvFilebrowserMenuItem *) Get(Current());
    currentItem = item->Text();
    return State;
  }
  else if (Key == kYellow)
  {
    cMpvFilebrowserMenuItem *item = (cMpvFilebrowserMenuItem *) Get(Current());
    string newPath = item->Path() + "/" + item->Text();
    if (!item->IsDirectory())
    {
      currentItem = item->Text();
      PlayFile(newPath, true);
      return osEnd;
    }
    return osContinue;
  }

  return cOsdMenu::ProcessKey(Key);
}

bool cMpvFilebrowser::PlayFile(string Filename, bool Shuffle)
{
  cPlugin *p;
  p = cPluginManager::GetPlugin("mpv");
  if (!p)
    return false;

  if (!Shuffle)
  {
    Mpv_PlayFile playFile;
    playFile.Filename = (char *)Filename.c_str();
    return p->Service("Mpv_PlayFile", &playFile);
  }
  else
  {
    Mpv_PlaylistShuffle shuffleFile;
    shuffleFile.Filename = (char *)Filename.c_str();
    return p->Service("Mpv_PlaylistShuffle", &shuffleFile);
  }

  // should never be reached, but silence a compiler warning
  return false;
}

cMpvFilebrowserMenuItem::cMpvFilebrowserMenuItem(string Path, string Item, bool IsDir)
{
  isDir = IsDir;
  path = Path;
  SetText(Item.c_str());
}

