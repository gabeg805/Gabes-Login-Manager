// 
// Created By: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// Name:
// 
//     Clock.c
// 
// 
// Syntax: 
// 
//     ./Clock
// 
// 
// Purpose:
// 
//     Display a clock that updates every second.
// 
// 
// Keywords:
// 
//     Unknown
// 
// 
// Functions:
// 
//     init_clock_root - Initialize the root window with all its objects
//     set_clock_color - Set color scheme for root window
//     set_clock_label - Set the clock label font and text size
//     clock_update    - Refresh the current clock label
//     main            - Display the clock
// 
// 
// File Structure:
// 
//     * Includes and Declares
//     * Initialization
//     * Set Color Scheme For Root Window
//     * Get Current Time
//     * Update the Clock
//     * Display the Clock
// 
// 
// Modification History:
// 	
//     gabeg Aug 02 2014 <> created
// 
// **********************************************************************************


// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Clock.h"
#include "../hdr/Transparency.h"

#include <gtk/gtk.h>
#include <time.h>

#define   DATE_XPOS     0
#define   DATE_YPOS     650
#define   DATE_WIDTH    400
#define   DATE_HEIGHT   50
#define   DATE_FONT     "Inconsolata"
#define   DATE_FSIZE    25*1024
#define   DATE_FMT      "%A, %B %-d"

#define   TIME_XPOS     0
#define   TIME_YPOS     575
#define   TIME_WIDTH    400
#define   TIME_HEIGHT   75
#define   TIME_FONT     "Inconsolata"
#define   TIME_FSIZE    45*1024
#define   TIME_FMT      "%-I:%M %p"

#define   REFRESH_TIME   30

// Declares
void init_date_clock_root(GtkWidget *window, GtkWidget *clock);
void init_time_clock_root(GtkWidget *window, GtkWidget *clock);
void set_clock_color(GtkWidget *window, GtkWidget *clock);
void set_clock_label(GtkWidget *clock, char *fmt, const char *font, int fsize);
gboolean date_clock_update(gpointer data);
gboolean time_clock_update(gpointer data);



// //////////////////////////
// ///// INITIALIZATION ///// 
// //////////////////////////

// Initialize the root window with all its objects
void init_date_clock_root(GtkWidget *window, GtkWidget *clock) {
    
    // Set window attributes
    gtk_window_set_title(GTK_WINDOW(window), "System Date Clock");
    gtk_window_move(GTK_WINDOW(window), DATE_XPOS, DATE_YPOS);
    gtk_window_set_default_size(GTK_WINDOW(window), DATE_WIDTH, DATE_HEIGHT);
        
    // Set clock attributes
    set_clock_color(window, clock);
    set_clock_label(clock, DATE_FMT, DATE_FONT, DATE_FSIZE);
    
    // Add the clock to the root window 
    gtk_container_add(GTK_CONTAINER(window), clock);
    g_timeout_add_seconds(REFRESH_TIME, date_clock_update, clock);
    
    // Enable transparency
    enable_transparency(window);
    
    // GTK signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}



// Initialize the root window with all its objects
void init_time_clock_root(GtkWidget *window, GtkWidget *clock) {
    
    // Set window attributes
    gtk_window_set_title(GTK_WINDOW(window), "System Time Clock");
    gtk_window_move(GTK_WINDOW(window), TIME_XPOS, TIME_YPOS);
    gtk_window_set_default_size(GTK_WINDOW(window), TIME_WIDTH, TIME_HEIGHT);
        
    // Set clock attributes
    set_clock_color(window, clock);
    set_clock_label(clock, TIME_FMT, TIME_FONT, TIME_FSIZE);
    
    // Add the clock to the root window 
    gtk_container_add(GTK_CONTAINER(window), clock);
    g_timeout_add_seconds(REFRESH_TIME, time_clock_update, clock);
    
    // Enable transparency
    enable_transparency(window);
    
    // GTK signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}



// ////////////////////////////////////////////
// ///// SET COLOR SCHEME FOR ROOT WINDOW /////
// ////////////////////////////////////////////

// Set color scheme for root window
void set_clock_color(GtkWidget *window, GtkWidget *clock) {
    
    // Define the color scheme
    const GdkRGBA bg_window = {0, 0, 0, 0};
    const GdkRGBA fg_window = {0, 0, 0, 0};
    const GdkRGBA bg_clock = {0, 0, 0, 0};
    const GdkRGBA fg_clock = {1, 1, 1, 1};
    
    // Set the color scheme
    gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &bg_window);
    gtk_widget_override_background_color(clock, GTK_STATE_FLAG_NORMAL, &bg_clock);
    gtk_widget_override_color(window, GTK_STATE_FLAG_NORMAL, &fg_window);
    gtk_widget_override_color(clock, GTK_STATE_FLAG_NORMAL, &fg_clock);    
}



// ////////////////////////////
// ///// SET CURRENT TIME /////
// ////////////////////////////

// Set the clock label font and text size
void set_clock_label(GtkWidget *clock, char *fmt, const char *font, int fsize) {

    /* Obtain current time as seconds elapsed since the Epoch. */
    time_t current_time = time(NULL);
    char time_string[50];
    struct tm *tmp;
    
    // Convert time
    tmp = localtime(&current_time);
    strftime(time_string, sizeof(time_string), fmt, tmp);
    
    
    // Define text attributes
    PangoAttrList *attrList = pango_attr_list_new();
    PangoAttribute *attrFont = pango_attr_family_new(font);
    PangoAttribute *attrSize = pango_attr_size_new(fsize);
    
    // Add attributes to the list (and increase the reference counter)
    attrList = pango_attr_list_ref(attrList);
    pango_attr_list_insert(attrList, attrSize); 
    pango_attr_list_insert(attrList, attrFont);

    
    // Set the label text and font        
    gtk_label_set_attributes(GTK_LABEL(clock), attrList);
    gtk_label_set_text(GTK_LABEL(clock), time_string);
}



// ////////////////////////////
// ///// UPDATE THE CLOCK /////
// ////////////////////////////

// Refresh the current clock label
gboolean date_clock_update(gpointer data) {
    GtkWidget *clock = (GtkWidget *) data;
    set_clock_label(clock, DATE_FMT, DATE_FONT, DATE_FSIZE);
    
    return TRUE;
}


// Refresh the current clock label
gboolean time_clock_update(gpointer data) {
    GtkWidget *clock = (GtkWidget *) data;
    set_clock_label(clock, TIME_FMT, TIME_FONT, TIME_FSIZE);
    
    return TRUE;
}



// /////////////////////////////
// ///// DISPLAY THE CLOCK /////
// /////////////////////////////

// Display the clock
/* int main(int argc, char *argv[]) { */
    
/*     // Initialize GTK toolkit */
/*     gtk_init(&argc, &argv); */
    
/*     // Define clock date  */
/*     GtkWidget *clock_date_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); */
/*     GtkWidget *clock_date = gtk_label_new(""); */
    
/*     // Define clock time  */
/*     GtkWidget *clock_time_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); */
/*     GtkWidget *clock_time = gtk_label_new(""); */
    
/*     // Initialize the root window and all its objects */
/*     init_date_clock_root(clock_date_window, clock_date); */
/*     init_time_clock_root(clock_time_window, clock_time); */
    
/*     // Display the clock date */
/*     gtk_widget_show(clock_date); */
/*     gtk_widget_show(clock_date_window); */

/*     // Display the clock time */
/*     gtk_widget_show(clock_time); */
/*     gtk_widget_show(clock_time_window); */
/*     g_timeout_add_seconds(10, clock_update, clock_time); */

/*     gtk_main(); */
    
/*     return 0; */
/* } */
