#ifndef SMPT_MESSAGES_H
#define SMPT_MESSAGES_H

/***************************************************************************//**
* \file smpt_messages.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This file defines functions for error messages. The error function needs to
* be initialized with a callback function using smpt_init_error_callback().
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_definitions.h"

/***************************************************************************//**
* \brief Sets the callback function for the error message
*
* \param[in] error_function The callback function
*******************************************************************************/
SMPT_API void smpt_init_error_callback(void (*error_function)(const char* format));

/***************************************************************************//**
* \brief Calls the error callback function with the error message.
*
* \param[in] format A variable number of arguments (usage like printf()))
*******************************************************************************/
SMPT_API void smpt_error(const char* format, ...);

/***************************************************************************//**
* \brief Prints a debug message to stdout. This function is for internal usage
* only.
*
* \param[in] format A variable number of arguments (usage like printf())
*******************************************************************************/
void smpt_debug(const char* format, ...);

/***************************************************************************//**
* \brief Prints the array to stdout. This function is for internal usage only.
*
* \param[in] array
* \param[in] array_length
*******************************************************************************/
void smpt_print_array(const uint8_t array[], uint32_t array_length);

#ifdef __cplusplus
}
#endif

#endif /* SMPT_MESSAGES_H */
