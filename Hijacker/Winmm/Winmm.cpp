#ifdef WINMM

#include "Winmm.h"

#include <tchar.h>

void Hijacker::Hijack(LPCTSTR lpSrc)
{
    Core::Hijack(_T("winmm.dll"), lpSrc);

    RESOLVE(CloseDriver);
    RESOLVE(DefDriverProc);
    RESOLVE(DriverCallback);
    RESOLVE(DrvGetModuleHandle);
    RESOLVE(GetDriverModuleHandle);
    RESOLVE(OpenDriver);
    RESOLVE(PlaySound);
    RESOLVE(PlaySoundA);
    RESOLVE(PlaySoundW);
    RESOLVE(SendDriverMessage);
    RESOLVE(WOWAppExit);
    RESOLVE(auxGetDevCapsA);
    RESOLVE(auxGetDevCapsW);
    RESOLVE(auxGetNumDevs);
    RESOLVE(auxGetVolume);
    RESOLVE(auxOutMessage);
    RESOLVE(auxSetVolume);
    RESOLVE(joyConfigChanged);
    RESOLVE(joyGetDevCapsA);
    RESOLVE(joyGetDevCapsW);
    RESOLVE(joyGetNumDevs);
    RESOLVE(joyGetPos);
    RESOLVE(joyGetPosEx);
    RESOLVE(joyGetThreshold);
    RESOLVE(joyReleaseCapture);
    RESOLVE(joySetCapture);
    RESOLVE(joySetThreshold);
    RESOLVE(mciDriverNotify);
    RESOLVE(mciDriverYield);
    RESOLVE(mciExecute);
    RESOLVE(mciFreeCommandResource);
    RESOLVE(mciGetCreatorTask);
    RESOLVE(mciGetDeviceIDA);
    RESOLVE(mciGetDeviceIDFromElementIDA);
    RESOLVE(mciGetDeviceIDFromElementIDW);
    RESOLVE(mciGetDeviceIDW);
    RESOLVE(mciGetDriverData);
    RESOLVE(mciGetErrorStringA);
    RESOLVE(mciGetErrorStringW);
    RESOLVE(mciGetYieldProc);
    RESOLVE(mciLoadCommandResource);
    RESOLVE(mciSendCommandA);
    RESOLVE(mciSendCommandW);
    RESOLVE(mciSendStringA);
    RESOLVE(mciSendStringW);
    RESOLVE(mciSetDriverData);
    RESOLVE(mciSetYieldProc);
    RESOLVE(midiConnect);
    RESOLVE(midiDisconnect);
    RESOLVE(midiInAddBuffer);
    RESOLVE(midiInClose);
    RESOLVE(midiInGetDevCapsA);
    RESOLVE(midiInGetDevCapsW);
    RESOLVE(midiInGetErrorTextA);
    RESOLVE(midiInGetErrorTextW);
    RESOLVE(midiInGetID);
    RESOLVE(midiInGetNumDevs);
    RESOLVE(midiInMessage);
    RESOLVE(midiInOpen);
    RESOLVE(midiInPrepareHeader);
    RESOLVE(midiInReset);
    RESOLVE(midiInStart);
    RESOLVE(midiInStop);
    RESOLVE(midiInUnprepareHeader);
    RESOLVE(midiOutCacheDrumPatches);
    RESOLVE(midiOutCachePatches);
    RESOLVE(midiOutClose);
    RESOLVE(midiOutGetDevCapsA);
    RESOLVE(midiOutGetDevCapsW);
    RESOLVE(midiOutGetErrorTextA);
    RESOLVE(midiOutGetErrorTextW);
    RESOLVE(midiOutGetID);
    RESOLVE(midiOutGetNumDevs);
    RESOLVE(midiOutGetVolume);
    RESOLVE(midiOutLongMsg);
    RESOLVE(midiOutMessage);
    RESOLVE(midiOutOpen);
    RESOLVE(midiOutPrepareHeader);
    RESOLVE(midiOutReset);
    RESOLVE(midiOutSetVolume);
    RESOLVE(midiOutShortMsg);
    RESOLVE(midiOutUnprepareHeader);
    RESOLVE(midiStreamClose);
    RESOLVE(midiStreamOpen);
    RESOLVE(midiStreamOut);
    RESOLVE(midiStreamPause);
    RESOLVE(midiStreamPosition);
    RESOLVE(midiStreamProperty);
    RESOLVE(midiStreamRestart);
    RESOLVE(midiStreamStop);
    RESOLVE(mixerClose);
    RESOLVE(mixerGetControlDetailsA);
    RESOLVE(mixerGetControlDetailsW);
    RESOLVE(mixerGetDevCapsA);
    RESOLVE(mixerGetDevCapsW);
    RESOLVE(mixerGetID);
    RESOLVE(mixerGetLineControlsA);
    RESOLVE(mixerGetLineControlsW);
    RESOLVE(mixerGetLineInfoA);
    RESOLVE(mixerGetLineInfoW);
    RESOLVE(mixerGetNumDevs);
    RESOLVE(mixerMessage);
    RESOLVE(mixerOpen);
    RESOLVE(mixerSetControlDetails);
    RESOLVE(mmDrvInstall);
    RESOLVE(mmGetCurrentTask);
    RESOLVE(mmTaskBlock);
    RESOLVE(mmTaskCreate);
    RESOLVE(mmTaskSignal);
    RESOLVE(mmTaskYield);
    RESOLVE(mmioAdvance);
    RESOLVE(mmioAscend);
    RESOLVE(mmioClose);
    RESOLVE(mmioCreateChunk);
    RESOLVE(mmioDescend);
    RESOLVE(mmioFlush);
    RESOLVE(mmioGetInfo);
    RESOLVE(mmioInstallIOProcA);
    RESOLVE(mmioInstallIOProcW);
    RESOLVE(mmioOpenA);
    RESOLVE(mmioOpenW);
    RESOLVE(mmioRead);
    RESOLVE(mmioRenameA);
    RESOLVE(mmioRenameW);
    RESOLVE(mmioSeek);
    RESOLVE(mmioSendMessage);
    RESOLVE(mmioSetBuffer);
    RESOLVE(mmioSetInfo);
    RESOLVE(mmioStringToFOURCCA);
    RESOLVE(mmioStringToFOURCCW);
    RESOLVE(mmioWrite);
    RESOLVE(mmsystemGetVersion);
    RESOLVE(sndPlaySoundA);
    RESOLVE(sndPlaySoundW);
    RESOLVE(timeBeginPeriod);
    RESOLVE(timeEndPeriod);
    RESOLVE(timeGetDevCaps);
    RESOLVE(timeGetSystemTime);
    RESOLVE(timeGetTime);
    RESOLVE(timeKillEvent);
    RESOLVE(timeSetEvent);
    RESOLVE(waveInAddBuffer);
    RESOLVE(waveInClose);
    RESOLVE(waveInGetDevCapsA);
    RESOLVE(waveInGetDevCapsW);
    RESOLVE(waveInGetErrorTextA);
    RESOLVE(waveInGetErrorTextW);
    RESOLVE(waveInGetID);
    RESOLVE(waveInGetNumDevs);
    RESOLVE(waveInGetPosition);
    RESOLVE(waveInMessage);
    RESOLVE(waveInOpen);
    RESOLVE(waveInPrepareHeader);
    RESOLVE(waveInReset);
    RESOLVE(waveInStart);
    RESOLVE(waveInStop);
    RESOLVE(waveInUnprepareHeader);
    RESOLVE(waveOutBreakLoop);
    RESOLVE(waveOutClose);
    RESOLVE(waveOutGetDevCapsA);
    RESOLVE(waveOutGetDevCapsW);
    RESOLVE(waveOutGetErrorTextA);
    RESOLVE(waveOutGetErrorTextW);
    RESOLVE(waveOutGetID);
    RESOLVE(waveOutGetNumDevs);
    RESOLVE(waveOutGetPitch);
    RESOLVE(waveOutGetPlaybackRate);
    RESOLVE(waveOutGetPosition);
    RESOLVE(waveOutGetVolume);
    RESOLVE(waveOutMessage);
    RESOLVE(waveOutOpen);
    RESOLVE(waveOutPause);
    RESOLVE(waveOutPrepareHeader);
    RESOLVE(waveOutReset);
    RESOLVE(waveOutRestart);
    RESOLVE(waveOutSetPitch);
    RESOLVE(waveOutSetPlaybackRate);
    RESOLVE(waveOutSetVolume);
    RESOLVE(waveOutUnprepareHeader);
    RESOLVE(waveOutWrite);
}

void Hijacker::Release()
{
    Core::Release();
}

EXTERN_C __declspec(naked) void FakeCloseDriver()                   { __asm { jmp[Hijacker::OriginalCloseDriver] } }
EXTERN_C __declspec(naked) void FakeDefDriverProc()                 { __asm { jmp[Hijacker::OriginalDefDriverProc] } }
EXTERN_C __declspec(naked) void FakeDriverCallback()                { __asm { jmp[Hijacker::OriginalDriverCallback] } }
EXTERN_C __declspec(naked) void FakeDrvGetModuleHandle()            { __asm { jmp[Hijacker::OriginalDrvGetModuleHandle] } }
EXTERN_C __declspec(naked) void FakeGetDriverModuleHandle()         { __asm { jmp[Hijacker::OriginalGetDriverModuleHandle] } }
EXTERN_C __declspec(naked) void FakeOpenDriver()                    { __asm { jmp[Hijacker::OriginalOpenDriver] } }
EXTERN_C __declspec(naked) void FakePlaySound()                     { __asm { jmp[Hijacker::OriginalPlaySound] } }
EXTERN_C __declspec(naked) void FakePlaySoundA()                    { __asm { jmp[Hijacker::OriginalPlaySoundA] } }
EXTERN_C __declspec(naked) void FakePlaySoundW()                    { __asm { jmp[Hijacker::OriginalPlaySoundW] } }
EXTERN_C __declspec(naked) void FakeSendDriverMessage()             { __asm { jmp[Hijacker::OriginalSendDriverMessage] } }
EXTERN_C __declspec(naked) void FakeWOWAppExit()                    { __asm { jmp[Hijacker::OriginalWOWAppExit] } }
EXTERN_C __declspec(naked) void FakeauxGetDevCapsA()                { __asm { jmp[Hijacker::OriginalauxGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakeauxGetDevCapsW()                { __asm { jmp[Hijacker::OriginalauxGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakeauxGetNumDevs()                 { __asm { jmp[Hijacker::OriginalauxGetNumDevs] } }
EXTERN_C __declspec(naked) void FakeauxGetVolume()                  { __asm { jmp[Hijacker::OriginalauxGetVolume] } }
EXTERN_C __declspec(naked) void FakeauxOutMessage()                 { __asm { jmp[Hijacker::OriginalauxOutMessage] } }
EXTERN_C __declspec(naked) void FakeauxSetVolume()                  { __asm { jmp[Hijacker::OriginalauxSetVolume] } }
EXTERN_C __declspec(naked) void FakejoyConfigChanged()              { __asm { jmp[Hijacker::OriginaljoyConfigChanged] } }
EXTERN_C __declspec(naked) void FakejoyGetDevCapsA()                { __asm { jmp[Hijacker::OriginaljoyGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakejoyGetDevCapsW()                { __asm { jmp[Hijacker::OriginaljoyGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakejoyGetNumDevs()                 { __asm { jmp[Hijacker::OriginaljoyGetNumDevs] } }
EXTERN_C __declspec(naked) void FakejoyGetPos()                     { __asm { jmp[Hijacker::OriginaljoyGetPos] } }
EXTERN_C __declspec(naked) void FakejoyGetPosEx()                   { __asm { jmp[Hijacker::OriginaljoyGetPosEx] } }
EXTERN_C __declspec(naked) void FakejoyGetThreshold()               { __asm { jmp[Hijacker::OriginaljoyGetThreshold] } }
EXTERN_C __declspec(naked) void FakejoyReleaseCapture()             { __asm { jmp[Hijacker::OriginaljoyReleaseCapture] } }
EXTERN_C __declspec(naked) void FakejoySetCapture()                 { __asm { jmp[Hijacker::OriginaljoySetCapture] } }
EXTERN_C __declspec(naked) void FakejoySetThreshold()               { __asm { jmp[Hijacker::OriginaljoySetThreshold] } }
EXTERN_C __declspec(naked) void FakemciDriverNotify()               { __asm { jmp[Hijacker::OriginalmciDriverNotify] } }
EXTERN_C __declspec(naked) void FakemciDriverYield()                { __asm { jmp[Hijacker::OriginalmciDriverYield] } }
EXTERN_C __declspec(naked) void FakemciExecute()                    { __asm { jmp[Hijacker::OriginalmciExecute] } }
EXTERN_C __declspec(naked) void FakemciFreeCommandResource()        { __asm { jmp[Hijacker::OriginalmciFreeCommandResource] } }
EXTERN_C __declspec(naked) void FakemciGetCreatorTask()             { __asm { jmp[Hijacker::OriginalmciGetCreatorTask] } }
EXTERN_C __declspec(naked) void FakemciGetDeviceIDA()               { __asm { jmp[Hijacker::OriginalmciGetDeviceIDA] } }
EXTERN_C __declspec(naked) void FakemciGetDeviceIDFromElementIDA()  { __asm { jmp[Hijacker::OriginalmciGetDeviceIDFromElementIDA] } }
EXTERN_C __declspec(naked) void FakemciGetDeviceIDFromElementIDW()  { __asm { jmp[Hijacker::OriginalmciGetDeviceIDFromElementIDW] } }
EXTERN_C __declspec(naked) void FakemciGetDeviceIDW()               { __asm { jmp[Hijacker::OriginalmciGetDeviceIDW] } }
EXTERN_C __declspec(naked) void FakemciGetDriverData()              { __asm { jmp[Hijacker::OriginalmciGetDriverData] } }
EXTERN_C __declspec(naked) void FakemciGetErrorStringA()            { __asm { jmp[Hijacker::OriginalmciGetErrorStringA] } }
EXTERN_C __declspec(naked) void FakemciGetErrorStringW()            { __asm { jmp[Hijacker::OriginalmciGetErrorStringW] } }
EXTERN_C __declspec(naked) void FakemciGetYieldProc()               { __asm { jmp[Hijacker::OriginalmciGetYieldProc] } }
EXTERN_C __declspec(naked) void FakemciLoadCommandResource()        { __asm { jmp[Hijacker::OriginalmciLoadCommandResource] } }
EXTERN_C __declspec(naked) void FakemciSendCommandA()               { __asm { jmp[Hijacker::OriginalmciSendCommandA] } }
EXTERN_C __declspec(naked) void FakemciSendCommandW()               { __asm { jmp[Hijacker::OriginalmciSendCommandW] } }
EXTERN_C __declspec(naked) void FakemciSendStringA()                { __asm { jmp[Hijacker::OriginalmciSendStringA] } }
EXTERN_C __declspec(naked) void FakemciSendStringW()                { __asm { jmp[Hijacker::OriginalmciSendStringW] } }
EXTERN_C __declspec(naked) void FakemciSetDriverData()              { __asm { jmp[Hijacker::OriginalmciSetDriverData] } }
EXTERN_C __declspec(naked) void FakemciSetYieldProc()               { __asm { jmp[Hijacker::OriginalmciSetYieldProc] } }
EXTERN_C __declspec(naked) void FakemidiConnect()                   { __asm { jmp[Hijacker::OriginalmidiConnect] } }
EXTERN_C __declspec(naked) void FakemidiDisconnect()                { __asm { jmp[Hijacker::OriginalmidiDisconnect] } }
EXTERN_C __declspec(naked) void FakemidiInAddBuffer()               { __asm { jmp[Hijacker::OriginalmidiInAddBuffer] } }
EXTERN_C __declspec(naked) void FakemidiInClose()                   { __asm { jmp[Hijacker::OriginalmidiInClose] } }
EXTERN_C __declspec(naked) void FakemidiInGetDevCapsA()             { __asm { jmp[Hijacker::OriginalmidiInGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakemidiInGetDevCapsW()             { __asm { jmp[Hijacker::OriginalmidiInGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakemidiInGetErrorTextA()           { __asm { jmp[Hijacker::OriginalmidiInGetErrorTextA] } }
EXTERN_C __declspec(naked) void FakemidiInGetErrorTextW()           { __asm { jmp[Hijacker::OriginalmidiInGetErrorTextW] } }
EXTERN_C __declspec(naked) void FakemidiInGetID()                   { __asm { jmp[Hijacker::OriginalmidiInGetID] } }
EXTERN_C __declspec(naked) void FakemidiInGetNumDevs()              { __asm { jmp[Hijacker::OriginalmidiInGetNumDevs] } }
EXTERN_C __declspec(naked) void FakemidiInMessage()                 { __asm { jmp[Hijacker::OriginalmidiInMessage] } }
EXTERN_C __declspec(naked) void FakemidiInOpen()                    { __asm { jmp[Hijacker::OriginalmidiInOpen] } }
EXTERN_C __declspec(naked) void FakemidiInPrepareHeader()           { __asm { jmp[Hijacker::OriginalmidiInPrepareHeader] } }
EXTERN_C __declspec(naked) void FakemidiInReset()                   { __asm { jmp[Hijacker::OriginalmidiInReset] } }
EXTERN_C __declspec(naked) void FakemidiInStart()                   { __asm { jmp[Hijacker::OriginalmidiInStart] } }
EXTERN_C __declspec(naked) void FakemidiInStop()                    { __asm { jmp[Hijacker::OriginalmidiInStop] } }
EXTERN_C __declspec(naked) void FakemidiInUnprepareHeader()         { __asm { jmp[Hijacker::OriginalmidiInUnprepareHeader] } }
EXTERN_C __declspec(naked) void FakemidiOutCacheDrumPatches()       { __asm { jmp[Hijacker::OriginalmidiOutCacheDrumPatches] } }
EXTERN_C __declspec(naked) void FakemidiOutCachePatches()           { __asm { jmp[Hijacker::OriginalmidiOutCachePatches] } }
EXTERN_C __declspec(naked) void FakemidiOutClose()                  { __asm { jmp[Hijacker::OriginalmidiOutClose] } }
EXTERN_C __declspec(naked) void FakemidiOutGetDevCapsA()            { __asm { jmp[Hijacker::OriginalmidiOutGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakemidiOutGetDevCapsW()            { __asm { jmp[Hijacker::OriginalmidiOutGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakemidiOutGetErrorTextA()          { __asm { jmp[Hijacker::OriginalmidiOutGetErrorTextA] } }
EXTERN_C __declspec(naked) void FakemidiOutGetErrorTextW()          { __asm { jmp[Hijacker::OriginalmidiOutGetErrorTextW] } }
EXTERN_C __declspec(naked) void FakemidiOutGetID()                  { __asm { jmp[Hijacker::OriginalmidiOutGetID] } }
EXTERN_C __declspec(naked) void FakemidiOutGetNumDevs()             { __asm { jmp[Hijacker::OriginalmidiOutGetNumDevs] } }
EXTERN_C __declspec(naked) void FakemidiOutGetVolume()              { __asm { jmp[Hijacker::OriginalmidiOutGetVolume] } }
EXTERN_C __declspec(naked) void FakemidiOutLongMsg()                { __asm { jmp[Hijacker::OriginalmidiOutLongMsg] } }
EXTERN_C __declspec(naked) void FakemidiOutMessage()                { __asm { jmp[Hijacker::OriginalmidiOutMessage] } }
EXTERN_C __declspec(naked) void FakemidiOutOpen()                   { __asm { jmp[Hijacker::OriginalmidiOutOpen] } }
EXTERN_C __declspec(naked) void FakemidiOutPrepareHeader()          { __asm { jmp[Hijacker::OriginalmidiOutPrepareHeader] } }
EXTERN_C __declspec(naked) void FakemidiOutReset()                  { __asm { jmp[Hijacker::OriginalmidiOutReset] } }
EXTERN_C __declspec(naked) void FakemidiOutSetVolume()              { __asm { jmp[Hijacker::OriginalmidiOutSetVolume] } }
EXTERN_C __declspec(naked) void FakemidiOutShortMsg()               { __asm { jmp[Hijacker::OriginalmidiOutShortMsg] } }
EXTERN_C __declspec(naked) void FakemidiOutUnprepareHeader()        { __asm { jmp[Hijacker::OriginalmidiOutUnprepareHeader] } }
EXTERN_C __declspec(naked) void FakemidiStreamClose()               { __asm { jmp[Hijacker::OriginalmidiStreamClose] } }
EXTERN_C __declspec(naked) void FakemidiStreamOpen()                { __asm { jmp[Hijacker::OriginalmidiStreamOpen] } }
EXTERN_C __declspec(naked) void FakemidiStreamOut()                 { __asm { jmp[Hijacker::OriginalmidiStreamOut] } }
EXTERN_C __declspec(naked) void FakemidiStreamPause()               { __asm { jmp[Hijacker::OriginalmidiStreamPause] } }
EXTERN_C __declspec(naked) void FakemidiStreamPosition()            { __asm { jmp[Hijacker::OriginalmidiStreamPosition] } }
EXTERN_C __declspec(naked) void FakemidiStreamProperty()            { __asm { jmp[Hijacker::OriginalmidiStreamProperty] } }
EXTERN_C __declspec(naked) void FakemidiStreamRestart()             { __asm { jmp[Hijacker::OriginalmidiStreamRestart] } }
EXTERN_C __declspec(naked) void FakemidiStreamStop()                { __asm { jmp[Hijacker::OriginalmidiStreamStop] } }
EXTERN_C __declspec(naked) void FakemixerClose()                    { __asm { jmp[Hijacker::OriginalmixerClose] } }
EXTERN_C __declspec(naked) void FakemixerGetControlDetailsA()       { __asm { jmp[Hijacker::OriginalmixerGetControlDetailsA] } }
EXTERN_C __declspec(naked) void FakemixerGetControlDetailsW()       { __asm { jmp[Hijacker::OriginalmixerGetControlDetailsW] } }
EXTERN_C __declspec(naked) void FakemixerGetDevCapsA()              { __asm { jmp[Hijacker::OriginalmixerGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakemixerGetDevCapsW()              { __asm { jmp[Hijacker::OriginalmixerGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakemixerGetID()                    { __asm { jmp[Hijacker::OriginalmixerGetID] } }
EXTERN_C __declspec(naked) void FakemixerGetLineControlsA()         { __asm { jmp[Hijacker::OriginalmixerGetLineControlsA] } }
EXTERN_C __declspec(naked) void FakemixerGetLineControlsW()         { __asm { jmp[Hijacker::OriginalmixerGetLineControlsW] } }
EXTERN_C __declspec(naked) void FakemixerGetLineInfoA()             { __asm { jmp[Hijacker::OriginalmixerGetLineInfoA] } }
EXTERN_C __declspec(naked) void FakemixerGetLineInfoW()             { __asm { jmp[Hijacker::OriginalmixerGetLineInfoW] } }
EXTERN_C __declspec(naked) void FakemixerGetNumDevs()               { __asm { jmp[Hijacker::OriginalmixerGetNumDevs] } }
EXTERN_C __declspec(naked) void FakemixerMessage()                  { __asm { jmp[Hijacker::OriginalmixerMessage] } }
EXTERN_C __declspec(naked) void FakemixerOpen()                     { __asm { jmp[Hijacker::OriginalmixerOpen] } }
EXTERN_C __declspec(naked) void FakemixerSetControlDetails()        { __asm { jmp[Hijacker::OriginalmixerSetControlDetails] } }
EXTERN_C __declspec(naked) void FakemmDrvInstall()                  { __asm { jmp[Hijacker::OriginalmmDrvInstall] } }
EXTERN_C __declspec(naked) void FakemmGetCurrentTask()              { __asm { jmp[Hijacker::OriginalmmGetCurrentTask] } }
EXTERN_C __declspec(naked) void FakemmTaskBlock()                   { __asm { jmp[Hijacker::OriginalmmTaskBlock] } }
EXTERN_C __declspec(naked) void FakemmTaskCreate()                  { __asm { jmp[Hijacker::OriginalmmTaskCreate] } }
EXTERN_C __declspec(naked) void FakemmTaskSignal()                  { __asm { jmp[Hijacker::OriginalmmTaskSignal] } }
EXTERN_C __declspec(naked) void FakemmTaskYield()                   { __asm { jmp[Hijacker::OriginalmmTaskYield] } }
EXTERN_C __declspec(naked) void FakemmioAdvance()                   { __asm { jmp[Hijacker::OriginalmmioAdvance] } }
EXTERN_C __declspec(naked) void FakemmioAscend()                    { __asm { jmp[Hijacker::OriginalmmioAscend] } }
EXTERN_C __declspec(naked) void FakemmioClose()                     { __asm { jmp[Hijacker::OriginalmmioClose] } }
EXTERN_C __declspec(naked) void FakemmioCreateChunk()               { __asm { jmp[Hijacker::OriginalmmioCreateChunk] } }
EXTERN_C __declspec(naked) void FakemmioDescend()                   { __asm { jmp[Hijacker::OriginalmmioDescend] } }
EXTERN_C __declspec(naked) void FakemmioFlush()                     { __asm { jmp[Hijacker::OriginalmmioFlush] } }
EXTERN_C __declspec(naked) void FakemmioGetInfo()                   { __asm { jmp[Hijacker::OriginalmmioGetInfo] } }
EXTERN_C __declspec(naked) void FakemmioInstallIOProcA()            { __asm { jmp[Hijacker::OriginalmmioInstallIOProcA] } }
EXTERN_C __declspec(naked) void FakemmioInstallIOProcW()            { __asm { jmp[Hijacker::OriginalmmioInstallIOProcW] } }
EXTERN_C __declspec(naked) void FakemmioOpenA()                     { __asm { jmp[Hijacker::OriginalmmioOpenA] } }
EXTERN_C __declspec(naked) void FakemmioOpenW()                     { __asm { jmp[Hijacker::OriginalmmioOpenW] } }
EXTERN_C __declspec(naked) void FakemmioRead()                      { __asm { jmp[Hijacker::OriginalmmioRead] } }
EXTERN_C __declspec(naked) void FakemmioRenameA()                   { __asm { jmp[Hijacker::OriginalmmioRenameA] } }
EXTERN_C __declspec(naked) void FakemmioRenameW()                   { __asm { jmp[Hijacker::OriginalmmioRenameW] } }
EXTERN_C __declspec(naked) void FakemmioSeek()                      { __asm { jmp[Hijacker::OriginalmmioSeek] } }
EXTERN_C __declspec(naked) void FakemmioSendMessage()               { __asm { jmp[Hijacker::OriginalmmioSendMessage] } }
EXTERN_C __declspec(naked) void FakemmioSetBuffer()                 { __asm { jmp[Hijacker::OriginalmmioSetBuffer] } }
EXTERN_C __declspec(naked) void FakemmioSetInfo()                   { __asm { jmp[Hijacker::OriginalmmioSetInfo] } }
EXTERN_C __declspec(naked) void FakemmioStringToFOURCCA()           { __asm { jmp[Hijacker::OriginalmmioStringToFOURCCA] } }
EXTERN_C __declspec(naked) void FakemmioStringToFOURCCW()           { __asm { jmp[Hijacker::OriginalmmioStringToFOURCCW] } }
EXTERN_C __declspec(naked) void FakemmioWrite()                     { __asm { jmp[Hijacker::OriginalmmioWrite] } }
EXTERN_C __declspec(naked) void FakemmsystemGetVersion()            { __asm { jmp[Hijacker::OriginalmmsystemGetVersion] } }
EXTERN_C __declspec(naked) void FakesndPlaySoundA()                 { __asm { jmp[Hijacker::OriginalsndPlaySoundA] } }
EXTERN_C __declspec(naked) void FakesndPlaySoundW()                 { __asm { jmp[Hijacker::OriginalsndPlaySoundW] } }
EXTERN_C __declspec(naked) void FaketimeBeginPeriod()               { __asm { jmp[Hijacker::OriginaltimeBeginPeriod] } }
EXTERN_C __declspec(naked) void FaketimeEndPeriod()                 { __asm { jmp[Hijacker::OriginaltimeEndPeriod] } }
EXTERN_C __declspec(naked) void FaketimeGetDevCaps()                { __asm { jmp[Hijacker::OriginaltimeGetDevCaps] } }
EXTERN_C __declspec(naked) void FaketimeGetSystemTime()             { __asm { jmp[Hijacker::OriginaltimeGetSystemTime] } }
EXTERN_C __declspec(naked) void FaketimeGetTime()                   { __asm { jmp[Hijacker::OriginaltimeGetTime] } }
EXTERN_C __declspec(naked) void FaketimeKillEvent()                 { __asm { jmp[Hijacker::OriginaltimeKillEvent] } }
EXTERN_C __declspec(naked) void FaketimeSetEvent()                  { __asm { jmp[Hijacker::OriginaltimeSetEvent] } }
EXTERN_C __declspec(naked) void FakewaveInAddBuffer()               { __asm { jmp[Hijacker::OriginalwaveInAddBuffer] } }
EXTERN_C __declspec(naked) void FakewaveInClose()                   { __asm { jmp[Hijacker::OriginalwaveInClose] } }
EXTERN_C __declspec(naked) void FakewaveInGetDevCapsA()             { __asm { jmp[Hijacker::OriginalwaveInGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakewaveInGetDevCapsW()             { __asm { jmp[Hijacker::OriginalwaveInGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakewaveInGetErrorTextA()           { __asm { jmp[Hijacker::OriginalwaveInGetErrorTextA] } }
EXTERN_C __declspec(naked) void FakewaveInGetErrorTextW()           { __asm { jmp[Hijacker::OriginalwaveInGetErrorTextW] } }
EXTERN_C __declspec(naked) void FakewaveInGetID()                   { __asm { jmp[Hijacker::OriginalwaveInGetID] } }
EXTERN_C __declspec(naked) void FakewaveInGetNumDevs()              { __asm { jmp[Hijacker::OriginalwaveInGetNumDevs] } }
EXTERN_C __declspec(naked) void FakewaveInGetPosition()             { __asm { jmp[Hijacker::OriginalwaveInGetPosition] } }
EXTERN_C __declspec(naked) void FakewaveInMessage()                 { __asm { jmp[Hijacker::OriginalwaveInMessage] } }
EXTERN_C __declspec(naked) void FakewaveInOpen()                    { __asm { jmp[Hijacker::OriginalwaveInOpen] } }
EXTERN_C __declspec(naked) void FakewaveInPrepareHeader()           { __asm { jmp[Hijacker::OriginalwaveInPrepareHeader] } }
EXTERN_C __declspec(naked) void FakewaveInReset()                   { __asm { jmp[Hijacker::OriginalwaveInReset] } }
EXTERN_C __declspec(naked) void FakewaveInStart()                   { __asm { jmp[Hijacker::OriginalwaveInStart] } }
EXTERN_C __declspec(naked) void FakewaveInStop()                    { __asm { jmp[Hijacker::OriginalwaveInStop] } }
EXTERN_C __declspec(naked) void FakewaveInUnprepareHeader()         { __asm { jmp[Hijacker::OriginalwaveInUnprepareHeader] } }
EXTERN_C __declspec(naked) void FakewaveOutBreakLoop()              { __asm { jmp[Hijacker::OriginalwaveOutBreakLoop] } }
EXTERN_C __declspec(naked) void FakewaveOutClose()                  { __asm { jmp[Hijacker::OriginalwaveOutClose] } }
EXTERN_C __declspec(naked) void FakewaveOutGetDevCapsA()            { __asm { jmp[Hijacker::OriginalwaveOutGetDevCapsA] } }
EXTERN_C __declspec(naked) void FakewaveOutGetDevCapsW()            { __asm { jmp[Hijacker::OriginalwaveOutGetDevCapsW] } }
EXTERN_C __declspec(naked) void FakewaveOutGetErrorTextA()          { __asm { jmp[Hijacker::OriginalwaveOutGetErrorTextA] } }
EXTERN_C __declspec(naked) void FakewaveOutGetErrorTextW()          { __asm { jmp[Hijacker::OriginalwaveOutGetErrorTextW] } }
EXTERN_C __declspec(naked) void FakewaveOutGetID()                  { __asm { jmp[Hijacker::OriginalwaveOutGetID] } }
EXTERN_C __declspec(naked) void FakewaveOutGetNumDevs()             { __asm { jmp[Hijacker::OriginalwaveOutGetNumDevs] } }
EXTERN_C __declspec(naked) void FakewaveOutGetPitch()               { __asm { jmp[Hijacker::OriginalwaveOutGetPitch] } }
EXTERN_C __declspec(naked) void FakewaveOutGetPlaybackRate()        { __asm { jmp[Hijacker::OriginalwaveOutGetPlaybackRate] } }
EXTERN_C __declspec(naked) void FakewaveOutGetPosition()            { __asm { jmp[Hijacker::OriginalwaveOutGetPosition] } }
EXTERN_C __declspec(naked) void FakewaveOutGetVolume()              { __asm { jmp[Hijacker::OriginalwaveOutGetVolume] } }
EXTERN_C __declspec(naked) void FakewaveOutMessage()                { __asm { jmp[Hijacker::OriginalwaveOutMessage] } }
EXTERN_C __declspec(naked) void FakewaveOutOpen()                   { __asm { jmp[Hijacker::OriginalwaveOutOpen] } }
EXTERN_C __declspec(naked) void FakewaveOutPause()                  { __asm { jmp[Hijacker::OriginalwaveOutPause] } }
EXTERN_C __declspec(naked) void FakewaveOutPrepareHeader()          { __asm { jmp[Hijacker::OriginalwaveOutPrepareHeader] } }
EXTERN_C __declspec(naked) void FakewaveOutReset()                  { __asm { jmp[Hijacker::OriginalwaveOutReset] } }
EXTERN_C __declspec(naked) void FakewaveOutRestart()                { __asm { jmp[Hijacker::OriginalwaveOutRestart] } }
EXTERN_C __declspec(naked) void FakewaveOutSetPitch()               { __asm { jmp[Hijacker::OriginalwaveOutSetPitch] } }
EXTERN_C __declspec(naked) void FakewaveOutSetPlaybackRate()        { __asm { jmp[Hijacker::OriginalwaveOutSetPlaybackRate] } }
EXTERN_C __declspec(naked) void FakewaveOutSetVolume()              { __asm { jmp[Hijacker::OriginalwaveOutSetVolume] } }
EXTERN_C __declspec(naked) void FakewaveOutUnprepareHeader()        { __asm { jmp[Hijacker::OriginalwaveOutUnprepareHeader] } }
EXTERN_C __declspec(naked) void FakewaveOutWrite()                  { __asm { jmp[Hijacker::OriginalwaveOutWrite] } }

#pragma comment(linker, "/EXPORT:CloseDriver=_FakeCloseDriver,@1")
#pragma comment(linker, "/EXPORT:DefDriverProc=_FakeDefDriverProc,@2")
#pragma comment(linker, "/EXPORT:DriverCallback=_FakeDriverCallback,@3")
#pragma comment(linker, "/EXPORT:DrvGetModuleHandle=_FakeDrvGetModuleHandle,@4")
#pragma comment(linker, "/EXPORT:GetDriverModuleHandle=_FakeGetDriverModuleHandle,@5")
#pragma comment(linker, "/EXPORT:OpenDriver=_FakeOpenDriver,@6")
#pragma comment(linker, "/EXPORT:PlaySound=_FakePlaySound,@7")
#pragma comment(linker, "/EXPORT:PlaySoundA=_FakePlaySoundA,@8")
#pragma comment(linker, "/EXPORT:PlaySoundW=_FakePlaySoundW,@9")
#pragma comment(linker, "/EXPORT:SendDriverMessage=_FakeSendDriverMessage,@10")
#pragma comment(linker, "/EXPORT:WOWAppExit=_FakeWOWAppExit,@11")
#pragma comment(linker, "/EXPORT:auxGetDevCapsA=_FakeauxGetDevCapsA,@12")
#pragma comment(linker, "/EXPORT:auxGetDevCapsW=_FakeauxGetDevCapsW,@13")
#pragma comment(linker, "/EXPORT:auxGetNumDevs=_FakeauxGetNumDevs,@14")
#pragma comment(linker, "/EXPORT:auxGetVolume=_FakeauxGetVolume,@15")
#pragma comment(linker, "/EXPORT:auxOutMessage=_FakeauxOutMessage,@16")
#pragma comment(linker, "/EXPORT:auxSetVolume=_FakeauxSetVolume,@17")
#pragma comment(linker, "/EXPORT:joyConfigChanged=_FakejoyConfigChanged,@18")
#pragma comment(linker, "/EXPORT:joyGetDevCapsA=_FakejoyGetDevCapsA,@19")
#pragma comment(linker, "/EXPORT:joyGetDevCapsW=_FakejoyGetDevCapsW,@20")
#pragma comment(linker, "/EXPORT:joyGetNumDevs=_FakejoyGetNumDevs,@21")
#pragma comment(linker, "/EXPORT:joyGetPos=_FakejoyGetPos,@22")
#pragma comment(linker, "/EXPORT:joyGetPosEx=_FakejoyGetPosEx,@23")
#pragma comment(linker, "/EXPORT:joyGetThreshold=_FakejoyGetThreshold,@24")
#pragma comment(linker, "/EXPORT:joyReleaseCapture=_FakejoyReleaseCapture,@25")
#pragma comment(linker, "/EXPORT:joySetCapture=_FakejoySetCapture,@26")
#pragma comment(linker, "/EXPORT:joySetThreshold=_FakejoySetThreshold,@27")
#pragma comment(linker, "/EXPORT:mciDriverNotify=_FakemciDriverNotify,@28")
#pragma comment(linker, "/EXPORT:mciDriverYield=_FakemciDriverYield,@29")
#pragma comment(linker, "/EXPORT:mciExecute=_FakemciExecute,@30")
#pragma comment(linker, "/EXPORT:mciFreeCommandResource=_FakemciFreeCommandResource,@31")
#pragma comment(linker, "/EXPORT:mciGetCreatorTask=_FakemciGetCreatorTask,@32")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDA=_FakemciGetDeviceIDA,@33")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDA=_FakemciGetDeviceIDFromElementIDA,@34")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDW=_FakemciGetDeviceIDFromElementIDW,@35")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDW=_FakemciGetDeviceIDW,@36")
#pragma comment(linker, "/EXPORT:mciGetDriverData=_FakemciGetDriverData,@37")
#pragma comment(linker, "/EXPORT:mciGetErrorStringA=_FakemciGetErrorStringA,@38")
#pragma comment(linker, "/EXPORT:mciGetErrorStringW=_FakemciGetErrorStringW,@39")
#pragma comment(linker, "/EXPORT:mciGetYieldProc=_FakemciGetYieldProc,@40")
#pragma comment(linker, "/EXPORT:mciLoadCommandResource=_FakemciLoadCommandResource,@41")
#pragma comment(linker, "/EXPORT:mciSendCommandA=_FakemciSendCommandA,@42")
#pragma comment(linker, "/EXPORT:mciSendCommandW=_FakemciSendCommandW,@43")
#pragma comment(linker, "/EXPORT:mciSendStringA=_FakemciSendStringA,@44")
#pragma comment(linker, "/EXPORT:mciSendStringW=_FakemciSendStringW,@45")
#pragma comment(linker, "/EXPORT:mciSetDriverData=_FakemciSetDriverData,@46")
#pragma comment(linker, "/EXPORT:mciSetYieldProc=_FakemciSetYieldProc,@47")
#pragma comment(linker, "/EXPORT:midiConnect=_FakemidiConnect,@48")
#pragma comment(linker, "/EXPORT:midiDisconnect=_FakemidiDisconnect,@49")
#pragma comment(linker, "/EXPORT:midiInAddBuffer=_FakemidiInAddBuffer,@50")
#pragma comment(linker, "/EXPORT:midiInClose=_FakemidiInClose,@51")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsA=_FakemidiInGetDevCapsA,@52")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsW=_FakemidiInGetDevCapsW,@53")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextA=_FakemidiInGetErrorTextA,@54")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextW=_FakemidiInGetErrorTextW,@55")
#pragma comment(linker, "/EXPORT:midiInGetID=_FakemidiInGetID,@56")
#pragma comment(linker, "/EXPORT:midiInGetNumDevs=_FakemidiInGetNumDevs,@57")
#pragma comment(linker, "/EXPORT:midiInMessage=_FakemidiInMessage,@58")
#pragma comment(linker, "/EXPORT:midiInOpen=_FakemidiInOpen,@59")
#pragma comment(linker, "/EXPORT:midiInPrepareHeader=_FakemidiInPrepareHeader,@60")
#pragma comment(linker, "/EXPORT:midiInReset=_FakemidiInReset,@61")
#pragma comment(linker, "/EXPORT:midiInStart=_FakemidiInStart,@62")
#pragma comment(linker, "/EXPORT:midiInStop=_FakemidiInStop,@63")
#pragma comment(linker, "/EXPORT:midiInUnprepareHeader=_FakemidiInUnprepareHeader,@64")
#pragma comment(linker, "/EXPORT:midiOutCacheDrumPatches=_FakemidiOutCacheDrumPatches,@65")
#pragma comment(linker, "/EXPORT:midiOutCachePatches=_FakemidiOutCachePatches,@66")
#pragma comment(linker, "/EXPORT:midiOutClose=_FakemidiOutClose,@67")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsA=_FakemidiOutGetDevCapsA,@68")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsW=_FakemidiOutGetDevCapsW,@69")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextA=_FakemidiOutGetErrorTextA,@70")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextW=_FakemidiOutGetErrorTextW,@71")
#pragma comment(linker, "/EXPORT:midiOutGetID=_FakemidiOutGetID,@72")
#pragma comment(linker, "/EXPORT:midiOutGetNumDevs=_FakemidiOutGetNumDevs,@73")
#pragma comment(linker, "/EXPORT:midiOutGetVolume=_FakemidiOutGetVolume,@74")
#pragma comment(linker, "/EXPORT:midiOutLongMsg=_FakemidiOutLongMsg,@75")
#pragma comment(linker, "/EXPORT:midiOutMessage=_FakemidiOutMessage,@76")
#pragma comment(linker, "/EXPORT:midiOutOpen=_FakemidiOutOpen,@77")
#pragma comment(linker, "/EXPORT:midiOutPrepareHeader=_FakemidiOutPrepareHeader,@78")
#pragma comment(linker, "/EXPORT:midiOutReset=_FakemidiOutReset,@79")
#pragma comment(linker, "/EXPORT:midiOutSetVolume=_FakemidiOutSetVolume,@80")
#pragma comment(linker, "/EXPORT:midiOutShortMsg=_FakemidiOutShortMsg,@81")
#pragma comment(linker, "/EXPORT:midiOutUnprepareHeader=_FakemidiOutUnprepareHeader,@82")
#pragma comment(linker, "/EXPORT:midiStreamClose=_FakemidiStreamClose,@83")
#pragma comment(linker, "/EXPORT:midiStreamOpen=_FakemidiStreamOpen,@84")
#pragma comment(linker, "/EXPORT:midiStreamOut=_FakemidiStreamOut,@85")
#pragma comment(linker, "/EXPORT:midiStreamPause=_FakemidiStreamPause,@86")
#pragma comment(linker, "/EXPORT:midiStreamPosition=_FakemidiStreamPosition,@87")
#pragma comment(linker, "/EXPORT:midiStreamProperty=_FakemidiStreamProperty,@88")
#pragma comment(linker, "/EXPORT:midiStreamRestart=_FakemidiStreamRestart,@89")
#pragma comment(linker, "/EXPORT:midiStreamStop=_FakemidiStreamStop,@90")
#pragma comment(linker, "/EXPORT:mixerClose=_FakemixerClose,@91")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsA=_FakemixerGetControlDetailsA,@92")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsW=_FakemixerGetControlDetailsW,@93")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsA=_FakemixerGetDevCapsA,@94")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsW=_FakemixerGetDevCapsW,@95")
#pragma comment(linker, "/EXPORT:mixerGetID=_FakemixerGetID,@96")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsA=_FakemixerGetLineControlsA,@97")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsW=_FakemixerGetLineControlsW,@98")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoA=_FakemixerGetLineInfoA,@99")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoW=_FakemixerGetLineInfoW,@100")
#pragma comment(linker, "/EXPORT:mixerGetNumDevs=_FakemixerGetNumDevs,@101")
#pragma comment(linker, "/EXPORT:mixerMessage=_FakemixerMessage,@102")
#pragma comment(linker, "/EXPORT:mixerOpen=_FakemixerOpen,@103")
#pragma comment(linker, "/EXPORT:mixerSetControlDetails=_FakemixerSetControlDetails,@104")
#pragma comment(linker, "/EXPORT:mmDrvInstall=_FakemmDrvInstall,@105")
#pragma comment(linker, "/EXPORT:mmGetCurrentTask=_FakemmGetCurrentTask,@106")
#pragma comment(linker, "/EXPORT:mmTaskBlock=_FakemmTaskBlock,@107")
#pragma comment(linker, "/EXPORT:mmTaskCreate=_FakemmTaskCreate,@108")
#pragma comment(linker, "/EXPORT:mmTaskSignal=_FakemmTaskSignal,@109")
#pragma comment(linker, "/EXPORT:mmTaskYield=_FakemmTaskYield,@110")
#pragma comment(linker, "/EXPORT:mmioAdvance=_FakemmioAdvance,@111")
#pragma comment(linker, "/EXPORT:mmioAscend=_FakemmioAscend,@112")
#pragma comment(linker, "/EXPORT:mmioClose=_FakemmioClose,@113")
#pragma comment(linker, "/EXPORT:mmioCreateChunk=_FakemmioCreateChunk,@114")
#pragma comment(linker, "/EXPORT:mmioDescend=_FakemmioDescend,@115")
#pragma comment(linker, "/EXPORT:mmioFlush=_FakemmioFlush,@116")
#pragma comment(linker, "/EXPORT:mmioGetInfo=_FakemmioGetInfo,@117")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcA=_FakemmioInstallIOProcA,@118")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcW=_FakemmioInstallIOProcW,@119")
#pragma comment(linker, "/EXPORT:mmioOpenA=_FakemmioOpenA,@120")
#pragma comment(linker, "/EXPORT:mmioOpenW=_FakemmioOpenW,@121")
#pragma comment(linker, "/EXPORT:mmioRead=_FakemmioRead,@122")
#pragma comment(linker, "/EXPORT:mmioRenameA=_FakemmioRenameA,@123")
#pragma comment(linker, "/EXPORT:mmioRenameW=_FakemmioRenameW,@124")
#pragma comment(linker, "/EXPORT:mmioSeek=_FakemmioSeek,@125")
#pragma comment(linker, "/EXPORT:mmioSendMessage=_FakemmioSendMessage,@126")
#pragma comment(linker, "/EXPORT:mmioSetBuffer=_FakemmioSetBuffer,@127")
#pragma comment(linker, "/EXPORT:mmioSetInfo=_FakemmioSetInfo,@128")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCA=_FakemmioStringToFOURCCA,@129")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCW=_FakemmioStringToFOURCCW,@130")
#pragma comment(linker, "/EXPORT:mmioWrite=_FakemmioWrite,@131")
#pragma comment(linker, "/EXPORT:mmsystemGetVersion=_FakemmsystemGetVersion,@132")
#pragma comment(linker, "/EXPORT:sndPlaySoundA=_FakesndPlaySoundA,@133")
#pragma comment(linker, "/EXPORT:sndPlaySoundW=_FakesndPlaySoundW,@134")
#pragma comment(linker, "/EXPORT:timeBeginPeriod=_FaketimeBeginPeriod,@135")
#pragma comment(linker, "/EXPORT:timeEndPeriod=_FaketimeEndPeriod,@136")
#pragma comment(linker, "/EXPORT:timeGetDevCaps=_FaketimeGetDevCaps,@137")
#pragma comment(linker, "/EXPORT:timeGetSystemTime=_FaketimeGetSystemTime,@138")
#pragma comment(linker, "/EXPORT:timeGetTime=_FaketimeGetTime,@139")
#pragma comment(linker, "/EXPORT:timeKillEvent=_FaketimeKillEvent,@140")
#pragma comment(linker, "/EXPORT:timeSetEvent=_FaketimeSetEvent,@141")
#pragma comment(linker, "/EXPORT:waveInAddBuffer=_FakewaveInAddBuffer,@142")
#pragma comment(linker, "/EXPORT:waveInClose=_FakewaveInClose,@143")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsA=_FakewaveInGetDevCapsA,@144")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsW=_FakewaveInGetDevCapsW,@145")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextA=_FakewaveInGetErrorTextA,@146")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextW=_FakewaveInGetErrorTextW,@147")
#pragma comment(linker, "/EXPORT:waveInGetID=_FakewaveInGetID,@148")
#pragma comment(linker, "/EXPORT:waveInGetNumDevs=_FakewaveInGetNumDevs,@149")
#pragma comment(linker, "/EXPORT:waveInGetPosition=_FakewaveInGetPosition,@150")
#pragma comment(linker, "/EXPORT:waveInMessage=_FakewaveInMessage,@151")
#pragma comment(linker, "/EXPORT:waveInOpen=_FakewaveInOpen,@152")
#pragma comment(linker, "/EXPORT:waveInPrepareHeader=_FakewaveInPrepareHeader,@153")
#pragma comment(linker, "/EXPORT:waveInReset=_FakewaveInReset,@154")
#pragma comment(linker, "/EXPORT:waveInStart=_FakewaveInStart,@155")
#pragma comment(linker, "/EXPORT:waveInStop=_FakewaveInStop,@156")
#pragma comment(linker, "/EXPORT:waveInUnprepareHeader=_FakewaveInUnprepareHeader,@157")
#pragma comment(linker, "/EXPORT:waveOutBreakLoop=_FakewaveOutBreakLoop,@158")
#pragma comment(linker, "/EXPORT:waveOutClose=_FakewaveOutClose,@159")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsA=_FakewaveOutGetDevCapsA,@160")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsW=_FakewaveOutGetDevCapsW,@161")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextA=_FakewaveOutGetErrorTextA,@162")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextW=_FakewaveOutGetErrorTextW,@163")
#pragma comment(linker, "/EXPORT:waveOutGetID=_FakewaveOutGetID,@164")
#pragma comment(linker, "/EXPORT:waveOutGetNumDevs=_FakewaveOutGetNumDevs,@165")
#pragma comment(linker, "/EXPORT:waveOutGetPitch=_FakewaveOutGetPitch,@166")
#pragma comment(linker, "/EXPORT:waveOutGetPlaybackRate=_FakewaveOutGetPlaybackRate,@167")
#pragma comment(linker, "/EXPORT:waveOutGetPosition=_FakewaveOutGetPosition,@168")
#pragma comment(linker, "/EXPORT:waveOutGetVolume=_FakewaveOutGetVolume,@169")
#pragma comment(linker, "/EXPORT:waveOutMessage=_FakewaveOutMessage,@170")
#pragma comment(linker, "/EXPORT:waveOutOpen=_FakewaveOutOpen,@171")
#pragma comment(linker, "/EXPORT:waveOutPause=_FakewaveOutPause,@172")
#pragma comment(linker, "/EXPORT:waveOutPrepareHeader=_FakewaveOutPrepareHeader,@173")
#pragma comment(linker, "/EXPORT:waveOutReset=_FakewaveOutReset,@174")
#pragma comment(linker, "/EXPORT:waveOutRestart=_FakewaveOutRestart,@175")
#pragma comment(linker, "/EXPORT:waveOutSetPitch=_FakewaveOutSetPitch,@176")
#pragma comment(linker, "/EXPORT:waveOutSetPlaybackRate=_FakewaveOutSetPlaybackRate,@177")
#pragma comment(linker, "/EXPORT:waveOutSetVolume=_FakewaveOutSetVolume,@178")
#pragma comment(linker, "/EXPORT:waveOutUnprepareHeader=_FakewaveOutUnprepareHeader,@179")
#pragma comment(linker, "/EXPORT:waveOutWrite=_FakewaveOutWrite,@180")

#endif
