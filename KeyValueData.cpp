#include "KeyValueData.h"


KeyValueData::KeyValueData() : buf_len(STORAGE_BUF_SIZE)
{
    num_vars = 0;
    start_pos = 0;
    strcpy(error, "");
    memset(buf, 0, buf_len);
    memset(vars, 0, MAX_NUM_VARS);
}

const char *KeyValueData::getVar(const char *const key)
{
    if (!num_vars) return reportError(key);

    for (int i=0; i<num_vars; i++)
    {
        // See if a key value pair is found
        if (!strcmp(key, &buf[vars[i].key_off])) return &buf[vars[i].data_off];
    }
    return reportError(key);
}

const char *KeyValueData::addVar(const char *const key, const char *const data)
{
    struct ViewVar var;
    uint16_t tmp;
    uint16_t key_len = strlen(key)+1;
    uint16_t data_len = strlen(data)+1;
    if (isFull() || start_pos + key_len + data_len > buf_len) return NULL;

    strcpy(&buf[start_pos], key);
    var.key_off = start_pos;

    strcpy(&buf[start_pos + key_len], data);
    var.data_off = start_pos+key_len;

    vars[num_vars++] = var;
    tmp = start_pos;
    start_pos += key_len + data_len;

    return &buf[tmp];
}

const char *KeyValueData::reportError(const char *const key)
{
    sprintf(error, UNSET_VAR_MESSAGE, key);
    return error;
}

bool KeyValueData::isFull()
{
    return num_vars >= MAX_NUM_VARS || buf_len <= start_pos;
}
