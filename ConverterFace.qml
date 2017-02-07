import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls.Private 1.0

import frumkin 1.0

Item {
    id: root
    default property Converter converter

    RowLayout {
        id: mainLayout
        spacing: 1

        width: root.width
        height: 100

        Rectangle {
            id: face1
            height: 100
            radius: height/4
            color: "lightgray"
            border.width: 1
            
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            //Layout.preferredWidth: 200
            RowLayout {
                anchors.fill: parent
                TextField {
                    id: sourceTextField
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50

                    selectByMouse : true
                    font.pixelSize: face1.height * 0.4
                    
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: RegExpValidator {regExp: /^[0-9]*[.][0-9]+[1-9]*/}
                    Component.onCompleted: {
                        text = "0.0"
                    }
                    onTextChanged: {
                        if (text.charAt(0) == '0' && text.charAt(1) != '0' && text.charAt(1) != '.') {

                            var tempCursorPosition = cursorPosition
                            console.log("f2 " + tempCursorPosition + cursorPosition)
                            text = text.substr(1)
                            cursorPosition = tempCursorPosition - 1
                        }
                        if (text.charAt(0) == '0' && text.charAt(1) == '0') {
                            console.log("f3")

                            text = text.substr(1)
                            cursorPosition = 1
                        }
                        if (text.charAt(0) == '.') {
                            console.log("f4")

                            text = "0" + text
                            cursorPosition = 0
                        }
                        if (text.charAt(text.length - 1) == ".") {
                            console.log("f5")

                            text = text + "0"
                            cursorPosition = text.length - 1
                        }
                        converter.sourceValue = parseFloat(text)
                        //conversion
                        var sourceConvertionCoefficient = sourceComboBox.model.getCoefficient(sourceComboBox.currentIndex)
                        var convertedConvertionCoefficient = convertedComboBox.model.getCoefficient(convertedComboBox.currentIndex)
                        converter.convert(sourceConvertionCoefficient , convertedConvertionCoefficient)
                    }
                    Keys.onPressed: {
                        //process dot key pushed, if double dot is met just move cursor
                        var val = text.toString();
                        if (event.key == Qt.Key_Period && val.charAt(cursorPosition) == '.') {
                            cursorPosition++;
                            event.accepted = true;
                        }
                    }

                    style: TextFieldStyle {

                        textColor: "black"


                        background: Rectangle {
                            border.width: 0
                            color: "lightgray"
                        }
                    }
                }
                Canvas {
                    width: 6; height: parent.height
                    Layout.fillWidth: true
                    Layout.minimumWidth: 6
                    // M1>>
                    onPaint: {
                        var ctx = getContext("2d")

                        // setup the stroke
                        ctx.strokeStyle = "black"

                        // create a path
                        ctx.beginPath()
                        ctx.moveTo(3,0)
                        ctx.lineTo(3,height/10)

                        ctx.moveTo(3,2*height/10)
                        ctx.lineTo(3,3*height/10)

                        ctx.moveTo(3,4*height/10)
                        ctx.lineTo(3,5*height/10)

                        ctx.moveTo(3,6*height/10)
                        ctx.lineTo(3,7*height/10)

                        ctx.moveTo(3,6*height/10)
                        ctx.lineTo(3,7*height/10)

                        ctx.moveTo(3,8*height/10)
                        ctx.lineTo(3,9*height/10)

                        // stroke path
                        ctx.stroke()
                    }
                    // <<M1
                }
                ComboBox {
                    id: sourceComboBox
                    Layout.minimumWidth: 150
                    anchors.rightMargin: 5
                    anchors.right: parent.right
                    textRole: "name"

                    //currentIndex: 0
                    activeFocusOnPress: true

                    model: converter.sourceUnitModel //NOTE surce unit model

                    onCurrentIndexChanged : {
                        console.log(model.getCoefficient(currentIndex))
                        var sourceConvertionCoefficient = model.getCoefficient(currentIndex)
                        var convertedConvertionCoefficient = convertedComboBox.model.getCoefficient(convertedComboBox.currentIndex)
                        converter.convert(sourceConvertionCoefficient , convertedConvertionCoefficient)
                    }

                    style: ComboBoxStyle {
                        background: Rectangle {
                            color: "lightgray"
                        }
                        label: Text {
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: face1.height * 0.4
                            color: "black"
                            text: control.currentText
                        }
                        selectionColor: "gray"

                        property Component __dropDownStyle: MenuStyle {
                            __maxPopupHeight: 600
                            __menuItemType: "comboboxitem"

                            frame: Rectangle {              // background
                                color: "lightgray"
                                border.width: 0
                            }

                            itemDelegate.label:            // an item text
                                                           Text {

                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.pixelSize: face1.height * 0.4
                                //font.family: "Courier"
                                //font.capitalization: Font.SmallCaps
                                color: styleData.selected ? "white" : "black"
                                text: styleData.text
                            }

                            itemDelegate.background: Rectangle {  // selection of an item
                                //radius: 0
                                color: styleData.selected ? "gray" : "transparent"
                            }

                            __scrollerStyle: ScrollViewStyle { }
                        }

                        property Component __popupStyle: Style {
                            property int __maxPopupHeight: 400
                            property int submenuOverlap: 0

                            property Component frame: Rectangle {
                                width: (parent ? parent.contentWidth : 0)
                                height: (parent ? parent.contentHeight : 0) + 2
                                //border.color: "black"
                                border.width: 0
                                property real maxHeight: 500
                                property int margin: 1
                            }

                            /*property Component menuItemPanel: Text {
                                text: "NOT IMPLEMENTED"
                                color: "red"
                                font {
                                    pixelSize: face1.height * 0.4
                                    bold: true
                                }
                            }*/

                            property Component __scrollerStyle: null
                        }
                        //dropdown customization
                    }
                }
            }
        }
        Rectangle {
            id: face2
            height: 100
            radius: height/4
            color: "lightgray"
            border.width: 1

            Layout.fillWidth: true
            Layout.minimumWidth: 200
            RowLayout {
                anchors.fill: parent
                Text {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    text: converter.convertedValue.toFixed(3) //NOTE converted value text
                    font.pixelSize: face2.height * 0.4
                    color: "#000"
                }
                Canvas {

                    width: 6; height: parent.height
                    Layout.fillWidth: true
                    Layout.minimumWidth: 6
                    // M1>>
                    onPaint: {
                        var ctx = getContext("2d")

                        // setup the stroke
                        ctx.strokeStyle = "black"

                        // create a path
                        ctx.beginPath()
                        ctx.moveTo(3,0)
                        ctx.lineTo(3,height/10)

                        ctx.moveTo(3,2*height/10)
                        ctx.lineTo(3,3*height/10)

                        ctx.moveTo(3,4*height/10)
                        ctx.lineTo(3,5*height/10)

                        ctx.moveTo(3,6*height/10)
                        ctx.lineTo(3,7*height/10)

                        ctx.moveTo(3,6*height/10)
                        ctx.lineTo(3,7*height/10)

                        ctx.moveTo(3,8*height/10)
                        ctx.lineTo(3,9*height/10)

                        // stroke path
                        ctx.stroke()
                    }
                    // <<M1
                }
                ComboBox {
                    id: convertedComboBox
                    Layout.minimumWidth: 150
                    anchors.rightMargin: 5
                    anchors.right: parent.right

                    //currentIndex: 0
                    activeFocusOnPress: true
                    textRole: "name"

                    model: converter.convertedUnitModel //NOTE converted units model

                    onCurrentIndexChanged : {
                        var sourceConvertionCoefficient = sourceComboBox.model.getCoefficient(sourceComboBox.currentIndex)
                        var convertedConvertionCoefficient = convertedComboBox.model.getCoefficient(convertedComboBox.currentIndex)
                        converter.convert(sourceConvertionCoefficient , convertedConvertionCoefficient)
                    }

                    style: ComboBoxStyle {
                        background: Rectangle {
                            color: "lightgray"
                            //width: 100
                            //anchors.fill: parent
                            //radius: height
                        }
                        label: Text {
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.pixelSize: face1.height * 0.4
                            //font.family: "Courier"
                            //font.capitalization: Font.SmallCaps
                            color: "black"
                            text: control.currentText
                        }
                        selectionColor: "gray"

                        property Component __dropDownStyle: MenuStyle {
                            __maxPopupHeight: 600
                            __menuItemType: "comboboxitem"

                            frame: Rectangle {              // background
                                color: "lightgray"
                                border.width: 0
                            }

                            itemDelegate.label:            // an item text
                                                           Text {

                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                font.pixelSize: face1.height * 0.4
                                //font.family: "Courier"
                                //font.capitalization: Font.SmallCaps
                                color: styleData.selected ? "white" : "black"
                                text: styleData.text
                            }

                            itemDelegate.background: Rectangle {  // selection of an item
                                //radius: 0
                                color: styleData.selected ? "gray" : "transparent"
                            }

                            __scrollerStyle: ScrollViewStyle { }
                        }

                        property Component __popupStyle: Style {
                            property int __maxPopupHeight: 400
                            property int submenuOverlap: 0

                            property Component frame: Rectangle {
                                width: (parent ? parent.contentWidth : 0)
                                height: (parent ? parent.contentHeight : 0) + 2
                                //border.color: "black"
                                border.width: 0
                                property real maxHeight: 500
                                property int margin: 1
                            }

                            property Component __scrollerStyle: null
                        }
                        //dropdown customization
                    }
                }
            }
        }
    }
    ComboBox {
        id: comboCategory
        anchors.top: mainLayout.bottom
        width: parent.width
        height: face1.height * 0.5

        activeFocusOnPress: true
        textRole: "categoryName"

        model: converter.categoryModel

        onCurrentIndexChanged : {
            sourceComboBox.model.updateCategory(converter.getModelCategory(currentIndex))
            convertedComboBox.model.updateCategory(converter.getModelCategory(currentIndex))

            //convertion
            var sourceConvertionCoefficient = sourceComboBox.model.getCoefficient(sourceComboBox.currentIndex)
            var convertedConvertionCoefficient = convertedComboBox.model.getCoefficient(convertedComboBox.currentIndex)
            converter.convert(sourceConvertionCoefficient , convertedConvertionCoefficient)
        }

        style: ComboBoxStyle {
            background: Rectangle {
                color: "lightgray"
                radius: height/6
                border.width: 1
                border.color: "black"
            }
            label: Text {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: face1.height * 0.4
                //font.family: "Courier"
                //font.capitalization: Font.SmallCaps
                color: "black"
                text: control.currentText
            }
            selectionColor: "gray"

            property Component __dropDownStyle: MenuStyle {
                __maxPopupHeight: 600
                __menuItemType: "comboboxitem"

                frame: Rectangle {              // background
                    color: "lightgray"
                    border.width: 0
                }

                itemDelegate.label:            // an item text
                                               Text {

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: face1.height * 0.4
                    //font.family: "Courier"
                    //font.capitalization: Font.SmallCaps
                    color: styleData.selected ? "white" : "black"
                    text: styleData.text
                }

                itemDelegate.background: Rectangle {  // selection of an item
                    //radius: 0
                    color: styleData.selected ? "gray" : "transparent"
                }

                __scrollerStyle: ScrollViewStyle { }
            }

            property Component __popupStyle: Style {
                property int __maxPopupHeight: 400
                property int submenuOverlap: 0

                property Component frame: Rectangle {
                    width: (parent ? parent.contentWidth : 0)
                    height: (parent ? parent.contentHeight : 0) + 2
                    //border.color: "black"
                    border.width: 0
                    property real maxHeight: 500
                    property int margin: 1
                }

                property Component __scrollerStyle: null
            }
            //dropdown customization
        }
    }




    /*function filterText(text_) {
        //filter text if we have wrong pattern, fix it
        text_ = (/^[0-9]*[.][0-9]+[1-9]).test(text_) ?
                    text_ : text_ + ".0";
        //filter text if we have 01.11 -> 1.11
        if(text_.charAt(0) == '0' && text_.charAt(1) != '0' && text_.toString().charAt(1) != '.') {
            text_ = text_.replace('0',"");
            //dbg console.log(text_);
        }

        return text_;
    }*/
}

