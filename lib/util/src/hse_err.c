/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (C) 2015-2020 Micron Technology, Inc.  All rights reserved.
 */

#include <hse_util/page.h>
#include <hse_util/minmax.h>
#include <hse_util/string.h>
#include <hse_util/hse_err.h>

#include <mpool/mpool.h>

#include <assert.h>
#include <ctype.h>

char hse_merr_bug0[] _merr_attributes = "hse_merr_bug0u";
char hse_merr_bug1[] _merr_attributes = "hse_merr_bug1u";
char hse_merr_bug2[] _merr_attributes = "hse_merr_bug2u";
char hse_merr_bug3[] _merr_attributes = "hse_merr_bug3u";
char hse_merr_base[] _merr_attributes = "hse_merr_baseu";

extern uint8_t __start_hse_merr;
extern uint8_t __stop_hse_merr;

merr_t
merr_pack(int errnum, const char *file, int line)
{
    merr_t err = 0;
    s64    off;

    if (errnum == 0)
        return 0;

    if (errnum < 0)
        errnum = -errnum;

    if (!file)
        goto finish;

    if (!IS_ALIGNED((ulong)file, sizeof(file)))
        file = hse_merr_bug0; /* invalid file */

    if (!(file > (char *)&__start_hse_merr ||
          file < (char *)&__stop_hse_merr))
        goto finish; /* file outside libhse */

    if (!IS_ALIGNED((ulong)file, MERR_ALIGN))
        file = hse_merr_bug1;

    off = (file - hse_merr_base) / MERR_ALIGN;

    if (((s64)((u64)off << MERR_FILE_SHIFT) >> MERR_FILE_SHIFT) == off)
        err = (u64)off << MERR_FILE_SHIFT;

  finish:
    err |= (1ul << MERR_RSVD_SHIFT);
    err |= ((u64)line << MERR_LINE_SHIFT) & MERR_LINE_MASK;
    err |= errnum & MERR_ERRNO_MASK;

    return err;
}

const char *
merr_file(merr_t err)
{
    const char *file;
    s32         off;

    if (err == 0 || err == -1)
        return NULL;

    off = (s64)(err & MERR_FILE_MASK) >> MERR_FILE_SHIFT;
    if (off == 0)
        return NULL;

    file = hse_merr_base + (off * MERR_ALIGN);

    if (!(file > (char *)&__start_hse_merr ||
          file < (char *)&__stop_hse_merr))
        return hse_merr_bug3;

#ifdef HSE_REL_SRC_DIR
    if ((uintptr_t)file == (uintptr_t)hse_merr_bug0 ||
        (uintptr_t)file == (uintptr_t)hse_merr_bug1 ||
        (uintptr_t)file == (uintptr_t)hse_merr_bug2 ||
        (uintptr_t)file == (uintptr_t)hse_merr_bug3) {
        return file;
    }

    /* Point the file pointer past the prefix in order to retrieve the file
     * path relative to the HSE source tree.
     */
    file += sizeof(HSE_REL_SRC_DIR) - 1;
#endif

    return file;
}

size_t
merr_strerror(merr_t err, char *buf, size_t buf_sz)
{
    char errbuf[1024], *errmsg;
    int errnum = merr_errno(err);

    if (errnum == EBUG)
        return strlcpy(buf, "HSE software bug", buf_sz);

    /* GNU strerror only modifies errbuf if errnum is invalid.
     * It will only return NULL if errbuf is NULL.
     */
    errmsg = strerror_r(errnum, errbuf, sizeof(errbuf));

    return strlcpy(buf, errmsg, buf_sz);
}

char *
merr_strinfo(merr_t err, char *buf, size_t buf_sz, size_t *need_sz)
{
    ssize_t     sz = 0;
    const char *file = NULL;

    if (err) {
        file = merr_file(err);
        if (file)
            sz = snprintf(buf, buf_sz, "%s:%d: ", file, merr_lineno(err));
        if (sz < 0) {
            sz = strlcpy(buf, "<error formating error message>", buf_sz);
            goto out;
        }
        if (sz >= buf_sz)
            goto out;

        sz = merr_strerror(err, buf + sz, buf_sz - sz);
    } else {
        sz = strlcpy(buf, "success", buf_sz);
    }

out:
    if (need_sz)
        *need_sz = sz < 0 ? 0 : (size_t)sz;
    return buf;
}
