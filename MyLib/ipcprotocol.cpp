#include "ipcprotocol.hpp"

using namespace std;
using namespace  MyLib;

const IPCProtocol::RequestHash_t RequestToString =
        boost::assign::map_list_of
        (IPCProtocol::Request::HandShake, "HandShake")
        (IPCProtocol::Request::LatestDesktopClientVersion, "LatestDesktopClientVersion")
        (IPCProtocol::Request::Login, "Login")
        (IPCProtocol::Request::PasswordChange, "PasswordChange")
        (IPCProtocol::Request::Login, "Login")
        (IPCProtocol::Request::PasswordRecovery, "PasswordRecovery")
        (IPCProtocol::Request::Registeration, "Registeration");

const IPCProtocol::HandShakeRequestArgHash_t HandShakeRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::HandShakeRequestArg::IP, "IP");

const IPCProtocol::HandShakeResponseStatusHash_t HandShakeResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::HandShakeResponseStatus::OK, "OK")
        (IPCProtocol::HandShakeResponseStatus::ProtocolTooOld, "ProtocolTooOld")
        (IPCProtocol::HandShakeResponseStatus::InvalidProtocol, "InvalidProtocol");

const IPCProtocol::LatestDesktopClientVersionRequestArgHash_t LatestDesktopClientVersionRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::LatestDesktopClientVersionRequestArg::IP, "IP");

const IPCProtocol::LatestDesktopClientVersionResponseArgHash_t LatestDesktopClientVersionResponseArgToString =
        boost::assign::map_list_of
        (IPCProtocol::LatestDesktopClientVersionResponseArg::Version, "Version")
        (IPCProtocol::LatestDesktopClientVersionResponseArg::VersionMajor, "VersionMajor")
        (IPCProtocol::LatestDesktopClientVersionResponseArg::VersionMinor, "VersionMinor")
        (IPCProtocol::LatestDesktopClientVersionResponseArg::VersionPatch, "VersionPatch")
        (IPCProtocol::LatestDesktopClientVersionResponseArg::VersionRevision, "VersionRevision");

const IPCProtocol::LatestDesktopClientVersionResponseStatusHash_t LatestDesktopClientVersionResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::LatestDesktopClientVersionResponseStatus::OK, "OK");

const IPCProtocol::LoginRequestArgHash_t LoginRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::LoginRequestArg::IP, "IP")
        (IPCProtocol::LoginRequestArg::Username, "Username")
        (IPCProtocol::LoginRequestArg::Password, "Password");

const IPCProtocol::LoginResponseStatusHash_t LoginResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::LoginResponseStatus::OK, "OK")
        (IPCProtocol::LoginResponseStatus::InvalidUserPwd, "InvalidUserPwd");

const IPCProtocol::PasswordChangeRequestArgHash_t PasswordChangeRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::PasswordChangeRequestArg::CurrentPassword, "CurrentPassword")
        (IPCProtocol::PasswordChangeRequestArg::NewPassowrd, "NewPassowrd");

const IPCProtocol::PasswordChangeResponseStatusHash_t PasswordChangeResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::PasswordChangeResponseStatus::OK, "OK")
        (IPCProtocol::PasswordChangeResponseStatus::InvalidCurrentPwd, "InvalidCurrentPwd");

const IPCProtocol::PasswordRecoveryRequestArgHash_t PasswordRecoveryRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::PasswordRecoveryRequestArg::IP, "IP")
        (IPCProtocol::PasswordRecoveryRequestArg::Username, "Username");

const IPCProtocol::PasswordRecoveryResponseStatusHash_t PasswordRecoveryResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::PasswordRecoveryResponseStatus::OK, "OK")
        (IPCProtocol::PasswordRecoveryResponseStatus::InvalidUser, "InvalidUser");

const IPCProtocol::RegisterationRequestArgHash_t RegisterationRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::RegisterationRequestArg::IP, "IP")
        (IPCProtocol::RegisterationRequestArg::Username, "Username")
        (IPCProtocol::RegisterationRequestArg::Password, "Password")
        (IPCProtocol::RegisterationRequestArg::FirstName, "FirstName")
        (IPCProtocol::RegisterationRequestArg::LastName, "LastName")
        (IPCProtocol::RegisterationRequestArg::Vocation, "Vocation")
        (IPCProtocol::RegisterationRequestArg::Birthday, "Birthday")
        (IPCProtocol::RegisterationRequestArg::Educations, "Educations")
        (IPCProtocol::RegisterationRequestArg::LearningExperiences, "LearningExperiences")
        (IPCProtocol::RegisterationRequestArg::Course, "Course")
        (IPCProtocol::RegisterationRequestArg::AcquaintanceMethod, "AcquaintanceMethod")
        (IPCProtocol::RegisterationRequestArg::Province, "Province")
        (IPCProtocol::RegisterationRequestArg::Phone, "Phone")
        (IPCProtocol::RegisterationRequestArg::Mobile, "Mobile");

const IPCProtocol::RegisterationResponseStatusHash_t RegisterationResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::RegisterationResponseStatus::OK, "OK")
        (IPCProtocol::RegisterationResponseStatus::InvalidData, "InvalidData");

std::string IPCProtocol::Name()
{
    return IPC_PROTOCOL_NAME;
}

std::string IPCProtocol::Version()
{
    return IPC_PROTOCOL_VERSION;
}

unsigned char IPCProtocol::VersionMajor()
{
    return IPC_PROTOCOL_VERSION_MAJOR;
}

unsigned char IPCProtocol::NameMinor()
{
    return IPC_PROTOCOL_VERSION_MINOR;
}

