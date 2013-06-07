import QtQuick 2.1;
import QtGraphicalEffects 1.0;

Rectangle {
    id : splashScreen;
    color: "transparent";
    width: 570;
    height: 328;

    property bool isClosing: false;
    property int passedSecondsSinceShown: 0;

    signal signal_splashScreenPoppedUp();
    signal signal_splashScreenTimedOut();

    function onClosing() {
        splashScreen.isClosing = true;
    }

    Component.onCompleted: {
        cppSplashScreen.onSignal_Closing.connect(splashScreen.onClosing);
        blurInAnim.start();
    }

    Image {
        id: splashImage;
        source: "splashscreen.png";
        asynchronous: true;
        cache: true;
        smooth: true;
        anchors.centerIn: parent;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        visible: false;
    }

    FastBlur {
        id: splashBlur;
        anchors.fill: splashImage;
        source: splashImage;
        radius: 150.0;
        cached: false;
    }

    PropertyAnimation {
        id: blurInAnim;
        target: splashBlur;
        property: "radius";
        to: 0.0;
        duration: 1500.0;
        easing.type: Easing.OutQuint;

        onRunningChanged: {
            if (!blurInAnim.running) {
                showTimer.start();
                signal_splashScreenPoppedUp();
            }
        }
    }

    PropertyAnimation {
        id: blurOutAnim;
        target: splashBlur;
        property: "radius";
        to: 150.0;
        duration: 1500.0;
        easing.type: Easing.InQuint;

        onRunningChanged: {
            if (!blurOutAnim.running) {
                signal_splashScreenTimedOut();
            }
        }
    }

    Timer {
        id: showTimer;
        interval: 100;
        running: false;
        repeat: true;

        onTriggered: {
            splashScreen.passedSecondsSinceShown += 100;
            if (splashScreen.passedSecondsSinceShown >= 2500) {
                if (splashScreen.isClosing) {
                    showTimer.stop();
                    blurOutAnim.start();
                }
            }
        }
    }
}

