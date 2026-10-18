#include "ShellController.h"
#include <QGuiApplication>
#ifdef Q_OS_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
static void setTaskbarVisible(bool visible) {
 HWND taskbar=FindWindowW(L"Shell_TrayWnd",nullptr);
 if(taskbar) ShowWindow(taskbar,visible?SW_SHOW:SW_HIDE);
 // Secondary monitors use separate taskbars.
 HWND secondary=nullptr;
 while((secondary=FindWindowExW(nullptr,secondary,L"Shell_SecondaryTrayWnd",nullptr)))
   ShowWindow(secondary,visible?SW_SHOW:SW_HIDE);
}
#endif
ShellController::ShellController(QObject *parent):QObject(parent){}
ShellController::~ShellController(){ restoreTaskbar(); }
void ShellController::restoreTaskbar(){
#ifdef Q_OS_WIN
 if(m_taskbarHidden) setTaskbarVisible(true);
#endif
 m_taskbarHidden=false; m_immersive=false; emit immersiveChanged();
}
void ShellController::setImmersive(bool enabled){
 if(!enabled){restoreTaskbar();return;}
#ifdef Q_OS_WIN
 // Opt-in only; no Explorer termination or registry modifications.
 setTaskbarVisible(false);
 m_taskbarHidden=true;
#endif
 m_immersive=true; emit immersiveChanged();
}
void ShellController::configureDesktop(QWindow *window){
 if(!window) return;
 // The wallpaper is visual-only: never capture pointer, touch, or keyboard input.
 window->setFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowTransparentForInput | Qt::WindowDoesNotAcceptFocus);
#ifdef Q_OS_WIN
 window->show();
 HWND hwnd=reinterpret_cast<HWND>(window->winId());
 LONG_PTR ex=GetWindowLongPtrW(hwnd,GWL_EXSTYLE);
 SetWindowLongPtrW(hwnd,GWL_EXSTYLE,ex|WS_EX_TRANSPARENT|WS_EX_NOACTIVATE|WS_EX_TOOLWINDOW);
 SetWindowPos(hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_FRAMECHANGED);
#endif
}
void ShellController::configurePanel(QWindow *window){
 if(!window)return;
 // Interactive window occupies only its actual visual bounds, never the entire screen.
 window->setFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
 window->show();
}
