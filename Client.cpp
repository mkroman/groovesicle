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

namespace Grooveshark {

QString const Client::API_URL = "http://grooveshark.com/";
QString const Client::BASE_URL = "http://grooveshark.com/";

Client::Client() : m_networkManager() {
}

void Client::establishConnection() {
  QNetworkReply* reply;
  QNetworkRequest request(QUrl("http://grooveshark.com"));

  qDebug("Establishing connection.");

  reply = m_networkManager.get(request);
  connect(reply, SIGNAL(finished()), SLOT(extractSessionCookie()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(errorCommunicationToken(QNetworkReply::NetworkError)));
}

void Client::extractSessionCookie() {
  QNetworkReply* reply;
  QList<QNetworkCookie> cookieList;

  reply = qobject_cast<QNetworkReply *>(sender());
  cookieList = m_networkManager.cookieJar()->cookiesForUrl(QUrl(BASE_URL));

  foreach (const QNetworkCookie& cookie, cookieList) {
    if (cookie.name() == "PHPSESSID") {
      m_session = QString(cookie.value());
      break;
    }
  }

  if (!m_session.isEmpty())
    qDebug("Extracted session cookie.");
  else
    qDebug("Failed to extract session cookie.");

  getCommunicationToken();
}

void Client::getCommunicationToken() {
  QVariantMap map;

  Request request("getCommunicationToken", map);
  request.setParameter("secretKey", "lortihovedet");

  connect(&request, SIGNAL(success(QVariantMap)), SLOT(processCommunicationToken(QVariantMap)));
  transmit(&request);
}

void Client::processCommunicationToken(const QVariantMap& result) {

}

void Client::errorCommunicationToken(const QNetworkReply::NetworkError& error) {
  qDebug("Failed to retrieve communication token.");
}

void Client::transmit(Request* gsRequest) {
  QNetworkReply* reply;
  QNetworkRequest request(QUrl(""));

  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  reply = m_networkManager.post(request, gsRequest->buildRequest());

  connect(reply, SIGNAL(finished()), gsRequest, SLOT(onFinished()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), gsRequest, SLOT(onError(QNetworkReply::NetworkError)));

  qDebug() << "Transmitting: " << gsRequest->buildRequest();
}

} // namespace Grooveshark

