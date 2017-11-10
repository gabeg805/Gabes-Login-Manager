/* *****************************************************************************
 * 
 * Name:    xsession.c
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Display button which allows a user to select which X Session to
 *              start after logging in.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "app/xsession.h"

/* Private functions */
static int      set_xsession_menu(GtkWidget **menu);
static char *** get_available_xsessions(void);

/* Private variables */
static const char      *Style   = "/etc/X11/elm/share/css/xsession.css";
static       GtkWidget *Xbutton = NULL;
static       GtkWidget *Xmenu   = NULL;

/* ************************************************************************** */
/* Create xsession menu button */
GtkWidget * new_xsession_widget(void)
{
    elmprintf(LOGINFO, "Displaying Xsession menu.");

    Xbutton = gtk_menu_button_new();
    Xmenu   = gtk_menu_new();

    set_xsession_menu(&Xmenu);
    gtk_button_set_relief(GTK_BUTTON(Xbutton), GTK_RELIEF_HALF);
    gtk_menu_button_set_popup(GTK_MENU_BUTTON(Xbutton), Xmenu);
    elm_gtk_set_widget_size(&Xbutton, 30, 30);
    elm_gtk_set_widget_style(&Xbutton, "XSession", Style);
    gtk_widget_show_all(Xmenu);
    gtk_widget_show_all(Xbutton);

    return Xbutton;
}

/* ************************************************************************** */
/* Set xsession information */
void set_xsession_info(GtkWidget *widget, gpointer data)
{
    ElmSessionInfoHelper  *helper = data;
    GtkMenuButton         *button = GTK_MENU_BUTTON(helper->widget);
    GtkMenu               *menu   = gtk_menu_button_get_popup(button);
    GtkMenuItem           *item   = GTK_MENU_ITEM(gtk_menu_get_active(menu));
    const gchar           *text   = gtk_widget_get_tooltip_text(GTK_WIDGET(item));
    size_t                 length = strlen(text)+1;

    printf("Info : %s~\n", text);

    memset(helper->data, 0, length);
    strncpy(helper->data, text, length);
}

/* ************************************************************************** */
/* Populate menu with xsession(s) on system */
int set_xsession_menu(GtkWidget **menu)
{
    char      ***xsessions = get_available_xsessions();
    GSList      *group     = NULL;
    GtkWidget   *menuitem  = NULL;
    size_t       index;

    if (!xsessions) {
        return -1;
    }

    /* Create the radio buttons for the window managers */
    for (index=0; xsessions[0][index] && xsessions[1][index]; index++)
    {
        menuitem = gtk_radio_menu_item_new_with_label(group, xsessions[0][index]);
        group    = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(menuitem));

        gtk_widget_set_tooltip_text(menuitem, xsessions[1][index]);
        gtk_menu_attach(GTK_MENU(*menu), menuitem, 0, 1, index, index+1);
        gtk_widget_show(menuitem);

        elm_free(&xsessions[0][index]);
        elm_free(&xsessions[1][index]);
    }

    /* Clear memory */
    elm_free(&xsessions[0]);
    elm_free(&xsessions[1]);
    elm_free(&xsessions);

    return 0;
}

/* ************************************************************************** */
/* Return all avaiable xsessions on the system */
char *** get_available_xsessions(void)
{
    /* Open directory for reading */
    const char    *dir     = "/usr/share/xsessions";
    DIR           *dhandle = opendir(dir);
    struct dirent *entry;

    if (!dhandle) {
        return NULL;
    }

    /* Allocate initial memory spaces for main pointer and its two columns */
    char   ***xsessions = NULL;
    char     *path      = NULL;
    char     *nameline  = NULL;
    char     *execline  = NULL;
    size_t    index     = 1;
    size_t    i;

    if (!elm_calloc(&xsessions, 2, sizeof *xsessions)) {
        elmprintf(LOGERRNO, "Unable to allocate xsessions array");
        return NULL;
    }
    else {
        xsessions[0] = NULL;
        xsessions[1] = NULL;
    }

    if (!elm_calloc(&xsessions[0], 1, sizeof *xsessions[0])) {
        elmprintf(LOGERRNO, "%s '%lu'",
                  "Unable to allocate xsessions array", 0);
        goto cleanup;
    }

    if (!elm_calloc(&xsessions[1], 1, sizeof *xsessions[0])) {
        elmprintf(LOGERRNO, "%s '%lu'",
                  "Unable to allocate xsessions array", 1);
        goto cleanup;
    }

    /* Iterate over files in directory */
    while ((entry=readdir(dhandle)))
    {
        /* Clear previously allocated memory */
        if (path) {
            elm_free(&path);
        }

        if (nameline) {
            elm_free(&nameline);
        }

        if (execline) {
            elm_free(&execline);
        }

        /* Check extension of file is correct */
        if ((entry->d_type != DT_REG) || (!strstr(entry->d_name, ".desktop"))) {
            continue;
        }

        /* Read file */
        path     = elm_sys_path("%s/%s", dir, entry->d_name);
        nameline = elm_sys_find_line(path, "Name=");
        execline = elm_sys_find_line(path, "Exec=");

        if (!nameline || !execline) {
            continue;
        }

        /* Copy string to array */
        if (!elm_sys_strcpy(&xsessions[0][index-1], &nameline[5])) {
            goto cleanup;
        }

        if (!elm_sys_strcpy(&xsessions[1][index-1], &execline[5])) {
            goto cleanup;
        }

        /* Resize allocated memory for next xsession */
        if (!elm_realloc(&xsessions[0], index+1, sizeof *xsessions[0])) {
            elmprintf(LOGERRNO, "Unable to reallocate xsessions array");
            goto cleanup;
        }

        if (!elm_realloc(&xsessions[1], index+1, sizeof *xsessions[0])) {
            elmprintf(LOGERRNO, "Unable to reallocate xsessions array");
            goto cleanup;
        }

        xsessions[0][index] = NULL;
        xsessions[1][index] = NULL;
        index++;
    }

    closedir(dhandle);

    return xsessions;

cleanup:
    if (path) {
        elm_free(&path);
    }

    if (nameline) {
        elm_free(&nameline);
    }

    if (execline) {
        elm_free(&execline);
    }

    for (i=0; i < (index-1); i++) {
        elm_free(&xsessions[0][i]);
        elm_free(&xsessions[1][i]);
    }

    if (xsessions[0]) {
        elm_free(&xsessions[0]);
    }
    if (xsessions[1]) {
        elm_free(&xsessions[1]);
    }

    elm_free(&xsessions);

    return NULL;
}
