/*
 *  Copyright (c) 2011, Mikkel Kroman <mk@maero.dk>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef GROOVESHARK_RESPONSE_HPP
#define GROOVESHARK_RESPONSE_HPP

#include <QObject>
#include <QVariantMap>

#include <QJson/Parser>

namespace Grooveshark {

class Response : public QObject {
    Q_OBJECT
public:
    Response(const QVariantMap& body);

    void setBody(const QVariantMap& body) { m_body = body; }

    bool error() const;

    const QVariant getResult() const;
    const QVariant getErrorMessage() const;
    const QVariantMap getHeaders() const;

    const QVariantMap& getBody() const { return m_body; }

private:
    QVariantMap m_body;
};

} // namespace Grooveshark

#endif // GROOVESHARK_RESPONSE_HPP
