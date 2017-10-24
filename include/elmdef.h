/* *****************************************************************************
 * 
 * Name:    elmdef.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Define macros for ELM.
 *              
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ELM_DEF_H
#define ELM_DEF_H

/* Defines */
#define PROGRAM "elm"

/* Defines */
#define ELM_EXIT_SUCCESS           0
#define ELM_EXIT_INV_OPT           1
#define ELM_EXIT_MNGR_NEW          10
#define ELM_EXIT_MNGR_APP          11
#define ELM_EXIT_MNGR_RUN          12
#define ELM_EXIT_MNGR_MKDIR        13
#define ELM_EXIT_MNGR_SIG_SETUP    14
#define ELM_EXIT_MNGR_SIG          15
#define ELM_EXIT_MNGR_X            16
#define ELM_EXIT_MNGR_PROMPT       17
#define ELM_EXIT_MNGR_BUILD_WIN    18
#define ELM_EXIT_MNGR_BUILD_APP    19
#define ELM_EXIT_MNGR_PTHREAD      20
#define ELM_EXIT_X_INIT            21
#define ELM_EXIT_X_ENV_DISPLAY     22
#define ELM_EXIT_X_ENV_TTY         23
#define ELM_EXIT_X_ENV_TTYN        24
#define ELM_EXIT_X_ENV_XAUTH       25
#define ELM_EXIT_X_ENV_VT          26
#define ELM_EXIT_X_RUN             27
#define ELM_EXIT_X_WAIT            28
#define ELM_EXIT_X_STOP            29
#define ELM_EXIT_X_XCOMPMGR        30

#define ELM_EXIT_PAM_LOGIN         31

#define ELM_VAR_RUN_DIR                                "/var/run/" PROGRAM

#define ELM_CMD_SHUTDOWN "/usr/bin/poweroff"
#define ELM_CMD_REBOOT   "/usr/bin/reboot"
#define ELM_CMD_XORG     "/usr/bin/Xorg"
#define ELM_CMD_XCOMPMGR "/usr/bin/xcompmgr"
#define ELM_CMD_XRDB     "/usr/bin/xrdb"
#define ELM_CMD_XMODMAP  "/usr/bin/xmodmap"

#define ELM_LOG  "/var/log/elm/elm.log"
#define ELM_XLOG "/var/log/elm/Xorg.log"

#endif /* ELM_DEF_H */
