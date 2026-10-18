import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

QtObject {
    id: appRoot
    property bool dashboardOpen: false
    property color ink: "#edf3ff"
    property color muted: "#a5b5cf"

    property Window desktop: Window {
        id: desktopWindow
        visible: false // Opt-in later: Explorer remains responsible for the wallpaper in this safe build.
        x: Screen.virtualX; y: Screen.virtualY
        width: Screen.width; height: Screen.height
        title: "Astra Desktop"
        color: "#0a1222"
        // Desktop intentionally disabled: a bottom-stacked window can still cover Explorer icons.
        // Component.onCompleted: shellController.configureDesktop(desktopWindow)
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0; color: "#223454" }
                GradientStop { position: 0.6; color: "#101b31" }
                GradientStop { position: 1; color: "#080e1b" }
            }
        }
        Rectangle { width: 430; height: 430; radius: 215; x: parent.width*0.32; y: parent.height*0.16; color: "#315184"; opacity: .25 }
        Column {
            x: 56; y: parent.height*0.3; spacing: 14
            Text { text: "ASTRA"; color: appRoot.ink; font.pixelSize: 54; font.weight: Font.DemiBold }
            Text { text: "A different place to work."; color: appRoot.muted; font.pixelSize: 20 }
            Text { text: "Windows ARM64 · immersive desktop preview"; color: "#8096b7"; font.pixelSize: 13 }
        }
    }
    property Window panel: Window {
        id: panelWindow
        visible: true
        x: Screen.virtualX + Screen.width - width - 16; y: Screen.virtualY + 12
        width: 440; height: appRoot.dashboardOpen ? 402 : 76
        color: "transparent"
        title: "Astra Panel"
        Component.onCompleted: shellController.configurePanel(panelWindow)
        Behavior on height { NumberAnimation { duration: 230; easing.type: Easing.OutCubic } }
        Rectangle {
            x: 0; y: 0; width: parent.width; height: 64; radius: 22
            color: "#e21b2b44"; border.color: "#52698a"
            RowLayout {
                anchors.fill: parent; anchors.leftMargin: 18; anchors.rightMargin: 18; spacing: 12
                Text { text: "✦ ASTRA"; color: appRoot.ink; font.bold: true; font.pixelSize: 17 }
                Text { text: "ARM64"; color: appRoot.muted; font.pixelSize: 12 }
                Item { Layout.fillWidth: true }
                Text { text: systemBridge.clock; color: appRoot.ink; font.bold: true; font.pixelSize: 18 }
                Text { text: systemBridge.battery < 0 ? "Battery —" : systemBridge.battery + "%"; color: appRoot.muted }
                Button { text: appRoot.dashboardOpen ? "Close" : "Dashboard"; onClicked: appRoot.dashboardOpen = !appRoot.dashboardOpen }
            }
        }
        Rectangle {
            visible: appRoot.dashboardOpen
            x: parent.width-width; y: 78; width: Math.min(420,parent.width); height: 312
            radius: 24; color: "#f01b2b44"; border.color: "#52698a"
            ColumnLayout {
                anchors.fill: parent; anchors.margins: 20; spacing: 12
                Text { text: "Control center"; color: appRoot.ink; font.pixelSize: 23; font.bold: true }
                Text { text: systemBridge.date + "  ·  " + systemBridge.clock; color: appRoot.muted }
                GridLayout {
                    columns: 2; Layout.fillWidth: true
                    Button { text: "Settings"; Layout.fillWidth: true; onClicked: systemBridge.openSettings() }
                    Button { text: "Explorer"; Layout.fillWidth: true; onClicked: systemBridge.openExplorer() }
                    Button { text: "Terminal"; Layout.fillWidth: true; onClicked: systemBridge.openTerminal() }
                    Button { text: "Start"; Layout.fillWidth: true; onClicked: systemBridge.openStartMenu() }
                }
                CheckBox {
                    text: "Hide Windows taskbar (experimental)"
                    checked: shellController.immersive
                    onToggled: shellController.setImmersive(checked)
                    palette.windowText: appRoot.ink
                }
                Text { text: "No Explorer termination · Exit restores taskbar"; color: appRoot.muted; font.pixelSize: 12 }
                Item { Layout.fillHeight: true }
                Button { text: "Exit AstraShell"; Layout.fillWidth: true; onClicked: systemBridge.quitShell() }
            }
        }
        Shortcut { sequence: "Ctrl+Q"; onActivated: systemBridge.quitShell() }
        Shortcut { sequence: "Ctrl+Shift+D"; onActivated: appRoot.dashboardOpen = !appRoot.dashboardOpen }
    }
}
