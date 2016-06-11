#ifndef SVCPARAMS_H
#define SVCPARAMS_H

#include <QFile>
#include <QTextStream>

class SvcParams {
private:
    unsigned long SEC_1904_1970 = 7171200; //time between 00:00:00 01.01.1904 and 00:00:00 01.01.1970
    /* FTYP */
    char* FTYP_MAJOR_BRAND;
    unsigned int FTYP_MINOR_VERSION;
    char* FTYP_COMP_BRAND_0;
    char* FTYP_COMP_BRAND_1;
    char* FTYP_COMP_BRAND_2;
    char* FTYP_COMP_BRAND_3;
    /* MVHD */
    unsigned short MVHD_VERSION;
    unsigned int MVHD_SIZE;
    unsigned short MVHD_FLAG_0;
    unsigned short MVHD_FLAG_1;
    unsigned short MVHD_FLAG_2;
    unsigned int MVHD_TIMESCALE;
    unsigned int MVHD_DURATION;
    unsigned int MVHD_RATE;
    unsigned int MVHD_VOLUME;
    /* TKHD */
    unsigned short TKHD_VERSION;
    unsigned int TKHD_SIZE;
    unsigned short TKHD_FLAG_0;
    unsigned short TKHD_FLAG_1;
    unsigned short TKHD_FLAG_2;
    unsigned int TKHD_DURATION;
    unsigned int TKHD_LAYER;
    unsigned int TKHD_ALTERNATE_GROUP;
    unsigned int TKHD_VOLUME; //0 bo to ścieżka wideo
    unsigned int TKHD_WIDTH; //width 16.16 fixed value //640 - pomyslec nad uniwersalnym sposobem
    unsigned int TKHD_HEIGHT; //height 16.16 fixed value //480
    /* MDHD */
    unsigned short MDHD_VERSION;
    unsigned int MDHD_SIZE;
    unsigned short MDHD_FLAG_0;
    unsigned short MDHD_FLAG_1;
    unsigned short MDHD_FLAG_2;
    unsigned short MDHD_TIMESCALE;
    unsigned short MDHD_DURATION;
    char* MDHD_UND_LAN_CODE;
    /* HDLR */
    unsigned short HDLR_VERSION;
    unsigned short HDLR_FLAG_0;
    unsigned short HDLR_FLAG_1;
    unsigned short HDLR_FLAG_2;
    char* HDLR_VIDE_TRACK;
    char* HDLR_VIDEO_HANDLER;
    unsigned int HDLR_SIZE; //zależy od  HDLR_VIDEO_HANDLER
    /* VMHD */
    unsigned short VMHD_VERSION;
    unsigned short VMHD_FLAG_0;
    unsigned short VMHD_FLAG_1;
    unsigned short VMHD_FLAG_2;
    /* DREF */
    unsigned short DREF_VERSION;
    unsigned short DREF_FLAG_0;
    unsigned short DREF_FLAG_1;
    unsigned short DREF_FLAG_2;
    /* URL  */
    unsigned short URL_VERSION;
    unsigned short URL_FLAG_0;
    unsigned short URL_FLAG_1;
    unsigned short URL_FLAG_2;
    /* STSD */
    unsigned short STSD_VERSION;
    unsigned short STSD_FLAG_0;
    unsigned short STSD_FLAG_1;
    unsigned short STSD_FLAG_2;
    /* AVC1 */
    unsigned int AVC1_WIDTH;
    unsigned int AVC1_HEIGHT;
    unsigned int AVC1_HORIZONTAL_RESOLUTION;
    unsigned int AVC1_VERTICAL_RESOLUTION;
    unsigned int AVC1_FRAME_COUNT;
    unsigned int AVC1_DEPTH;
    /* AVCC */
    unsigned int AVCC_CONFIGURATION_VERSION;
    unsigned int AVCC_AVC_PROFILE_INDICATION;
    unsigned int AVCC_PROFILE_COMPABILITY;
    unsigned int AVCC_LEVEL_INDICATION;
    /* STTS */
    unsigned short STTS_VERSION;
    unsigned short STTS_FLAG_0;
    unsigned short STTS_FLAG_1;
    unsigned short STTS_FLAG_2;
    /* STSC */
    unsigned short STSC_VERSION;
    unsigned short STSC_FLAG_0;
    unsigned short STSC_FLAG_1;
    unsigned short STSC_FLAG_2;
    /* STSZ */
    unsigned short STSZ_VERSION;
    unsigned short STSZ_FLAG_0;
    unsigned short STSZ_FLAG_1;
    unsigned short STSZ_FLAG_2;
    /* STCO */
    unsigned short STCO_VERSION;
    unsigned short STCO_FLAG_0;
    unsigned short STCO_FLAG_1;
    unsigned short STCO_FLAG_2;
    /* STSS */
    unsigned short STSS_VERSION;
    unsigned short STSS_FLAG_0;
    unsigned short STSS_FLAG_1;
    unsigned short STSS_FLAG_2;

public:
    SvcParams();

    void writeContent(QString name);

    unsigned long getSEC_1904_1970() const;
    char *getFTYP_MAJOR_BRAND() const;
    unsigned int getFTYP_MINOR_VERSION() const;
    char *getFTYP_COMP_BRAND_0() const;
    char *getFTYP_COMP_BRAND_1() const;
    char *getFTYP_COMP_BRAND_2() const;
    char *getFTYP_COMP_BRAND_3() const;
    unsigned short getMVHD_VERSION() const;
    unsigned int getMVHD_SIZE() const;
    unsigned short getMVHD_FLAG_0() const;
    unsigned short getMVHD_FLAG_1() const;
    unsigned short getMVHD_FLAG_2() const;
    unsigned int getMVHD_TIMESCALE() const;
    unsigned int getMVHD_DURATION() const;
    unsigned int getMVHD_RATE() const;
    unsigned int getMVHD_VOLUME() const;
    unsigned short getTKHD_VERSION() const;
    unsigned int getTKHD_SIZE() const;
    unsigned short getTKHD_FLAG_0() const;
    unsigned short getTKHD_FLAG_1() const;
    unsigned short getTKHD_FLAG_2() const;
    unsigned int getTKHD_DURATION() const;
    unsigned int getTKHD_LAYER() const;
    unsigned int getTKHD_ALTERNATE_GROUP() const;
    unsigned int getTKHD_VOLUME() const;
    unsigned int getTKHD_WIDTH() const;
    unsigned int getTKHD_HEIGHT() const;
    unsigned short getMDHD_VERSION() const;
    unsigned int getMDHD_SIZE() const;
    unsigned short getMDHD_FLAG_0() const;
    unsigned short getMDHD_FLAG_1() const;
    unsigned short getMDHD_FLAG_2() const;
    unsigned short getMDHD_TIMESCALE() const;
    unsigned short getMDHD_DURATION() const;
    char *getMDHD_UND_LAN_CODE() const;
    unsigned short getHDLR_VERSION() const;
    unsigned short getHDLR_FLAG_0() const;
    unsigned short getHDLR_FLAG_1() const;
    unsigned short getHDLR_FLAG_2() const;
    char *getHDLR_VIDE_TRACK() const;
    char *getHDLR_VIDEO_HANDLER() const;
    unsigned int getHDLR_SIZE() const;
    unsigned short getVMHD_VERSION() const;
    unsigned short getVMHD_FLAG_0() const;
    unsigned short getVMHD_FLAG_1() const;
    unsigned short getVMHD_FLAG_2() const;
    unsigned short getDREF_VERSION() const;
    unsigned short getDREF_FLAG_0() const;
    unsigned short getDREF_FLAG_1() const;
    unsigned short getDREF_FLAG_2() const;
    unsigned short getURL_VERSION() const;
    unsigned short getURL_FLAG_0() const;
    unsigned short getURL_FLAG_1() const;
    unsigned short getURL_FLAG_2() const;
    unsigned short getSTSD_VERSION() const;
    unsigned short getSTSD_FLAG_0() const;
    unsigned short getSTSD_FLAG_1() const;
    unsigned short getSTSD_FLAG_2() const;
    unsigned int getAVC1_WIDTH() const;
    unsigned int getAVC1_HEIGHT() const;
    unsigned int getAVC1_HORIZONTAL_RESOLUTION() const;
    unsigned int getAVC1_VERTICAL_RESOLUTION() const;
    unsigned int getAVC1_FRAME_COUNT() const;
    unsigned int getAVC1_DEPTH() const;
    unsigned int getAVCC_CONFIGURATION_VERSION() const;
    unsigned int getAVCC_AVC_PROFILE_INDICATION() const;
    unsigned int getAVCC_PROFILE_COMPABILITY() const;
    unsigned int getAVCC_LEVEL_INDICATION() const;
    unsigned short getSTTS_VERSION() const;
    unsigned short getSTTS_FLAG_0() const;
    unsigned short getSTTS_FLAG_1() const;
    unsigned short getSTTS_FLAG_2() const;
    unsigned short getSTSC_VERSION() const;
    unsigned short getSTSC_FLAG_0() const;
    unsigned short getSTSC_FLAG_1() const;
    unsigned short getSTSC_FLAG_2() const;
    unsigned short getSTSZ_VERSION() const;
    unsigned short getSTSZ_FLAG_0() const;
    unsigned short getSTSZ_FLAG_1() const;
    unsigned short getSTSZ_FLAG_2() const;
    unsigned short getSTCO_VERSION() const;
    unsigned short getSTCO_FLAG_0() const;
    void setSTCO_FLAG_1(unsigned short value);
    unsigned short getSTCO_FLAG_2() const;
    unsigned short getSTSS_VERSION() const;
    unsigned short getSTSS_FLAG_0() const;
    unsigned short getSTSS_FLAG_1() const;
    unsigned short getSTSS_FLAG_2() const;
signals:

public slots:
};

#endif // SVCPARAMS_H
