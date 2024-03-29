#ifndef CONFIGURATION_PARSER_HPP
#define CONFIGURATION_PARSER_HPP

#include <set>
#include <string>

#include "configuration.hpp"
#include "core.hpp"

class ConfigurationParser {
 private:
  static const std::string COMMENT_TOKEN;
  static const std::string END_TOKEN;
  static const std::string OPEN_BLOCK_TOKEN;
  static const std::string CLOSE_BLOCK_TOKEN;
  static const std::set<std::string> SINGLE_TOKEN;

  typedef std::string Token;
  typedef std::vector<Token> Tokens;

  ConfigurationParser();
  ConfigurationParser(const ConfigurationParser& ref);

  ConfigurationParser& operator=(const ConfigurationParser& ref);

  static int eraseComment(std::string& contents);
  static int tokenize(const std::string& str, Tokens& tokens);
  static int parse(const Tokens& tokens, Configuration& configuration);

  static int parseServer(const Tokens& tokens,
                         ServerConfiguration& ServerConfiguration);
  static int parseLocation(
      const Tokens& tokens, const ServerConfiguration& serverConfiguration,
      ServerConfiguration::LocationConfiguration& locationConfiguration);

  static int parseServerLine(const Token& directive, const Tokens& valueTokens,
                             std::string& host, int& port,
                             std::set<const std::string>& server_names,
                             std::map<const int, const std::string>& error_page,
                             std::string& client_max_body_size,
                             std::string& root, bool& auto_index,
                             std::string& index, std::string& index_if_dir);
  static int parseLocationLine(
      const Token& directive, const Tokens& valueTokens,
      std::map<const int, const std::string>& error_page,
      std::string& client_max_body_size, std::string& root, bool& auto_index,
      std::string& index, std::string& index_if_dir,
      std::set<const std::string>& allowed_method, std::string& return_uri,
      std::string& upload_store);

  static int parseHost(std::string& host, const Tokens& valueTokens);
  static int parsePort(int& port, const Tokens& valueTokens);
  static int parseServer_names(std::set<const std::string>& server_names,
                               const Tokens& valueTokens);
  static int parseError_page(std::map<const int, const std::string>& error_page,
                             const Tokens& valueTokens);
  static int parseClient_max_body_size(std::string& client_max_body_size,
                                       const Tokens& valueTokens);
  static int parseRoot(std::string& root, const Tokens& valueTokens);
  static int parseAuto_index(bool& auto_index, const Tokens& valueTokens);
  static int parseIndex(std::string& index, const Tokens& valueTokens);
  static int parseIndex_if_dir(std::string& index_if_dir,
                               const Tokens& valueTokens);
  static int parseAllowed_method(std::set<const std::string>& allowed_method,
                                 const Tokens& valueTokens);
  static int parseReturn_uri(std::string& return_uri,
                             const Tokens& valueTokens);
  static int parseUpload_store(std::string& upload_store,
                               const Tokens& valueTokens);

  static bool isHost(const std::string& port);
  static bool isPort(const std::string& port);
  static bool isErrorCode(const std::string& error_code);
  static bool isAutoIndex(const std::string& auto_index);

 public:
  virtual ~ConfigurationParser();

  static int parse(const std::string& contents, Configuration& configuration);
};

#endif
