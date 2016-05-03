#ifndef __JSON_H__
#define __JSON_H__

/*JSON type define*/
#define JSON_False      (1<<0)
#define JSON_True       (1<<1)
#define JSON_NULL       (1<<2)
#define JSON_Number     (1<<3)
#define JSON_String     (1<<4)
#define JSON_Array      (1<<5)
#define JSON_Object     (1<<6)


typedef struct JSON_t{
    struct JSON_t *next,*prev;
    struct JSON_T *child;
    int type;
    char *valuestring;
    int valueint;
    double valuedouble;
    char *string;    
} JSON_t;


extern JSON_t *Parse(const char *value);


#endif 
