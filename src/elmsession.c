/* *****************************************************************************
 * 
 * Name:    elmsession.c
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Construct a user session for the Extensible Login Manager.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "elmsession.h"
#include "elmauthenticate.h"
#include "elmio.h"
#include <stdlib.h>

/* Private functions */
static int elm_session_authenticate(void);
static int elm_session_login(void);
static int elm_session_logout(void);
static int elm_session_alloc(void);

/* Private globals */
static ElmSession *Session = NULL;

/* ************************************************************************** */
/* Create Extensible Login Manager base structure */
ElmSession * elm_new_session(ElmLoginInfo *info)
{
    /* Allocate user session object */
    int status;
    if ((status=elm_session_alloc()) != 0)
        exit(ELM_EXIT_SESSION_NEW);

    Session->authenticate = &elm_session_authenticate;
    Session->login        = &elm_session_login;
    Session->logout       = &elm_session_logout;
    Session->_info        = info;

    return Session;
}

/* ************************************************************************** */
/* Authenticate login credentials */
int elm_session_authenticate(void)
{
    if (Session == NULL) {
        elmprintf(LOG, "Unable to authenticate login credentials.");
        return -1;
    }

    char *username = Session->_info->username;
    char *password = Session->_info->password;
    elmprintf(LOG, "Authenticating credentials of '%s'." , username);

    return elm_authenticate(username, password);
}

/* ************************************************************************** */
/* Login to user session */
int elm_session_login(void)
{
    if (Session == NULL) {
        elmprintf(LOG, "Unable to login to user session.");
        return -1;
    }

    char *xsession = Session->_info->xsession;
    elmprintf(LOG, "Logging into session '%s'.", xsession);

    return elm_login(xsession, &Session->pid);
}

/* ************************************************************************** */
/* Logout of session */
int elm_session_logout(void)
{
    if (Session == NULL) {
        elmprintf(LOG, "Unable to logout of user session.");
        return -1;
    }

    char *username = Session->_info->username;
    elmprintf(LOG, "Logging out of user session for '%s'.", username);

    return elm_logout();
}

/* ************************************************************************** */
/* Allocate session object */
int elm_session_alloc(void)
{
    Session = calloc(1, sizeof(ElmSession));
    if (Session == NULL) {
        elmprintf(LOG, "Unable to initialize user session.");
        return 1;
    }

    return 0;
}
