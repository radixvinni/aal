#define USE_MIRACL
#define USE_MSIEVE

#ifdef USE_MIRACL

int sea_main(int argc,char **argv);
int shoof_main(int argc,char **argv);
int shoof2_main(int argc,char **argv);
int modpol_main(int argc,char **argv);

#else

#ifdef __GNUC__
#define USE_MIRACL
#endif

#define sea_main(a,b) ;
#define shoof_main(a,b) ;
#define shoof2_main(a,b) ;
#define modpol_main(a,b) ;

#endif

//другие способы: http://www.rsdn.ru/article/qna/baseserv/fileexist.xml
#define FileExists(fname) (std::ifstream(fname) != NULL)

#ifdef USE_MSIEVE
//msieve library
extern "C" {
  int msieve_main(int argc, char **argv);
}
#else
#ifdef __GNUC__
#define USE_MSIEVE
#endif
#define msieve_main(a,b) ;
#endif
