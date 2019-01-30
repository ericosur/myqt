#ifndef __LIBHU_MSGQ__
#define __LIBHU_MSGQ__

/* HU message queue key */
typedef enum {
	/* for general msgq send/recv and data type is string  */
	MSGQ_KEY_GEN_START = 0x7FFE0000,

	MSGQ_KEY_RADIOUI,
	MSGQ_KEY_LIBRADIO,
	MSGQ_KEY_RADIOD,

	MSGQ_KEY_GEN_END = 0x7FFF0000,

	/* for system notification msgq send/recv and data type is string  */
	MSGQ_KEY_SYS_NOTI_START = 0x8FFE0000,

	MSGQ_KEY_TOAST,
	MSGQ_KEY_DROPDOWN,
	MSGQ_KEY_DIALOG,
	MSGQ_KEY_STATUSBAR,

	MSGQ_KEY_SYS_NOTI_END = 0x8FFF0000,

	/* for some special msgq send/recv and data type may be a structure or others */
	MSGQ_KEY_OHERS_START = 0x9FFE0000,

	MSGQ_KEY_RESMGR,
	MSGQ_KEY_APP_LAUNCH,
	MSGQ_KEY_DISPATCH_ID,
	MSGQ_KEY_BEEP,
	MSGQ_KEY_CGMGR,
	MSGQ_KEY_LAYER,
	MSGQ_KEY_IPOD,
	MSGQ_KEY_BOOT,
	MSGQ_KEY_MEDIA,
	MSGQ_KEY_VIDEOCONTROL,

	MSGQ_KEY_OHERS_END = 0x9FFF0000,

	MSGQ_KEY_UNKNOWN,
	MSGQ_KEY_MAX,

} msgq_key_t;

/* HU message queue type, refactor: TODO */
#define MSGQ_TYPE_GEN		11
#define MSGQ_TYPE_RESMGR	11
#define MSGQ_TYPE_BEEP		9
#define MSGQ_TYPE_CGMGR	11
#define MSGQ_TYPE_BOOT	11
#define MSGQ_TYPE_IPOD		9
#define MSGQ_TYPE_DISPATCH_ID			11
#define MSGQ_TYPE_LAYER_PRIO_FST		11
#define MSGQ_TYPE_LAYER_PRIO_SND		12
#define MSGQ_TYPE_TOAST				11
#define MSGQ_TYPE_DROPDOWN			11
#define MSGQ_TYPE_DIALOG				11
#define MSGQ_TYPE_STATUSBAR			9

/* HU App message queue type, refactor: TODO */
typedef enum _PROG_TYPE {
	PROG_START = 22,

	PROG_RADIO,
	PROG_BT,
	PROG_VIDEO,
	PROG_MEDIA,
	PROG_DVD,
	PROG_MIRA,
	PROG_IPOD,
	PROG_HDMI,
	PROG_WEATHER,
	PROG_BROWSER,
	PROG_ADDON,
	PROG_NAVI,
	PROG_SETTING,
	PROG_LAUNCHER,
	PROG_RADIOD,
	PROG_VOICE,
	PROG_EULA,
	PROG_CARPLAY,
	PROG_ANDROID,
	PROG_ANIMATION,

	PROG_NONE,

	PROG_MAX,
} PROG_TYPE;

#endif
