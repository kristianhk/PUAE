#pragma once
#ifndef SRC_INCLUDE_OPTIONS_H_INCLUDED
#define SRC_INCLUDE_OPTIONS_H_INCLUDED 1

/*
 * UAE - The Un*x Amiga Emulator
 *
 * Stuff
 *
 * Copyright 1995, 1996 Ed Hanway
 * Copyright 1995-2001 Bernd Schmidt
 */

#define UAEMAJOR 2
#define UAEMINOR 7
#define UAESUBREV 0

#include "uae_types.h"

typedef enum { KBD_LANG_US, KBD_LANG_DK, KBD_LANG_DE, KBD_LANG_SE, KBD_LANG_FR, KBD_LANG_IT, KBD_LANG_ES, KBD_LANG_FI, KBD_LANG_TR } KbdLang;

extern long int version;
struct uaedev_mount_info;
struct zfile;

#define MAX_PATHS 8
#ifndef PATH_MAX
#define PATH_MAX 256
#endif

struct multipath {
	TCHAR path[MAX_PATHS][PATH_MAX];
};

struct strlist {
	struct strlist *next;
	TCHAR *option, *value;
	int unknown;
};

#define MAX_TOTAL_SCSI_DEVICES 8

/* maximum number native input devices supported (single type) */
#define MAX_INPUT_DEVICES 16
/* maximum number of native input device's buttons and axles supported */
#define MAX_INPUT_DEVICE_EVENTS 256
/* 4 different customization settings */
#define MAX_INPUT_SETTINGS 4
#define GAMEPORT_INPUT_SETTINGS 3 // last slot is for gameport panel mappings

#define MAX_INPUT_SUB_EVENT 8
#define MAX_INPUT_SUB_EVENT_ALL 9
#define SPARE_SUB_EVENT 8

// this better be here than in sound.h -mustafa.
#define FILTER_SOUND_OFF 0
#define FILTER_SOUND_EMUL 1
#define FILTER_SOUND_ON 2

#define FILTER_SOUND_TYPE_A500 0
#define FILTER_SOUND_TYPE_A1200 1

#define INTERNALEVENT_COUNT 1

struct uae_input_device {
	TCHAR *name;
	TCHAR *configname;
	uae_s16 eventid[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT_ALL];
	TCHAR *custom[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT_ALL];
	uae_u64 flags[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT_ALL];
	uae_s8 port[MAX_INPUT_DEVICE_EVENTS][MAX_INPUT_SUB_EVENT_ALL];
	uae_s16 extra[MAX_INPUT_DEVICE_EVENTS];
	uae_s8 enabled;
};

#define MAX_JPORTS 4
#define NORMAL_JPORTS 2
#define MAX_JPORTNAME 128
struct jport {
	int id;
	int mode; // 0=def,1=mouse,2=joy,3=anajoy,4=lightpen
	int autofire;
	TCHAR name[MAX_JPORTNAME];
	TCHAR configname[MAX_JPORTNAME];
};
#define JPORT_NONE -1
#define JPORT_CUSTOM -2
#define JPORT_AF_NORMAL 1
#define JPORT_AF_TOGGLE 2
#define JPORT_AF_ALWAYS 3

#define KBTYPE_AMIGA 0
#define KBTYPE_PC1 1
#define KBTYPE_PC2 2

#define MAX_SPARE_DRIVES 20
#define MAX_CUSTOM_MEMORY_ADDRS 2

#define CONFIG_TYPE_HARDWARE 1
#define CONFIG_TYPE_HOST 2
#define CONFIG_BLEN 2560

#define TABLET_OFF 0
#define TABLET_MOUSEHACK 1
#define TABLET_REAL 2

struct cdslot
{
	TCHAR name[MAX_DPATH];
	bool inuse;
	bool delayed;
	int type;
};
struct floppyslot
{
	TCHAR df[MAX_DPATH];
	int dfxtype;
	int dfxclick;
	TCHAR dfxclickexternal[256];
	bool forcedwriteprotect;
};

#define ASPECTMULT 1024
#define WH_NATIVE 1
struct wh {
	int x, y;
	int width, height;
	int special;
};

#define MOUNT_CONFIG_SIZE 30
#define UAEDEV_DIR 0
#define UAEDEV_HDF 1
#define UAEDEV_CD 2
#define UAEDEV_TAPE 3

#define BOOTPRI_NOAUTOBOOT -128
#define BOOTPRI_NOAUTOMOUNT -129
#define ISAUTOBOOT(ci) ((ci)->bootpri > BOOTPRI_NOAUTOBOOT)
#define ISAUTOMOUNT(ci) ((ci)->bootpri > BOOTPRI_NOAUTOMOUNT)
#ifndef HAS_UAEDEV_CONFIG_INFO
# define HAS_UAEDEV_CONFIG_INFO 1
#endif // HAS_UAEDEV_CONFIG_INFO
struct uaedev_config_info {
	int type;
	TCHAR devname[MAX_DPATH];
	TCHAR volname[MAX_DPATH];
	TCHAR rootdir[MAX_DPATH];
	bool readonly;
	int bootpri;
	TCHAR filesys[MAX_DPATH];
	int lowcyl;
	int highcyl; // zero if detected from size
	int cyls; // calculated/corrected highcyl
	int surfaces;
	int sectors;
	int reserved;
	int blocksize;
	int controller;
	// zero if default
	int pcyls, pheads, psecs;
	int flags;
	int buffers;
	int bufmemtype;
	int stacksize;
	int priority;
	uae_u32 mask;
	int maxtransfer;
	uae_u32 dostype;
	int unit;
	int interleave;
	int sectorsperblock;
	int forceload;
	int device_emu_unit;

};

#ifndef HAS_UAEDEV_CONFIG_DATA
# define HAS_UAEDEV_CONFIG_DATA 1
#endif // HAS_UAEDEV_CONFIG_DATA
struct uaedev_config_data
{
	struct uaedev_config_info ci;
	int configoffset; // HD config entry index
	int unitnum; // scsi unit number (if tape currently)
};

enum { CP_GENERIC = 1, CP_CDTV, CP_CD32, CP_A500, CP_A500P, CP_A600, CP_A1000,
	CP_A1200, CP_A2000, CP_A3000, CP_A3000T, CP_A4000, CP_A4000T };

#define IDE_A600A1200 1
#define IDE_A4000 2

#define GFX_WINDOW 0
#define GFX_FULLSCREEN 1
#define GFX_FULLWINDOW 2

#define AUTOSCALE_NONE 0
#define AUTOSCALE_STATIC_AUTO 1
#define AUTOSCALE_STATIC_NOMINAL 2
#define AUTOSCALE_STATIC_MAX 3
#define AUTOSCALE_NORMAL 4
#define AUTOSCALE_RESIZE 5
#define AUTOSCALE_CENTER 6
#define AUTOSCALE_MANUAL 7 // use gfx_xcenter_pos and gfx_ycenter_pos
#define AUTOSCALE_INTEGER 8
#define AUTOSCALE_INTEGER_AUTOSCALE 9

#define MONITOREMU_NONE 0
#define MONITOREMU_AUTO 1
#define MONITOREMU_A2024 2
#define MONITOREMU_GRAFFITI 3

#define MAX_FILTERSHADERS 4

#define MAX_CHIPSET_REFRESH 10
#define MAX_CHIPSET_REFRESH_TOTAL (MAX_CHIPSET_REFRESH + 2)
#define CHIPSET_REFRESH_PAL (MAX_CHIPSET_REFRESH + 0)
#define CHIPSET_REFRESH_NTSC (MAX_CHIPSET_REFRESH + 1)
struct chipset_refresh
{
	int index;
	bool locked;
	bool rtg;
	int horiz;
	int vert;
	int lace;
	int ntsc;
	int vsync;
	int framelength;
	double rate;
	TCHAR label[16];
	TCHAR commands[256];
};

#define APMODE_NATIVE 0
#define APMODE_RTG 1

struct apmode
{
	int gfx_fullscreen;
	int gfx_display;
	int gfx_vsync;
	// 0 = immediate flip
	// -1 = wait for flip, before frame ends
	// 1 = wait for flip, after new frame has started
	int gfx_vflip;
	// doubleframemode strobo
	bool gfx_strobo;
	int gfx_vsyncmode;
	int gfx_backbuffers;
	bool gfx_interlaced;
	int gfx_refreshrate;
};

#ifndef HAS_UAE_PREFS_STRUCT
# define HAS_UAE_PREFS_STRUCT 1
#endif // HAS_UAEPREFS_STRUCT
struct uae_prefs {

	struct strlist *all_lines;

	TCHAR description[256];
	TCHAR info[256];
	int config_version;
	TCHAR config_hardware_path[MAX_DPATH];
	TCHAR config_host_path[MAX_DPATH];
	TCHAR config_window_title[256];

	bool illegal_mem;
	bool use_serial;
	bool serial_demand;
	bool serial_hwctsrts;
	bool serial_direct;
	int serial_stopbits;
	bool parallel_demand;
	int parallel_matrix_emulation;
	bool parallel_postscript_emulation;
	bool parallel_postscript_detection;
	int parallel_autoflush_time;
	TCHAR ghostscript_parameters[256];
	bool use_gfxlib;
	bool socket_emu;

#ifdef DEBUGGER
	bool start_debugger;
#endif
	bool start_gui;

	KbdLang keyboard_lang;

	int produce_sound;
	int sound_stereo;
	int sound_stereo_separation;
	int sound_mixed_stereo_delay;
	int sound_freq;
	int sound_maxbsiz;
	int sound_interpol;
	int sound_filter;
	int sound_filter_type;
	int sound_volume;
	int sound_volume_cd;
	bool sound_stereo_swap_paula;
	bool sound_stereo_swap_ahi;
	bool sound_auto;

	int sampler_freq;
	int sampler_buffer;
	bool sampler_stereo;

#ifdef JIT
	int comptrustbyte;
	int comptrustword;
	int comptrustlong;
	int comptrustnaddr;
	bool compnf;
	bool compfpu;
	bool comp_midopt;
	bool comp_lowopt;
	bool fpu_strict;

	bool comp_hardflush;
	bool comp_constjump;
	bool comp_oldsegv;

	int optcount[10];
#endif
	int cachesize;
	bool avoid_cmov;

	int gfx_framerate, gfx_autoframerate;
	struct wh gfx_size_win;
	struct wh gfx_size_fs;
	struct wh gfx_size;
	struct wh gfx_size_win_xtra[6];
	struct wh gfx_size_fs_xtra[6];
	bool gfx_autoresolution;
	int gfx_autoresolution_delay;
	int gfx_autoresolution_minv, gfx_autoresolution_minh;
	bool gfx_scandoubler;
	struct apmode gfx_apmode[2];
	int gfx_resolution;
	int gfx_vresolution;
	int gfx_lores_mode;
	int gfx_scanlines;
	int gfx_xcenter, gfx_ycenter;
	int gfx_xcenter_pos, gfx_ycenter_pos;
	int gfx_xcenter_size, gfx_ycenter_size;
	int gfx_max_horizontal, gfx_max_vertical;
	int gfx_saturation, gfx_luminance, gfx_contrast, gfx_gamma;
	bool gfx_blackerthanblack;
	int gfx_api;
	int color_mode;
	int gfx_extrawidth;
	bool lightboost_strobo;

	int gfx_filter;
	TCHAR gfx_filtershader[2 * MAX_FILTERSHADERS + 1][MAX_DPATH];
	TCHAR gfx_filtermask[2 * MAX_FILTERSHADERS + 1][MAX_DPATH];
	TCHAR gfx_filteroverlay[MAX_DPATH];
	struct wh gfx_filteroverlay_pos;
	int gfx_filteroverlay_overscan;
	int gfx_filter_scanlines;
	int gfx_filter_scanlineratio;
	int gfx_filter_scanlinelevel;
	float gfx_filter_horiz_zoom, gfx_filter_vert_zoom;
	float gfx_filter_horiz_zoom_mult, gfx_filter_vert_zoom_mult;
	float gfx_filter_horiz_offset, gfx_filter_vert_offset;
	int gfx_filter_filtermode;
	int gfx_filter_bilinear;
	int gfx_filter_noise, gfx_filter_blur;
	int gfx_filter_saturation, gfx_filter_luminance, gfx_filter_contrast, gfx_filter_gamma;
	int gfx_filter_keep_aspect, gfx_filter_aspect;
	int gfx_filter_autoscale;
	int gfx_filter_keep_autoscale_aspect;

	float rtg_horiz_zoom_mult;
	float rtg_vert_zoom_mult;

	bool immediate_blits;
	int waiting_blits;
	unsigned int chipset_mask;
	bool ntscmode;
	bool genlock;
	int monitoremu;
	double chipset_refreshrate;
	struct chipset_refresh cr[MAX_CHIPSET_REFRESH + 2];
	int cr_selected;
	int collision_level;
	int leds_on_screen;
	int leds_on_screen_mask[2];
	struct wh osd_pos;
	int keyboard_leds[3];
	bool keyboard_leds_in_use;
	int scsi;
	bool sana2;
	bool uaeserial;
	int catweasel;
	int catweasel_io;
	int cpu_idle;
	bool cpu_cycle_exact;
	int cpu_clock_multiplier;
	int cpu_frequency;
	bool blitter_cycle_exact;
	int floppy_speed;
	int floppy_write_length;
	int floppy_random_bits_min;
	int floppy_random_bits_max;
	int floppy_auto_ext2;
	bool tod_hack;
	uae_u32 maprom;
	bool rom_readwrite;
	int turbo_emulation;
	bool headless;
	int filesys_limit;
	int filesys_max_name;
	int filesys_max_file_size;

	int cs_compatible;
	int cs_ciaatod;
	int cs_rtc;
	int cs_rtc_adjust;
	int cs_rtc_adjust_mode;
	bool cs_ksmirror_e0;
	bool cs_ksmirror_a8;
	bool cs_ciaoverlay;
	bool cs_cd32cd;
	bool cs_cd32c2p;
	bool cs_cd32nvram;
	bool cs_cdtvcd;
	bool cs_cdtvram;
	int cs_cdtvcard;
	int cs_ide;
	bool cs_pcmcia;
	bool cs_a1000ram;
	int cs_fatgaryrev;
	int cs_ramseyrev;
	int cs_agnusrev;
	int cs_deniserev;
	int cs_mbdmac;
	bool cs_cdtvscsi;
	bool cs_a2091, cs_a4091;
	bool cs_df0idhw;
	bool cs_slowmemisfast;
	bool cs_resetwarning;
	bool cs_denisenoehb;
	bool cs_dipagnus;
	bool cs_agnusbltbusybug;
	bool cs_ciatodbug;
	int cs_hacks;

	TCHAR romfile[MAX_DPATH];
	TCHAR romident[256];
	TCHAR romextfile[MAX_DPATH];
	uae_u32 romextfile2addr;
	TCHAR romextfile2[MAX_DPATH];
	TCHAR romextident[256];
	TCHAR flashfile[MAX_DPATH];
	TCHAR rtcfile[MAX_DPATH];
#ifdef ACTION_REPLAY
	TCHAR cartfile[MAX_DPATH];
	TCHAR cartident[256];
	int cart_internal;
#endif
	TCHAR pci_devices[256];
	TCHAR prtname[256];
	TCHAR sername[256];
	TCHAR amaxromfile[MAX_DPATH];
	TCHAR a2065name[MAX_DPATH];
	struct cdslot cdslots[MAX_TOTAL_SCSI_DEVICES];
	TCHAR quitstatefile[MAX_DPATH];
	TCHAR statefile[MAX_DPATH];
	TCHAR inprecfile[MAX_DPATH];
	bool inprec_autoplay;
	char scsi_device[256];

	struct multipath path_floppy;
	struct multipath path_hardfile;
	struct multipath path_rom;
	struct multipath path_cd;

	int m68k_speed;
	double m68k_speed_throttle;
	int cpu_model;
	int mmu_model;
	int cpu060_revision;
	int fpu_model;
	int fpu_revision;
	bool cpu_compatible;
	bool int_no_unimplemented;
	bool fpu_no_unimplemented;
	bool address_space_24;
	bool picasso96_nocustom;
	int picasso96_modeflags;

	uae_u32 z3fastmem_size, z3fastmem2_size;
	uae_u32 z3fastmem_start;
	uae_u32 z3chipmem_size;
	uae_u32 z3chipmem_start;
	uae_u32 fastmem_size, fastmem2_size;
	bool fastmem_autoconfig;
	uae_u32 chipmem_size;
	uae_u32 bogomem_size;
	uae_u32 mbresmem_low_size;
	uae_u32 mbresmem_high_size;
	uae_u32 rtgmem_size;
	bool rtg_hardwareinterrupt;
	bool rtg_hardwaresprite;
	int rtgmem_type;
	bool rtg_more_compatible;
	uae_u32 custom_memory_addrs[MAX_CUSTOM_MEMORY_ADDRS];
	uae_u32 custom_memory_sizes[MAX_CUSTOM_MEMORY_ADDRS];

	bool kickshifter;
	bool filesys_no_uaefsdb;
	bool filesys_custom_uaefsdb;
	bool mmkeyboard;
	int uae_hide;
	bool clipboard_sharing;
	bool native_code;
	bool uae_hide_autoconfig;
	bool jit_direct_compatible_memory;

	int mountitems;
	struct uaedev_config_data mountconfig[MOUNT_CONFIG_SIZE];

	int nr_floppies;
	struct floppyslot floppyslots[4];
	bool floppy_read_only;
	TCHAR dfxlist[MAX_SPARE_DRIVES][MAX_DPATH];
#ifdef DRIVESOUND
	int dfxclickvolume;
	int dfxclickchannelmask;
#endif

	bool hide_cursor;				/* Whether to hide host WM cursor or not */

	/* Target specific options */
#ifdef USE_X11_GFX
	bool x11_use_low_bandwidth;
	bool x11_use_mitshm;
	int x11_use_dgamode;
	bool x11_hide_cursor;
#endif

#ifdef USE_SVGALIB_GFX
	int svga_no_linear;
#endif

	int win32_rtgvblankrate;
#ifdef USE_CURSES_GFX
	int curses_reverse_video;
#endif

#if 0
#if defined USE_SDL_GFX || defined USE_X11_GFX
	bool map_raw_keys;
#endif
#endif
	bool use_gl;

#ifdef USE_AMIGA_GFX
	int  amiga_screen_type;
	char amiga_publicscreen[256];
	int  amiga_use_grey;
	int  amiga_use_dither;
#endif

#ifdef SAVESTATE
	bool statecapture;
	int statecapturerate, statecapturebuffersize;
#endif

	/* input */

	struct jport jports[MAX_JPORTS];
	int input_selected_setting;
	int input_joymouse_multiplier;
	int input_joymouse_deadzone;
	int input_joystick_deadzone;
	int input_joymouse_speed;
	int input_analog_joystick_mult;
	int input_analog_joystick_offset;
	int input_autofire_linecnt;
	int input_mouse_speed;
	int input_tablet;
	bool input_magic_mouse;
	int input_magic_mouse_cursor;
	int input_keyboard_type;
	struct uae_input_device joystick_settings[MAX_INPUT_SETTINGS][MAX_INPUT_DEVICES];
	struct uae_input_device mouse_settings[MAX_INPUT_SETTINGS][MAX_INPUT_DEVICES];
	struct uae_input_device keyboard_settings[MAX_INPUT_SETTINGS][MAX_INPUT_DEVICES];
	struct uae_input_device internalevent_settings[MAX_INPUT_SETTINGS][INTERNALEVENT_COUNT];
	TCHAR input_config_name[GAMEPORT_INPUT_SETTINGS][256];
	int dongle;
	int input_contact_bounce;
};

extern int config_changed;
extern void config_check_vsync (void);
extern void set_config_changed (void);

/* Contains the filename of .uaerc */
extern TCHAR optionsfile[];
extern void save_options (struct zfile *, struct uae_prefs *, int);

extern void cfgfile_write (struct zfile *, const TCHAR *option, const TCHAR *format,...);
extern void cfgfile_dwrite (struct zfile *, const TCHAR *option, const TCHAR *format,...);
extern void cfgfile_target_write (struct zfile *, const TCHAR *option, const TCHAR *format,...);
extern void cfgfile_target_dwrite (struct zfile *, const TCHAR *option, const TCHAR *format,...);

extern void cfgfile_write_bool (struct zfile *f, const TCHAR *option, bool b);
extern void cfgfile_dwrite_bool (struct zfile *f,const  TCHAR *option, bool b);
extern void cfgfile_target_write_bool (struct zfile *f, const TCHAR *option, bool b);
extern void cfgfile_target_dwrite_bool (struct zfile *f, const TCHAR *option, bool b);

extern void cfgfile_write_str (struct zfile *f, const TCHAR *option, const TCHAR *value);
extern void cfgfile_dwrite_str (struct zfile *f, const TCHAR *option, const TCHAR *value);
extern void cfgfile_target_write_str (struct zfile *f, const TCHAR *option, const TCHAR *value);
extern void cfgfile_target_dwrite_str (struct zfile *f, const TCHAR *option, const TCHAR *value);

extern void cfgfile_backup (const TCHAR *path);
extern struct uaedev_config_data *add_filesys_config (struct uae_prefs *p, int index, struct uaedev_config_info*);
extern bool get_hd_geometry (struct uaedev_config_info *);
extern void uci_set_defaults (struct uaedev_config_info *uci, bool rdb);

extern void error_log (const TCHAR*, ...);
extern TCHAR *get_error_log (void);
extern bool is_error_log (void);

extern void default_prefs (struct uae_prefs *, int);
extern void discard_prefs (struct uae_prefs *, int);

int parse_cmdline_option (struct uae_prefs *, TCHAR, const TCHAR *);

extern int cfgfile_yesno (const TCHAR *option, const TCHAR *value, const TCHAR *name, bool *location);
extern int cfgfile_intval (const TCHAR *option, const TCHAR *value, const TCHAR *name, int *location, int scale);
extern int cfgfile_strval (const TCHAR *option, const TCHAR *value, const TCHAR *name, int *location, const TCHAR *table[], int more);
extern int cfgfile_string (const TCHAR *option, const TCHAR *value, const TCHAR *name, TCHAR *location, int maxsz);
extern TCHAR *cfgfile_subst_path (const TCHAR *path, const TCHAR *subst, const TCHAR *file);

extern TCHAR *target_expand_environment (const TCHAR *path);
extern int target_parse_option (struct uae_prefs *, const TCHAR *option, const TCHAR *value);
extern void target_save_options (struct zfile*, struct uae_prefs *);
extern void target_default_options (struct uae_prefs *, int type);
extern void target_fixup_options (struct uae_prefs *);
extern int target_cfgfile_load (struct uae_prefs *, const TCHAR *filename, int type, int isdefault);
extern void cfgfile_save_options (struct zfile *f, struct uae_prefs *p, int type);
extern int target_get_display (const TCHAR*);
extern const TCHAR *target_get_display_name (int, bool);

extern int cfgfile_load (struct uae_prefs *p, const TCHAR *filename, int *type, int ignorelink, int userconfig);
extern int cfgfile_save (struct uae_prefs *p, const TCHAR *filename, int);
extern void cfgfile_parse_line (struct uae_prefs *p, TCHAR *, int);
extern void cfgfile_parse_lines (struct uae_prefs *p, const TCHAR *, int);
extern int cfgfile_parse_option (struct uae_prefs *p, TCHAR *option, TCHAR *value, int);
extern int cfgfile_get_description (const TCHAR *filename, TCHAR *description, TCHAR *hostlink, TCHAR *hardwarelink, int *type);
extern void cfgfile_show_usage (void);
extern uae_u32 cfgfile_uaelib (int mode, uae_u32 name, uae_u32 dst, uae_u32 maxlen);
extern uae_u32 cfgfile_uaelib_modify (uae_u32 mode, uae_u32 parms, uae_u32 size, uae_u32 out, uae_u32 outsize);
extern uae_u32 cfgfile_modify (uae_u32 index, TCHAR *parms, uae_u32 size, TCHAR *out, uae_u32 outsize);
extern void cfgfile_addcfgparam (TCHAR *);
extern int built_in_prefs (struct uae_prefs *p, int model, int config, int compa, int romcheck);
extern int built_in_chipset_prefs (struct uae_prefs *p);
extern int cmdlineparser (const TCHAR *s, TCHAR *outp[], int max);
extern int cfgfile_configuration_change (int);
extern void fixup_prefs_dimensions (struct uae_prefs *prefs);
extern void fixup_prefs (struct uae_prefs *prefs);
extern void fixup_cpu (struct uae_prefs *prefs);

extern void check_prefs_changed_custom (void);
extern void check_prefs_changed_cpu (void);
extern void check_prefs_changed_audio (void);
extern void check_prefs_changed_cd (void);
extern int check_prefs_changed_gfx (void);

extern struct uae_prefs currprefs, changed_prefs;

extern int machdep_init (void);
extern void machdep_free (void);

/* AIX doesn't think it is Unix. Neither do I. */
#if defined(_ALL_SOURCE) || defined(_AIX)
#undef __unix
#define __unix
#endif

#define MAX_COLOR_MODES 5

/* #define NEED_TO_DEBUG_BADLY */

#if !defined(USER_PROGRAMS_BEHAVE)
#define USER_PROGRAMS_BEHAVE 0
#endif

/* Some memsets which know that they can safely overwrite some more memory
 * at both ends and use that knowledge to align the pointers. */

#define QUADRUPLIFY(c) (((c) | ((c) << 8)) | (((c) | ((c) << 8)) << 16))

/* When you call this routine, bear in mind that it rounds the bounds and
 * may need some padding for the array. */

#define fuzzy_memset(p, c, o, l) fuzzy_memset_1 ((p), QUADRUPLIFY (c), (o) & ~3, ((l) + 4) >> 2)
STATIC_INLINE void fuzzy_memset_1 (void *p, uae_u32 c, int offset, int len)
{
    uae_u32 *p2 = (uae_u32 *)((TCHAR *)p + offset);
    int a = len & 7;
    len >>= 3;
    switch (a) {
     case 7: p2--; goto l1;
     case 6: p2-=2; goto l2;
     case 5: p2-=3; goto l3;
     case 4: p2-=4; goto l4;
     case 3: p2-=5; goto l5;
     case 2: p2-=6; goto l6;
     case 1: p2-=7; goto l7;
     case 0: if (!--len) return; break;
    }

    for (;;) {
	p2[0] = c;
	l1:
	p2[1] = c;
	l2:
	p2[2] = c;
	l3:
	p2[3] = c;
	l4:
	p2[4] = c;
	l5:
	p2[5] = c;
	l6:
	p2[6] = c;
	l7:
	p2[7] = c;

	if (!len)
	    break;
	len--;
	p2 += 8;
    }
}

/* This one knows it will never be asked to clear more than 32 bytes.  Make sure you call this with a
   constant for the length.  */
#define fuzzy_memset_le32(p, c, o, l) fuzzy_memset_le32_1 ((p), QUADRUPLIFY (c), (o) & ~3, ((l) + 7) >> 2)
STATIC_INLINE void fuzzy_memset_le32_1 (void *p, uae_u32 c, int offset, int len)
{
    uae_u32 *p2 = (uae_u32 *)((TCHAR *)p + offset);

    switch (len) {
     case 9: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; p2[6] = c; p2[7] = c; p2[8] = c; break;
     case 8: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; p2[6] = c; p2[7] = c; break;
     case 7: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; p2[6] = c; break;
     case 6: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; p2[5] = c; break;
     case 5: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; p2[4] = c; break;
     case 4: p2[0] = c; p2[1] = c; p2[2] = c; p2[3] = c; break;
     case 3: p2[0] = c; p2[1] = c; p2[2] = c; break;
     case 2: p2[0] = c; p2[1] = c; break;
     case 1: p2[0] = c; break;
     case 0: break;
     default: printf("Hit the programmer.\n"); break;
    }
}

#if defined TARGET_AMIGAOS && defined(__GNUC__)
#include "od-amiga/amiga-kludges.h"
#endif

#endif // SRC_INCLUDE_OPTIONS_H_INCLUDED
