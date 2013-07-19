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
        typedef std::unordered_map<_T, std::string, Hasher<_T>> HashToString_t;
        typedef std::unordered_map<std::string, _T> HashToEnum_t;
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

    typedef HashMapper<IPCProtocol::Request>::HashToString_t RequestToString_t;
    typedef HashMapper<IPCProtocol::Request>::HashToEnum_t RequestToEnum_t;


    struct RequestArg {
        enum class Common : unsigned char {
            Void
        };

        enum class HandShake : unsigned char {
            IP
        };

        enum class LatestDesktopClientVersion : unsigned char {
            IP
        };

        typedef HashMapper<Common>::Hash_t CommonHash_t;
        typedef HashMapper<Common>::HashToString_t CommonToString_t;
        typedef HashMapper<Common>::HashToEnum_t CommonToEnum_t;

        typedef HashMapper<HandShake>::Hash_t HandShakeHash_t;
        typedef HashMapper<HandShake>::HashToString_t HandShakeToString_t;
        typedef HashMapper<HandShake>::HashToEnum_t HandShakeToEnum_t;

        typedef HashMapper<LatestDesktopClientVersion>::Hash_t LatestDesktopClientVersionHash_t;
        typedef HashMapper<LatestDesktopClientVersion>::HashToString_t LatestDesktopClientVersionToString_t;
        typedef HashMapper<LatestDesktopClientVersion>::HashToEnum_t LatestDesktopClientVersionToEnum_t;
    };


    struct ResponseStatus {
        enum class Common : unsigned char {
            InvalidProtocol,
            InvalidProtocolVersion,
            ExpiredProtocolVersion,
            OK
        };

        typedef HashMapper<Common>::HashToString_t CommonToString_t;
        typedef HashMapper<Common>::HashToEnum_t CommonToEnum_t;
    };


    struct ResponseArg {
        enum class Common : unsigned char {
            Void
        };

        enum class LatestDesktopClientVersion : unsigned char {
            String,
            Major,
            Minor,
            Patch,
            Revision
        };

        typedef HashMapper<Common>::Hash_t CommonHash_t;
        typedef HashMapper<Common>::HashToString_t CommonToString_t;
        typedef HashMapper<Common>::HashToEnum_t CommonToEnum_t;

        typedef HashMapper<LatestDesktopClientVersion>::Hash_t LatestDesktopClientVersionHash_t;
        typedef HashMapper<LatestDesktopClientVersion>::HashToString_t LatestDesktopClientVersionToString_t;
        typedef HashMapper<LatestDesktopClientVersion>::HashToEnum_t LatestDesktopClientVersionToEnum_t;
    };

/*
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
    };*/

public:
    static const RequestToString_t RequestToString;
    static const RequestToEnum_t RequestToEnum;

    static const RequestArg::CommonToString_t CommonRequestArgToString;
    static const RequestArg::CommonToEnum_t CommonRequestArgToEnum;

    static const RequestArg::HandShakeToString_t HandShakeRequestArgToString;
    static const RequestArg::HandShakeToEnum_t HandShakeRequestArgToEnum;

    static const RequestArg::LatestDesktopClientVersionToString_t LatestDesktopClientVersionRequestArgToString;
    static const RequestArg::LatestDesktopClientVersionToEnum_t LatestDesktopClientVersionRequestArgToEnum;

    static const ResponseStatus::CommonToString_t CommonResponseStatusToString;
    static const ResponseStatus::CommonToEnum_t CommonResponseStatusToEnum;

    static const ResponseArg::CommonToString_t CommonResponseArgToString;
    static const ResponseArg::CommonToEnum_t CommonResponseArgToEnum;

    static const ResponseArg::LatestDesktopClientVersionToString_t LatestDesktopClientVersionResponseArgToString;
    static const ResponseArg::LatestDesktopClientVersionToEnum_t LatestDesktopClientVersionResponseArgToEnum;

public:
    static std::string Name();
    static std::string Version();
    static Version_t VersionMajor();
    static Version_t VersionMinor();
};


#endif /* IPCPROTOCOL_HPP */


