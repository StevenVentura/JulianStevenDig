
#include <windows.h>
#include <iostream>
#include <string>

class FileHelper {
public:
static const std::string getexepath()
{
  char result[ MAX_PATH ];
  return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}




  static const std::string imagePath() {
    std::string imagePath = getexepath();
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath.substr(0,imagePath.find_last_of("\\"));
    imagePath = imagePath + "\\images\\";
    return imagePath;
  }
};
