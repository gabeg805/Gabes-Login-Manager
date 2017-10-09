/* *****************************************************************************
 * 
 * Name:    credentials.c
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Create username and password widgets.
 *              
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "app/credentials.h"

/* Private functions */
static const gchar * get_entry_buffer_text(GtkWidget *widget, char **field);
static       int     set_entry_buffer(GtkWidget *widget, char *placeholder);

/* Private variables */
static       GtkWidget  *Username    = NULL;
static       GtkWidget  *Password    = NULL;
static const char       *Style       = "/etc/X11/elm/src/app/style/credentials.css";
static       int         EntryLength = 32;

/* ************************************************************************** */
/* Create username entry */
GtkWidget * new_username_widget(void)
{
    Username = gtk_entry_new();

    set_entry_buffer(Username, "Username");
    gtk_entry_set_activates_default(GTK_ENTRY(Username), TRUE);

    return Username;
}

/* ************************************************************************** */
/* Create password entry */
GtkWidget * new_password_widget(void)
{
    Password = gtk_entry_new();

    set_entry_buffer(Password, "Password");
    gtk_entry_set_visibility(GTK_ENTRY(Password), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password), '*');
    gtk_entry_set_activates_default(GTK_ENTRY(Password), TRUE);

    return Password;
}

/* ************************************************************************** */
/* Return username widget */
GtkWidget * get_username_widget(void)
{
    return Username;
}

/* ************************************************************************** */
/* Return password widget */
GtkWidget * get_password_widget(void)
{
    return Password;
}

/* ************************************************************************** */
/* Return username */
const char * get_username(void)
{
    const gchar *text = get_entry_buffer_text(Username, NULL);
    printf("Username: %s~\n", text);
    return text;
}

/* ************************************************************************** */
/* Return password */
const char * get_password(void)
{
    const gchar *text = get_entry_buffer_text(Password, NULL);
    printf("Password: %s~\n", text);
    return text;
}

/* ************************************************************************** */
/* Get entry box text */
const gchar * get_entry_buffer_text(GtkWidget *widget, char **field)
{
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
    const gchar    *text   = gtk_entry_buffer_get_text(buffer);

    set_entry_buffer(widget, NULL);

    return text;
}

/* ************************************************************************** */
/* Set entry box text buffer */
int set_entry_buffer(GtkWidget *widget, char *placeholder)
{
    GtkEntryBuffer *buffer = gtk_entry_buffer_new(0, -1);

    gtk_entry_buffer_set_max_length(buffer, EntryLength);
    gtk_entry_set_buffer(GTK_ENTRY(widget), buffer);
    if (placeholder != NULL)
        gtk_entry_set_placeholder_text(GTK_ENTRY(widget), placeholder);

    return 0;
}
