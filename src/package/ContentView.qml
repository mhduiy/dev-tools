import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.deepin.dtk as D
import org.deepin.ds.dock 1.0

Item {
    id: root
    property alias model: repeater.model

    signal invokeCommand(var cmd)
    
    ScrollView {
        id: scrollView
        anchors.fill: parent
        anchors.margins: 20
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        GridLayout {
            width: scrollView.availableWidth
            columnSpacing: 10
            rowSpacing: 10
            columns: 4
            Repeater {
                id: repeater
                delegate: Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 130
                    color: Qt.rgba(255, 255, 255, 0.2)
                    border.width: 1
                    border.color: Qt.rgba(0, 0, 0, 0.2)
                    radius: 8

                    scale: tapHandler.pressed ? 0.85 : hoverHandler.hovered ? 0.95 : 1

                    Behavior on scale {
                        NumberAnimation {
                            duration: 500
                            easing.type: Easing.OutCirc
                        }
                    }

                    HoverHandler {
                        id: hoverHandler
                    }

                    TapHandler {
                        id: tapHandler
                        onTapped: {
                            root.invokeCommand(model.cmd)
                        }
                    }

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.topMargin: 10
                        anchors.bottomMargin: 10
                        spacing: 10
                        D.DciIcon {
                            Layout.preferredHeight: 60
                            Layout.preferredWidth: 60
                            Layout.alignment: Qt.AlignCenter
                            sourceSize: Qt.size(60, 60)
                            name: model.icon
                        }
                        Text {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            text: model.title
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
    }
}
