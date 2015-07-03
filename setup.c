//////////////////////////////////////////////////////////////////////////////
///                                                                        ///
/// This file is part of the VDR mpv plugin and licensed under AGPLv3      ///
///                                                                        ///
/// See the README file for copyright information                          ///
///                                                                        ///
//////////////////////////////////////////////////////////////////////////////

#include "setup.h"
#include "config.h"

cMpvPluginSetup::cMpvPluginSetup()
{
  SetupHideMainMenuEntry = MpvPluginConfig->HideMainMenuEntry;
  SetupUsePassthrough = MpvPluginConfig->UsePassthrough;
  SetupUseDtsHdPassthrough = MpvPluginConfig->UseDtsHdPassthrough;
  SetupPlaylistOnNextKey = MpvPluginConfig->PlaylistOnNextKey;
  SetupPlaylistIfNoChapters = MpvPluginConfig->PlaylistIfNoChapters;
  SetupStereoDownmix = MpvPluginConfig->StereoDownmix;
  SetupShowMediaTitle = MpvPluginConfig->ShowMediaTitle;
  Setup();
}

eOSState cMpvPluginSetup::ProcessKey(eKeys key)
{
  int oldUsePassthrough = SetupUsePassthrough;
  int oldPlaylistOnNextKey = SetupPlaylistOnNextKey;
  eOSState state = cMenuSetupPage::ProcessKey(key);

  if (key != kNone && (SetupUsePassthrough != oldUsePassthrough || SetupPlaylistOnNextKey != oldPlaylistOnNextKey))
    Setup();

  return state;
}

void cMpvPluginSetup::Setup()
{
  int current = Current();
  Clear();

  Add(new cMenuEditBoolItem(tr("Hide main menu entry"), &SetupHideMainMenuEntry, trVDR("no"), trVDR("yes")));
  Add(new cMenuEditBoolItem(tr("Audio Passthrough"), &SetupUsePassthrough));
  if (SetupUsePassthrough)
    Add(new cMenuEditBoolItem(tr("DTS-HD Passthrough"), &SetupUseDtsHdPassthrough));
  else
    Add(new cMenuEditBoolItem(tr("Enable stereo downmix"), &SetupStereoDownmix));
  Add(new cMenuEditBoolItem(tr("Use prev/next keys for playlist control"), &SetupPlaylistOnNextKey));
  if (!SetupPlaylistOnNextKey)
    Add(new cMenuEditBoolItem(tr("Control playlist if no chapters in file"), &SetupPlaylistIfNoChapters));
  Add(new cMenuEditBoolItem(tr("Show media title instead of filename"), &SetupShowMediaTitle));
  SetCurrent(Get(current));
  Display();
}

void cMpvPluginSetup::Store()
{
    SetupStore("HideMainMenuEntry", MpvPluginConfig->HideMainMenuEntry = SetupHideMainMenuEntry);
    SetupStore("UsePassthrough", MpvPluginConfig->UsePassthrough = SetupUsePassthrough);
    SetupStore("UseDtsHdPassthrough", MpvPluginConfig->UseDtsHdPassthrough = SetupUseDtsHdPassthrough);
    SetupStore("StereoDownmix", MpvPluginConfig->StereoDownmix = SetupStereoDownmix);
    SetupStore("PlaylistOnNextKey", MpvPluginConfig->PlaylistOnNextKey = SetupPlaylistOnNextKey);
    SetupStore("PlaylistIfNoChapters", MpvPluginConfig->PlaylistIfNoChapters = SetupPlaylistIfNoChapters);
    SetupStore("ShowMediaTitle", MpvPluginConfig->ShowMediaTitle = SetupShowMediaTitle);
}

