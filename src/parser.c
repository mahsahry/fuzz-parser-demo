#include <stddef.h>
#include <string.h>
#include <stdint.h>

int parse_kv(const uint8_t *data, size_t len) {
    const uint8_t *eq = memchr(data, '=', len);
    if (!eq) return 0;

    size_t vlen = (size_t)(data + len - (eq + 1));
    if (vlen == 0) return 0;

    char value[32];

    size_t to_copy = vlen;
    if (to_copy >= sizeof(value)) {
    to_copy = sizeof(value) - 1;
}
    memcpy(value, eq + 1, to_copy);
    value[to_copy] = '\0';

    if (value[0] == 'A') return 1;
    return 0;
}
