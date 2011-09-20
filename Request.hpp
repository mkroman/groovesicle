/*
 * Copyright (c) 2011, Mikkel Kroman <mk@maero.dk>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef GROOVESHARK_REQUEST_HPP
#define GROOVESHARK_REQUEST_HPP

#include <QObject>
#include <QVariantMap>
#include <QNetworkReply>

#include <QJson/Serializer>

#include "Response.hpp"

namespace Grooveshark {

class Request : public QObject {
    Q_OBJECT
public:
    Request(QString const& method);
    Request(QString const& method, QVariantMap& parameters);

    QByteArray buildRequest();

    void setParameter(const QString& name, const QString& value);
    void setHeader(const QString& name, const QString& value);

public slots:
    void onFinished();
    void onError(const QNetworkReply::NetworkError& error);

signals:
    void success(const Response& response);

private:
    void insertDefaultParameters();

    QString     m_method;
    Response*   m_response;
    QVariantMap m_headers;
    QVariantMap m_parameters;
};

} // namespace Grooveshark

#endif // GROOVESHARK_REQUEST_HPP
