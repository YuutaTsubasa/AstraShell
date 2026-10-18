#include "SystemBridge.h"
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QCoreApplication>
#ifdef Q_OS_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
SystemBridge::SystemBridge(QObject *parent):QObject(parent){
 connect(&m_timer,&QTimer::timeout,this,&SystemBridge::refresh);
 m_timer.start(1000); refresh();
}
void SystemBridge::refresh(){
 auto now=QDateTime::currentDateTime();
 QString clock=now.toString("HH:mm");
 QString date=now.toString("ddd, MMM d");
 int battery=-1; bool charging=false;
#ifdef Q_OS_WIN
 SYSTEM_POWER_STATUS p{};
 if(GetSystemPowerStatus(&p)) {
  if(p.BatteryLifePercent!=255) battery=p.BatteryLifePercent;
  charging=(p.ACLineStatus==1);
 }
#endif
 if(clock!=m_clock||date!=m_date||battery!=m_battery||charging!=m_charging){
  m_clock=clock;m_date=date;m_battery=battery;m_charging=charging;emit changed();
 }
}
QString SystemBridge::platform() const {
#ifdef Q_OS_WIN
 return QStringLiteral("Windows");
#else
 return QStringLiteral("Preview (non-Windows)");
#endif
}
void SystemBridge::openSettings(){QDesktopServices::openUrl(QUrl("ms-settings:"));}
void SystemBridge::openExplorer(){QProcess::startDetached("explorer.exe",{});}
void SystemBridge::openTerminal(){QProcess::startDetached("wt.exe",{});}
void SystemBridge::openStartMenu(){
#ifdef Q_OS_WIN
 // Trigger Windows key; leaves Explorer intact.
 INPUT input[2]{};
 input[0].type=INPUT_KEYBOARD;input[0].ki.wVk=VK_LWIN;
 input[1].type=INPUT_KEYBOARD;input[1].ki.wVk=VK_LWIN;input[1].ki.dwFlags=KEYEVENTF_KEYUP;
 SendInput(2,input,sizeof(INPUT));
#endif
}
void SystemBridge::quitShell(){QCoreApplication::quit();}
