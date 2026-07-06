CC ?= cc

CFLAGS ?= -O2 -g
CPPFLAGS += \
	-std=gnu11 \
	-include include/config.h \
	-D_XOPEN_SOURCE=700 \
	-D_GNU_SOURCE \
	-fno-strict-aliasing \
	-ffunction-sections \
	-fdata-sections \
	-Wall \
	-Wunused-but-set-parameter \
	-Wno-missing-braces \
	-I. \
	-Iinclude
LDFLAGS += -Wl,--gc-sections
LDLIBS += -lpthread

OBJS = \
	main.o \
	standalone.o \
	kernel-lib/list_sort.o \
	kernel-lib/raid56.o \
	kernel-lib/rbtree.o \
	kernel-lib/tables.o \
	kernel-shared/accessors.o \
	kernel-shared/async-thread.o \
	kernel-shared/backref.o \
	kernel-shared/ctree.o \
	kernel-shared/delayed-ref.o \
	kernel-shared/dir-item.o \
	kernel-shared/disk-io.o \
	kernel-shared/extent-io-tree.o \
	kernel-shared/extent-tree.o \
	kernel-shared/extent_io.o \
	kernel-shared/file-item.o \
	kernel-shared/file.o \
	kernel-shared/free-space-cache.o \
	kernel-shared/free-space-tree.o \
	kernel-shared/inode-item.o \
	kernel-shared/inode.o \
	kernel-shared/locking.o \
	kernel-shared/messages.o \
	kernel-shared/print-tree.o \
	kernel-shared/root-tree.o \
	kernel-shared/transaction.o \
	kernel-shared/tree-checker.o \
	kernel-shared/ulist.o \
	kernel-shared/uuid-tree.o \
	kernel-shared/volumes.o \
	kernel-shared/zoned.o \
	common/array.o \
	common/compat.o \
	common/cpu-utils.o \
	common/extent-cache.o \
	common/extent-tree-utils.o \
	common/filesystem-utils.o \
	common/format-output.o \
	common/fsfeatures.o \
	common/inject-error.o \
	common/messages.o \
	common/parse-utils.o \
	common/path-utils.o \
	common/rbtree-utils.o \
	common/root-tree-utils.o \
	common/send-stream.o \
	common/send-utils.o \
	common/sort-utils.o \
	common/string-table.o \
	common/string-utils.o \
	common/sysfs-utils.o \
	common/task-utils.o \
	common/units.o \
	common/utils.o \
	crypto/crc32c.o \
	crypto/hash.o \
	crypto/sha224-256.o \
	crypto/blake2b-ref.o \
	crypto/xxhash.o

.PHONY: all clean

all: dump.btrfs

dump.btrfs: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f dump.btrfs $(OBJS)
