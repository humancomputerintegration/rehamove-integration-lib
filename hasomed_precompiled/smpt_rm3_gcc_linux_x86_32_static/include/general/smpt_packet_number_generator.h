#ifndef SMPT_PACKET_NUMBER_GENERATOR_H
#define SMPT_PACKET_NUMBER_GENERATOR_H

/***************************************************************************//**
* \file smpt_packet_number_generator.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2016
*
* This file defines a simple packet number generator. It generates packet
* numbers 0-63 in ascending order.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_definitions.h"

/***************************************************************************//**
* \brief Resets the packet number generator. The next packet number is to 0.
*
* \param[in,out] device The device struct is needed for internal handling.
*******************************************************************************/
void smpt_packet_number_generator_reset(Smpt_device *const device);

/***************************************************************************//**
* \brief Returns the next packet number
*
* \param[in,out] device The device struct is needed for internal handling.
* \returns The next packet number (0-63)
*******************************************************************************/
uint8_t smpt_packet_number_generator_next(Smpt_device *const device);

#ifdef __cplusplus
}
#endif

#endif /* SMPT_PACKET_NUMBER_GENERATOR_H */

