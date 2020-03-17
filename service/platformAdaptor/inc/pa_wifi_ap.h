#ifndef PA_WIFI_AP_H
#define PA_WIFI_AP_H
// -------------------------------------------------------------------------------------------------
/**
 *
 *
 *  Copyright (C) Sierra Wireless Inc.
 *
 */
// -------------------------------------------------------------------------------------------------
#include "legato.h"
#include "interfaces.h"
//--------------------------------------------------------------------------------------------------
/**
 * Return value from WiFi platform adapter scripts code.
 * 50 is returned if WiFi hardware is absent.
 * 100 is returned if WiFi driver can not be installed.
 */
//--------------------------------------------------------------------------------------------------
#define PA_NOT_FOUND        50
#define PA_NOT_POSSIBLE     100
//--------------------------------------------------------------------------------------------------
/**
 * Event handler for PA WiFi access point changes.
 *
 * Handles the PA WiFi events.
 */
//--------------------------------------------------------------------------------------------------
typedef void (*pa_wifiAp_NewEventHandlerFunc_t)
(
    le_wifiAp_Event_t event,
        ///< [IN]
        ///< WiFi event to process
    void *contextPtr
        ///< [IN]
        ///< Associated WiFi event context
);

//--------------------------------------------------------------------------------------------------
/**
 * Add handler function for WiFi related events.
 *
 * These events provide information on WiFi access point status.
 *
 * @return LE_OK Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_wifiAp_AddEventHandler
(
    pa_wifiAp_NewEventHandlerFunc_t handlerPtr,
        ///< [IN]
        ///< Event handler function pointer

    void *contextPtr
        ///< [IN]
        ///< Associated event context
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to initialize the PA WiFi Access Point.
 *
 * @return LE_OK     The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_wifiAp_Init
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function must be called to release the platform adaptor WiFi module.
 *
 * @return LE_OK     The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
LE_SHARED le_result_t pa_wifiAp_Release
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function starts the WiFi access point.
 * Note that all settings, if to be used, such as security, username, password must set prior to
 * starting the access point.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 * @return LE_NOT_FOUND     The WiFi card is absent.
 * @return LE_NOT_POSSIBLE  The WiFi card may not work.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_Start
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * This function stops the WiFi access point.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_Stop
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the security protocol to use.
 *
 * @note WEP is not supported as it is unsecure and has been deprecated in favor of WPA/WPA2.
 * This limitation applies to access point mode only.
 *
 * @return LE_BAD_PARAMETER Some parameter is invalid.
 * @return LE_OK            Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetSecurityProtocol
(
    le_wifiAp_SecurityProtocol_t securityProtocol
        ///< [IN]
        ///< The security protocol used to communicate with the access point.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the Service Set IDentification (SSID) of the access point.
 *
 * @note The SSID does not have to be human readable ASCII values, but often is.
 *
 * @return LE_BAD_PARAMETER Some parameter is invalid.
 * @return LE_OK            Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetSsid
(
    const uint8_t *ssidPtr,
        ///< [IN]
        ///< The SSID to set as an octet array.

    size_t ssidNumElements
        ///< [IN]
        ///< The length of the SSID in octets.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the passphrase used to generate the PSK.
 *
 * @note This is one way to authenticate against the access point. The other one is provided by the
 * le_wifiAp_SetPreSharedKey() function. Both ways are exclusive and are effective only when used
 * with WPA-personal authentication.
 *
 * @return LE_BAD_PARAMETER Parameter is invalid.
 * @return LE_OK            Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetPassPhrase
(
    const char *passphrasePtr
        ///< [IN]
        ///< Passphrase to authenticate against the access point.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the pre-shared key (PSK).
 *
 * @note This is one way to authenticate against the access point. The other one is provided by the
 * le_wifiAp_SetPassPhrase() function. Both ways are exclusive and are effective only when used
 * with WPA-personal authentication.
 *
 * @return LE_BAD_PARAMETER Parameter is invalid.
 * @return LE_OK            Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetPreSharedKey
(
    const char *preSharedKeyPtr
        ///< [IN]
        ///< Pre-shared key used to authenticate against the access point.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set if the Access Point should announce it's presence.
 * Default value is TRUE.
 * If the value is set to FALSE, the access point will be hidden.
 *
 * @return LE_OK            Function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetDiscoverable
(
    bool isDiscoverable
        ///< [IN]
        ///< If TRUE, the access point SSID is visible by the clients otherwise it is hidden.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set which IEEE standard to use.
 * Default hardware mode is IEEE 802.11g.
 *
 * @return
 *      - LE_BAD_PARAMETER if invalid IEEE standard is set.
 *      - LE_OK if the function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetIeeeStandard
(
    le_wifiAp_IeeeStdBitMask_t stdMask
        ///< [IN]
        ///< Bit mask for the IEEE standard.
);

//--------------------------------------------------------------------------------------------------
/**
 * Get which IEEE standard was set.
 * Default hardware mode is IEEE 802.11g.
 *
 * @return
 *      - LE_FAULT if the function failed.
 *      - LE_OK if the function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_GetIeeeStandard
(
    le_wifiAp_IeeeStdBitMask_t *stdMaskPtr
        ///< [OUT]
        ///< Bit mask for the IEEE standard.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set what country code to use for regulatory domain.
 * ISO/IEC 3166-1 Alpha-2 code is used.
 * Default country code is US.
 * @return
 *      - LE_FAULT if the function failed.
 *      - LE_OK if the function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetCountryCode
(
    const char *countryCodePtr
        ///< [IN]
        ///< the country code.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set which WiFi channel to use.
 * Default number is 7.
 * Some legal restrictions might apply for your region.
 * The channel number must be between 1 and 14 for IEEE 802.11b/g.
 * The channel number must be between 7 and 196 for IEEE 802.11a.
 * The channel number must be between 1 and 6 for IEEE 802.11ad.
 * @return
 *      - LE_OUT_OF_RANGE if requested channel number is out of range.
 *      - LE_OK if the function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetChannel
(
    uint16_t channelNumber
        ///< [IN]
        ///< the channel number.
);

//--------------------------------------------------------------------------------------------------
/**
 * Set the maximum number of clients connected to WiFi access point at the same time.
 * Default value is 10.
 *
 * @note This value depends on the hardware/software capabilities of the WiFi module used.
 *
 * @return LE_OUT_OF_RANGE  Requested number of users exceeds the capabilities of the Access Point.
 * @return LE_OK            Function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetMaxNumberClients
(
    int maxNumberClients
        ///< [IN]
        ///< the maximum number of clients regarding the WiFi driver and hardware capabilities.
);

//--------------------------------------------------------------------------------------------------
/**
 * Define the access point IP address and the client IP addresses range.
 *
 * @note The access point IP address must be defined outside the client IP addresses range.
 *
 * @return LE_BAD_PARAMETER At least, one of the given IP addresses is invalid.
 * @return LE_FAULT         A system call has failed.
 * @return LE_OK            Function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t pa_wifiAp_SetIpRange
(
    const char *ipApPtr,
        ///< [IN]
        ///< the IP address of the Access Point.
    const char *ipStartPtr,
        ///< [IN]
        ///< the start IP address of the Access Point.
    const char *ipStopPtr
        ///< [IN]
        ///< the stop IP address of the Access Point.
);
#endif // PA_WIFI_AP_H
