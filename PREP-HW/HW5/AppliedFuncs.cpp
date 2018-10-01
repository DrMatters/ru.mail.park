#include <cctype>
#include <cstring>

namespace initSet {
  bool initialIsOk(const char* initial) {
    size_t i = 0;
    while(initial[i] != '\0') {
      if(!isalpha((int)initial[i])) {
        return false;
      }
      ++i;
    }
    return true;
  }
  void normaliseInit(char* initial) { //Приведение слова нормальному виду
    size_t i = 0;
    while(initial[i] != '\0') {
      if(i >= 1) {
        initial[i] = tolower((int)initial[i]);
      } else {
        initial[i] = toupper((int)initial[i]);
      }
      ++i;
    }
  }

} //end of namespace initSet