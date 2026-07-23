#include "varsys_enum.h"

const char* varsys_data_correspondant_name(varsys_data_correspondant_e correspondant) {
    char* ret = "UNKNOWN";

    switch (correspondant) {

#define X(id, value)                                                                                                                                 \
    case id:                                                                                                                                         \
        ret = #id;                                                                                                                                   \
        break;

        VARSYS_DATA_CORRESPONDANT_LIST_IDENTIFIANT
#undef X

        default:
            break;
    }

    return ret;
}

const char* varsys_data_command_name(varsys_data_command_e command) {
    char* ret = "UNKNOWN";

    switch (command) {

#define X(id)                                                                                                                                        \
    case id:                                                                                                                                         \
        ret = #id;                                                                                                                                   \
        break;

        VARSYS_DATA_COMMAND_LIST
#undef X

        default:
            break;
    }

    return ret;
}