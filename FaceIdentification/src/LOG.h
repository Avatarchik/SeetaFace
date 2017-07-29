#ifndef __LOG_H__
#define __LOG_H__

#if  defined (_MSC_VER) || defined (_WIN32) || defined (_WIN64) || defined(__linux__) || defined(__linux)

//#define LOG   printf
#define CHECK(x)	  { if(!(x)){ printf("[ERROR] @ %s:%d\n",__FILE__,__LINE__);system("pause");throw(__FILE__);} }

#define uCHECK(x,uFaceErrorCode)	  { if(!(x)){ printf("[ERROR] @ %s:%d ErrorCode=%d\n",__FILE__,__LINE__,uFaceErrorCode);throw(uFaceErrorCode);} }


#define LOG(...)      {printf(__VA_ARGS__);}
#define LOGI(...)     {printf("[INFO]  "); printf(__VA_ARGS__);printf("\n");}
//#define LOGE(...)     printf("[ERROR] "); printf(__VA_ARGS__)

#define LOGT()     {printf("[TAG] File %s:%d\n",__FILE__, __LINE__);}

#define LOGW(...)     {printf("[WARN] "); printf(__VA_ARGS__);printf("\n");}

#define LOGE(...)     {printf("[ERROR] File %s:%d  ",__FILE__, __LINE__); printf(__VA_ARGS__);printf("\n");}

//#define LOGE2(format, ...) {printf("[ERROR] File %s:%d  ",__FILE__, __LINE__,"format"/n", __LINE__, ##__VA_ARGS__);}

//printf("FILE: "__FILE__", LINE: %d: "format"/n", __LINE__, ##__VA_ARGS__)

//#define LOGE()        {printf("[ERROR] File %s:%d\n",__FILE__, __LINE__);}
//#define LOGE(val)       printf("[ERROR] File %s:%d %s\n fun:s",__FILE__, __LINE__, #val)     


#else

#define LOG(_Expression)     ((void)0)
#define LOGI LOG
#define LOGE LOG

#endif


#endif
