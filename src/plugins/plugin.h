#ifndef PLUGIN_H
#define PLUGIN_H

ssize_t (*plugin_read)(void *buf, size_t nbytes);
ssize_t (*plugin_write)(const void *buf, size_t num);

#endif

