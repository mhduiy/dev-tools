import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import org.deepin.dtk 1.0
import org.deepin.dtk.style 1.0 as DS

import org.deepin.ds 1.0
import org.deepin.dtk 1.0 as D
import org.deepin.ds.dock 1.0

AppletItem {
    id: devtoolsitem
    property bool useColumnLayout: Panel.position % 2
    property int dockOrder: 13
    // 1:4 the distance between app : dock height; get width/height≈0.8
    implicitWidth: useColumnLayout ? Panel.rootObject.dockSize : Panel.rootObject.dockItemMaxSize * 0.8
    implicitHeight: useColumnLayout ? Panel.rootObject.dockItemMaxSize * 0.8 : Panel.rootObject.dockSize


    PanelPopup {
        id: panelPopup

        width: 610
        height: 480

        popupX: (Screen.width - width) / 2
        popupY: -1 * height - 10

        ContentView {
            anchors.fill: parent
            model: Applet.model

            onInvokeCommand: (cmd) => {
                Applet.invokeCommand(cmd)
            }
        }

    }

    D.DciIcon {
        id: icon
        anchors.fill: parent
        name: Applet.iconName
        scale: Panel.rootObject.dockItemMaxSize * 9 / 14 / Dock.MAX_DOCK_TASKMANAGER_ICON_SIZE
        sourceSize: Qt.size(Dock.MAX_DOCK_TASKMANAGER_ICON_SIZE, Dock.MAX_DOCK_TASKMANAGER_ICON_SIZE)

        TapHandler {
            acceptedButtons: Qt.LeftButton
            onTapped: {
                panelPopup.open()
            }
        }
        HoverHandler {
            onHoveredChanged: {}
        }
    }
}
