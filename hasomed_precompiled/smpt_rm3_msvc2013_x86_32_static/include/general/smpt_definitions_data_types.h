#ifndef SMPT_DEFINITIONS_DATA_TYPES_H
#define SMPT_DEFINITIONS_DATA_TYPES_H

/***************************************************************************//**
* \file smpt_definitions_data_types.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file defines the data types of the protocol, which are unrelated to
* a specific level.
* Note that stdint.h and stdbool from C99 are required as inlcudes. Nevertheless
* the SMPT library is written to be compatible with C89.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Define bool, because the Microsoft Compiler <= MSVC-2012 has no stdbool.h. */
#ifdef _MSC_VER
    #if (_MSC_VER < 1800)
        #define false   0
        #define true    1
        #define bool int
    #else
        #include <stdbool.h>
    #endif /* (_MSC_VER < 1800) */
#else
    #include <stdbool.h>
#endif /* _MSC_VER */

#ifdef SMPT_DLL

    #ifdef SMPT_EXPORTS
    #define SMPT_API __declspec(dllexport)
    #else
    #define SMPT_API __declspec(dllimport)
    #endif

#else
#define SMPT_API

#endif

typedef enum
{
    Smpt_Cmd_Ll_Init                 =  0,   /**< PC -> stimulator smpt_send_ll_init()            */
    Smpt_Cmd_Ll_Init_Ack             =  1,   /**< PC <- stimulator smpt_get_ll_init_ack()         */
    Smpt_Cmd_Ll_Channel_Config       =  2,   /**< PC -> stimulator smpt_send_ll_channel_config()  */
    Smpt_Cmd_Ll_Channel_Config_Ack   =  3,   /**< PC <- stimulator smpt_get_ll_channel_config_ack()*/
    Smpt_Cmd_Ll_Stop                 =  4,   /**< PC -> stimulator smpt_send_ll_stop()            */
    Smpt_Cmd_Ll_Stop_Ack             =  5,   /**< PC <- stimulator smpt_last_ack()                */
    /* 06 - 15 deprecated commands */
    Smpt_Cmd_Ll_Emg_Switches         = 18,   /**< PC -> stimulator smpt_send_ll_emg_switches()    */
    Smpt_Cmd_Ll_Emg_Switches_Ack     = 19,   /**< PC <- stimulator smpt_last_ack()                */

    Smpt_Cmd_Ml_Init                 = 30,   /**< PC -> stimulator smpt_send_ml_init()            */
    Smpt_Cmd_Ml_Init_Ack             = 31,   /**< PC <- stimulator smpt_last_ack()                */
    Smpt_Cmd_Ml_Update               = 32,   /**< PC -> stimulator smpt_send_ml_update()          */
    Smpt_Cmd_Ml_Update_Ack           = 33,   /**< PC <- stimulator smpt_last_ack()                */
    Smpt_Cmd_Ml_Stop                 = 34,   /**< PC -> stimulator smpt_send_ml_stop()            */
    Smpt_Cmd_Ml_Stop_Ack             = 35,   /**< PC <- stimulator smpt_last_ack()                */
    Smpt_Cmd_Ml_Get_Current_Data     = 36,   /**< PC -> stimulator smpt_send_ml_get_current_data()*/
    Smpt_Cmd_Ml_Get_Current_Data_Ack = 37,   /**< PC <- stimulator smpt_last_ack()                */

    Smpt_Cmd_Get_Version_Main        = 50,   /**< PC -> stimulator smpt_send_get_version_main()   */
    Smpt_Cmd_Get_Version_Main_Ack    = 51,   /**< PC <- stimulator smpt_get_get_version_main_ack()*/
    Smpt_Cmd_Get_Device_Id           = 52,   /**< PC -> stimulator smpt_send_get_device_id()      */
    Smpt_Cmd_Get_Device_Id_Ack       = 53,   /**< PC <- stimulator smpt_get_get_device_id_ack()   */
    Smpt_Cmd_Get_Battery_Status      = 54,   /**< PC -> stimulator smpt_send_get_battery_status() */
    Smpt_Cmd_Get_Battery_Status_Ack  = 55,   /**< PC <- stimulator smpt_get_get_battery_status_ack() */
    Smpt_Cmd_Set_Power               = 56,
    Smpt_Cmd_Set_Power_Ack           = 57,
    Smpt_Cmd_Reset                   = 58,   /**< PC -> stimulator smpt_reset()                   */
    Smpt_Cmd_Reset_Ack               = 59,   /**< PC <- stimulator smpt_last_ack()                */
    Smpt_Cmd_Get_Version_Stim        = 60,
    Smpt_Cmd_Get_Version_Stim_Ack    = 61,
    Smpt_Cmd_Get_Stim_Status         = 62,   /**< PC -> stimulator smpt_send_get_stim_status()    */
    Smpt_Cmd_Get_Stim_Status_Ack     = 63,   /**< PC <- stimulator smpt_get_get_stim_status_ack() */
    Smpt_Cmd_Get_Main_Status         = 64,   /**< PC -> stimulator smpt_send_get_main_status()    */
    Smpt_Cmd_Get_Main_Status_Ack     = 65,   /**< PC <- stimulator smpt_get_get_main_status_ack() */
    Smpt_Cmd_General_Error           = 66,
    Smpt_Cmd_Unknown_Cmd             = 67,   /**< PC <- stimulator The stimulator sends this cmd,
                                                  if the received cmd can not be processed,
                                                  because the command number is invalid.    */

    Smpt_Cmd_Al_Init                 = 80,
    Smpt_Cmd_Al_Init_Ack             = 81,
    Smpt_Cmd_Al_Update               = 82,
    Smpt_Cmd_Al_Update_Ack           = 83,
    Smpt_Cmd_Al_Stop                 = 84,
    Smpt_Cmd_Al_Stop_Ack             = 85,
    Smpt_Cmd_Al_File_Block           = 86,
    Smpt_Cmd_Al_Current_Data         = 87,
    Smpt_Cmd_Al_Get_Status           = 88,
    Smpt_Cmd_Al_Get_Status_Ack       = 89,
    Smpt_Cmd_Al_Get_File             = 90,
    Smpt_Cmd_Al_Get_File_Ack         = 91,
    Smpt_Cmd_Al_Remove_File          = 92,
    Smpt_Cmd_Al_Remove_File_Ack      = 93,

    Smpt_Cmd_Dl_Init                 = 100,   /**< PC -> dyscom hw smpt_send_dl_init()            */
    Smpt_Cmd_Dl_Init_Ack             = 101,   /**< PC <- dyscom hw smpt_last_ack()                */
    Smpt_Cmd_Dl_Start                = 102,   /**< PC -> dyscom hw smpt_send_dl_start()           */
    Smpt_Cmd_Dl_Start_Ack            = 103,   /**< PC <- dyscom hw smpt_last_ack()                */
    Smpt_Cmd_Dl_Stop                 = 104,   /**< PC -> dyscom hw smpt_send_dl_stop()            */
    Smpt_Cmd_Dl_Stop_Ack             = 105,   /**< PC <- dyscom hw smpt_last_ack()                */
    Smpt_Cmd_Dl_Send_Live_Data       = 106,   /**< PC <- dyscom hw smpt_send_dl_send_live_data()  */
    Smpt_Cmd_Dl_Send_File            = 107,   /**< PC <- dyscom hw smpt_send_dl_file()            */
    Smpt_Cmd_Dl_Send_MMI             = 108,   /**< PC <- dyscom hw smpt_send_dl_mmi               */
    Smpt_Cmd_Dl_Get                  = 109,   /**< PC -> dyscom hw smpt_send_dl_get()             */
    Smpt_Cmd_Dl_Get_Ack              = 110,   /**< PC <- dyscom hw smpt_last_ack()                */
    Smpt_Cmd_Dl_Power_Module         = 111,   /**< PC -> dyscom hw smpt_send_dl_module_power      */
    Smpt_Cmd_Dl_Power_Module_Ack     = 112,   /**< PC <- dyscom hw smpt_send_dl_power_module_ack  */
    Smpt_Cmd_Dl_Send_File_Ack        = 113,   /**< PC -> dyscom hw smpt_send_dl_file_ack          */
    Smpt_Cmd_Dl_Sys                  = 114,   /**< PC -> dyscom hw smpt_send_dl_sys               */
    Smpt_Cmd_Dl_Sys_Ack              = 115,   /**< PC <- dyscom hw smpt_last_ack                  */

    Smpt_Cmd_Bl_Init                 = 120,
    Smpt_Cmd_Bl_Init_Ack             = 121,
    Smpt_Cmd_Bl_Update_Init          = 122,
    Smpt_Cmd_Bl_Update_Init_Ack      = 123,
    Smpt_Cmd_Bl_Update_Block         = 124,
    Smpt_Cmd_Bl_Update_Block_Ack     = 125,
    Smpt_Cmd_Bl_Update_Stop          = 126,
    Smpt_Cmd_Bl_Update_Stop_Ack      = 127,

    Smpt_Cmd_Dm_Init                 = 140,  /**< PC -> stimulator smpt_send_dm_init()            */
    Smpt_Cmd_Dm_Init_Ack             = 141,  /**< PC <- stimulator smpt_get_dm_init_ack()         */
    Smpt_Cmd_Dm_Start                = 142,  /**< PC -> stimulator smpt_send_dm_start()           */
    Smpt_Cmd_Dm_Start_Ack            = 143,  /**< PC <- stimulator smpt_last_ack()                */
    Smpt_Cmd_Dm_Stop                 = 144,  /**< PC -> stimulator smpt_send_dm_stop()            */
    Smpt_Cmd_Dm_Stop_Ack             = 145,  /**< PC <- stimulator smpt_last_ack()                */
    Smpt_Cmd_Dm_Data                 = 147,  /**< PC <- stimulator smpt_get_dm_data()             */

    Smpt_Cmd_Sl_Test_Memory_Card     = 160,
    Smpt_Cmd_Sl_Test_Memory_Card_Ack = 161,
    Smpt_Cmd_Sl_Set_Debug            = 162,
    Smpt_Cmd_Sl_Set_Debug_Ack        = 163,
    Smpt_Cmd_Sl_Debug_Message        = 164,
    /* 165 */
    Smpt_Cmd_Sl_Set_Fuel_Gauge       = 166,
    Smpt_Cmd_Sl_Set_Fuel_Gauge_Ack   = 167,
    Smpt_Cmd_Sl_Set_Bluetooth        = 168,
    Smpt_Cmd_Sl_Set_Bluetooth_Ack    = 169,
    Smpt_Cmd_Sl_Set_Device_Id        = 170,
    Smpt_Cmd_Sl_Set_Device_Id_Ack    = 171,

    Smpt_Cmd_Last_Item = Smpt_Cmd_Sl_Set_Device_Id_Ack /* Adjust this line if another enum item
                                                          is added. */

} Smpt_Cmd; /**< \enum Smpt_Cmd Command numbers */


typedef enum
{
    Smpt_Cmd_Numbers_Low_Level_Min     = 0,
    Smpt_Cmd_Numbers_Low_Level_Max     = 29,

    Smpt_Cmd_Numbers_Mid_Level_Min     = 30,
    Smpt_Cmd_Numbers_Mid_Level_Max     = 49,

    Smpt_Cmd_Numbers_General_Level_Min  = 50,
    Smpt_Cmd_Numbers_General_Level_Max  = 79,

    Smpt_Cmd_Numbers_Service_Level_Min = 160,
    Smpt_Cmd_Numbers_Service_Level_Max = 189,

    Smpt_Cmd_Numbers_Apero_Level_Min   = 80,
    Smpt_Cmd_Numbers_Apero_Level_Max   = 99,

    Smpt_Cmd_Numbers_DysCom_Level_Min  = 100,
    Smpt_Cmd_Numbers_DysCom_Level_Max  = 119,

    Smpt_Cmd_Numbers_Boot_Level_Min    = 120,
    Smpt_Cmd_Numbers_Boot_Level_Max    = 139,

    Smpt_Cmd_Numbers_Data_Measurement_Min = 140,
    Smpt_Cmd_Numbers_Data_Measurement_Max = 159
} Smpt_Cmd_Numbers_Min_Max; /**< \enum Smpt_Cmd_Numbers_Min_Max
                                       Defines the min/max cmd numbers for the different levels
                                       in the enum Smpt_Cmd. */

typedef enum
{
    Smpt_Result_Successful                  = 0,  /**< No error, command execution is started */
    Smpt_Result_Transfer_Error              = 1,  /**< Checksum or length mismatch */
    Smpt_Result_Parameter_Error             = 2,  /**< At least one parameter value is wrong or
                                                       missing */
    Smpt_Result_Protocol_Error              = 3,  /**< The protocol version is not supported */
    Smpt_Result_Uc_Stim_Timeout_Error       = 4,  /**< There was an internal timeout. */
    Smpt_Result_Emg_Timeout_Error           = 5,
    Smpt_Result_Emg_Register_Error          = 6,
    Smpt_Result_Not_Initialized_Error       = 7,  /**< The current level is not initialized. This
                                                       happens if another level is still active
                                                       or the level has not been initialized. */
    Smpt_Result_Hv_Error                    = 8,
    Smpt_Result_Demux_Timeout_Error         = 9,  /**< The demux is not responding */

    Smpt_Result_Electrode_Error             = 10, /**< An electrode error happened during
                                                       stimulation. A minimum current of 15 mA is
                                                       required. If an electrode error is detected
                                                       the pulse generation is stopped. */
    Smpt_Result_Invalid_Cmd_Error           = 11, /**< Stimulation device can not process command.*/

    Smpt_Result_Demux_Parameter_Error       = 12, 
    Smpt_Result_Demux_Not_Initialized_Error = 13, 
    Smpt_Result_Demux_Transfer_Error        = 14, 
    Smpt_Result_Demux_Unknown_Ack_Error     = 15, 

    Smpt_Result_Pulse_Timeout_Error         = 16,
    Smpt_Result_Fuel_Gauge_Error            = 17, /**< The fuel gauge is not responding. */
    Smpt_Result_Live_Signal_Error           = 18,
    Smpt_Result_File_Transmission_Timeout   = 19,
    Smpt_Result_File_Not_Found              = 20,
    Smpt_Result_Busy                        = 21, /**< used in dl as result in dl_get_ack command
                                                       when some sending operation is still in
                                                       progress and no new sending operation
                                                       could be started */
    Smpt_Result_File_Error                  = 22,

    Smpt_Result_Flash_Erase_Error           = 23,
    Smpt_Result_Flash_Write_Error           = 24,
    Smpt_Result_Unknown_Controller_Error    = 25,
    Smpt_Result_Firmware_Too_Large_Error    = 26,

    Smpt_Result_Fuel_Gauge_Not_Programmed   = 27,

    Smpt_Result_Last_Item =  Smpt_Result_Fuel_Gauge_Not_Programmed /* Adjust this line if another enum item
                                                                      is added. */

} Smpt_Result; /**< \enum Smpt_Result Result values */


typedef enum
{
    Smpt_Length_Number_Of_Channels = 4,

    Smpt_Length_Number_Of_Acks    = 100,
    Smpt_Length_Serial_Port_Chars = 256,    /**< Array length of the serial port name */
    Smpt_Length_Points            = 16,      /**< Array length of points*/

    Smpt_Length_Header_Size              = 11,
    Smpt_Length_Max_Packet_Size          = 1200,  /**< The maximum packet size */
    Smpt_Length_Max_Packet_Size_No_Emg   = 512,
    Smpt_Length_Min_Packet_Size          = 12,
    Smpt_Length_Device_Id                = 10,
    Smpt_Length_Power_Modules            = 64,
    Smpt_Length_Packet_Output_Buffer     = 5 * Smpt_Length_Max_Packet_Size,
    Smpt_Length_File_Name                = 60,
    Smpt_Length_Packet_Input_Buffer_Rows = 100,
    Smpt_Length_Debug_Messages           = 150

} Smpt_Length; /**< \enum Smpt_Length
                *   Array lengths */

typedef enum
{
    Smpt_Packet_Number_Modulo = 64

} Smpt_Constants_Diverse;

typedef enum /* Limit */
{
    Smpt_Limit_Header_Size             = Smpt_Length_Header_Size,
    Smpt_Limit_Max_Packet_Size         = Smpt_Length_Max_Packet_Size,
    Smpt_Limit_Max_Packet_Size_No_Emg  = Smpt_Length_Max_Packet_Size_No_Emg,
    Smpt_Limit_Min_Packet_Size         = Smpt_Length_Min_Packet_Size

} Smpt_Limit; /** \enum Smpt_Limit Definitions for earlier versions of the library */

typedef enum
{
    Smpt_Channel_Red   = 0,
    Smpt_Channel_Blue  = 1,
    Smpt_Channel_Black = 2,
    Smpt_Channel_White = 3,
    Smpt_Channel_Undefined = -1
} Smpt_Channel; /**< \enum Smpt_Channel Channel colors*/

typedef enum
{
    Smpt_Demux_None  = 0,
    Smpt_Demux_Rt_72 = 1
} Smpt_Demux; /**< \enum Smpt_Demux Demux Types */

typedef enum /* Smpt_High_Voltage */
{
    Smpt_High_Voltage_Default = 0,
    Smpt_High_Voltage_Off     = 1,
    Smpt_High_Voltage_30V     = 2,
    Smpt_High_Voltage_60V     = 3,
    Smpt_High_Voltage_90V     = 4,
    Smpt_High_Voltage_120V    = 5,
    Smpt_High_Voltage_150V    = 6,
    Smpt_High_Voltage_Last_Item = Smpt_High_Voltage_150V

} Smpt_High_Voltage; /**< \enum Smpt_High_Voltage Values for the high voltage settings */

typedef enum /* Smpt_Main_Status */
{
    Smpt_Main_Status_Uninitialized  = 0,
    Smpt_Main_Status_Dm_Initialized = 1,
    Smpt_Main_Status_Dm_Running     = 2,
    Smpt_Main_Status_Last_Item      = Smpt_Main_Status_Dm_Running

} Smpt_Main_Status; /**< \enum Smpt_Main_Status */

typedef enum /* Smpt_Stim_Status */
{
    Smpt_Stim_Status_Uninitialized  = 0,
    Smpt_Stim_Status_Ll_Initialized = 1,
    Smpt_Stim_Status_Ml_Initialized = 2,
    Smpt_Stim_Status_Ml_Running     = 3,
    Smpt_Stim_Status_Last_Item      = Smpt_Stim_Status_Ml_Running

} Smpt_Stim_Status; /**< \enum Smpt_Stim_Status  */

typedef struct /* Point */
{
    uint16_t time;              /**< [0 .. 1 .. 4095] µs duration. (Every value < 10 = 10 µs) \n
                                     If denervation_point == 1 (true), time is multiplied by 500  */
    float current;              /**< [-150 .. -149.5 .. 150] mA current */
    uint8_t control_mode;       /**< Control mode, \see Smpt_Ll_Control_Mode */
    uint8_t interpolation_mode; /**< Interpolation mode, \see Smpt_Ll_Interpolation_Mode */
} Smpt_point; /**< \struct Smpt_point
                  *   Struct for point definition.
                  *   \see Smpt_ll_channel_config */

typedef struct /* Smpt_ack */
{
    uint8_t packet_number;      /**< Packet number echo */
    uint16_t command_number;    /**< Command number of the ack */
    Smpt_Result result;         /**< \see Smpt_Result */

} Smpt_ack; /**< \struct Smpt_ack
                    General acknowledgement struct */

typedef struct /* Smpt_cmd */
{
    uint8_t packet_number;      /**< [0 - 63] Packet number */
    uint16_t command_number;    /**< Command number \see Smpt_Cmd */

} Smpt_cmd; /**< \struct Smpt_cmd
                 General command struct  */

typedef struct
{
    uint32_t acks_length;                            /**< ... */
    uint32_t acks_current_index;                     /**< ... */
    Smpt_ack acks[Smpt_Length_Number_Of_Acks];       /**< ... */

    uint32_t requests_current_index;                 /**< ... */
    uint32_t requests_expected_index;                /**< ... */
    uint32_t number_of_expected;                     /**< ... */
    Smpt_cmd requests[Smpt_Length_Number_Of_Acks];   /**< ... */

    uint32_t new_ack_available;                      /**< ... */

} Smpt_cmd_list; /**< \struct Smpt_cmd_list
                       Struct for internal data handling. */

typedef struct
{
    uint8_t  *buffer;                    /**< ... */
    uint8_t  *buffer_state;              /**< ... */
    uint32_t write_row_length_count;     /**< ... */
    uint32_t write_row_count;            /**< ... */
    uint32_t read_row_count;             /**< ... */
    bool     ignore_next_byte;           /**< ... */
    uint32_t number_of_rows;             /**< ... */
    uint32_t row_length;                 /**< ... */
} Packet_input_buffer; /**< \struct Packet_input_buffer
                       Struct for internal data handling. */

#ifdef _WIN32
    #include "windows.h"
#endif

typedef struct /* Smpt_device */
{
#if defined(_WIN32) || defined(__linux__)
    uint32_t packet_length;                       /**< ... */
    uint8_t packet[Smpt_Length_Max_Packet_Size];  /**< ... */

    Smpt_cmd_list cmd_list;                       /**< ... */
#endif
#ifdef _WIN32
    HANDLE serial_port_handle_;                   /**< ... */
#endif
#ifdef __linux__
    int serial_port_descriptor;
#endif
    int8_t current_packet_number;                 /**< ... */
#if defined(_WIN32) || defined(__linux__)
    char serial_port_name[Smpt_Length_Serial_Port_Chars];                    /**< ... */
    Packet_input_buffer packet_input_buffer;      /**< ... */
    uint8_t packet_input_buffer_data [Smpt_Length_Packet_Input_Buffer_Rows *
                                      Smpt_Length_Max_Packet_Size];          /**< ... */
    uint8_t packet_input_buffer_state[Smpt_Length_Packet_Input_Buffer_Rows]; /**< ... */
#endif
} Smpt_device; /**< \struct Smpt_device
                *    Struct used for internal data handling. Do not modify the variables
                     unless you know, what you are doing. */


typedef struct /* Smpt_version */
{
    uint8_t major;    /**< major version number */
    uint8_t minor;    /**< minor version number */
    uint8_t revision; /**< revision version number */

} Smpt_version; /**< \struct Smpt_version
                             Struct for general version information */

typedef struct /* Smpt_uc_version */
{
    Smpt_version fw_version;    /**< Firmware version \see Smpt_version */
    Smpt_version smpt_version;  /**< ScienceMode version \see Smpt_version */

} Smpt_uc_version; /**< \struct Smpt_uc_version
                                Contains the firmware and the ScienceMode version */

typedef struct /* Smpt_get_version_ack */
{
    uint8_t         packet_number; /**< [0 - 63] Packet number echo */
    Smpt_Result     result;        /**< \see Smpt_Result */
    Smpt_uc_version uc_version;    /**< \see Smpt_uc_version */

} Smpt_get_version_ack; /**< \struct Smpt_get_version_ack
                             Struct for the get_version_ack response.*/

typedef struct /* Smpt_get_device_id_ack */
{
    uint8_t     packet_number;    /**< [0 - 63] Packet number echo */
    Smpt_Result result;           /**< \see Smpt_Result */
    char        device_id[Smpt_Length_Device_Id]; /**< ID of the device */

} Smpt_get_device_id_ack; /**< \struct Smpt_get_device_id_ack
                               Struct for the get_device_id_ack response. */

typedef struct /* Smpt_get_battery_status_ack */
{
    uint8_t     packet_number;   /**< [0 - 63] Packet number echo */
    Smpt_Result result;          /**< \see Smpt_Result */
    uint8_t     battery_level;   /**< [0 .. 1 .. 100] % Rechargeable battery level */
    uint16_t    battery_voltage; /**< [0 .. 1 .. 65535] mV Rechargeable battery voltage */

} Smpt_get_battery_status_ack; /**< \struct Smpt_get_battery_status_ack */

typedef struct /* Smpt_get_stim_status_ack */
{
    uint8_t           packet_number;      /**< [0 - 63] Packet number echo */
    Smpt_Result       result;             /**< \see Smpt_Result */
    Smpt_Stim_Status  stim_status;        /**< \see Smpt_Stim_Status */
    Smpt_High_Voltage high_voltage_level; /**< \see Smpt_High_Voltage */

} Smpt_get_stim_status_ack; /**< \struct Smpt_get_stim_status_ack */


typedef struct /* Smpt_get_main_status_ack */
{
    uint8_t          packet_number; /**< [0 - 63] Packet number echo */
    Smpt_Result      result;        /**< \see Smpt_Result */
    Smpt_Main_Status main_status;   /**< \see Smpt_Main_Status */

} Smpt_get_main_status_ack; /**< \struct Smpt_get_main_status_ack */


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ack
*******************************************************************************/
SMPT_API void smpt_clear_ack(Smpt_ack *const ack);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] get_battery_status_ack
*******************************************************************************/
SMPT_API void smpt_clear_get_battery_status_ack(Smpt_get_battery_status_ack *const
                                                get_battery_status_ack);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] get_device_id_ack
*******************************************************************************/
SMPT_API void smpt_clear_get_device_id_ack(Smpt_get_device_id_ack *const
                                           get_device_id_ack);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] get_version_ack
*******************************************************************************/
SMPT_API void smpt_clear_get_version_ack(Smpt_get_version_ack *const get_version_ack);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] get_stim_status_ack
*******************************************************************************/
SMPT_API void smpt_clear_get_stim_status_ack(Smpt_get_stim_status_ack *const get_stim_status_ack);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] get_main_status_ack
*******************************************************************************/
SMPT_API void smpt_clear_get_main_status_ack(Smpt_get_main_status_ack *const get_main_status_ack);

/***************************************************************************//**
* \brief Clears the struct (sets all value to 0).
*
* \param[in,out] device
*******************************************************************************/
SMPT_API void smpt_clear_device(Smpt_device *const device);

/***************************************************************************//**
* \brief Checks if a command is a general command.
*
* \param[in] cmd
*******************************************************************************/
SMPT_API bool smpt_is_general(Smpt_Cmd cmd);

/***************************************************************************//**
* \brief Checks if a command is a low-level command.
*
* \param[in] cmd
*******************************************************************************/
SMPT_API bool smpt_is_low_level(Smpt_Cmd cmd);

/***************************************************************************//**
* \brief Checks if a command is a mid-level command.
*
* \param[in] cmd
*******************************************************************************/
SMPT_API bool smpt_is_mid_level(Smpt_Cmd cmd);

/***************************************************************************//**
* \brief Checks if a command is a data-measurement command.
*
* \param[in] cmd
*******************************************************************************/
SMPT_API bool smpt_is_data_measurement(Smpt_Cmd cmd);

SMPT_API bool smpt_is_dyscom_level (Smpt_Cmd cmd); /**< ... */
SMPT_API bool smpt_is_apero_level  (Smpt_Cmd cmd); /**< ... */
SMPT_API bool smpt_is_boot_level   (Smpt_Cmd cmd); /**< ... */
SMPT_API bool smpt_is_service_level(Smpt_Cmd cmd); /**< ... */

#ifdef __cplusplus
}
#endif


#endif /* SMPT_DEFINITIONS_DATA_TYPES_H */
