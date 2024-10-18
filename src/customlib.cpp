#include "pxt.h"
#include "customlib.h"

namespace customlib
{

#if MICROBIT_CODAL

#include "ble_advdata.h"
#include "peer_manager.h"

    /**
     * For configure advertising
     *
     * https://github.com/lancaster-university/codal-microbit-v2/blob/master/source/bluetooth/MicroBitBLEManager.cpp#L133
     * https://github.com/lancaster-university/codal-microbit-v2/blob/master/source/bluetooth/MicroBitBLEManager.cpp#L134
     */
    // ********************************************************************************
    // static uint8_t              m_adv_handle    = BLE_GAP_ADV_SET_HANDLE_NOT_SET;
    static uint8_t m_adv_handle = 0; // ******** WARNING: magic handle number! ********
    // ********************************************************************************
    static uint8_t m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
    static uint8_t m_enc_scanrsp[BLE_GAP_ADV_SET_DATA_SIZE_MAX];

    // static void microbit_ble_configureAdvertising( bool, bool, bool, uint16_t, int, ble_advdata_t *);
    // https://github.com/lancaster-university/codal-microbit-v2/blob/master/source/bluetooth/MicroBitBLEManager.cpp#L1187

    /**
     * Function to configure advertising
     *
     * @param connectable Choose connectable advertising events.
     * @param discoverable Choose LE General Discoverable Mode.
     * @param whitelist Filter scan and connect requests with whitelist.
     * @param interval_ms Advertising interval in milliseconds.
     * @param timeout_seconds Advertising timeout in seconds.
     * @param p_advdata advertising data.
     * @param p_scanrsp scan responce data.
     */
    static void custom_microbit_ble_configureAdvertising(bool connectable, bool discoverable, bool whitelist,
                                                         uint16_t interval_ms, int timeout_seconds,
                                                         ble_advdata_t *p_advdata, ble_advdata_t *p_scanrsp)
    {
        MICROBIT_DEBUG_DMESG("configureAdvertising connectable %d, discoverable %d", (int)connectable, (int)discoverable);
        MICROBIT_DEBUG_DMESG("whitelist %d, interval_ms %d, timeout_seconds %d", (int)whitelist, (int)interval_ms, (int)timeout_seconds);

        ble_gap_adv_params_t gap_adv_params;
        memset(&gap_adv_params, 0, sizeof(gap_adv_params));
        gap_adv_params.properties.type = connectable
                                             ? BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED
                                             : BLE_GAP_ADV_TYPE_NONCONNECTABLE_SCANNABLE_UNDIRECTED;
        gap_adv_params.interval = (1000 * interval_ms) / 625; // 625 us units
        if (gap_adv_params.interval < BLE_GAP_ADV_INTERVAL_MIN)
            gap_adv_params.interval = BLE_GAP_ADV_INTERVAL_MIN;
        if (gap_adv_params.interval > BLE_GAP_ADV_INTERVAL_MAX)
            gap_adv_params.interval = BLE_GAP_ADV_INTERVAL_MAX;
        gap_adv_params.duration = timeout_seconds * 100; // 10 ms units
        gap_adv_params.filter_policy = whitelist
                                           ? BLE_GAP_ADV_FP_FILTER_BOTH
                                           : BLE_GAP_ADV_FP_ANY;
        gap_adv_params.primary_phy = BLE_GAP_PHY_1MBPS;

        ble_gap_adv_data_t gap_adv_data;
        memset(&gap_adv_data, 0, sizeof(gap_adv_data));
        gap_adv_data.adv_data.p_data = m_enc_advdata;
        gap_adv_data.adv_data.len = BLE_GAP_ADV_SET_DATA_SIZE_MAX;
        MICROBIT_BLE_ECHK(ble_advdata_encode(p_advdata, gap_adv_data.adv_data.p_data, &gap_adv_data.adv_data.len));
        // NRF_LOG_HEXDUMP_INFO( gap_adv_data.adv_data.p_data, gap_adv_data.adv_data.len);
        gap_adv_data.scan_rsp_data.p_data = m_enc_scanrsp;
        gap_adv_data.scan_rsp_data.len = BLE_GAP_ADV_SET_DATA_SIZE_MAX;
        MICROBIT_BLE_ECHK(ble_advdata_encode(p_scanrsp, gap_adv_data.scan_rsp_data.p_data, &gap_adv_data.scan_rsp_data.len));
        // NRF_LOG_HEXDUMP_INFO( gap_adv_data.scan_rsp_data.p_data, gap_adv_data.scan_rsp_data.len);
        MICROBIT_BLE_ECHK(sd_ble_gap_adv_set_configure(&m_adv_handle, &gap_adv_data, &gap_adv_params));
    }

    // Setup advertising.
    // https://github.com/lancaster-university/codal-microbit-v2/blob/master/source/bluetooth/MicroBitBLEManager.cpp#L478

    // static void microbit_ble_configureAdvertising( bool, bool, bool, uint16_t, int, ble_uuid_t *)
    // https://github.com/lancaster-university/codal-microbit-v2/blob/master/source/bluetooth/MicroBitBLEManager.cpp#L1218

    void resetAdvertising(const ManagedString &gapName, const uint16_t serviceUUID)
    {
        // Stop
        uBit.bleManager.stopAdvertising();

        // [Advertising] Complete local name
        ble_gap_conn_sec_mode_t sec_mode;
        memset(&sec_mode, 0, sizeof(sec_mode));
        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
        MICROBIT_BLE_ECHK(sd_ble_gap_device_name_set(&sec_mode, (const uint8_t *)gapName.toCharArray(), gapName.length()));

        // [Scan Response] Complete list of 16-bit Service IDs.
        static ble_uuid_t uuid;
        uuid.type = BLE_UUID_TYPE_BLE;
        uuid.uuid = serviceUUID;

        // Configure
        bool connectable = true;
        bool discoverable = true;
        bool whitelist = false;

#if CONFIG_ENABLED(MICROBIT_BLE_WHITELIST)
        // Configure a whitelist to filter all connection requetss from unbonded devices.
        // Most BLE stacks only permit one connection at a time, so this prevents denial of service attacks.
        //    ble->gap().setScanningPolicyMode(Gap::SCAN_POLICY_IGNORE_WHITELIST);
        //    ble->gap().setAdvertisingPolicyMode(Gap::ADV_POLICY_FILTER_CONN_REQS);

        pm_peer_id_t peer_list[MICROBIT_BLE_MAXIMUM_BONDS];
        uint32_t list_size = MICROBIT_BLE_MAXIMUM_BONDS;
        MICROBIT_BLE_ECHK(pm_peer_id_list(peer_list, &list_size, PM_PEER_ID_INVALID, PM_PEER_ID_LIST_ALL_ID));
        // MICROBIT_BLE_ECHK( pm_whitelist_set( list_size ? peer_list : NULL, list_size));
        // MICROBIT_BLE_ECHK( pm_device_identities_list_set( list_size ? peer_list : NULL, list_size));
        connectable = discoverable = whitelist = list_size > 0;
        MICROBIT_DEBUG_DMESG("whitelist size = %d", list_size);
#endif

        // adv_data
        ble_advdata_t advdata;
        memset(&advdata, 0, sizeof(advdata));
        advdata.name_type = BLE_ADVDATA_FULL_NAME;
        advdata.flags = !whitelist && discoverable
                            ? BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED | BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE
                            : BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
        // scan_rsp_data
        ble_advdata_t scanrsp;
        memset(&scanrsp, 0, sizeof(scanrsp));
        // advdata.name_type = BLE_ADVDATA_NO_NAME;
        scanrsp.uuids_complete.p_uuids = &uuid;
        scanrsp.uuids_complete.uuid_cnt = 1;
        // configure
        custom_microbit_ble_configureAdvertising(connectable, discoverable, whitelist,
                                                 MICROBIT_BLE_ADVERTISING_INTERVAL, MICROBIT_BLE_ADVERTISING_TIMEOUT,
                                                 &advdata, &scanrsp);

        // Restart
        uBit.bleManager.advertise();
    }

#else // MICROBIT_CODAL

    void resetAdvertising(const ManagedString &gapName, const uint16_t serviceUUID)
    {
        uBit.ble->stopAdvertising();
        // [Advertising] Complete local name
        uBit.ble->accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)gapName.toCharArray(), gapName.length());
        // [Scan Response] Complete list of 16-bit Service IDs.
        uBit.ble->accumulateScanResponse(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t *)&serviceUUID, 2);
        uBit.ble->startAdvertising();
    }

#endif // MICROBIT_CODAL
}
