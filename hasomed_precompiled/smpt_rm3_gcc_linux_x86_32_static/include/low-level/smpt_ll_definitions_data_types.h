#ifndef SMPT_LL_DEFINITIONS_DATA_TYPES_H
#define SMPT_LL_DEFINITIONS_DATA_TYPES_H

/***************************************************************************//**
* \file smpt_ll_definitions_data_types.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file defines the data types for the low level protocol.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_definitions_data_types.h"

typedef enum /* Smpt_Ll_Control_Mode */
{
    Smpt_Ll_Control_Current      = 0,        /**< The current is controlled */
    Smpt_Ll_Control_Voltage      = 1,        /**< Not yet implemented */
    Smpt_Ll_Control_Measure_Mode = 2,        /**< Not yet implemented */
    Smpt_Ll_Control_Qi           = 3,        /**< Not yet implemented */
    Smpt_Ll_Control_Qt           = 4,        /**< Not yet implemented */
    Smpt_Ll_Control_X1           = 5,        /**< Not yet implemented */
    /* Adjust the following item if another enum item is added */
    Smpt_Ll_Control_Last_Item = Smpt_Ll_Control_X1

} Smpt_Ll_Control_Mode; /**< \enum Smpt_Ll_Control_Mode The controls modes in Ll_channel_config.
                              \see Smpt_Ll_channel_config */


typedef enum /* Ll_Interpolation_Mode */
{
    Smpt_Ll_Interpolation_Jump   = 0,   /**< No interpolation between the points */
    Smpt_Ll_Interpolation_Linear = 1,   /**< Not yet implemented */
    Smpt_Ll_Interpolation_Exp    = 2,   /**< Not yet implemented */
    Smpt_Ll_Interpolation_X      = 3,   /**< Not yet implemented */
    /* Adjust the following item if another enum item is added */
    Smpt_Ll_Interpolation_Last_Item = Smpt_Ll_Interpolation_X

} Smpt_Ll_Interpolation_Mode; /**< \enum Smpt_Ll_Interpolation_Mode The interpolation modes in
                                         Ll_channel_config. \see Smpt_Ll_channel_config */
typedef enum
{
    Smpt_Length_Number_Of_Switches = 512,                          /**< Currently unused */
    Smpt_Length_Demux_Config = Smpt_Length_Number_Of_Switches / 8, /**< Currently unused */
    Smpt_Length_Demux_Id     = 50                                  /**< Currently unused */

} Smpt_Ll_Length;

typedef struct /* Ll_init */
{
    bool enable_demux;              /**< Not yet implemented */
    bool enable_denervation;        /**< Not yet implemented */
    Smpt_High_Voltage high_voltage_level; /**< Sets the high voltage level \see Smpt_High_Voltage */
    uint8_t packet_number;                /**< [0 - 63] Packet number */

} Smpt_ll_init; /**< \struct Smpt_ll_init
                     Struct for the Ll_init command. \see smpt_send_ll_init() */

typedef struct /* Ll_init_ack */
{
    uint8_t packet_number;    /**< Packet number echo */
    Smpt_Result result;       /**< \see Smpt_Result */
    char    demux_id[Smpt_Length_Demux_Id];  /**< Not yet implemented */

} Smpt_ll_init_ack; /**< \struct Smpt_ll_init_ack
                     *   Struct for the Ll_init_ack response.
                     *   \see smpt_get_ll_init_ack() */


typedef Smpt_point Smpt_ll_point; /**< \struct Smpt_ll_init_ack
                                       \see Smpt_point */


typedef struct /* Ll_channel_config */
{
    bool enable_stimulation;   /**< Value | Description
                                    ----- | -----------
                                    False | Do not transfer stimulation points, no stimulation
                                    True  | Transfer points, the points are executed.  */
    Smpt_Channel channel;      /**< [0 - 3] Channel number \n \see Smpt_Channel */
    bool modify_demux;         /**< Not yet implemented */
    uint8_t number_of_points;  /**< [1 - 16] Number of points */
    Smpt_ll_point points[Smpt_Length_Points]; /**< Stimulation points \see Smpt_Ll_point */
    uint8_t demux_config[Smpt_Length_Demux_Config]; /**< Not yet implemented */
    uint8_t demux_length;                           /**< Not yet implemented */
    uint8_t packet_number;           /**< [0 - 63] Packet number */

} Smpt_ll_channel_config; /**< \struct Smpt_ll_channel_config
                               Struct for the Ll_channel_config command.
                               \see smpt_send_ll_channel_config() */


typedef struct /* Smpt_Ll_channel_config_ack */
{
    uint8_t packet_number;     /**< Packet number echo */
    Smpt_Result result;        /**< \see Smpt_Result */
    Smpt_Channel electrode_error;   /**< Contains the channel of the electrode error,
                                    if the result is electrode error. \see Smpt_Channel*/
} Smpt_ll_channel_config_ack;  /**< \struct Smpt_ll_channel_config_ack
                                *   Struct for the Ll_channel_config_ack response.
                                *   \see smpt_get_ll_channel_config_ack() */


typedef Smpt_ack Smpt_ll_ack;  /**< \struct Smpt_ll_ack
                                    \see Smpt_ack */

typedef enum
{
    Smpt_Ll_Demux_Unused   = 0,  /**< Currently unused */
    Smpt_Ll_Demux_Positive = 1,  /**< Currently unused */
    Smpt_Ll_Demux_Negative = 2   /**< Currently unused */
} Smpt_Ll_Demux_Element_Mode;    /**< Currently unused */


typedef struct
{
    Smpt_Demux demux_id; /**< Not yet implemented */
    Smpt_Ll_Demux_Element_Mode electrodes[Smpt_Length_Number_Of_Switches]; /**< Not yet implemented */
} Smpt_ll_demux; /**< Currently unused */

typedef struct
{
    uint8_t ks_1_start;     /**< Not yet implemented */
    uint8_t ks_1_duration;  /**< Not yet implemented */
    uint8_t ks_2_start;     /**< Not yet implemented */
    uint8_t ks_2_duration;  /**< Not yet implemented */
    uint8_t ls_stop;        /**< Not yet implemented */
    uint8_t packet_number;  /**< [0 - 63] Packet number */
} Smpt_ll_emg_switches;     /**< Currently unused */


/***************************************************************************//**
* \brief This function is currently unused.
*******************************************************************************/
SMPT_API bool smpt_ll_demux_convert(Smpt_ll_channel_config *const ll_channel_config,
                                    const Smpt_ll_demux *const ll_demux);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_init
*******************************************************************************/
SMPT_API void smpt_clear_ll_init(Smpt_ll_init *const ll_init);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_init_ack
*******************************************************************************/
SMPT_API void smpt_clear_ll_init_ack(Smpt_ll_init_ack *const ll_init_ack);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_channel_config
*******************************************************************************/
SMPT_API void smpt_clear_ll_channel_config(Smpt_ll_channel_config *const ll_channel_config);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_channel_config_ack
*******************************************************************************/
SMPT_API void smpt_clear_ll_channel_config_ack(Smpt_ll_channel_config_ack *const ll_channel_config_ack);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_ack
*******************************************************************************/
SMPT_API void smpt_clear_ll_ack(Smpt_ll_ack *const ll_ack);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_point
*******************************************************************************/
SMPT_API void smpt_clear_ll_point(Smpt_ll_point *const ll_point);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in,out] ll_emg_switches
*******************************************************************************/
SMPT_API void smpt_clear_ll_emg_switches(Smpt_ll_emg_switches *const ll_emg_switches);


#ifdef __cplusplus
}
#endif

#endif /* SMPT_LL_DEFINITIONS_DATA_TYPES_H */
