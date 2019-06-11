#ifndef SMPT_ML_CLIENT_H
#define SMPT_ML_CLIENT_H

/***************************************************************************//**
* \file smpt_ml_client.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file contains mid level ScienceMode functions to control the stimulator
* with an external device.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 Section Windows and Linux
*******************************************************************************/
#if defined(_WIN32) || defined(__linux__)

#include "smpt_definitions.h"
#include "smpt_ml_definitions_data_types.h"
#include "smpt_ml_packet_validity.h"
#include "smpt_messages.h"
#include "smpt_client.h"

/***************************************************************************//**
* \brief Builds the Ml_init packet and sends it to the serial port.
* This command switches on the high voltage for both modules (execution duration
* 2 x 40 ms).
*
* \param[in,out] device
* \param[in] ml_init
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ml_init(Smpt_device *const device, const Smpt_ml_init *const ml_init);


/***************************************************************************//**
* \brief Builds the Ml_update packet and sends it to the serial port.
*
* This command starts or updates the stimulation using the parameters.
*
* \param[in,out] device
* \param[in] ml_update
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ml_update(Smpt_device *const device,
                                  const Smpt_ml_update *const ml_update);


/***************************************************************************//**
* \brief Builds the Ml_get_current_data packet and sends it to the serial port.
*
* This command is used as a keep-alive signal. After the start of the
* stimulation (Ml_update) you need to send this command at least every 2 seconds.
* The response contains general and requested status information.
*
* \param[in,out] device
* \param[in] ml_get_current_data
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ml_get_current_data(Smpt_device *const device,
                                            const Smpt_ml_get_current_data
                                            *const ml_get_current_data);


/***************************************************************************//**
* \brief Builds the Ml_stop packet and sends it to the serial port.
* This command switches off the high voltage for both modules (execution duration
* 40 ms).
*
* \param[in,out] device
* \param[in] packet_number
* \returns True if the command was send successfully
*******************************************************************************/
SMPT_API bool smpt_send_ml_stop(Smpt_device *const device, uint8_t packet_number);


/***************************************************************************//**
* \brief Write the last received ml_get_current_data_ack in the given struct
*
* \param[in,out] device
* \param[in,out] ml_get_current_data_ack
*******************************************************************************/
SMPT_API bool smpt_get_ml_get_current_data_ack(Smpt_device *const device,
                                               Smpt_ml_get_current_data_ack *const
                                               ml_get_current_data_ack);

#endif /* defined(_WIN32) || defined(__linux__) */

#ifdef __cplusplus
}
#endif

#endif /* SMPT_ML_CLIENT_H */
