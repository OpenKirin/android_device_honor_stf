/*
 * Copyright (C) 2017 OpenKirin, OldDroid, XePeleato
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
 
std::string UFSPath("/dev/block/platform/ff3b0000.ufs");
std::string TargetPath("/dev/block/bootdevice");
 
bool IsUFS() {
    struct stat st;
    lstat(UFSPath.c_str(), &st);
 
    if (S_ISDIR(st.st_mode)) {
        return true;
    }
 
    return false;
}
 
int main()
{
    if(IsUFS()) {
        symlink(UFSPath.c_str(), TargetPath.c_str());
        printf("hw_service: ufs storage detected");
    } else {
        symlink("/dev/block/platform/hi_mci.0", TargetPath.c_str());
        printf("hw_service: emmc storage detected");
    }
    return 0;
}
