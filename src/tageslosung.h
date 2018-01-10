#ifndef TAGESLOSUNG_H
#define TAGESLOSUNG_H

#endif
#include "config.h"

#include <Ecore_Con.h>
#include <Elementary.h>

#include <e_gadget_types.h>

#define E_WEIGHT evas_object_size_hint_weight_set
#define E_ALIGN  evas_object_size_hint_align_set
#define E_EXPAND(X) E_WEIGHT((X), EVAS_HINT_EXPAND, EVAS_HINT_EXPAND)
#define E_FILL(X)   E_ALIGN((X), EVAS_HINT_FILL, EVAS_HINT_FILL)

void          _settings_1(void *data, Evas_Object *obj, void *event_info EINA_UNUSED);
void          _settings_2(void *data, Evas_Object *obj, const char *emission EINA_UNUSED, const char *source EINA_UNUSED);
void          _settings(void *data, Evas_Object *obj, void *event_info EINA_UNUSED);
void    		  change_timer(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
void          open_bibelserver_config(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED);
void			  delete_timer();
void 			  stringReplace(char *search, char *replace, char *string);
void          remove_space(char *src);
void          _sl_font_changed(void *data, Evas_Object *obj, void *event_info EINA_UNUSED);
void          _set_text(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED);
int           _xml_parse(void *data);
void          set_color(Evas_Object *ly);
void          _read_eet();
void          _save_eet();

unsigned int  createHEX(int r, int g, int b, int a);


void   _config_load();

char      *losungstext;
char      *losungsvers;
char      *lehrtext;
char      *lehrtextvers;
char      *date;
char      *translation;

char 		  *s;
char      *orient_helper;


static    Ecore_Timer *timer = NULL;
// static    Ecore_Timer *daytimer = NULL;

int        id_num;

Evas_Object *win;
Evas_Object *ly;

int         ci_id;
double      ci_font_size;
double      ci_switch_time;
const char *ci_translation;
Eina_Bool   ci_popup;
Eina_Bool   ci_switch;
Eina_Bool   ci_online;
// Eina_Bool   ci_theme;
Eina_Bool   ci_layout;
int         ci_r;
int         ci_g;
int         ci_b;
int         ci_a;


Eina_List *losungen;
Eina_List *configlist;

typedef struct {
        const char *date;
        const char *losungstext;
        const char *losungsvers;
        const char *lehrtext;
        const char *lehrtextvers;
} Losungen;

typedef struct {
        int         id;
        double      font_size;
		  double      switch_time;
        const char *translation;
		  Eina_Bool   popup;
		  Eina_Bool   switcher;
		  Eina_Bool   online;
// 		  Eina_Bool   theme;
		  Eina_Bool   layout;
		  int         r;
	     int         g;
        int         b;
        int         a;
} Config_Item;

