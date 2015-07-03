#ifndef __MPV_FILEBROWSER
#define __MPV_FILEBROWSER

#include <string>
#include <vdr/plugin.h>

using std::string;

class cMpvFilebrowser:public cOsdMenu
{
  private:
    string rootDir;
    static string currentDir;
    static string currentItem;

    void ShowDirectory(string Path);
    void AddItem(string Path, string Text, bool IsDir);
    bool PlayFile(string Filename, bool Shuffle=false);

  public:
    cMpvFilebrowser(string RootDir);
    virtual eOSState ProcessKey(eKeys Key);
    static string CurrentDir() { return currentDir; }
};

class cMpvFilebrowserMenuItem:public cOsdItem
{
  private:
    string path;
    bool isDir;

  public:
    cMpvFilebrowserMenuItem(string Path, string Item, bool IsDir);
    string Path() { return path; }
    bool IsDirectory() { return isDir; }
};

#endif

