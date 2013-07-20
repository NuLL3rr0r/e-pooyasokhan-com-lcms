#include <boost/property_tree/json_parser.hpp>
#include "crypto.hpp"
#include "ipcprotocol.hpp"
#include "log.hpp"

using namespace std;
using namespace  MyLib;

const IPCProtocol::RequestToString_t IPCProtocol::RequestToString =
        boost::assign::map_list_of
        (IPCProtocol::Request::HandShake, "HandShake")
        (IPCProtocol::Request::LatestDesktopClientVersion, "LatestDesktopClientVersion")
        /*(IPCProtocol::Request::Login, "Login")
        (IPCProtocol::Request::PasswordChange, "PasswordChange")
        (IPCProtocol::Request::Login, "Login")
        (IPCProtocol::Request::PasswordRecovery, "PasswordRecovery")
        (IPCProtocol::Request::Registeration, "Registeration")*/;
const IPCProtocol::RequestToEnum_t IPCProtocol::RequestToEnum =
        boost::assign::map_list_of
        ("HandShake", IPCProtocol::Request::HandShake)
        ("LatestDesktopClientVersion", IPCProtocol::Request::LatestDesktopClientVersion)
        /*("Login", IPCProtocol::Request::Login,)
        ("PasswordChange", IPCProtocol::Request::PasswordChange)
        ("Login", IPCProtocol::Request::Login)
        ("PasswordRecovery", IPCProtocol::Request::PasswordRecovery)
        ("Registeration", IPCProtocol::Request::Registeration)*/;

const IPCProtocol::RequestArg::CommonToString_t IPCProtocol::CommonRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::RequestArg::Common::Void, "Void")
        ;
const IPCProtocol::RequestArg::CommonToEnum_t IPCProtocol::CommonRequestArgToEnum =
        boost::assign::map_list_of
        ("Void", IPCProtocol::RequestArg::Common::Void)
        ;

const IPCProtocol::RequestArg::HandShakeToString_t IPCProtocol::HandShakeRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::RequestArg::HandShake::IP, "IP")
        ;
const IPCProtocol::RequestArg::HandShakeToEnum_t IPCProtocol::HandShakeRequestArgToEnum =
        boost::assign::map_list_of
        ("IP", IPCProtocol::RequestArg::HandShake::IP)
        ;

const IPCProtocol::RequestArg::LatestDesktopClientVersionToString_t
IPCProtocol::LatestDesktopClientVersionRequestArgToString =
        boost::assign::map_list_of
        (IPCProtocol::RequestArg::LatestDesktopClientVersion::IP, "IP")
        ;
const IPCProtocol::RequestArg::LatestDesktopClientVersionToEnum_t
IPCProtocol::LatestDesktopClientVersionRequestArgToEnum =
        boost::assign::map_list_of
        ("IP", IPCProtocol::RequestArg::LatestDesktopClientVersion::IP)
        ;

const IPCProtocol::ResponseStatus::CommonToString_t IPCProtocol::CommonResponseStatusToString =
        boost::assign::map_list_of
        (IPCProtocol::ResponseStatus::Common::InvalidProtocol, "InvalidProtocol")
        (IPCProtocol::ResponseStatus::Common::InvalidProtocolVersion, "InvalidProtocolVersion")
        (IPCProtocol::ResponseStatus::Common::ExpiredProtocolVersion, "ExpiredProtocolVersion")
        (IPCProtocol::ResponseStatus::Common::OK, "OK")
        ;
const IPCProtocol::ResponseStatus::CommonToEnum_t IPCProtocol::CommonResponseStatusToEnum =
        boost::assign::map_list_of
        ("InvalidProtocol", IPCProtocol::ResponseStatus::Common::InvalidProtocol)
        ("InvalidProtocolVersion", IPCProtocol::ResponseStatus::Common::InvalidProtocolVersion)
        ("ExpiredProtocolVersion", IPCProtocol::ResponseStatus::Common::ExpiredProtocolVersion)
        ("OK", IPCProtocol::ResponseStatus::Common::OK)
        ;

const IPCProtocol::ResponseArg::CommonToString_t IPCProtocol::CommonResponseArgToString =
        boost::assign::map_list_of
        (IPCProtocol::ResponseArg::Common::Void, "Void")
        ;
const IPCProtocol::ResponseArg::CommonToEnum_t IPCProtocol::CommonResponseArgToEnum =
        boost::assign::map_list_of
        ("Void", IPCProtocol::ResponseArg::Common::Void)
        ;

const IPCProtocol::ResponseArg::LatestDesktopClientVersionToString_t
IPCProtocol::LatestDesktopClientVersionResponseArgToString =
        boost::assign::map_list_of
        (IPCProtocol::ResponseArg::LatestDesktopClientVersion::String, "String")
        (IPCProtocol::ResponseArg::LatestDesktopClientVersion::Major, "Major")
        (IPCProtocol::ResponseArg::LatestDesktopClientVersion::Minor, "Minor")
        (IPCProtocol::ResponseArg::LatestDesktopClientVersion::Patch, "Patch")
        (IPCProtocol::ResponseArg::LatestDesktopClientVersion::Revision, "Revision")
        ;
const IPCProtocol::ResponseArg::LatestDesktopClientVersionToEnum_t
IPCProtocol::LatestDesktopClientVersionResponseArgToEnum =
        boost::assign::map_list_of
        ("String", IPCProtocol::ResponseArg::LatestDesktopClientVersion::String)
        ("Major", IPCProtocol::ResponseArg::LatestDesktopClientVersion::Major)
        ("Minor", IPCProtocol::ResponseArg::LatestDesktopClientVersion::Minor)
        ("Patch", IPCProtocol::ResponseArg::LatestDesktopClientVersion::Patch)
        ("Revision", IPCProtocol::ResponseArg::LatestDesktopClientVersion::Revision)
        ;

std::string IPCProtocol::Name()
{
    return IPC_PROTOCOL_NAME;
}

std::string IPCProtocol::Version()
{
    return IPC_PROTOCOL_VERSION;
}

IPCProtocol::Version_t IPCProtocol::VersionMajor()
{
    return IPC_PROTOCOL_VERSION_MAJOR;
}

IPCProtocol::Version_t IPCProtocol::VersionMinor()
{
    return IPC_PROTOCOL_VERSION_MINOR;
}

void IPCProtocol::GetMessage(const std::string &message, boost::property_tree::ptree &out_tree)
{
    out_tree.clear();
    std::string decrypted;
    Crypto::Decrypt(message, decrypted);

    std::string json;
    Compression::CompressionBuffer_t buffer(decrypted.begin(), decrypted.end());
    Compression::Decompress(buffer, json);

    std::stringstream stream;
    stream << json;
    boost::property_tree::read_json(stream, out_tree);
}

void IPCProtocol::SetMessage(const boost::property_tree::ptree &tree, std::string &out_message)
{
    out_message.clear();
    std::stringstream stream;
    boost::property_tree::write_json(stream, tree);
    std::string json(stream.str());

    Compression::CompressionBuffer_t buffer;
    Compression::Compress(json, buffer);

    Crypto::Encrypt(string(buffer.begin(), buffer.end()), out_message);
}

