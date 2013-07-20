import QtQuick 2.1;

Rectangle {
    id: rootObject;
    color: "transparent";
    width: 256;
    height: 30;

    property bool isStopped: false;

    function onStarted() {
        rootObject.isStopped = false;
        loadingAnimation.start();
    }

    function onStopped() {
        rootObject.isStopped = true;
        loadingAnimation.stop();
    }

    Component.onCompleted: {
        cppLoading.onSignal_Started.connect(rootObject.onStarted);
        cppLoading.onSignal_Stopped.connect(rootObject.onStopped);
    }

    AnimatedImage {
        id: loadingAnimatedImage;
        width: 24;
        height: 24;
        anchors.verticalCenter: parent.verticalCenter;
        source: "pacman.gif";

        transform: Rotation {
            id: loadingAnimatedImageRotation;
            origin.x: loadingAnimatedImage.width / 2.0;
            origin.y: loadingAnimatedImage.height / 2.0;
            axis {
                x: 0;
                y: 1;
                z: 0;
            }
            angle: 0;
        }
    }

    SequentialAnimation {
        id: loadingAnimation;

        PropertyAnimation {
            target: loadingAnimatedImage;
            property: "x";
            from: loadingAnimatedImage.width;
            to: rootObject.width - (loadingAnimatedImage.width * 2);
            duration: 1500;
            easing.type: Easing.OutBack;
        }

        PropertyAnimation {
            target: loadingAnimatedImageRotation;
            property: "angle";
            from: 0;
            to: 180;
            duration: 150;
            easing.type: Easing.InQuint;
        }

        PropertyAnimation {
            target: loadingAnimatedImage;
            property: "x";
            from: rootObject.width - (loadingAnimatedImage.width * 2);
            to: loadingAnimatedImage.width;
            duration: 1500;
            easing.type: Easing.OutBack;
        }

        PropertyAnimation {
            target: loadingAnimatedImageRotation;
            property: "angle";
            from: 180;
            to: 0;
            duration: 150;
            easing.type: Easing.InQuint;
        }

        onRunningChanged: {
            if (!loadingAnimation.running) {
                if (!rootObject.isStopped) {
                    loadingAnimation.start();
                }
            }
        }
    }
}

