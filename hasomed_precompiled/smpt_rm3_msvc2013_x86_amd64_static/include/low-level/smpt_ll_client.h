#ifndef SMPT_LL_CLIENT_H
#define SMPT_LL_CLIENT_H

/***************************************************************************//**
* \file smpt_ll_client.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file contains low level ScienceMode functions to control the stimulator
* with an external device.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(__linux__)

#include "smpt_ll_definitions.h"
#include "smpt_messages.h"
#include "smpt_ll_packet_validity.h"
#include "smpt_client.h"

/* Send commands */
/***************************************************************************//**
* \brief Builds the Ll_init packet and sends it to the device.
* This command switches on the high voltage (execution duration 40 ms).
*
* \param[in,out] device
* \param[in] ll_init
*
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ll_init(Smpt_device *const device,
                                const Smpt_ll_init *const ll_init);


/***************************************************************************//**
* \brief Builds the Ll_channel_config packet and sends it to the device.
*
* Send this command periodically to set the frequency of your choice. You can also
* send commands shortly after another. The stimulator will internally buffer the
* command and execute it as fast as possible.
* It is recommended, but not necessary to wait for the response of the command.
*
* \param[in,out] device
* \param[in] ll_channel_config
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ll_channel_config(Smpt_device *const device,
                                          const Smpt_ll_channel_config *const ll_channel_config);


/***************************************************************************//**
* \brief Builds the Ll_stop packet and sends it to the device.
* This command switches off the high voltage (execution duration 40 ms).
*
* \param[in,out] device
* \param[in] packet_number
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ll_stop(Smpt_device *const device,
                                uint8_t packet_number);

/***************************************************************************//**
* \brief This function is currently unused.
*******************************************************************************/
SMPT_API bool smpt_send_ll_emg_switches(Smpt_device *const device,
                                        const Smpt_ll_emg_switches *const ll_emg_switches);

/**** Acks ***************************************************************/

/**** Get data from acks *************************************************/
/***************************************************************************//**
* \brief Writes the received ll_init_ack response in the given struct.
*
* \param[in,out] device
* \param[in,out] ll_init_ack
*******************************************************************************/
SMPT_API bool smpt_get_ll_init_ack(const Smpt_device *const device,
                                   Smpt_ll_init_ack *const ll_init_ack);

/***************************************************************************//**
* \brief Write the received ll_channel_config_ack in the given struct

* \param[in,out] device
* \param[in,out] ll_channel_config_ack
*******************************************************************************/
SMPT_API bool smpt_get_ll_channel_config_ack(const Smpt_device *const device,
                 Smpt_ll_channel_config_ack *const ll_channel_config_ack);


#endif /* defined(_WIN32) || defined(__linux__) */

#ifdef __cplusplus
}
#endif

#endif /* SMPT_LL_CLIENT_H */
