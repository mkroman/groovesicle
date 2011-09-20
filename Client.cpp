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

#include "Client.hpp"
#include "Request.hpp"

#include <QCryptographicHash>

namespace Grooveshark {

QString const Client::APIUrl = "https://cowbell.grooveshark.com/more.php";
QString const Client::BaseUrl = "http://grooveshark.com/";

QString const Client::Name = "htmlshark";
QString const Client::Revision = "20110906";

Client::Client() : m_networkManager() {
}

void Client::establishConnection() {
  QNetworkReply* reply;
  QNetworkRequest request(BaseUrl);

  reply = m_networkManager.get(request);

  qDebug("Establishing connection.");

  connect(reply, SIGNAL(finished()), SLOT(extractSessionCookie()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(errorCommunicationToken(QNetworkReply::NetworkError)));
}

void Client::extractSessionCookie() {
  QNetworkReply* reply;
  QList<QNetworkCookie> cookieList;

  reply = qobject_cast<QNetworkReply*>(sender());
  cookieList = m_networkManager.cookieJar()->cookiesForUrl(QUrl(BaseUrl));

  foreach (const QNetworkCookie& cookie, cookieList) {
    if (cookie.name() == "PHPSESSID") {
      m_sessionId = cookie.value();
      break;
    }
  }

  if (!m_sessionId.isEmpty())
    qDebug("Extracted session cookie.");
  else
    qDebug("Failed to extract session cookie.");

  getCommunicationToken();
}

void Client::getCommunicationToken() {
  Request* request = new Request("getCommunicationToken");

  request->setParent(this);
  request->setParameter("secretKey", QCryptographicHash::hash(m_sessionId.toAscii(), QCryptographicHash::Md5).toHex());

  connect(request, SIGNAL(success(Response)), SLOT(processCommunicationToken(Response)));

  transmit(request);
}

void Client::processCommunicationToken(const Response& response) {
  if (response.error()) {
    qDebug() << Q_FUNC_INFO << "failed";
    return;
  }
  else {
    m_sessionToken = response.getResult().toString();
  }
}

void Client::errorCommunicationToken(const QNetworkReply::NetworkError& error) {
  qDebug("Failed to retrieve communication token.");
}

void Client::transmit(Request* request) {
  QNetworkReply* reply;
  QNetworkRequest networkRequest(APIUrl);

  networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  if (!m_sessionId.isEmpty())
    request->setHeader("session", m_sessionId);

  reply = m_networkManager.post(networkRequest, request->buildRequest());

  connect(reply, SIGNAL(finished()), request, SLOT(onFinished()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), request, SLOT(onError(QNetworkReply::NetworkError)));
}

} // namespace Grooveshark

