#ifndef SMPT_ML_PACKET_VALIDITY_H
#define SMPT_ML_PACKET_VALIDITY_H

/***************************************************************************//**
* \file smpt_ml_packet_validity.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file contains functions for validity checks of the mid-level command
* structs.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_ml_definitions_data_types.h"

/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ml_init
* \returns True if all parameters are valid.
*******************************************************************************/
bool smpt_is_valid_ml_init(const Smpt_ml_init *const ml_init);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ml_update
* \returns True if all parameters are valid.
*******************************************************************************/
bool smpt_is_valid_ml_update(const Smpt_ml_update *const ml_update);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ml_get_current_data
* \returns True if all parameters are valid.
*******************************************************************************/
bool smpt_is_valid_ml_get_current_data(const Smpt_ml_get_current_data *const ml_get_current_data);


/***************************************************************************//**
* \brief Checks the validity of the passed struct.
*
* \param[in] ml_get_current_data_ack
* \returns True if all parameters are valid.
*******************************************************************************/
bool smpt_is_valid_ml_get_current_data_ack(const Smpt_ml_get_current_data_ack
                                           *const ml_get_current_data_ack);

#ifdef __cplusplus
}
#endif

#endif /* SMPT_ML_PACKET_VALIDITY_H */
