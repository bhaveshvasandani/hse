/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (C) 2016-2021 Micron Technology, Inc.  All rights reserved.
 */

#ifndef CLI_UTIL_H
#define CLI_UTIL_H

#include <stddef.h>

int
hse_kvdb_params(const char *kvdb_home, bool get);

int
kvdb_info_print(
    const char *         kvdb_home,
    const size_t         paramc,
    const char *const *  paramv,
    struct yaml_context *yc,
    bool                 verbose);

int
kvdb_compact_request(const char *kvdb_home, const char *request_type, unsigned timeout_sec);
#endif
