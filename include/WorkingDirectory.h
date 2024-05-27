#ifndef WORKINGDIRECTORY_H
#define WORKINGDIRECTORY_H

#include <string>

#ifdef MACOS
#include "CoreFoundation/CoreFoundation.h"
#endif

class WorkingDirectory {

public:

    WorkingDirectory();

    inline const std::string& Get() { return path; };

private:

    std::string path;

};


#endif //WORKINGDIRECTORY_H
