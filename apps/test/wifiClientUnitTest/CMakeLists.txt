#*******************************************************************************
# Copyright (C) Sierra Wireless Inc.
#*******************************************************************************

set(TEST_EXEC wifiClientUnitTest)

set(LEGATO_WIFI_SERVICES "${LEGATO_ROOT}/modules/WiFi/service")

if(TEST_COVERAGE EQUAL 1)
    set(CFLAGS "--cflags=\"--coverage\"")
    set(LFLAGS "--ldflags=\"--coverage\"")
endif()

mkexe(${TEST_EXEC}
    .
    -i ${LEGATO_WIFI_SERVICES}/daemon
    -i ${LEGATO_WIFI_SERVICES}/platformAdaptor/inc
    -i ${LEGATO_ROOT}/framework/liblegato
    -i ${PA_DIR}/simu/components/le_pa
    -i ${PA_DIR}/simu/components/simuConfig
    -s ${PA_DIR}
    --cflags="-DWITHOUT_SIMUCONFIG"
    ${CFLAGS}
    ${LFLAGS}
)

add_test(${TEST_EXEC} ${EXECUTABLE_OUTPUT_PATH}/${TEST_EXEC})

# This is a C test
add_dependencies(tests_c ${TEST_EXEC})