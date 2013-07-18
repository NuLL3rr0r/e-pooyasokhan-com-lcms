#ifndef IPCPROTOCOL_HPP
#define IPCPROTOCOL_HPP


#include <string>
#include <unordered_map>
#include <boost/assign/list_of.hpp>
#include <boost/bimap.hpp>

namespace MyLib {
    class IPCProtocol;
}

class MyLib::IPCProtocol
{
public:
    typedef unsigned char Version_t;

private:
    template <typename _T>
    struct Hasher
    {
        std::size_t operator()(const _T &t) const
        {
            return std::hash<unsigned char>()(static_cast<unsigned char>(t));
        }
    };

    template <typename _T>
    struct HashMapper
    {
        typedef std::unordered_map<_T, std::string, Hasher<_T>> Hash_t;

        Hash_t hash;

        void Register(_T t, const std::string &s)
        {
            hash[t] = s;
        }
    };

    template <typename _T>
    struct EnumMapper
    {
        typedef boost::bimap<_T, std::string> Bimap_t;

        Bimap_t bimap;

        void Register(_T t, const std::string &s)
        {
            bimap.insert(Bimap_t::value_type(t, s));
        }

//        void Find(_T t)
    };

    struct EnumMapper2
    {
        //typedef boost::bimap<_T, std::string> Bimap_t;

    };


public:
    enum class Request : unsigned char {
        HandShake,
        LatestDesktopClientVersion,
        Login,
        PasswordChange,
        PasswordRecovery,
        Registeration
    };

    enum class HandShakeRequestArg : unsigned char {
        IP
    };

    enum class HandShakeResponseStatus : unsigned char {
        OK,
        ProtocolTooOld,
        InvalidProtocol
    };

    enum class LatestDesktopClientVersionRequestArg : unsigned char {
        IP
    };

    enum class LatestDesktopClientVersionResponseArg : unsigned char {
        Version,
        VersionMajor,
        VersionMinor,
        VersionPatch,
        VersionRevision
    };

    enum class LatestDesktopClientVersionResponseStatus : unsigned char {
        OK
    };

    enum class LoginRequestArg : unsigned char {
        IP,
        Username,
        Password
    };

    enum class LoginResponseStatus : unsigned char {
        OK,
        InvalidUserPwd
    };

    enum class PasswordChangeRequestArg : unsigned char {
        CurrentPassword,
        NewPassowrd
    };

    enum class PasswordChangeResponseStatus : unsigned char {
        OK,
        InvalidCurrentPwd
    };

    enum class PasswordRecoveryRequestArg : unsigned char {
        IP,
        Username
    };

    enum class PasswordRecoveryResponseStatus : unsigned char {
        OK,
        InvalidUser
    };

    enum class RegisterationRequestArg : unsigned char {
        IP,
        Username,
        Password,
        FirstName,
        LastName,
        Vocation,
        Birthday,
        Educations,
        LearningExperiences,
        Course,
        AcquaintanceMethod,
        Province,
        Phone,
        Mobile
    };

    enum class RegisterationResponseStatus : unsigned char {
        OK,
        InvalidData
    };

public:
    typedef std::unordered_map<Request, std::string, Hasher<Request>> RequestHash_t;

    typedef std::unordered_map<HandShakeRequestArg, std::string,
    Hasher<HandShakeRequestArg>> HandShakeRequestArgHash_t;

    typedef std::unordered_map<HandShakeResponseStatus, std::string,
    Hasher<HandShakeResponseStatus>> HandShakeResponseStatusHash_t;

    typedef std::unordered_map<LatestDesktopClientVersionRequestArg, std::string,
    Hasher<LatestDesktopClientVersionRequestArg>> LatestDesktopClientVersionRequestArgHash_t;

    typedef std::unordered_map<LatestDesktopClientVersionResponseArg, std::string,
    Hasher<LatestDesktopClientVersionResponseArg>> LatestDesktopClientVersionResponseArgHash_t;

    typedef std::unordered_map<LatestDesktopClientVersionResponseStatus, std::string,
    Hasher<LatestDesktopClientVersionResponseStatus>> LatestDesktopClientVersionResponseStatusHash_t;

    typedef std::unordered_map<LoginRequestArg, std::string,
    Hasher<LoginRequestArg>> LoginRequestArgHash_t;

    typedef std::unordered_map<LoginResponseStatus, std::string,
    Hasher<LoginResponseStatus>> LoginResponseStatusHash_t;

    typedef std::unordered_map<PasswordChangeRequestArg, std::string,
    Hasher<PasswordChangeRequestArg>> PasswordChangeRequestArgHash_t;

    typedef std::unordered_map<PasswordChangeResponseStatus, std::string,
    Hasher<PasswordChangeResponseStatus>> PasswordChangeResponseStatusHash_t;

    typedef std::unordered_map<PasswordRecoveryRequestArg, std::string,
    Hasher<PasswordRecoveryRequestArg>> PasswordRecoveryRequestArgHash_t;

    typedef std::unordered_map<PasswordRecoveryResponseStatus, std::string,
    Hasher<PasswordRecoveryResponseStatus>> PasswordRecoveryResponseStatusHash_t;

    typedef std::unordered_map<RegisterationRequestArg, std::string,
    Hasher<RegisterationRequestArg>> RegisterationRequestArgHash_t;

    typedef std::unordered_map<RegisterationResponseStatus, std::string,
    Hasher<RegisterationResponseStatus>> RegisterationResponseStatusHash_t;

public:
    static const HashMapper<IPCProtocol::Request>::Hash_t RequestToString;
    static const HandShakeRequestArgHash_t HandShakeRequestArgToString;
    static const HandShakeResponseStatusHash_t HandShakeResponseStatusToString;
    static const LatestDesktopClientVersionRequestArgHash_t LatestDesktopClientVersionRequestArgToString;
    static const LatestDesktopClientVersionResponseArgHash_t LatestDesktopClientVersionResponseArgToString;
    static const LatestDesktopClientVersionResponseStatusHash_t LatestDesktopClientVersionResponseStatusToString;
    static const LoginRequestArgHash_t LoginRequestArgToString;
    static const LoginResponseStatusHash_t LoginResponseStatusToString;
    static const PasswordChangeRequestArgHash_t PasswordChangeRequestArgToString;
    static const PasswordChangeResponseStatusHash_t PasswordChangeResponseStatusToString;
    static const PasswordRecoveryRequestArgHash_t PasswordRecoveryRequestArgToString;
    static const PasswordRecoveryResponseStatusHash_t PasswordRecoveryResponseStatusToString;
    static const RegisterationRequestArgHash_t RegisterationRequestArgToString;
    static const RegisterationResponseStatusHash_t RegisterationResponseStatusToString;

public:
    static std::string Name();
    static std::string Version();
    static Version_t VersionMajor();
    static Version_t VersionMinor();
};


#endif /* IPCPROTOCOL_HPP */


