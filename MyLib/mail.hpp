#if defined ( MYLIB_SERVER_BULD )


#ifndef MAILER_HPP
#define MAILER_HPP


#include <string>

namespace MyLib {
    class Mail;
}

class MyLib::Mail
{
private:
    static const std::string UNKNOWN_ERROR;

private:
    std::string m_from;
    std::string m_to;
    std::string m_subject;
    std::string m_body;

public:
    Mail();
    Mail(const std::string &from, const std::string &to,
         const std::string &subject, const std::string &body);

public:
    std::string GetFrom();
    std::string GetTo();
    std::string GetSubject();
    std::string GetBody();
    void SetFrom(const std::string &from);
    void SetTo(const std::string &to);
    void SetSubject(const std::string &subject);
    void SetBody(const std::string &body);

public:
    bool Send() const;
    bool Send(std::string &out_error) const;
    void SendAsync() const;
};


#endif /* MAILER_HPP */


#endif  // defined ( MYLIB_SERVER_BULD )

