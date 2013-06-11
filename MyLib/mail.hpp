#if defined ( MYLIB_SERVER_BULD )


#ifndef MAILER_HPP
#define MAILER_HPP


#include <string>
#include <vector>

namespace MyLib {
    class Mail;
}

class MyLib::Mail
{
private:
    std::string m_from;
    std::string m_to;
    std::string m_subject;
    std::string m_body;
    std::vector<std::string> &m_attachments;

public:
    Mail();
    Mail(const std::string &from, const std::string &to,
         const std::string &subject, const std::string &body,
         const std::vector<std::string> &attachments = {  });

public:
    std::string GetFrom();
    std::string GetTo();
    std::string GetSubject();
    std::string GetBody();
    const std::vector<std::string> &GetAttachments();
    void SetFrom(const std::string &from);
    void SetTo(const std::string &to);
    void SetSubject(const std::string &subject);
    void SetBody(const std::string &body);
    void SetAttachments(const std::vector<std::string> &attachments);

public:
    bool Send() const;
    bool Send(std::string &out_error) const;
    void SendAsync() const;
};


#endif /* MAILER_HPP */


#endif  // defined ( MYLIB_SERVER_BULD )

