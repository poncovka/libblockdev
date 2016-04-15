#include <glib.h>
#include <utils.h>

#ifndef BD_LVM
#define BD_LVM

#define LVM_MIN_VERSION "2.02.116"

#ifdef __LP64__
// 64bit system
#define BD_LVM_MAX_LV_SIZE (8 EiB)
#else
// 32bit system
#define BD_LVM_MAX_LV_SIZE (16 TiB)
#endif

#define BD_LVM_DEFAULT_PE_START (1 MiB)
#define BD_LVM_DEFAULT_PE_SIZE (4 MiB)
#define BD_LVM_MIN_PE_SIZE (1 KiB)
#define BD_LVM_MAX_PE_SIZE (16 GiB)
#define USE_DEFAULT_PE_SIZE 0
#define RESOLVE_PE_SIZE(size) ((size) == USE_DEFAULT_PE_SIZE ? BD_LVM_DEFAULT_PE_SIZE : (size))

#define BD_LVM_MIN_THPOOL_MD_SIZE (2 MiB)
#define BD_LVM_MAX_THPOOL_MD_SIZE (16 GiB)
#define BD_LVM_MIN_THPOOL_CHUNK_SIZE (64 KiB)
#define BD_LVM_MAX_THPOOL_CHUNK_SIZE (1 GiB)
#define THPOOL_MD_FACTOR_NEW (0.2)
#define THPOOL_MD_FACTOR_EXISTS (1 / 6.0)

/* according to lvmcache (7) */
#define BD_LVM_MIN_CACHE_MD_SIZE (8 MiB)

GQuark bd_lvm_error_quark (void);
#define BD_LVM_ERROR bd_lvm_error_quark ()
typedef enum {
    BD_LVM_ERROR_PARSE,
    BD_LVM_ERROR_NOEXIST,
    BD_LVM_ERROR_DM_ERROR,
    BD_LVM_ERROR_NOT_ROOT,
    BD_LVM_ERROR_CACHE_INVAL,
    BD_LVM_ERROR_CACHE_NOCACHE,
} BDLVMError;

typedef enum {
    BD_LVM_CACHE_POOL_STRIPED = 1 << 0,
    BD_LVM_CACHE_POOL_RAID1 =    1 << 1,
    BD_LVM_CACHE_POOL_RAID5 =    1 << 2,
    BD_LVM_CACHE_POOL_RAID6 =    1 << 3,
    BD_LVM_CACHE_POOL_RAID10 =   1 << 4,

    BD_LVM_CACHE_POOL_META_STRIPED = 1 << 10,
    BD_LVM_CACHE_POOL_META_RAID1 =    1 << 11,
    BD_LVM_CACHE_POOL_META_RAID5 =    1 << 12,
    BD_LVM_CACHE_POOL_META_RAID6 =    1 << 13,
    BD_LVM_CACHE_POOL_META_RAID10 =   1 << 14,
} BDLVMCachePoolFlags;

typedef enum {
    BD_LVM_CACHE_MODE_WRITETHROUGH,
    BD_LVM_CACHE_MODE_WRITEBACK,
    BD_LVM_CACHE_MODE_UNKNOWN,
} BDLVMCacheMode;

typedef struct BDLVMPVdata {
    gchar *pv_name;
    gchar *pv_uuid;
    guint64 pv_free;
    guint64 pv_size;
    guint64 pe_start;
    gchar *vg_name;
    gchar *vg_uuid;
    guint64 vg_size;
    guint64 vg_free;
    guint64 vg_extent_size;
    guint64 vg_extent_count;
    guint64 vg_free_count;
    guint64 vg_pv_count;
} BDLVMPVdata;

void bd_lvm_pvdata_free (BDLVMPVdata *data);
BDLVMPVdata* bd_lvm_pvdata_copy (BDLVMPVdata *data);

typedef struct BDLVMVGdata {
    gchar *name;
    gchar *uuid;
    guint64 size;
    guint64 free;
    guint64 extent_size;
    guint64 extent_count;
    guint64 free_count;
    guint64 pv_count;
} BDLVMVGdata;

void bd_lvm_vgdata_free (BDLVMVGdata *data);
BDLVMVGdata* bd_lvm_vgdata_copy (BDLVMVGdata *data);

typedef struct BDLVMLVdata {
    gchar *lv_name;
    gchar *vg_name;
    gchar *uuid;
    guint64 size;
    gchar *attr;
    gchar *segtype;
} BDLVMLVdata;

void bd_lvm_lvdata_free (BDLVMLVdata *data);
BDLVMLVdata* bd_lvm_lvdata_copy (BDLVMLVdata *data);

typedef struct BDLVMCacheStats {
    guint64 block_size;
    guint64 cache_size;
    guint64 cache_used;
    guint64 md_block_size;
    guint64 md_size;
    guint64 md_used;
    guint64 read_hits;
    guint64 read_misses;
    guint64 write_hits;
    guint64 write_misses;
    BDLVMCacheMode mode;
} BDLVMCacheStats;

void bd_lvm_cache_stats_free (BDLVMCacheStats *data);
BDLVMCacheStats* bd_lvm_cache_stats_copy (BDLVMCacheStats *data);

gboolean bd_lvm_is_supported_pe_size (guint64 size, GError **error);
guint64 *bd_lvm_get_supported_pe_sizes (GError **error);
guint64 bd_lvm_get_max_lv_size (GError **error);
guint64 bd_lvm_round_size_to_pe (guint64 size, guint64 pe_size, gboolean roundup, GError **error);
guint64 bd_lvm_get_lv_physical_size (guint64 lv_size, guint64 pe_size, GError **error);
guint64 bd_lvm_get_thpool_padding (guint64 size, guint64 pe_size, gboolean included, GError **error);
gboolean bd_lvm_is_valid_thpool_md_size (guint64 size, GError **error);
gboolean bd_lvm_is_valid_thpool_chunk_size (guint64 size, gboolean discard, GError **error);

gboolean bd_lvm_pvcreate (gchar *device, guint64 data_alignment, guint64 metadata_size, BDExtraArg **extra, GError **error);
gboolean bd_lvm_pvresize (gchar *device, guint64 size, BDExtraArg **extra, GError **error);
gboolean bd_lvm_pvremove (gchar *device, BDExtraArg **extra, GError **error);
gboolean bd_lvm_pvmove (gchar *src, gchar *dest, BDExtraArg **extra, GError **error);
gboolean bd_lvm_pvscan (gchar *device, gboolean update_cache, BDExtraArg **extra, GError **error);
BDLVMPVdata* bd_lvm_pvinfo (gchar *device, GError **error);
BDLVMPVdata** bd_lvm_pvs (GError **error);

gboolean bd_lvm_vgcreate (gchar *name, gchar **pv_list, guint64 pe_size, BDExtraArg **extra, GError **error);
gboolean bd_lvm_vgremove (gchar *vg_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_vgrename (gchar *old_vg_name, gchar *new_vg_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_vgactivate (gchar *vg_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_vgdeactivate (gchar *vg_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_vgextend (gchar *vg_name, gchar *device, BDExtraArg **extra, GError **error);
gboolean bd_lvm_vgreduce (gchar *vg_name, gchar *device, BDExtraArg **extra, GError **error);
BDLVMVGdata* bd_lvm_vginfo (gchar *vg_name, GError **error);
BDLVMVGdata** bd_lvm_vgs (GError **error);

gchar* bd_lvm_lvorigin (gchar *vg_name, gchar *lv_name, GError **error);
gboolean bd_lvm_lvcreate (gchar *vg_name, gchar *lv_name, guint64 size, gchar *type, gchar **pv_list, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvremove (gchar *vg_name, gchar *lv_name, gboolean force, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvrename (gchar *vg_name, gchar *lv_name, gchar *new_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvresize (gchar *vg_name, gchar *lv_name, guint64 size, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvactivate (gchar *vg_name, gchar *lv_name, gboolean ignore_skip, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvdeactivate (gchar *vg_name, gchar *lv_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvsnapshotcreate (gchar *vg_name, gchar *origin_name, gchar *snapshot_name, guint64 size, BDExtraArg **extra, GError **error);
gboolean bd_lvm_lvsnapshotmerge (gchar *vg_name, gchar *snapshot_name, BDExtraArg **extra, GError **error);
BDLVMLVdata* bd_lvm_lvinfo (gchar *vg_name, gchar *lv_name, GError **error);
BDLVMLVdata** bd_lvm_lvs (gchar *vg_name, GError **error);

gboolean bd_lvm_thpoolcreate (gchar *vg_name, gchar *lv_name, guint64 size, guint64 md_size, guint64 chunk_size, gchar *profile, BDExtraArg **extra, GError **error);
gboolean bd_lvm_thlvcreate (gchar *vg_name, gchar *pool_name, gchar *lv_name, guint64 size, BDExtraArg **extra, GError **error);
gchar* bd_lvm_thlvpoolname (gchar *vg_name, gchar *lv_name, GError **error);
gboolean bd_lvm_thsnapshotcreate (gchar *vg_name, gchar *origin_name, gchar *snapshot_name, gchar *pool_name, BDExtraArg **extra, GError **error);
gboolean bd_lvm_set_global_config (gchar *new_config, GError **error);
gchar* bd_lvm_get_global_config (GError **error);

guint64 bd_lvm_cache_get_default_md_size (guint64 cache_size, GError **error);
const gchar* bd_lvm_cache_get_mode_str (BDLVMCacheMode mode, GError **error);
BDLVMCacheMode bd_lvm_cache_get_mode_from_str (gchar *mode_str, GError **error);
gboolean bd_lvm_cache_create_pool (gchar *vg_name, gchar *pool_name, guint64 pool_size, guint64 md_size, BDLVMCacheMode mode, BDLVMCachePoolFlags flags, gchar **fast_pvs, GError **error);
gboolean bd_lvm_cache_attach (gchar *vg_name, gchar *data_lv, gchar *cache_pool_lv, BDExtraArg **extra, GError **error);
gboolean bd_lvm_cache_detach (gchar *vg_name, gchar *cached_lv, gboolean destroy, BDExtraArg **extra, GError **error);
gboolean bd_lvm_cache_create_cached_lv (gchar *vg_name, gchar *lv_name, guint64 data_size, guint64 cache_size, guint64 md_size, BDLVMCacheMode mode, BDLVMCachePoolFlags flags,
                                        gchar **slow_pvs, gchar **fast_pvs, GError **error);
gchar* bd_lvm_cache_pool_name (gchar *vg_name, gchar *cached_lv, GError **error);
BDLVMCacheStats* bd_lvm_cache_stats (gchar *vg_name, gchar *cached_lv, GError **error);

gchar* bd_lvm_data_lv_name (gchar *vg_name, gchar *lv_name, GError **error);
gchar* bd_lvm_metadata_lv_name (gchar *vg_name, gchar *lv_name, GError **error);

#endif /* BD_LVM */
