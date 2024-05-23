//
// Created by gal on 5/23/2024.
//

#include "WorkingDirectory.h"

WorkingDirectory::WorkingDirectory() {

    path = "./resources/";

#ifdef MACOS
// This will change the default working directory to the resource path on MacOS

    CFBundleRef mainBundle = CFBundleRef();
    CFURLRefresourceURL = CFBundleCopyResourceDirectoryURL(mainBundle);
    char path[PATH_MAX];

    if(CFURLGetFileSystemRepresentation(resourceURL, TRUE, (UInt8 *)path, PATH_MAX)){
        CFRelease(resourceURL);
        chdir(path);
    }

#endif
}
