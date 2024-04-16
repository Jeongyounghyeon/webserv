#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "cgi.hpp"
#include "configuration.hpp"
#include "entity.hpp"
#include "http.hpp"
#include "uri.hpp"

class Transaction {
 public:
  typedef ServerConfiguration::LocationConfiguration Configuration;

  Transaction();
  Transaction(const Transaction& obj);
  ~Transaction();
  Transaction& operator=(const Transaction& obj);

  // Request Context
  const Configuration& GetConfiguration(const ServerConfiguration&);

  // Request
  int ParseRequestHeader(const char* buff, ssize_t size, ssize_t& offset);
  int ParseRequestBody(char* buff, ssize_t size, ssize_t& offset);

  // Response
  int HttpGetMethod();
  int HttpPostMethod();
  int HttpDeleteMethod();

  std::string GetTargetResource();
  bool IsAllowedMethod();
  bool IsRedirectedUri();

  void SetCgiEnv();
  void FreeCgiEnv();

  /*
        Getters
  */
  const Configuration& config() const;
  const Uri& uri() const;
  const std::string& method() const;
  const HeadersIn& headers_in() const;
  const HeadersOut& headers_out() const;
  const std::string& body() const;
  int status_code();

 private:
  void Test();
  int ParseRequestLine(std::string& request_line);
  int ParseFieldValue(std::string& header);
  int DecodeChunkedEncoding(char* buff, ssize_t size, ssize_t& offset);

  // Request Context
  Configuration config_;

  // Request
  std::string method_;
  Uri uri_;
  HeadersIn headers_in_;
  std::string body_in_;

  // Response
  int status_code_;
  std::string target_resource_;
  HeadersOut headers_out_;
  Entity entity_;
  Cgi cgi_;
};

#endif
