# AstraShell v0.2.1 — input safety hotfix (experimental)

This patch prioritizes the reported issue where normal application windows become unresponsive when dragged over AstraShell.

## Changes
- Disables the full-screen desktop surface by default. Windows Explorer keeps managing the wallpaper and desktop icons. This is deliberate: a click-through surface still has z-order and wallpaper integration issues.
- Adds `Qt::WindowTransparentForInput` and native `WS_EX_TRANSPARENT | WS_EX_NOACTIVATE` to the optional desktop surface if it is enabled later.
- Reduces the interactive top panel from screen-wide to a 440 × 76 DIP floating window, expanding to 440 × 402 DIP only while Dashboard is open.
- Anchors the panel to the right of its screen rather than assuming x=0. Screen hotplug and per-monitor panels are **not yet implemented**.
- Keeps the taskbar-hide feature opt-in, with restore on clean exit. If the app crashes while the taskbar is hidden, use Task Manager to restart Explorer or sign out and back in.

## Build
Open `CMakeLists.txt` in Qt Creator with a Qt 6.5+ ARM64 kit. Build and run. Windows ARM64 execution has not been verified in this environment.

## Known limitations
- This is a safety hotfix, **not** full multi-monitor support. Only one panel is created, and it may require restart after display changes.
- No AppBar work-area reservation; maximized windows may extend underneath the panel.
- No full desktop wallpaper replacement; no notification or Wi-Fi integration yet.
- No guarantee that Windows system overlays will remain beneath the panel.
- Dashboard remains an interactive rectangle while open. Avoid dragging other windows through that area.

## Recovery
Close AstraShell with Ctrl+Q when its panel has focus, or use Task Manager to terminate it. If the taskbar remains hidden, restart Windows Explorer from Task Manager.
