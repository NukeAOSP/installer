#ifndef TRESOURCES_HPP
#define TRESOURCES_HPP

#include <filesystem>
#include <gupta/ini.hpp>
#include <map>
#include <memory>

namespace gupta {
class cf_basicfile;
}

// namespace gupta {
// namespace detail {
// struct stdstringInsenstive;
//}
// using ParsedIni =
//    std::map<std::string,
//             std::map<std::string, std::string, detail::stdstringInsenstive>,
//             detail::stdstringInsenstive>;
//} // namespace gupta

// extern template class std::map<std::string, gupta::ParsedIni>;

class TResources;
extern template class std::shared_ptr<TResources>;
extern template class std::map<std::string, gupta::ParsedIni>;

class TResources {
public:
  using buffer_t = std::vector<uint8_t>;
  using path = std::filesystem::path;
  using string = std::string;

  TResources(path Source);
  ~TResources();

  path extractFile(path DestFile, const path &SrcFile);
  path extractTemporaryFile(path File);
  void extractTemporaryFiles(const char *WildCard);

  buffer_t GetFile(path File);
  buffer_t GetFileText(path File);

  buffer_t &GetFile(path File, buffer_t &buf);
  buffer_t &GetFileText(path File, buffer_t &buf);

  string GetIniValue(const path &IniFile, const string &Section,
                     const string &key, const string &Default);

  string GetIniValue(const string &Section, const string &key,
                     const string &Default);

  string MainIni() const;
  void setMainIni(const string &MainIni);

  path TmpFolder() const;

private:
  path Source_, TmpFolder_;
  string MainIni_;
  std::map<string, gupta::ParsedIni> Inis_;
  buffer_t ExeResourceBuf_;
  std::vector<std::unique_ptr<gupta::cf_basicfile>> Files_;

  buffer_t &GetFile(path File, buffer_t &buf, const char *FileOpenMode);
  std::vector<gupta::cf_basicfile *> GetFiles(std::string WildCard);
};

#endif // TRESOURCES_HPP
