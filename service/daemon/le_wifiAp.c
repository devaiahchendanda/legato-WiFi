// -------------------------------------------------------------------------------------------------
/**
 *  Legato WiFi Access Point
 *
 *  Copyright (C) Sierra Wireless Inc.
 *
 */
// -------------------------------------------------------------------------------------------------
#include "legato.h"

#include "interfaces.h"

#include "pa_wifi_ap.h"


//--------------------------------------------------------------------------------------------------
/**
 * Event ID for WiFi Access Point Event message notification.
 *
 */
//--------------------------------------------------------------------------------------------------
static le_event_Id_t NewWifiApEventId;

//--------------------------------------------------------------------------------------------------
/**
 * CallBack for PA Access Point Events.
 */
//--------------------------------------------------------------------------------------------------

static void PaEventApHandler
(
    le_wifiAp_Event_t event,
    void *ctxPtr
)
{

    LE_DEBUG("Event: %d", event);

    le_event_Report(NewWifiApEventId, (void *)&event, sizeof(le_wifiAp_Event_t));
}


//--------------------------------------------------------------------------------------------------
/**
 * The first-layer WiFi Ap Event Handler.
 *
 */
//--------------------------------------------------------------------------------------------------
static void FirstLayerWifiApEventHandler
(
    void *reportPtr,
    void *secondLayerHandlerFunc
)
{
    le_wifiAp_EventHandlerFunc_t  clientHandlerFunc = secondLayerHandlerFunc;
    le_wifiAp_Event_t            *wifiEventPtr      = (le_wifiAp_Event_t *)reportPtr;

    if (NULL != wifiEventPtr)
    {
        LE_DEBUG("Event: %d", *wifiEventPtr);
        clientHandlerFunc(*wifiEventPtr, le_event_GetContextPtr());
    }
    else
    {
        LE_ERROR("Event is NULL");
    }
}

//--------------------------------------------------------------------------------------------------
/**
 * Add handler function for EVENT 'le_wifiAp_NewEvent'
 *
 * These events provide information on WiFi Access Point
 */
//--------------------------------------------------------------------------------------------------
le_wifiAp_NewEventHandlerRef_t le_wifiAp_AddNewEventHandler
(
    le_wifiAp_EventHandlerFunc_t handlerFuncPtr,
        ///< [IN]
        ///< Event handler function

    void *contextPtr
        ///< [IN]
        ///< Associated event context
)
{
    le_event_HandlerRef_t handlerRef;

    LE_DEBUG("Add new event handler");
    if (handlerFuncPtr == NULL)
    {
        LE_KILL_CLIENT("handlerFuncPtr is NULL !");
        return NULL;
    }

    handlerRef = le_event_AddLayeredHandler("NewWiFiApEventHandler",
        NewWifiApEventId,
        FirstLayerWifiApEventHandler,
        (le_event_HandlerFunc_t)handlerFuncPtr);

    le_event_SetContextPtr(handlerRef, contextPtr);

    return (le_wifiAp_NewEventHandlerRef_t)(handlerRef);
}

//--------------------------------------------------------------------------------------------------
/**
 * Remove handler function for EVENT 'le_wifiAp_NewEvent'
 */
//--------------------------------------------------------------------------------------------------
void le_wifiAp_RemoveNewEventHandler
(
    le_wifiAp_NewEventHandlerRef_t handlerRef
        ///< [IN]
        ///< Event handler function to remove.
)
{
    le_event_RemoveHandler((le_event_HandlerRef_t)handlerRef);
}

//--------------------------------------------------------------------------------------------------
/**
 * This function starts the WiFi Access Point.
 * Note that all settings, if to be used, such as security, username, password must set prior to
 * starting the Access Point.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 * @return LE_NOT_FOUND     The WiFi card is absent.
 * @return LE_NOT_POSSIBLE  The WiFi card may not work.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_Start
(
    void
)
{
    return pa_wifiAp_Start();
}

//--------------------------------------------------------------------------------------------------
/**
 * This function stops the WiFi Access Point.
 *
 * @return LE_FAULT         The function failed.
 * @return LE_OK            The function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_Stop
(
    void
)
{
    return pa_wifiAp_Stop();
}



//--------------------------------------------------------------------------------------------------
/**
 * Set the Service Set IDentification (SSID) of the access point
 *
 * @note The SSID does not have to be human readable ASCII values, but often is.
 *
 * @return LE_BAD_PARAMETER Some parameter is invalid.
 * @return LE_OK            Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetSsid
(
    const uint8_t *ssidPtr,
        ///< [IN]
        ///< The SSID to set as a octet array.

    size_t ssidNumElements
        ///< [IN]
        ///< The length of the SSID in octets.
)
{
    return pa_wifiAp_SetSsid(ssidPtr, ssidNumElements);
}


//--------------------------------------------------------------------------------------------------
/**
 * Set the security protocol to use.
 *
 * @note that the SSID does not have to be human readable ASCII values, but often has.
 *
 * @return LE_BAD_PARAMETER Some parameter is invalid.
 * @return LE_OK            Function succeeded.
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetSecurityProtocol
(
    le_wifiAp_SecurityProtocol_t securityProtocol
        ///< [IN]
        ///< The security protocol used to communicate with the access point.
)
{
    return pa_wifiAp_SetSecurityProtocol(securityProtocol);
}


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
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetPassPhrase
(
    const char *passphrasePtr
        ///< [IN]
        ///< Passphrase to authenticate against the access point.
)
{
    return pa_wifiAp_SetPassPhrase(passphrasePtr);
}


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
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetPreSharedKey
(
    const char *preSharedKeyPtr
        ///< [IN]
        ///< Pre-shared key used to authenticate against the access point.
)
{
    return pa_wifiAp_SetPreSharedKey(preSharedKeyPtr);
}


//--------------------------------------------------------------------------------------------------
/**
 * Set if the Access Point should announce its presence.
 * Default value is TRUE.
 * If the value is set to FALSE, the Access Point will be hidden.
 *
 * @return LE_OK            Function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetDiscoverable
(
    bool isDiscoverable
        ///< [IN]
        ///< If TRUE the Access Point shows up on scans, else it is hidden.
)
{
    return pa_wifiAp_SetDiscoverable(isDiscoverable);
}


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
le_result_t le_wifiAp_SetChannel
(
    uint16_t channelNumber
        ///< [IN]
        ///< the channel number.
)
{
    return pa_wifiAp_SetChannel(channelNumber);
}


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
le_result_t le_wifiAp_SetIeeeStandard
(
    le_wifiAp_IeeeStdBitMask_t stdMask
        ///< [IN]
        ///< Bit mask for the IEEE standard.
)
{
    return pa_wifiAp_SetIeeeStandard(stdMask);
}

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
le_result_t le_wifiAp_GetIeeeStandard
(
    le_wifiAp_IeeeStdBitMask_t *stdMaskPtr
        ///< [OUT]
        ///< Bit mask for the IEEE standard.
)
{
    if ( NULL == stdMaskPtr )
    {
        LE_WARN("stdMaskPtr is NULL.");
        return LE_FAULT;
    }
    return pa_wifiAp_GetIeeeStandard(stdMaskPtr);
}

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
le_result_t le_wifiAp_SetCountryCode
(
    const char *countryCodePtr
        ///< [IN]
        ///< the country code.
)
{
    return pa_wifiAp_SetCountryCode(countryCodePtr);
}

//--------------------------------------------------------------------------------------------------
/**
 *  WiFi access point component initialization.
 */
//--------------------------------------------------------------------------------------------------
void le_wifiAp_Init
(
    void
)
{
    LE_DEBUG("WiFi Access Point Service is ready");

    pa_wifiAp_Init();

    // Create an event Id for new WiFi Events
    NewWifiApEventId = le_event_CreateId("WiFiApEventId", sizeof(le_wifiAp_Event_t));

    // register for events from PA.
    pa_wifiAp_AddEventHandler(PaEventApHandler, NULL);

}

//--------------------------------------------------------------------------------------------------
/**
 * Set number of maximally allowed clients to connect to the Access Point at the same time.
 *
 * @return LE_OUT_OF_RANGE  Requested number of users exceeds the capabilities of the Access Point.
 * @return LE_OK            Function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetMaxNumberOfClients
(
    int8_t maxNumberOfClients
        ///< [IN]
        ///< the maximum number of clients
)
{
    if (0 == maxNumberOfClients)
    {
        return LE_OUT_OF_RANGE;
    }
    return pa_wifiAp_SetMaxNumberClients(maxNumberOfClients);
}

//--------------------------------------------------------------------------------------------------
/**
 * Defines the IP adresses range for the host AP.
 *
 * @return LE_BAD_PARAMETER At least, one of the given IP addresses is invalid.
 * @return LE_FAULT         A system call has failed.
 * @return LE_OK            Function succeeded.
 *
 */
//--------------------------------------------------------------------------------------------------
le_result_t le_wifiAp_SetIpRange
(
    const char *ip_ap,
        ///< [IN]
        ///< the IP address of the Access Point.
    const char *ip_start,
        ///< [IN]
        ///< the start IP address of the Access Point.
    const char *ip_stop
        ///< [IN]
        ///< the stop IP address of the Access Point.
)
{
    return pa_wifiAp_SetIpRange(ip_ap, ip_start, ip_stop);
}

