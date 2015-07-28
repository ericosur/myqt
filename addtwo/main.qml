import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.pega.rasmus 1.0

ApplicationWindow {
    id: mainwindow
    title: qsTr("Hello World") + trans.empty
    width: 640
    height: 480
    visible: true

    MyTranslation {
        id: trans;
    }

    // between min (inclusive) and max (exclusive)
    function getRandom(min, max)  {
        return Math.random() * (max - min) + min;
    }

    // not good
    function getRandomCeil(min, max)  {
        return Math.ceil(Math.random() * (max - min)) + min - 1;
    }

    function myAdd(x, y) {
        return x+y;
    }

    MainForm {
        anchors.fill: parent

        function myInit() {
            textInput1.text = getRandomCeil(1, 9999);
            textInput2.text = getRandomCeil(1, 9999);
        }

        Component.onCompleted: {
            myInit();
            // show system locale name at title
            textArea1.append('system locale: ' + Qt.locale().name);
        }

        buttonInit.onClicked: {
            myInit();
            textArea1.append(qsTr("lorem"))
        }

        button1.onClicked: {
            var val1 = parseInt(textInput1.text);
            var val2 = parseInt(textInput2.text);
            var str = textInput1.text + '+' + textInput2.text;
            textArea1.append(str);
            textArea1.append(myAdd(val1, val2));
        }

        button2.onClicked: {
            var val1 = parseInt(textInput1.text);
            var val2 = parseInt(textInput2.text);
            var str = val1 + '* sin(' + val2 + ')';
            textArea1.append(str);
            var res = val1 * Math.sin(val2);
            textArea1.append(res);
        }

        button3.onClicked: {
            var val1 = parseInt(textInput1.text);
            var val2 = parseInt(textInput2.text);
            var str = val1 + '* cos(' + val2 + ')';
            textArea1.append(str);
            var res = val1 * Math.cos(val2);
            textArea1.append(res);
        }

        comboBox1.onCurrentIndexChanged: {
            if (comboBox1.currentText) {
                //textArea1.append(comboBox1.currentText + comboBox1.currentIndex.toString());
                //textArea1.append(comboBox1.model.get(comboBox1.currentIndex).loc);
                //textArea1.append(comboBox1.model.get(0).loc);  // if access via 'var'
                trans.selectLanguage( comboBox1.model.get(comboBox1.currentIndex).loc );
                //messageDialog.show('set to ' + comboBox1.currentText, qsTr("May I have your attention, please?"));
                textArea1.append(qsTr("May I have your attention, please?"));
            }
        }

    }

    MessageDialog {
        id: messageDialog
        //title: 'title'

        function show(inn, cap) {
            messageDialog.text = inn;
            messageDialog.title = cap;
            messageDialog.open();
        }
    }
}
