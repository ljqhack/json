#include "json.h"

static JSON_t * NewItem(void)
{
    JSON_t *node = (JSON_t*)malloc(sizeof(JSON_t));
    if(node)
    {
        memset(node, 0, sizeof(JSON_t));
    }
    return node;
}

void DeleteItem(JSON_t *c)
{
    JSON_t *node = c;
    while(node)
    {
        
    }
}

JSON_t *Parse(const char *value)
{
    
}
