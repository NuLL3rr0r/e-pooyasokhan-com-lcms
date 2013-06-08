import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.0

Rectangle {
    id: loginWindow;
    color: "transparent";
    width: 1;
    height: 1;

    LayoutMirroring.enabled: true
    LayoutMirroring.childrenInherit: true

    property bool isWindowAnimRunning: false;
    property int windowOpenAnimDuration: 750;
    property string windowOpenAnimEasing: Easing.InOutElastic;
    property real windowOpenAnimEasingAmplitude : 2.0;
    property real windowOpenAnimEasingOvershoot: 0.0;
    property real windowOpenAnimEasingPeriod: 2.5;
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


    property bool isFormAnimRunning: false;
    property int formAnimDuration: 500;
    property int formAnimDurationWindow: formAnimDuration / 5;
    property string formAnimEasing: Easing.OutExpo;
    property int formAnimStartWindowX: 0.0;
    property int formAnimStartWindowY: 0.0;
    property int formAnimEndWindowX: 0.0;
    property int formAnimEndWindowY: 0.0;

    function onShown() {
        loginWindow.windowOpenAnimStartWindowX = cppLoginWindow.X;
        loginWindow.windowOpenAnimStartWindowY = cppLoginWindow.Y;
        loginWindow.windowOpenAnimEndWindowX = (((loginWindow.width
                                                  -loginRectangle.parentWidth)
                                                  / 2)
                                                 + cppLoginWindow.X);
        loginWindow.windowOpenAnimEndWindowY = (((loginWindow.height
                                                  - loginRectangle.parentHeight)
                                                  / 2)
                                                 + cppLoginWindow.Y);
        windowOpenAnim.start();
    }

    Component.onCompleted: {
        cppLoginWindow.onSignal_Shown.connect(loginWindow.onShown);
        loginEmailRow.opacity = 0.0;
        loginPwdRow.opacity = 0.0;
        loginButtonsRow1.opacity = 0.0;
        loginButtonsRow2.opacity = 0.0;
        loginButtonsRow3.opacity = 0.0;
        loginRectangle.visible = true;
        loginEmailTextField.focus = false;
    }

    Rectangle {
        id: loginRectangle;
        anchors.centerIn: parent;
        visible: false;

        property int parentWidth: 300;
        property int parentHeight: 220;

        Column {
            anchors.centerIn: parent;
            spacing: 12;

            Row {
                id: loginEmailRow;
                spacing: 8;

                Column {
                    Label {
                        text: "پست الکترونیکی";
                    }
                }

                Column {
                    TextField {
                        id: loginEmailTextField;
                        style: textFieldStyle;
                        width: 165;
                        focus: true;
                    }
                }
            }

            Row {
                id: loginPwdRow;
                spacing: 8;

                Column {
                    Label {
                        text: "کلمه عبور";
                    }
                }

                Column {
                    TextField {
                        id: loginPwdTextField;
                        style: textFieldStyle;
                        width: 165;
                    }
                }
            }

            Row {
                id: loginButtonsRow1;
                spacing: 8;

                Column {
                    spacing: 8;

                    Button {
                        text: "ورود";
                        style: buttonStyle;
                        width: 106;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                            }
                        }
                    }
                }

                Column {
                    spacing: 8;
                    Button {
                        text: "لغو";
                        style: buttonStyle;
                        width: 106;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                            }
                        }
                    }
                }
            }

            Row {
                id: loginButtonsRow2;
                spacing: 8;

                Column {
                    spacing: 8;

                    Button {
                        text: "کلمه عبور را فراموش کرده ام";
                        style: buttonStyle;
                        width: 220;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                                loginWindow.isFormAnimRunning = true;
                                loginWindow.formAnimStartWindowX = cppLoginWindow.X;
                                loginWindow.formAnimStartWindowY = cppLoginWindow.Y;
                                loginWindow.formAnimEndWindowX = (((loginRectangle.parentWidth
                                                                       - forgotRectangle.parentWidth)
                                                                      / 2)
                                                                     + cppLoginWindow.X);
                                loginWindow.formAnimEndWindowY = (((loginRectangle.parentHeight
                                                                       - forgotRectangle.parentHeight)
                                                                      / 2)
                                                                     + cppLoginWindow.Y);;
                                forgotRectangle.opacity = 0.0;
                                forgotRectangle.visible = true;
                                loginToForgotAnim.start();
                            }
                        }
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    id: loginButtonsRow3;
                    spacing: 8;

                    Button {
                        text: "ثبت نام کاربر جدید";
                        style: buttonStyle;
                        width: 220;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                                loginWindow.isFormAnimRunning = true;
                                loginWindow.formAnimStartWindowX = cppLoginWindow.X;
                                loginWindow.formAnimStartWindowY = cppLoginWindow.Y;
                                loginWindow.formAnimEndWindowX = (((loginRectangle.parentWidth
                                                                       - registerRectangle.parentWidth)
                                                                      / 2)
                                                                     + cppLoginWindow.X);
                                loginWindow.formAnimEndWindowY = (((loginRectangle.parentHeight
                                                                       - registerRectangle.parentHeight)
                                                                      / 2)
                                                                     + cppLoginWindow.Y);;
                                registerRectangle.opacity = 0.0;
                                registerRectangle.visible = true;
                                loginToRegisterAnim.start();
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: forgotRectangle;
        anchors.centerIn: parent;
        visible: false;

        property int parentWidth: 300;
        property int parentHeight: 110;

        Column {
            anchors.centerIn: parent;
            spacing: 12;

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "پست الکترونیکی";
                    }
                }

                Column {
                    TextField {
                        id: forgotEmailTextField;
                        style: textFieldStyle;
                        width: 165;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    spacing: 8;

                    Button {
                        text: "بازیابی";
                        style: buttonStyle;
                        width: 106;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                            }
                        }
                    }
                }

                Column {
                    spacing: 8;
                    Button {
                        text: "لغو";
                        style: buttonStyle;
                        width: 106;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                                loginWindow.isFormAnimRunning = true;
                                loginWindow.formAnimStartWindowX = cppLoginWindow.X;
                                loginWindow.formAnimStartWindowY = cppLoginWindow.Y;
                                loginWindow.formAnimEndWindowX = (((forgotRectangle.parentWidth
                                                                       - loginRectangle.parentWidth)
                                                                      / 2)
                                                                     + cppLoginWindow.X);
                                loginWindow.formAnimEndWindowY = (((forgotRectangle.parentHeight
                                                                       - loginRectangle.parentHeight)
                                                                      / 2)
                                                                     + cppLoginWindow.Y);;
                                loginRectangle.opacity = 0.0;
                                loginRectangle.visible = true;
                                forgotToLoginAnim.start();
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: registerRectangle;
        anchors.centerIn: parent;
        visible: false;

        property int parentWidth: 550;
        property int parentHeight: 670;

        Column {
            anchors.centerIn: parent;
            spacing: 12;

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "پست الکترونیکی";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerEmailTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "کلمه عبور";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerPwdTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "تکرار کلمه عبور";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerPwdConfirmTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "نام";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerFirstNameTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "نام خانوادگی";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerLastNameTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "شغل";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerVocationTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "سال تولد";
                        width: 135;
                    }
                }

                Column {
                    ComboBox {
                        id: registerBirthdayComboBox;
                        style: comboBoxStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "میزان و رشته تحصیلات";
                        width: 135;
                    }
                }

                Column {
                    TextArea {
                        id: registerEducationsTextArea;
                        width: 350;
                        height: 95;
                        focus: true;
                        backgroundColor: "#f0f0f0";
                        antialiasing: true;
                        wrapMode: TextEdit.WordWrap;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "شرح سوابق یادگیری";
                        width: 135;
                    }
                }

                Column {
                    TextArea {
                        id: registerLearningExperiencesTextArea;
                        width: 350;
                        height: 95;
                        focus: true;
                        backgroundColor: "#f0f0f0";
                        antialiasing: true;
                        wrapMode: TextEdit.WordWrap;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "فشرده انگلیسی از پایه تا";
                        width: 135;
                    }
                }

                Column {
                    width: 350;

                    ExclusiveGroup {
                        id: registerCourseExclusiveGroup;
                    }

                    Row {
                        RadioButton {
                            id: registerCourseTOEFLRadioButton;
                            exclusiveGroup: registerCourseExclusiveGroup;
                            style: radioButtonStyle;
                            text: "TOEFL";
                            width: 65;
                        }

                        RadioButton {
                            id: registerCourseIELTSRadioButton;
                            exclusiveGroup: registerCourseExclusiveGroup;
                            style: radioButtonStyle;
                            text: "IELTS";
                            width: 65;
                        }
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "طریقه آشنائی با آموزشگاه";
                        width: 135;
                    }
                }

                Column {
                    width: 350;

                    ExclusiveGroup {
                        id: registerAcquaintanceMethodExclusiveGroup;
                    }

                    Row {
                        RadioButton {
                            id: registerAcquaintanceMethodRecommendationRadioButton;
                            exclusiveGroup: registerAcquaintanceMethodExclusiveGroup;
                            style: radioButtonStyle;
                            text: "معرفی";
                            width: 65;
                        }

                        RadioButton {
                            id: registerAcquaintanceMethodAdsEmailRadioButton;
                            exclusiveGroup: registerAcquaintanceMethodExclusiveGroup;
                            style: radioButtonStyle;
                            text: "ایمیل تبلیغاتی";
                            width: 105;
                        }

                        RadioButton {
                            id: registerAcquaintanceMethodPSWebsiteRadioButton;
                            exclusiveGroup: registerAcquaintanceMethodExclusiveGroup;
                            style: radioButtonStyle;
                            text: "وب سایت آموزشگاه";
                            width: 130;
                        }

                        RadioButton {
                            id: registerAcquaintanceMethodOtherRadioButton;
                            exclusiveGroup: registerAcquaintanceMethodExclusiveGroup;
                            style: radioButtonStyle;
                            text: "سایر";
                            width: 60;
                        }
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "استان";
                        width: 135;
                    }
                }

                Column {
                    ComboBox {
                        id: registerProvinceComboBox;
                        style: comboBoxStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "تلفن منزل";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerPhoneTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }

            Row {
                spacing: 8;

                Column {
                    Label {
                        text: "تلفن همراه";
                        width: 135;
                    }
                }

                Column {
                    TextField {
                        id: registerMobileTextField;
                        style: textFieldStyle;
                        width: 350;
                        focus: true;
                    }
                }
            }


            Row {
                spacing: 8;

                Column {
                    spacing: 8;

                    Button {
                        text: "ثبت نام";
                        style: buttonStyle;
                        width: 106;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                            }
                        }
                    }
                }

                Column {
                    spacing: 8;
                    Button {
                        text: "لغو";
                        style: buttonStyle;
                        width: 106;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                                loginWindow.isFormAnimRunning = true;
                                loginWindow.formAnimStartWindowX = cppLoginWindow.X;
                                loginWindow.formAnimStartWindowY = cppLoginWindow.Y;
                                loginWindow.formAnimEndWindowX = (((registerRectangle.parentWidth
                                                                       - loginRectangle.parentWidth)
                                                                      / 2)
                                                                     + cppLoginWindow.X);
                                loginWindow.formAnimEndWindowY = (((registerRectangle.parentHeight
                                                                       - loginRectangle.parentHeight)
                                                                      / 2)
                                                                     + cppLoginWindow.Y);;
                                loginRectangle.opacity = 0.0;
                                loginRectangle.visible = true;
                                registerToLoginAnim.start();
                            }
                        }
                    }
                }
            }
        }
    }

    property Component buttonStyle: ButtonStyle {
        id: buttonStyle;
        background: Rectangle {
            implicitHeight: 20;
            implicitWidth: 100;
            color: control.pressed ? "darkGray" : "lightGray";
            antialiasing: true;
            border.color: "gray";
            radius: height / 4;
        }
    }

    property Component textFieldStyle: TextFieldStyle {
        background: Rectangle {
            implicitWidth: 100;
            implicitHeight: 20;
            color: "#f0f0f0";
            antialiasing: true;
            border.color: "gray";
            radius: height / 4;
        }
    }

    property Component comboBoxStyle: ComboBoxStyle {
        background: Rectangle {
            implicitWidth: 100;
            implicitHeight: 20;
            color: "#f0f0f0";
            antialiasing: true;
            border.color: "gray";
            radius: height / 4;
        }
    }

    property Component radioButtonStyle: RadioButtonStyle {
    }

    SequentialAnimation {
        id: windowOpenAnim;

        ParallelAnimation {
            NumberAnimation {
                target: cppLoginWindow;
                property: "X";
                from: loginWindow.windowOpenAnimStartWindowX;
                to: loginWindow.windowOpenAnimEndWindowX;
                duration: loginWindow.windowOpenAnimDuration;
                easing.type: loginWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }

            NumberAnimation {
                target: cppLoginWindow;
                property: "Y";
                from: loginWindow.windowOpenAnimStartWindowY;
                to: loginWindow.windowOpenAnimEndWindowY;
                duration: loginWindow.windowOpenAnimDuration;
                easing.type: loginWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }

            NumberAnimation {
                target: loginWindow;
                property: "width";
                from: loginWindow.width;
                to: loginRectangle.parentWidth;
                duration: loginWindow.windowOpenAnimDuration;
                easing.type: loginWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }

            NumberAnimation {
                target: loginWindow;
                property: "height";
                from: loginWindow.height;
                to: loginRectangle.parentHeight;
                duration: loginWindow.windowOpenAnimDuration;
                easing.type: loginWindow.windowOpenAnimEasing;
                easing.amplitude: windowOpenAnimEasingAmplitude;
                easing.period: windowOpenAnimEasingPeriod;
                easing.overshoot: windowOpenAnimEasingOvershoot;
            }
        }

        SequentialAnimation {
            PropertyAnimation {
                target: loginEmailRow;
                property: "opacity";
                from: 0.0;
                to: 1.0;
                duration: loginWindow.windowOpenContentAnimDuration;
                easing.type: loginWindow.windowOpenContentAnimEasing;
                easing.amplitude: windowOpenContentAnimEasingAmplitude;
                easing.overshoot: windowOpenContentAnimEasingOvershoot;
                easing.period: windowOpenContentAnimEasingPeriod;
            }

            PropertyAnimation {
                target: loginPwdRow;
                property: "opacity";
                from: 0.0;
                to: 1.0;
                duration: loginWindow.windowOpenContentAnimDuration;
                easing.type: loginWindow.windowOpenContentAnimEasing;
                easing.amplitude: windowOpenContentAnimEasingAmplitude;
                easing.overshoot: windowOpenContentAnimEasingOvershoot;
                easing.period: windowOpenContentAnimEasingPeriod;
            }

            PropertyAnimation {
                target: loginButtonsRow1;
                property: "opacity";
                from: 0.0;
                to: 1.0;
                duration: loginWindow.windowOpenContentAnimDuration;
                easing.type: loginWindow.windowOpenContentAnimEasing;
                easing.amplitude: windowOpenContentAnimEasingAmplitude;
                easing.overshoot: windowOpenContentAnimEasingOvershoot;
                easing.period: windowOpenContentAnimEasingPeriod;
            }

            PropertyAnimation {
                target: loginButtonsRow2;
                property: "opacity";
                from: 0.0;
                to: 1.0;
                duration: loginWindow.windowOpenContentAnimDuration;
                easing.type: loginWindow.windowOpenContentAnimEasing;
                easing.amplitude: windowOpenContentAnimEasingAmplitude;
                easing.overshoot: windowOpenContentAnimEasingOvershoot;
                easing.period: windowOpenContentAnimEasingPeriod;
            }

            PropertyAnimation {
                target: loginButtonsRow3;
                property: "opacity";
                from: 0.0;
                to: 1.0;
                duration: loginWindow.windowOpenContentAnimDuration;
                easing.type: loginWindow.windowOpenContentAnimEasing;
                easing.amplitude: windowOpenContentAnimEasingAmplitude;
                easing.overshoot: windowOpenContentAnimEasingOvershoot;
                easing.period: windowOpenContentAnimEasingPeriod;
            }

            PropertyAnimation {
                target: loginEmailRow;
                property: "opacity";
                from: 0.3;
                to: 1.0;
                duration: loginWindow.windowOpenContentFocusAnimDuration;
                easing.type: loginWindow.windowOpenContentFocusAnimEasing;
                easing.amplitude: windowOpenContentFocusAnimEasingAmplitude;
                easing.overshoot: windowOpenContentFocusAnimEasingOvershoot;
                easing.period: windowOpenContentFocusAnimEasingPeriod;
            }
        }

        onRunningChanged: {
            if (!windowOpenAnim.running) {
                loginEmailTextField.selectAll();
                loginEmailTextField.focus = true;
            }
        }
    }


    ParallelAnimation {
        id: loginToForgotAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: forgotRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: forgotRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: forgotRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "X";
            from: loginWindow.formAnimStartWindowX;
            to: loginWindow.formAnimEndWindowX;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "Y";
            from: loginWindow.formAnimStartWindowY;
            to: loginWindow.formAnimEndWindowY;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        onRunningChanged: {
            if (!loginToForgotAnim.running) {
                loginRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
                forgotEmailTextField.selectAll();
                forgotEmailTextField.focus = true;
            }
        }
    }

    ParallelAnimation {
        id: loginToRegisterAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: registerRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: registerRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: registerRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "X";
            from: loginWindow.formAnimStartWindowX;
            to: loginWindow.formAnimEndWindowX;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "Y";
            from: loginWindow.formAnimStartWindowY;
            to: loginWindow.formAnimEndWindowY;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        onRunningChanged: {
            if (!loginToRegisterAnim.running) {
                loginRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
                registerEmailTextField.selectAll();
                registerEmailTextField.focus = true;
            }
        }
    }

    ParallelAnimation {
        id: forgotToLoginAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: loginRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: loginRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
        }

        PropertyAnimation {
            target: forgotRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "X";
            from: loginWindow.formAnimStartWindowX;
            to: loginWindow.formAnimEndWindowX;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "Y";
            from: loginWindow.formAnimStartWindowY;
            to: loginWindow.formAnimEndWindowY;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        onRunningChanged: {
            if (!forgotToLoginAnim.running) {
                forgotRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
                loginEmailTextField.selectAll();
                loginEmailTextField.focus = true;
            }
        }
    }

    ParallelAnimation {
        id: registerToLoginAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: loginRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: loginRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: registerRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "X";
            from: loginWindow.formAnimStartWindowX;
            to: loginWindow.formAnimEndWindowX;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        NumberAnimation {
            target: cppLoginWindow;
            property: "Y";
            from: loginWindow.formAnimStartWindowY;
            to: loginWindow.formAnimEndWindowY;
            duration: loginWindow.formAnimDurationWindow;
            easing.type: loginWindow.formAnimEasing;
        }

        onRunningChanged: {
            if (!registerToLoginAnim.running) {
                registerRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
                loginEmailTextField.selectAll();
                loginEmailTextField.focus = true;
            }
        }
    }
}

