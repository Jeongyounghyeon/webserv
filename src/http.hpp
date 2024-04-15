#ifndef HTTP_HPP
#define HTTP_HPP

#include <list>
#include <map>
#include <string>

#define CRLF "\r\n"

#define HTTP_GET_METHOD "GET\0"
#define HTTP_POST_METHOD "POST\0"
#define HTTP_DELETE_METHOD "DELETE\0"

#define HTTP_CONTINUE 100
#define HTTP_SWITCHING_PROTOCOLS 101
#define HTTP_PROCESSING 102

#define HTTP_OK 200
#define HTTP_CREATED 201
#define HTTP_ACCEPTED 202
#define HTTP_NO_CONTENT 204
#define HTTP_PARTIAL_CONTENT 206

#define HTTP_SPECIAL_RESPONSE 300
#define HTTP_MOVED_PERMANENTLY 301
#define HTTP_MOVED_TEMPORARILY 302
#define HTTP_SEE_OTHER 303
#define HTTP_NOT_MODIFIED 304
#define HTTP_TEMPORARY_REDIRECT 307
#define HTTP_PERMANENT_REDIRECT 308

#define HTTP_BAD_REQUEST 400
#define HTTP_UNAUTHORIZED 401
#define HTTP_FORBIDDEN 403
#define HTTP_NOT_FOUND 404
#define HTTP_NOT_ALLOWED 405
#define HTTP_REQUEST_TIME_OUT 408
#define HTTP_CONFLICT 409
#define HTTP_LENGTH_REQUIRED 411
#define HTTP_PRECONDITION_FAILED 412
#define HTTP_REQUEST_ENTITY_TOO_LARGE 413
#define HTTP_REQUEST_URI_TOO_LARGE 414
#define HTTP_UNSUPPORTED_MEDIA_TYPE 415
#define HTTP_RANGE_NOT_SATISFIABLE 416
#define HTTP_MISDIRECTED_REQUEST 421
#define HTTP_TOO_MANY_REQUESTS 429

#define HTTP_INTERNAL_SERVER_ERROR 500
#define HTTP_NOT_IMPLEMENTED 501
#define HTTP_BAD_GATEWAY 502
#define HTTP_SERVICE_UNAVAILABLE 503
#define HTTP_GATEWAY_TIME_OUT 504
#define HTTP_VERSION_NOT_SUPPORTED 505
#define HTTP_INSUFFICIENT_STORAGE 507

typedef const std::string HeaderKey;
typedef std::list<const std::string> HeaderValue;
typedef std::map<HeaderKey, HeaderValue>::iterator HeadersIterator;
typedef std::map<HeaderKey, HeaderValue>::const_iterator HeadersConstIterator;

void InsertHeader(std::map<HeaderKey, HeaderValue>& headers,
                  const std::string key, const std::string value) {
  if (value.size() == 0) {
    return;
  }
  HeadersConstIterator end = headers.end();
  HeadersIterator it = headers.find(key);
  if (it == end) {
    headers.insert(std::make_pair(key, HeaderValue()));
    it = headers.find(key);
  }
  it->second.push_back(value);
}

struct HeadersIn {
  std::map<HeaderKey, HeaderValue> headers_;

  std::string host_;
  std::string connection_;
  std::string if_modified_since_;
  std::string if_unmodified_since_;
  std::string if_match_;
  std::string if_none_match_;
  std::string user_agent_;
  std::string referer_;
  std::string content_length_;
  std::string content_range_;
  std::string content_type_;

  std::string range_;
  std::string if_range_;

  std::string transfer_encoding_;
  std::string te_;
  std::string expect_;
  std::string upgrade_;

  ssize_t content_length_n_;
  bool chuncked;
};

struct HeadersOut {
  std::string server_;
  std::string date_;
  std::string content_length_;
  std::string content_encoding_;
  std::string content_type_;
  std::string location_;
  std::string refresh_;
  std::string last_modified_;
  std::string content_range_;
  std::string accept_ranges_;
  std::string www_authenticate_;
  std::string expires_;
  std::string etag_;
};

#endif
