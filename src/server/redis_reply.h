/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#pragma once

#include <event2/buffer.h>

#include <string>
#include <vector>

#define CRLF "\r\n"                    // NOLINT
#define RESP_PREFIX_ERROR "-"          // NOLINT
#define RESP_PREFIX_SIMPLE_STRING "+"  // NOLINT

namespace redis {

enum class RESP { v2, v3 };

void Reply(evbuffer *output, const std::string &data);
std::string SimpleString(const std::string &data);
std::string Error(const std::string &err);

template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
std::string Integer(T data) {
  return ":" + std::to_string(data) + CRLF;
}

inline std::string NilString(const RESP ver) {
  if (ver == RESP::v3) {
    return "_" CRLF;
  }
  return "$-1" CRLF;
}

std::string BulkString(const std::string &data);

template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
std::string MultiLen(T len) {
  return "*" + std::to_string(len) + CRLF;
}

std::string Array(const std::vector<std::string> &list);
std::string ArrayOfBulkStrings(const std::vector<std::string> &elements);

}  // namespace redis
