# Add header here if it needs to be mocked
mocked_headers = [
    meson.project_source_root() / 'include/hse/hse.h',
    meson.project_source_root() / 'lib/c0/c0sk_internal.h',
    meson.project_source_root() / 'lib/cn/cn_cursor.h',
    meson.project_source_root() / 'lib/cn/cndb_internal.h',
    meson.project_source_root() / 'lib/cn/cn_mblocks.h',
    meson.project_source_root() / 'lib/cn/cn_tree_compact.h',
    meson.project_source_root() / 'lib/cn/cn_tree_create.h',
    meson.project_source_root() / 'lib/cn/cn_tree_cursor.h',
    meson.project_source_root() / 'lib/cn/cn_tree.h',
    meson.project_source_root() / 'lib/cn/cn_tree_internal.h',
    meson.project_source_root() / 'lib/cn/cn_tree_iter.h',
    meson.project_source_root() / 'lib/cn/cn_tree_stats.h',
    meson.project_source_root() / 'lib/cn/csched_noop.h',
    meson.project_source_root() / 'lib/cn/csched_sp3.h',
    meson.project_source_root() / 'lib/cn/csched_sp3_work.h',
    meson.project_source_root() / 'lib/cn/kblock_builder.h',
    meson.project_source_root() / 'lib/cn/kcompact.h',
    meson.project_source_root() / 'lib/cn/kvset.h',
    meson.project_source_root() / 'lib/cn/mbset.h',
    meson.project_source_root() / 'lib/cn/spill.h',
    meson.project_source_root() / 'lib/cn/vblock_builder.h',
    meson.project_source_root() / 'lib/cn/wbt_builder.h',
    meson.project_source_root() / 'lib/cn/wbt_reader.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/c0.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/c0_kvmultiset.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/c0sk.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/cndb.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/cn.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/cn_kvdb.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/cn_tree_view.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/csched.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/ikvdb.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/kvset_builder.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/kvdb_ctxn.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/kvset_view.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/kvs.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/lc.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/sched_sts.h',
    meson.project_source_root() / 'lib/include/hse_ikvdb/wal.h',
    meson.project_source_root() / 'lib/kvdb/kvdb_keylock.h',
    meson.project_source_root() / 'lib/kvdb/kvdb_log.h',
    meson.project_source_root() / 'lib/kvdb/sched_sts_perfc.h',
    meson.project_source_root() / 'lib/lc/bonsai_iter.h',
    meson.project_source_root() / 'lib/mpool/include/mpool/mpool.h',
    meson.project_source_root() / 'lib/util/include/hse_util/alloc.h',
    meson.project_source_root() / 'lib/util/include/hse_util/hlog.h',
    meson.project_source_root() / 'lib/util/include/hse_util/keylock.h',
    meson.project_source_root() / 'lib/util/include/hse_util/perfc.h',
    meson.project_source_root() / 'lib/util/include/hse_util/platform.h',
    meson.project_source_root() / 'lib/util/include/hse_util/slab.h',
    meson.project_source_root() / 'lib/util/include/hse_util/token_bucket.h',
    meson.project_source_root() / 'lib/util/include/hse_util/workqueue.h',
    meson.project_source_root() / 'lib/util/src/logging_util.h',
    meson.project_source_root() / 'tests/support/include/hse_test_support/allocation.h',
]

mapi_idx_h = custom_target(
    'mapi-idx-h',
    command: [
        mapi_idx_generate,
        '@OUTPUT@',
        meson.project_source_root(),
        '@PRIVATE_DIR@',
        '@0@'.format(' '.join(mocked_headers)),
    ],
    depend_files: mocked_headers,
    output: 'mapi_idx.h',
)

mocked_components = {
    'c0': meson.project_source_root() / 'lib' / 'c0',
    'lc': meson.project_source_root() / 'lib' / 'lc',
    'cn': meson.project_source_root() / 'lib' / 'cn',
    'wal': meson.project_source_root() / 'lib' / 'wal',
    'hse': meson.project_source_root() / 'include' / 'hse',
    'ikvdb': meson.project_source_root() / 'lib' / 'include' / 'hse_ikvdb',
    'kvdb': meson.project_source_root() / 'lib' / 'kvdb',
    'kvs': meson.project_source_root() / 'lib' / 'kvs',
    'mpool': meson.project_source_root() / 'lib' / 'mpool' / 'include' / 'mpool',
    'test-support': meson.project_source_root() / 'tests' / 'support' / 'include' / 'hse_test_support',
    'util': meson.project_source_root() / 'lib' / 'util' / 'include' / 'hse_util',
    'util-internal': meson.project_source_root() / 'lib' / 'util' / 'src',
}

mock_includes = include_directories('.')
mock_sources = [mapi_idx_h]

foreach mc, source_dir : mocked_components
    if not fs.exists(source_dir)
        error('@0@ does not exist'.format(source_dir))
    endif

    ut_mock_decl_files_output = run_command(
        ut_mock_decl_files,
        source_dir,
        check: true,
    ).stdout().strip()

    if ut_mock_decl_files_output == ''
        continue
    endif

    mock_decl_files = ut_mock_decl_files_output.split('\n')

    foreach f : mock_decl_files
        stem = fs.stem(f)

        hdr = '@0@_ut.h'.format(stem)
        mock_decl = custom_target(
            '@0@.@1@-utpp-h'.format(mc, stem),
            build_by_default: true,
            input: f,
            command: [
                utpp,
                '--',
                '-h',
                '-o',
                '@OUTDIR@' / hdr,
                '@INPUT@',
            ],
            depend_files: [f],
            output: hdr,
        )

        mock_sources += mock_decl

        src = '@0@_ut_impl.i'.format(stem)
        mock_impl = custom_target(
            '@0@.@1@-utpp-c'.format(mc, stem),
            build_by_default: true,
            input: f,
            command: [
                utpp,
                '--',
                '-c',
                '-o',
                '@OUTDIR@' / src,
                '@INPUT@',
            ],
            depend_files: [f],
            output: src,
        )

        mock_sources += mock_impl
    endforeach
endforeach
