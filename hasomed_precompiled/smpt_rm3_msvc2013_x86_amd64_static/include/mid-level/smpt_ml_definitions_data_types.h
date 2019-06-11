#ifndef SMPT_ML_DEFINITIONS_DATA_TYPES_H
#define SMPT_ML_DEFINITIONS_DATA_TYPES_H

/***************************************************************************//**
* \file smpt_ml_definitions_data_types.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file defines the data types of the protocol, which are related to the
* mid-level.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_definitions_data_types.h"

typedef struct /* Ml_init */
{
    bool enable_demux;               /**< False - The demultiplexer is disabled, \n
                                          True  - The demultiplexer is enabled */
    uint8_t packet_number;           /**< [0-63] Packet number */

} Smpt_ml_init; /**< \struct Smpt_ml_init
                     Struct for the Ml_init command. \see smpt_send_ml_init() */

typedef Smpt_ack Smpt_ml_ack; /**< \struct Smpt_ml_ack
                                   \see Smpt_ack */

typedef Smpt_point Smpt_ml_point; /**< \struct Smpt_ml_point
                                       \see Smpt_point */

typedef struct /* Ml_channel_config */
{
    uint8_t ramp;                      /**< [0-15] pulses \n
                                            Number of linear increasing lower current pulse pattern
                                            until the full current is reached\n
                                            The ramp is excecuted if the channel is enabled. */
    float period;                      /**< [0,5–16383] ms \n ([<0.1-2000] Hz)
                                             Time between two pulse patterns */
    uint8_t number_of_points;          /**< [1 - 16] Number of points */
    Smpt_ml_point points[Smpt_Length_Points];
                                       /**< Stimulation points \see Smpt_point */

    bool enable_demux;                 /**< False - The demultiplexer is disabled, \n
                                            True  - The demultiplexer is enabled */
    /* demux configuration is added later */

} Smpt_ml_channel_config; /**< \struct Smpt_ml_channel_config
                               Channel configuration for one channel. */

typedef struct /* Ml_update */
{
    bool softstart;                    /**< False - The softstart is disabled, \n
                                            True  - The softstart is enabled (approx. 20 s) */
    bool enable_channel[Smpt_Length_Number_Of_Channels];
                                        /**< Enable/Disable each channel  \n
                                          *  e.g. enable_channel[Smpt_Channel_Red] = true; \n
                                          *  to enable channel red \n
                                          *  False - The channel is disabled, \n
                                          *  True - The channel is enabled */
    Smpt_ml_channel_config channel_config[Smpt_Length_Number_Of_Channels];
                                          /**< Channel configuration for each channel */
    uint8_t packet_number;                /**< [0 - 63] Packet number */

} Smpt_ml_update; /**< \struct Smpt_ml_update
                       Struct for the Ml_update command. \see smpt_send_ml_update() */

typedef enum /* Ml_Data */
{
    Smpt_Ml_Data_Stimulation          = 1
} Smpt_Ml_Data; /**< \enum Smpt_Ml_Data */

typedef struct /* Ml_get_current_data */
{
    uint8_t packet_number;           /**< [0 - 63] Packet number */
    bool data_selection[8];          /**< Selection of the requested data, \see Smpt_Ml_Data */

} Smpt_ml_get_current_data; /**< \struct Smpt_ml_get_current_data
                                 Struct for the Ml_get_current_data command.
                                 \see smpt_send_ml_get_current_data() */

typedef enum /* Ml_Stimulation_State */
{
    Smpt_Ml_Stimulation_Stopped = 0,
    Smpt_Ml_Stimulation_Running = 1,

    Smpt_Ml_Stimulation_Last_Item = 1
} Smpt_Ml_Stimulation_State; /**< \enum Smpt_Ml_Stimulation_State */

typedef struct /* Smpt_ml_stimulation_data */
{
    bool electrode_error[Smpt_Length_Number_Of_Channels]; /**< False - No electrode error \n
                                                               True - Electrode error \n
                                                               or channels. */
    Smpt_Ml_Stimulation_State stimulation_state; /**< \see Current stimulation state */

} Smpt_ml_stimulation_data;    /**< \struct Smpt_ml_stimulation_data
                                    Contains the current stimulation data. */

typedef struct /* Ml_get_current_data_ack */
{
    uint8_t packet_number;              /**< [0 - 63] Echo packet number */
    /* general */
    Smpt_Result result;                 /**< \see Smpt_Result */
    bool data_selection[8];             /**< \see Smpt_ml_get_current_data */

    /* optional */
    Smpt_ml_stimulation_data stimulation_data;  /**< \see Smpt_ml_stimulation_data */

} Smpt_ml_get_current_data_ack; /**< \struct Smpt_ml_get_current_data_ack
                                     Struct for the Ml_get_current_data_ack command.
                                     \see smpt_get_ml_get_current_data_ack() */


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in] ml_init
*******************************************************************************/
SMPT_API void smpt_clear_ml_init(Smpt_ml_init *const ml_init);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in] ml_update
*******************************************************************************/
SMPT_API void smpt_clear_ml_update(Smpt_ml_update *const ml_update);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in] ml_get_current_data
*******************************************************************************/
SMPT_API void smpt_clear_ml_get_current_data(Smpt_ml_get_current_data *const ml_get_current_data);


/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in] ml_get_current_data_ack
*******************************************************************************/
SMPT_API void smpt_clear_ml_get_current_data_ack(Smpt_ml_get_current_data_ack
                                                 *const ml_get_current_data_ack);

/***************************************************************************//**
* \brief Clears the struct (sets all values to 0).
*
* \param[in] ml_ack
*******************************************************************************/
SMPT_API void smpt_clear_ml_ack(Smpt_ml_ack *const ml_ack);

#ifdef __cplusplus
}
#endif

#endif /* SMPT_ML_DEFINITIONS_DATA_TYPES_H */
