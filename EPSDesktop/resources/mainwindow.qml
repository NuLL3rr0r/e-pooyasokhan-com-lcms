import QtQuick 2.1

Rectangle {
    id: mainWindow;
    color: "transparent";
    width: 1;
    height: 1;

    LayoutMirroring.enabled: true
    LayoutMirroring.childrenInherit: true

    property bool isAnAnimRunning: false;

    property int windowOpenAnimDuration: 750;
    property string windowOpenAnimEasing: Easing.InOutElastic;
    property real windowOpenAnimEasingAmplitude : 2.0;
    property real windowOpenAnimEasingOvershoot: 0.0;
    property real windowOpenAnimEasingPeriod: 2.5;
    property int windowOpenAnimTargetWidth: 0.0;
    property int windowOpenAnimTargetHeight: 0.0;
    property int windowOpenAnimStartWindowX: 0.0;
    property int windowOpenAnimStartWindowY: 0.0;
    property int windowOpenAnimEndWindowX: 0.0;
    property int windowOpenAnimEndWindowY: 0.0;
    property int windowOpenContentAnimDuration: 200;
    property string windowOpenContentAnimEasing: Easing.InCirc;
    property real windowOpenContentAnimEasingAmplitude: 0.0;
    property real windowOpenContentAnimEasingOvershoot: 0.0;
    property real windowOpenContentAnimEasingPeriod: 0.0;
    property int windowOpenContentFocusAnimDuration: 350;
    property string windowOpenContentFocusAnimEasing: Easing.OutBounce;
    property real windowOpenContentFocusAnimEasingAmplitude: 2.75;
    property real windowOpenContentFocusAnimEasingOvershoot: 0.0;
    property real windowOpenContentFocusAnimEasingPeriod: 0.0;

    property int windowCloseAnimDuration: 650;
    property string windowCloseAnimEasing: Easing.InOutElastic;
    property real windowCloseAnimEasingAmplitude : 2.0;
    property real windowCloseAnimEasingOvershoot: 0.0;
    property real windowCloseAnimEasingPeriod: 2.5;
    property int windowCloseAnimStartWindowX: 0.0;
    property int windowCloseAnimStartWindowY: 0.0;
    property int windowCloseAnimEndWindowX: 0.0;
    property int windowCloseAnimEndWindowY: 0.0;
    property int windowCloseContentAnimDuration: 100;
    property string windowCloseContentAnimEasing: Easing.OutBack;
    property real windowCloseContentAnimEasingAmplitude: 0.0;
    property real windowCloseContentAnimEasingOvershoot: 0.0;
    property real windowCloseContentAnimEasingPeriod: 0.0;

    signal signal_closed();

    function onShown() {
        if (!mainWindow.isAnAnimRunning) {
            mainWindow.isAnAnimRunning = true;
            mainWindow.windowOpenAnimStartWindowX = cppMainWindow.X;
            mainWindow.windowOpenAnimStartWindowY = cppMainWindow.Y;
            mainWindow.windowOpenAnimEndWindowX = 0;
            mainWindow.windowOpenAnimEndWindowY = 0;
            mainWindow.windowOpenAnimTargetWidth = cppMainWindow.GetScreenWidth();
            mainWindow.windowOpenAnimTargetHeight = cppMainWindow.GetScreenHeight();
            windowOpenAnim.start();
        }
    }

    Component.onCompleted: {
        cppMainWindow.onSignal_Shown.connect(mainWindow.onShown);
    }

    SequentialAnimation {
        id: windowOpenAnim;

        ParallelAnimation {
            NumberAnimation {
                target: cppMainWindow;
                property: "X";
                from: mainWindow.windowOpenAnimStartWindowX;
                to: mainWindow.windowOpenAnimEndWindowX;
                duration: mainWindow.windowOpenAnimDuration;
                easing.type: mainWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }

            NumberAnimation {
                target: cppMainWindow;
                property: "Y";
                from: mainWindow.windowOpenAnimStartWindowY;
                to: mainWindow.windowOpenAnimEndWindowY;
                duration: mainWindow.windowOpenAnimDuration;
                easing.type: mainWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }

            NumberAnimation {
                target: mainWindow;
                property: "width";
                from: mainWindow.width;
                to: mainWindow.windowOpenAnimTargetWidth;
                duration: mainWindow.windowOpenAnimDuration;
                easing.type: mainWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }

            NumberAnimation {
                target: mainWindow;
                property: "height";
                from: mainWindow.height;
                to: mainWindow.windowOpenAnimTargetHeight;
                duration: mainWindow.windowOpenAnimDuration;
                easing.type: mainWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }
        }

        SequentialAnimation {
        }

        onRunningChanged: {
            if (!windowOpenAnim.running) {
                loginEmailTextField.selectAll();
                loginEmailTextField.focus = true;
                mainWindow.isAnAnimRunning = false;
            }
        }
    }

    SequentialAnimation {
        id: windowCloseAnim;

        SequentialAnimation {
        }

        ParallelAnimation {
            NumberAnimation {
                target: cppMainWindow;
                property: "X";
                from: mainWindow.windowCloseAnimStartWindowX;
                to: mainWindow.windowCloseAnimEndWindowX;
                duration: mainWindow.windowCloseAnimDuration;
                easing.type: mainWindow.windowCloseAnimEasing;
                easing.amplitude: windowCloseAnimEasingAmplitude;
                easing.period: windowCloseAnimEasingPeriod;
                easing.overshoot: windowCloseAnimEasingOvershoot;
            }

            NumberAnimation {
                target: cppMainWindow;
                property: "Y";
                from: mainWindow.windowCloseAnimStartWindowY;
                to: mainWindow.windowCloseAnimEndWindowY;
                duration: mainWindow.windowCloseAnimDuration;
                easing.type: mainWindow.windowCloseAnimEasing;
                easing.amplitude: windowCloseAnimEasingAmplitude;
                easing.period: windowCloseAnimEasingPeriod;
                easing.overshoot: windowCloseAnimEasingOvershoot;
            }

            NumberAnimation {
                target: mainWindow;
                property: "width";
                from: mainWindow.width;
                to: 1;
                duration: mainWindow.windowCloseAnimDuration;
                easing.type: mainWindow.windowCloseAnimEasing;
                easing.amplitude: windowCloseAnimEasingAmplitude;
                easing.period: windowCloseAnimEasingPeriod;
                easing.overshoot: windowCloseAnimEasingOvershoot;
            }

            NumberAnimation {
                target: mainWindow;
                property: "height";
                from: mainWindow.height;
                to: 1;
                duration: mainWindow.windowCloseAnimDuration;
                easing.type: mainWindow.windowCloseAnimEasing;
                easing.amplitude: windowCloseAnimEasingAmplitude;
                easing.period: windowCloseAnimEasingPeriod;
                easing.overshoot: windowCloseAnimEasingOvershoot;
            }
        }

        onRunningChanged: {
            if (!windowCloseAnim.running) {
                signal_closed();
                mainWindow.isAnAnimRunning = false;
            }
        }
    }
}

