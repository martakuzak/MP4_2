#ifndef NALUNITTYPE
#define NALUNITTYPE


enum NalUnitType {
    UNSPECIFIED = 0,
    NON_IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP = 1, // VCL - start
    SLICE_DATA_PARTITION_A_LAYER_RBSP = 2,
    SLICE_DATA_PARTITION_B_LAYER_RBSP = 3,
    SLICE_DATA_PARTITION_C_LAYER_RBSP = 4,
    IDR_SLICE_LAYER_WITHOUT_PARTITIONING_RBSP = 5, // VCL - end
    SEI_RBSP = 6,
    SEQ_PARAMETER_SET_RBSP = 7,
    PIC_PARAMETER_SET_RBSP = 8,
    ACCESS_UNIT_DELIMITER_RBSP = 9,
    END_OF_SEQUENCE_RBSP = 10,
    END_OF_STREAM_RBSP = 11,
    FILLER_DATA_RBSP = 12,
    SEQ_PARAMETER_SET_EXTENSION_RBSP = 13,
    PREFIX_NAL_UNIT_RBSP = 14, // NAL unit type 14 is used for prefix NAL unit
    SUBSET_SEQUENCE_PARAMETER_SET_RBSP = 15, //NAL unit type 15 is used for subset sequence parameter set
    RESERVED_16 = 16,
    RESERVED_17 = 17,
    RESERVED_18 = 18,
    SLICE_LAYER_WITHOUT_PARTITIONING_RBSP = 19,
    SLICE_LAYER_EXTENSION_RBSP = 20, // NAL unit type 20 is used for coded slice in scalable extension
    RESERVED_21 = 21,
    RESERVED_22 = 22,
    RESERVED_23 = 23,
    UNSPECIFIED_24 = 24,
    UNSPECIFIED_25 = 25,
    UNSPECIFIED_26 = 26,
    UNSPECIFIED_27 = 27,
    UNSPECIFIED_28 = 28,
    UNSPECIFIED_29 = 29,
    UNSPECIFIED_30 = 30,
    UNSPECIFIED_31 = 31
};


#endif // NALUNITTYPE

