#if defined ( MYLIB_SERVER_BULD )


#include <boost/thread/thread.hpp>
#include <boost/filesystem.hpp>
#include <vmime/vmime.hpp>

#if defined (_WIN32)
#include <vmime/platforms/windows/windowsHandler.hpp>
#else
#include <vmime/platforms/posix/posixHandler.hpp>
#endif  // defined (_WIN32)

#include "log.hpp"
#include "mail.hpp"


#define     Mail::UNKNOWN_ERROR         "MyLib::Mail unknown error!"


using namespace std;
using namespace boost;
using namespace MyLib;

Mail::Mail()
{
}

Mail::Mail(const std::string &from, const std::string &to,
           const std::string &subject, const std::string &body,
           const std::vector<std::string> &attachments)
    : m_from(from),
      m_to(to),
      m_subject(subject),
      m_body(body),
      m_attachments(attachments)
{
}

std::string Mail::GetFrom()
{
    return m_from;
}

std::string Mail::GetTo()
{
    return m_to;
}

std::string Mail::GetSubject()
{
    return m_subject;
}

std::string Mail::GetBody()
{
    return m_body;
}

const std::vector<std::string> &Mail::GetAttachments()
{
    return m_attachments;
}

void Mail::SetFrom(const std::string &from)
{
    m_from = from;
}

void Mail::SetTo(const std::string &to)
{
    m_to = to;
}

void Mail::SetSubject(const std::string &subject)
{
    m_subject = subject;
}

void Mail::SetBody(const std::string &body)
{
    m_body = body;
}

void SetAttachments(const std::vector<std::string> &attachments)
{
    m_attachments.clear();
    for (auto a : attachments) {
        m_attachments.push_back(a);
    }
}

bool Mail::Send() const
{
    string err;
    return Send(err);
}

bool Mail::Send(std::string &out_error) const
{
    try {
#if defined (_WIN32)
        vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();
#else
        vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
#endif /* defined (_WIN32) */

        vmime::messageBuilder mb;

        mb.setExpeditor(vmime::mailbox(m_from));
        mb.getRecipients().appendAddress(vmime::create<vmime::mailbox>(m_to));

        mb.setSubject(*vmime::text::newFromString(m_subject, vmime::charsets::UTF_8));

        mb.constructTextPart(vmime::mediaType(vmime::mediaTypes::TEXT, vmime::mediaTypes::TEXT_HTML));
        mb.getTextPart()->setCharset(vmime::charsets::UTF_8);
        mb.getTextPart()->setText(vmime::create<vmime::stringContentHandler>(m_body));

        if (m_attachments.size() > 0) {
            for (auto a : m_attachments) {
                vmime::ref <vmime::attachment> att = vmime::create <vmime::fileAttachment>
                        (a, vmime::mediaType("application/octet-stream"),
                         vmime::text(boost::filesystem::stem(a).string());
                mb.appendAttachment(att);
            }
        }

        vmime::ref<vmime::message> msg = mb.construct();

        vmime::utility::url url("smtp://localhost");
        vmime::ref<vmime::net::session> sess = vmime::create<vmime::net::session>();
        vmime::ref<vmime::net::transport> tr = sess->getTransport(url);

        tr->connect();
        tr->send(msg);
        tr->disconnect();

        return true;
    }

    catch (vmime::exception &ex) {
        FATAL(ex.what());
        out_error.assign(ex.what());
    }

    catch(std::exception &ex) {
        FATAL(ex.what());
        out_error.assign(ex.what());
    }

    catch (...) {
        FATAL(ex.what(UNKNOWN_ERROR));
        out_error.assign(UNKNOWN_ERROR);
    }

    return false;
}

void Mail::SendAsync() const
{
    boost::thread t(static_cast<bool (Mail::*)() const>(&Mail::Send), this);
    t.detach();
}


#endif  // defined ( MYLIB_SERVER_BULD )

