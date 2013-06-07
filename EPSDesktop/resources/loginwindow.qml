import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.0

Rectangle {
    id: loginWindow;
    color: "transparent";
    width: 300;
    height: 220;

    LayoutMirroring.enabled: true
    LayoutMirroring.childrenInherit: true

    property bool isFormAnimRunning: false;
    property double formAnimDuration: 500.0;
    property string formAnimEasingFade: Easing.InBack;
    property string formAnimEasingScale: Easing.OutExpo;

    Component.onCompleted: {
        loginRectangle.visible = true;
        loginEmailTextField.focus = true;
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
                    spacing: 8;

                    Button {
                        text: "ثبت نام کاربر جدید";
                        style: buttonStyle;
                        width: 220;

                        onClicked: {
                            if (!loginWindow.isFormAnimRunning) {
                                loginWindow.isFormAnimRunning = true;
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

    ParallelAnimation{
        id: loginToForgotAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: forgotRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: forgotRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        PropertyAnimation {
            target: forgotRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        onRunningChanged: {
            if (!loginToForgotAnim.running) {
                loginRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
            }
        }
    }

    ParallelAnimation{
        id: loginToRegisterAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: registerRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: registerRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        PropertyAnimation {
            target: registerRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        onRunningChanged: {
            if (!loginToRegisterAnim.running) {
                loginRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
            }
        }
    }

    ParallelAnimation{
        id: forgotToLoginAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: loginRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: loginRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: forgotRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        onRunningChanged: {
            if (!forgotToLoginAnim.running) {
                forgotRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
            }
        }
    }

    ParallelAnimation{
        id: registerToLoginAnim;

        PropertyAnimation {
            target: loginWindow;
            property: "width";
            from: loginWindow.width;
            to: loginRectangle.parentWidth;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: loginWindow;
            property: "height";
            from: loginWindow.height;
            to: loginRectangle.parentHeight;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingScale;
        }

        PropertyAnimation {
            target: registerRectangle;
            property: "opacity";
            from: 1.0;
            to: 0.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        PropertyAnimation {
            target: loginRectangle;
            property: "opacity";
            from: 0.0;
            to: 1.0;
            duration: loginWindow.formAnimDuration;
            easing.type: loginWindow.formAnimEasingFade;
        }

        onRunningChanged: {
            if (!registerToLoginAnim.running) {
                registerRectangle.visible = false;
                loginWindow.isFormAnimRunning = false;
            }
        }
    }
}

