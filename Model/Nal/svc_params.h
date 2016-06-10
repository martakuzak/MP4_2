#ifndef SVC_PARAMS
#define SVC_PARAMS

namespace svc {
    const unsigned long SEC_1904_1970 = 7171200; //time between 00:00:00 01.01.1904 and 00:00:00 01.01.1970
    /* FTYP */
    const char* FTYP_MAJOR_BRAND = "isom";
    const unsigned int FTYP_MINOR_VERSION = 0x200;
    const char* FTYP_COMP_BRAND_0 = "isom";
    const char* FTYP_COMP_BRAND_1 = "iso2";
    const char* FTYP_COMP_BRAND_2 = "mp41";
    const char* FTYP_COMP_BRAND_3 = "avc10";
    /* MVHD */
    const unsigned short MVHD_VERSION = 0;
    const unsigned int MVHD_SIZE = MVHD_VERSION ? 120 : 108;
    const unsigned short MVHD_FLAG_0 = 0;
    const unsigned short MVHD_FLAG_1 = 0;
    const unsigned short MVHD_FLAG_2 = 0;
    const unsigned int MVHD_TIMESCALE = 1000;
    const unsigned int MVHD_DURATION = 119520;
    const unsigned int MVHD_RATE = 0x00010000;
    const unsigned int MVHD_VOLUME = 0x0100;
    /* TKHD */
    const unsigned short TKHD_VERSION = 0;
    const unsigned int TKHD_SIZE = TKHD_VERSION ? 114 : 92;
    const unsigned short TKHD_FLAG_0 = 0;
    const unsigned short TKHD_FLAG_1 = 0;
    const unsigned short TKHD_FLAG_2 = 0;
    const unsigned int TKHD_DURATION = MVHD_DURATION;
    const unsigned int TKHD_LAYER = 1;
    const unsigned int TKHD_ALTERNATE_GROUP = 0;
    const unsigned int TKHD_VOLUME = 0; //0 bo to ścieżka wideo
    const unsigned int TKHD_WIDTH = 55705600; //width 16.16 fixed value //640 - pomyslec nad uniwersalnym sposobem
    const unsigned int TKHD_HEIGHT = 42467328; //height 16.16 fixed value //480
    /* MDHD */
    const unsigned short MDHD_VERSION = 0;
    const unsigned int MDHD_SIZE = MDHD_VERSION ? 44 : 32;
    const unsigned short MDHD_FLAG_0 = 0;
    const unsigned short MDHD_FLAG_1 = 0;
    const unsigned short MDHD_FLAG_2 = 0;
    const unsigned short MDHD_TIMESCALE = 25;
    const unsigned short MDHD_DURATION = 2988;
    const char* MDHD_UND_LAN_CODE = "und";
    /* HDLR */
    const unsigned short HDLR_VERSION = 0;
    const unsigned short HDLR_FLAG_0 = 0;
    const unsigned short HDLR_FLAG_1 = 0;
    const unsigned short HDLR_FLAG_2 = 0;
    const char* HDLR_VIDE_TRACK = "vide";
    const char* HDLR_VIDEO_HANDLER = "VideoHandler";
    const unsigned int HDLR_SIZE = 32 + strlen(HDLR_VIDEO_HANDLER); //zależy od  HDLR_VIDEO_HANDLER
    /* VMHD */
    const unsigned short VMHD_VERSION = 0;
    const unsigned short VMHD_FLAG_0 = 0;
    const unsigned short VMHD_FLAG_1 = 0;
    const unsigned short VMHD_FLAG_2 = 1;
    /* DREF */
    const unsigned short DREF_VERSION = 0;
    const unsigned short DREF_FLAG_0 = 0;
    const unsigned short DREF_FLAG_1 = 0;
    const unsigned short DREF_FLAG_2 = 1;
    /* URL  */
    const unsigned short URL_VERSION = 0;
    const unsigned short URL_FLAG_0 = 0;
    const unsigned short URL_FLAG_1 = 0;
    const unsigned short URL_FLAG_2 = 1;
    /* STSD */
    const unsigned short STSD_VERSION = 0;
    const unsigned short STSD_FLAG_0 = 0;
    const unsigned short STSD_FLAG_1 = 0;
    const unsigned short STSD_FLAG_2 = 0;
    /* AVC1 */
    const unsigned int AVC1_WIDTH = TKHD_WIDTH;
    const unsigned int AVC1_HEIGHT = TKHD_HEIGHT;
    const unsigned int AVC1_HORIZONTAL_RESOLUTION = 0x0048;
    const unsigned int AVC1_VERTICAL_RESOLUTION = 0x0048;
    const unsigned int AVC1_FRAME_COUNT = 1;
    const unsigned int AVC1_DEPTH = 24;
    /* AVCC */
    const unsigned int AVCC_CONFIGURATION_VERSION = 1;
    const unsigned int AVCC_AVC_PROFILE_INDICATION = 100;
    const unsigned int AVCC_PROFILE_COMPABILITY = 0;
    const unsigned int AVCC_LEVEL_INDICATION = 30;
    /* STTS */
    const unsigned short STTS_VERSION = 0;
    const unsigned short STTS_FLAG_0 = 0;
    const unsigned short STTS_FLAG_1 = 0;
    const unsigned short STTS_FLAG_2 = 0;
    /* STSC */
    const unsigned short STSC_VERSION = 0;
    const unsigned short STSC_FLAG_0 = 0;
    const unsigned short STSC_FLAG_1 = 0;
    const unsigned short STSC_FLAG_2 = 0;
    /* STSZ */
    const unsigned short STSZ_VERSION = 0;
    const unsigned short STSZ_FLAG_0 = 0;
    const unsigned short STSZ_FLAG_1 = 0;
    const unsigned short STSZ_FLAG_2 = 0;
    /* STCO */
    const unsigned short STCO_VERSION = 0;
    const unsigned short STCO_FLAG_0 = 0;
    const unsigned short STCO_FLAG_1 = 0;
    const unsigned short STCO_FLAG_2 = 0;
    /* STSS */
    const unsigned short STSS_VERSION = 0;
    const unsigned short STSS_FLAG_0 = 0;
    const unsigned short STSS_FLAG_1 = 0;
    const unsigned short STSS_FLAG_2 = 0;
}

#endif // SVC_PARAMS
