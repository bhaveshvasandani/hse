/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (C) 2015-2020 Micron Technology, Inc.  All rights reserved.
 */

#ifndef HSE_KVDB_KVDB_LOG_H
#define HSE_KVDB_KVDB_LOG_H

#include <hse_util/platform.h>
#include <hse_util/alloc.h>
#include <hse_util/slab.h>
#include <hse_util/page.h>
#include <hse_util/logging.h>
#include <hse_util/hse_err.h>
#include <hse_util/event_counter.h>

#include <hse/hse.h>
#include <mpool/mpool_structs.h>

#include <hse_ikvdb/../../kvdb/kvdb_omf.h>

/* MTF_MOCK_DECL(kvdb_log) */

#define KVDB_LOG_TABLE_DEFAULT 8192
#define KVDB_LOG_HIGH_WATER(log) (log->kl_captgt * 3 / 4)

struct kvdb_kvs;
struct mpool;
struct mpool_mdc;

struct kvdb_mdh {
    u32 mdh_type;
    u32 mdh_serial; /* order in which records appeared in log */
};

struct kvdb_mclass {
    struct kvdb_mdh mc_hdr;
    u32             mc_id;
    u32             mc_pathlen;
    char            mc_path[PATH_MAX];
};

struct kvdb_log {
    struct mpool_mdc *kl_mdc; /* our MDC */
    struct mpool *    kl_mp;  /* mpool operating upon */
    struct table *    kl_work;
    struct table *    kl_work_old;
    u64               kl_captgt;
    u64               kl_highwater;
    u64               kl_serial;
    u64               kl_cndb_oid1;
    u64               kl_cndb_oid2;
    u64               kl_wal_oid1;
    u64               kl_wal_oid2;
    bool              kl_rdonly;

    struct kvdb_mclass kl_mc[MP_MED_COUNT];

    /* buffering MDC I/O -- NB: cannot mix reads and writes */
    unsigned char kl_buf[KVDB_OMF_REC_MAX];
};

struct kvdb_mdv {
    struct kvdb_mdh mdv_hdr;
    u32             mdv_magic;
    u32             mdv_version;
    u64             mdv_captgt;
};

struct kvdb_mdc {
    struct kvdb_mdh mdc_hdr;
    u32             mdc_disp;
    u32             mdc_id;
    u64             mdc_new_oid1;
    u64             mdc_new_oid2;
};

union kvdb_mdu {
    struct kvdb_mdh h;
    struct kvdb_mdv v;
    struct kvdb_mdc c;
};

struct kvdb_log_tx;

/* MTF_MOCK */
merr_t
kvdb_log_replay(struct kvdb_log *log);

/* MTF_MOCK */
merr_t
kvdb_log_open(const char *kvdb_home, struct mpool *mpool, int mode, struct kvdb_log **handle);

/* MTF_MOCK */
merr_t
kvdb_log_close(struct kvdb_log *log);

merr_t
kvdb_log_usage(struct kvdb_log *log, uint64_t *allocated, uint64_t *used);

/*----------------------------------------------------------------
 * Quasi-external kvdb_log API - probably not best to call directly
 *
 * These methods define actions that could be called independently,
 * but the above open/replay/save/close should be complete.
 */

/* MTF_MOCK */
merr_t
kvdb_log_create(struct kvdb_log *log, u64 captgt, const struct kvdb_cparams *params);

/* MTF_MOCK */
merr_t
kvdb_log_rollover(struct kvdb_log *log);

/* MTF_MOCK */
merr_t
kvdb_log_compact(struct kvdb_log *log);

/* MTF_MOCK */
merr_t
kvdb_log_mdc_create(
    struct kvdb_log *    log,
    enum kvdb_log_mdc_id mdcid,
    u64                  oid1,
    u64                  oid2,
    struct kvdb_log_tx **tx);

/* MTF_MOCK */
merr_t
kvdb_log_abort(struct kvdb_log *log, struct kvdb_log_tx *tx);

/* MTF_MOCK */
merr_t
kvdb_log_done(struct kvdb_log *log, struct kvdb_log_tx *tx);

/* MTF_MOCK */
void
kvdb_log_cndboid_get(struct kvdb_log *log, u64 *cndb_oid1, u64 *cndb_oid2);

/* MTF_MOCK */
void
kvdb_log_waloid_get(struct kvdb_log *log, u64 *wal_oid1, u64 *wal_oid2);

/* MTF_MOCK */
merr_t
kvdb_log_deserialize_to_kvdb_rparams(const char *kvdb_home, struct kvdb_rparams *params);

/* MTF_MOCK */
merr_t
kvdb_log_deserialize_to_kvdb_dparams(const char *kvdb_home, struct kvdb_dparams *params);

/* PRIVATE */
bool
kvdb_log_finished(union kvdb_mdu *mdp);

/* PRIVATE */
merr_t
kvdb_log_disp_set(union kvdb_mdu *mdp, enum kvdb_log_disp disp);

#if HSE_MOCKING
#include "kvdb_log_ut.h"
#endif /* HSE_MOCKING */

#endif
