import QtQuick 2.0;

Rectangle {
    width: 570;
    height: 328;
    color: "transparent";

    Image {
        source: "splashscreen.png";
        asynchronous: true;
        cache: true;
        smooth: true;
        anchors.centerIn: parent;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
    }
}
