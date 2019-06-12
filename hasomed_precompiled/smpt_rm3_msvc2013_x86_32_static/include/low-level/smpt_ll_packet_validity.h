#ifndef SMPT_LL_PACKET_VALIDITY_H
#define SMPT_LL_PACKET_VALIDITY_H

/***************************************************************************//**
* \file smpt_ll_packet_validity.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file contains functions for validity checks of the command structs.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_ll_definitions.h"

/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_init
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_init(const Smpt_ll_init *const ll_init);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_init_ack
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_init_ack(const Smpt_ll_init_ack *const ll_init_ack);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_channel_config
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_channel_config(const Smpt_ll_channel_config
                                              *const ll_channel_config);

/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_channel_config_ack
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_channel_config_ack(const Smpt_ll_channel_config_ack
                                                  *const ll_channel_config_ack);

/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_emg_switches
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_emg_switches(const Smpt_ll_emg_switches *const ll_emg_switches);



/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_point
* \param[in] index index of the point for debugging purposes
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_point(const Smpt_ll_point *const ll_point, uint8_t index);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ll_demux
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_demux_rt_72(const Smpt_ll_demux *const ll_demux);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] demux_config
* \param[in] demux_length
* \returns True if all parameters are valid.
*******************************************************************************/
SMPT_API bool smpt_is_valid_ll_demux_config_rt_72(uint8_t demux_config[], uint32_t demux_length);

#ifdef __cplusplus
}
#endif

#endif /* SMPT_LL_PACKET_VALIDITY_H */
