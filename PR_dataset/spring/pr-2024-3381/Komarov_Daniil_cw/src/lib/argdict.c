#include "../include/argdict.h"

// This function creates empty ArgDict object
//
// Return:
// ArgDict object on success, NULL if memory allocation error occured
ArgDict* argdict_new()
{
    ArgDict *result = (ArgDict *)malloc(sizeof(ArgDict));
    if(result == NULL) return NULL;
    result->len = 0;
    result->arr = (struct DictNode *)malloc(sizeof(struct DictNode));
    return result; 
}

// This function adds argument to ArgDict
// (Sets new value if this argument is already added)
//
// Arguments:
// dict - ptr to ArgDict object to add argument in
// key - dict entry key
// value - dict entry value
//
// Return:
// Return codes should be handled with handle_error() from "errors.h"
int argdict_set(ArgDict *dict, enum ArgType key, char *value)
{
    // Check if already added
    for(size_t i = 0; i < dict->len; i++)
    {
        if(dict->arr[i].key == key)
        {
            free(dict->arr[i].value);
            dict->arr[i].value = (char *)malloc(strlen(value)+1);
            // If memory error occurs, leave that entry unallocated
            // and return error code
            if(dict->arr[i].value == NULL) return RETCODE_MEMORY_ERROR;
            strcpy(dict->arr[i].value, value);
            return 0;
        }
    }
    
    // Add if not found
    struct DictNode *new_dict = (struct DictNode *)realloc(dict->arr, 
        sizeof(struct DictNode) * (dict->len + 1));
    
    if(new_dict == NULL) return RETCODE_MEMORY_ERROR;
    
    dict->arr = new_dict;
    dict->arr[dict->len].key = key;
    dict->arr[dict->len].value = (char *)malloc(strlen(value)+1);
    // If memory error occurs, leave that entry unallocated
    // and return error code
    if(dict->arr[dict->len].value == NULL) return RETCODE_MEMORY_ERROR;
    
    strcpy(dict->arr[dict->len].value, value);
    dict->len++;
    return RETCODE_OK;
}

// Find value by key in ArgDict
// Warning: *result will be allocated
// if key found in ArgDict, so if it's already a pointer,
// memory leak occurs
//
// Return:
// 0 = OK, value stored in *result
// 1 = Not found (*result stays unmodified)
int argdict_find(ArgDict *dict, enum ArgType key, char **result)
{
    for(size_t i = 0; i < dict->len; i++)
    {
        if(dict->arr[i].key == key)
        {
            if(result != NULL)
            {
                *result = (char *)malloc(strlen(dict->arr[i].value)+1);
                strcpy(*result, dict->arr[i].value);
            }
            return 0;
        }
    }
    return 1;
}

// Delete ArgDict object
//
// Arguments:
// dict - ptr to ArgDict to destroy
void argdict_del(ArgDict *dict)
{
    for(size_t i = 0; i < dict->len; i++)
    {
        // Unallocated values can occur if some memory allocations
        // errors happend previously, so checking every value before free
        if(dict->arr[i].value != NULL) free(dict->arr[i].value);
    }
    free(dict->arr);
    free(dict);
}
