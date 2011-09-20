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

#ifndef GROOVESHARK_CLIENT_HPP
#define GROOVESHARK_CLIENT_HPP

#include <QDebug>
#include <QObject>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>

#include <QJson/Serializer>

namespace Grooveshark {

class Request;
class Client : public QObject {
    Q_OBJECT

public:
    static QString const API_URL;
    static QString const BASE_URL;

    Client();

    void establishConnection();
    void transmit(Request* request);

private slots:
    void extractSessionCookie();

private:
    QString               m_session;
    QNetworkAccessManager m_networkManager;
};

} // namespace Grooveshark

#endif // GROOVESHARK_CLIENT_HPP
