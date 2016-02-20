#ifndef VIEW_DATA
#define VIEW_DATA

#include <string.h>
#include "Arduino.h"

#define MAX_NUM_VARS 5
#define STORAGE_BUF_SIZE 50
#define MAX_ERROR_LEN 20
#define UNSET_VAR_MESSAGE "UNSET KEY: '%s'"

struct ViewVar
{
    // Key offset from buf pointer
    uint16_t key_off;

    // Data offset from buf pointer
    uint16_t data_off;
};

class KeyValueData
{
    private:
        const uint16_t buf_len;
        uint16_t num_vars;
        struct ViewVar vars[MAX_NUM_VARS];
        char buf[STORAGE_BUF_SIZE];
        uint16_t start_pos;
        char error[MAX_ERROR_LEN];

        const char *reportError(const char *const key);
    public:
        KeyValueData();
        const char *getVar(const char *const key);
        const char *addVar(const char *const key, const char *const data);
        //const char *addVar(int data);
        bool isFull();
};


#endif
