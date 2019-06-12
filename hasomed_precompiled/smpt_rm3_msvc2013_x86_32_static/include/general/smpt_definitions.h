#ifndef SMPT_DEFINITIONS_H
#define SMPT_DEFINITIONS_H

/***************************************************************************//**
* \file smpt_definitions.h
* \author Bjoern Kuberski
* \copyright Hasomed GmbH 2013-2017
*
* This is the main science mode include file.
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "smpt_definitions_data_types.h"

typedef enum /* Smpt_General */
{
    Smpt_Library_Version_Major     = 3,  /**< Used for interface changes that breaks backward
                                              compatibility */
    Smpt_Library_Version_Minor     = 2,  /**< Used for adding commands, parameters\n
                                              The interface is backward compatible. */
    Smpt_Library_Version_Revision  = 4   /**< Used for bugfixes, no interface changes */

} Smpt_General; /**< \enum Smpt_General General protocol and library constants */

#ifdef __cplusplus
}
#endif

#endif /* SMPT_DEFINITIONS_H */
