#ifndef DUMP_BTRFS_UUID_H
#define DUMP_BTRFS_UUID_H

typedef unsigned char uuid_t[16];

void uuid_unparse(const uuid_t uu, char *out);
int uuid_parse(const char *in, uuid_t uu);
void uuid_generate(uuid_t out);
int uuid_is_null(const uuid_t uu);

#endif
