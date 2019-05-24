import QtQuick.Controls 1.1
import QtQuick.Extras 1.4

ControlView {
    id: controlView
    darkBackground: customizerItem.currentStyleDark

    property color fontColor: darkBackground ? "white" : "black"

    property bool accelerating: false

    Keys.onSpacePressed: accelerating = true
    Keys.onReleased: {
        if (event.key === Qt.Key_Space) {
            accelerating = false;
            event.accepted = true;
        }
    }

    Button {
        id: accelerate
        text: "Accelerate"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        height: root.height * 0.125

        onPressedChanged: accelerating = pressed

        style: BlackButtonStyle {
            background: BlackButtonBackground {
                pressed: control.pressed
            }
            label: Text {
                text: control.text
                color: "white"
                font.pixelSize: Math.max(textSingleton.font.pixelSize, root.toPixels(0.04))
                font.family: openSans.name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    control: CircularGauge {
        id: gauge
        minimumValue: customizerItem.minimumValue
        maximumValue: customizerItem.maximumValue
        width: controlBounds.width
        height: controlBounds.height

        value: accelerating ? maximumValue : 0
        style: styleMap[customizerItem.currentStylePath]

        // This stops the styles being recreated when a new one is chosen.
        property var styleMap: {
            var styles = {};
            for (var i = 0; i < customizerItem.allStylePaths.length; ++i) {
                var path = customizerItem.allStylePaths[i];
                styles[path] = Qt.createComponent(path, gauge);
            }
            styles;
        }

        // Called to update the style after the user has edited a property.
        Connections {
            target: customizerItem
            onMinimumValueAngleChanged: __style.minimumValueAngle = customizerItem.minimumValueAngle
            onMaximumValueAngleChanged: __style.maximumValueAngle = customizerItem.maximumValueAngle
            onLabelStepSizeChanged: __style.tickmarkStepSize = __style.labelStepSize = customizerItem.labelStepSize
        }

        Behavior on value {
            NumberAnimation {
                easing.type: Easing.OutCubic
                duration: 6000
            }
        }
    }

    customizer: Column {
        readonly property var allStylePaths: {
            var paths = [];
            for (var i = 0; i < stylePicker.model.count; ++i) {
                paths.push(stylePicker.model.get(i).path);
            }
            paths;
        }
        property alias currentStylePath: stylePicker.currentStylePath
        property alias currentStyleDark: stylePicker.currentStyleDark
        property alias minimumValue: minimumValueSlider.value
        property alias maximumValue: maximumValueSlider.value
        property alias minimumValueAngle: minimumAngleSlider.value
        property alias maximumValueAngle: maximumAngleSlider.value
        property alias labelStepSize: labelStepSizeSlider.value

        id: circularGaugeColumn
        spacing: customizerPropertySpacing

        readonly property bool isDefaultStyle: stylePicker.model.get(stylePicker.currentIndex).name === "Default"

        Item {
            id: stylePickerBottomSpacing
            width: parent.width
            height: stylePicker.height + textSingleton.implicitHeight

            StylePicker {
                id: stylePicker
                currentIndex: 1

                model: ListModel {
                    ListElement {
                        name: "Default"
                        path: "CircularGaugeDefaultStyle.qml"
                        dark: true
                    }
                    ListElement {
                        name: "Dark"
                        path: "CircularGaugeDarkStyle.qml"
                        dark: true
                    }
                    ListElement {
                        name: "Light"
                        path: "CircularGaugeLightStyle.qml"
                        dark: false
                    }
                }
            }
        }

        CustomizerLabel {
            text: "Minimum angle"
        }

        CustomizerSlider {
            id: minimumAngleSlider
            minimumValue: -180
            value: -145
            maximumValue: 180
            width: parent.width
        }

        CustomizerLabel {
            text: "Maximum angle"
        }

        CustomizerSlider {
            id: maximumAngleSlider
            minimumValue: -180
            value: 145
            maximumValue: 180
        }

        CustomizerLabel {
            text: "Minimum value"
        }

        CustomizerSlider {
            id: minimumValueSlider
            minimumValue: 0
            value: 0
            maximumValue: 360
            stepSize: 1
        }

        CustomizerLabel {
            text: "Maximum value"
        }

        CustomizerSlider {
            id: maximumValueSlider
            minimumValue: 0
            value: 240
            maximumValue: 300
            stepSize: 1
        }

        CustomizerLabel {
            text: "Label step size"
        }

        CustomizerSlider {
            id: labelStepSizeSlider
            minimumValue: 10
            value: 20
            maximumValue: 100
            stepSize: 20
        }
    }
}
