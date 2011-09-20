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

#include "Request.hpp"

namespace Grooveshark {

Request::Request(QString const& method, QVariantMap& parameters)
  : m_method(method), m_parameters(parameters) {
  QVariantMap country;

  m_headers.insert("client", "htmlshark");
  m_headers.insert("clientRevision", "20110606.04");

  country.insert("CC1","0");
  country.insert("CC3","0");
  country.insert("ID","223");
  country.insert("CC2","0");
  country.insert("CC4","1073741824");

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

} // namespace Grooveshark
