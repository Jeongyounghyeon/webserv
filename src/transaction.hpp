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
  int ParseRequestHeader(std::string buff);
  int ParseRequestBody(std::string buff, size_t content_length);

  // Response
  int HttpProcess();
  pid_t ExecuteCgi();
  std::string CreateResponseMessage();

  /*
        Getters
  */
  const Configuration& config() const;
  std::string method() const;
  const Uri& uri() const;
  Uri& uri();
  const HeadersIn& headers_in() const;
  std::string body_in() const;
  std::string http_version() const;
  std::string server_version() const;
  int status_code() const;
  std::string target_resource() const;
  const HeadersOut& headers_out() const;
  std::string body_out() const;
  std::string response() const;
  const Entity& entity() const;
  Entity& entity();
  const Cgi& cgi() const;

  /*
        Setters
  */
  void set_status_code(const int& status_code);

 private:
  int ParseRequestLine(std::string& request_line);
  int ParseFieldValue(std::string& header);
  int DecodeChunkedEncoding(std::string buff);

  int HttpGet();
  int HttpPost();
  int HttpDelete();

  void SetCgiEnv();
  void FreeCgiEnv();

  void SetAllowdMethod();
  void SetEntityHeaders();
  std::string AppendStatusLine();
  std::string AppendResponseHeader(const std::string key,
                                   const std::string value);
  void SetErrorPage();

  // Request Context
  Configuration config_;

  // Request
  std::string method_;
  Uri uri_;
  HeadersIn headers_in_;
  std::string body_in_;

  // Response
  std::string http_version_;
  std::string server_version_;
  int status_code_;
  std::string target_resource_;
  HeadersOut headers_out_;
  std::string body_out_;
  Entity entity_;
  Cgi cgi_;

  std::string response_;
};

#endif
