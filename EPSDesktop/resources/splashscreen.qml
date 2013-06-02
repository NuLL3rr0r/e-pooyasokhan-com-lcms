import QtQuick 2.0;
import QtGraphicalEffects 1.0;

Rectangle {
    signal signal_SplashScreenPoppedUp();
    signal signal_SplashScreenTimedOut();

    width: 570;
    height: 328;
    color: "transparent";

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
                //showTimer.start();
                signal_SplashScreenPoppedUp();
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
                signal_SplashScreenTimedOut();
            }
        }
    }

    Component.onCompleted: {
        blurInAnim.start();
    }

    Timer {
        id: showTimer;
        interval: 2500;
        running: false;
        repeat: false;

        onTriggered: {
            showTimer.stop();
            blurOutAnim.start();
        }
    }
}

