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

#include <QDebug>

#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"

namespace Grooveshark {

Request::Request(QString const& method)
  : m_method(method), m_parameters() {
  insertDefaultParameters();
}

Request::Request(QString const& method, QVariantMap& parameters)
  : m_method(method), m_parameters(parameters) {
  insertDefaultParameters();
}

void Request::insertDefaultParameters() {
  QVariantMap country;

  m_headers.insert("client", Client::Name);
  m_headers.insert("clientRevision", Client::Revision);

  country.insert("ID","57");
  country.insert("CC1","72057594037927936");
  country.insert("CC2","0");
  country.insert("CC3","0");
  country.insert("CC4","0");

  m_headers.insertMulti("country", country);
}

QByteArray Request::buildRequest() {
  QVariantMap values;
  QJson::Serializer serializer;

  values.insert("method", m_method);
  values.insert("header", m_headers);
  values.insert("parameters", m_parameters);

  return serializer.serialize(values);
}

void Request::setParameter(const QString& name, const QString& value) {
  m_parameters.insert(name, value);
}

void Request::setHeader(const QString& name, const QString& value) {
  m_headers[name] = value;
}

void Request::onFinished() {
  bool parserSuccess;
  QVariantMap body;
  QJson::Parser parser;
  QNetworkReply* reply;

  reply = qobject_cast<QNetworkReply *>(sender());
  body  = parser.parse(reply->readAll(), &parserSuccess).toMap();

  if (parserSuccess) {
    m_response = new Response(body);
    m_response->setParent(this);

    emit success(*m_response);
  }
  else {
    // error
  }
}

void Request::onError(const QNetworkReply::NetworkError& error) {
  qDebug("lolz onerror");
}

} // namespace Grooveshark
