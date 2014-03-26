#if defined(__linux__)

#include <string.h>
#include <dlfcn.h>

int sea_main(int argc,char **argv) {
    typedef int (*main_t)(int,char**);
    static void* handle = NULL;
    static main_t _main = NULL;
    
    if (!handle) {
      handle = dlopen("./libsea.so", RTLD_LAZY);
      if (!handle)
            return 1;
      // reset errors
      dlerror();
    }
    
    if (!_main) {
      _main = (main_t) dlsym(handle, "sea_main");
    
      const char *dlsym_error = dlerror();
      if (dlsym_error) {
          dlclose(handle);
          handle = NULL;
          return 1;
      }
    }
    _main(argc,argv);
}
int shoof_main(int argc,char **argv) {
    typedef int (*main_t)(int,char**);
    static void* handle = NULL;
    static main_t _main = NULL;
    
    if (!handle) {
      handle = dlopen("./libschoof.so", RTLD_LAZY);
      if (!handle)
            return 1;
      // reset errors
      dlerror();
    }
    
    if (!_main) {
      _main = (main_t) dlsym(handle, "schoof_main");
    
      const char *dlsym_error = dlerror();
      if (dlsym_error) {
          dlclose(handle);
          handle = NULL;
          return 1;
      }
    }
    _main(argc,argv);
}
int shoof2_main(int argc,char **argv){
    typedef int (*main_t)(int,char**);
    static void* handle = NULL;
    static main_t _main = NULL;
    
    if (!handle) {
      handle = dlopen("./libschoof2.so", RTLD_LAZY);
      if (!handle)
            return 1;
      // reset errors
      dlerror();
    }
    
    if (!_main) {
      _main = (main_t) dlsym(handle, "schoof2_main");
    
      const char *dlsym_error = dlerror();
      if (dlsym_error) {
          dlclose(handle);
          handle = NULL;
          return 1;
      }
    }
    _main(argc,argv);
}
int modpol_main(int argc,char **argv){
    typedef int (*main_t)(int,char**);
    static void* handle = NULL;
    static main_t _main = NULL;
    
    if (!handle) {
      handle = dlopen("./libmodpol.so", RTLD_LAZY);
      if (!handle)
            return 1;
      // reset errors
      dlerror();
    }
    
    if (!_main) {
      _main = (main_t) dlsym(handle, "modpol_main");
    
      const char *dlsym_error = dlerror();
      if (dlsym_error) {
          dlclose(handle);
          handle = NULL;
          return 1;
      }
    }
    _main(argc,argv);
}


#endif
