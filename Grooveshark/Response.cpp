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

#include "Response.hpp"

namespace Grooveshark {

Response::Response(const QVariantMap& body) : m_body(body) {
}

bool Response::error() const {
  if (m_body.contains("fault") && m_body["fault"].toMap().contains("code"))
    return true;
  else
    return false;
}

const QVariant Response::getResult() const {
  if (m_body.contains("result"))
    return m_body["result"];
  else
    return QVariant();
}

const QVariantMap Response::getHeaders() const {
  if (m_body.contains("header") && !m_body["header"].toMap().isEmpty())
    return m_body["header"].toMap();
  else
    return QVariantMap();
}

} // namespace Grooveshark
