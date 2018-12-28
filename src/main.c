#include "tageslosung.h"

Evas_Object *win = NULL;
static    Evas_Object *popup = NULL;
Evas_Object *ly = NULL;
// static    Evas_Object *popup;
int       switcher = 1;

char      *losungstext = NULL;
char      *losungsvers = NULL;
char      *lehrtext = NULL;
char      *lehrtextvers = NULL;
char      *date = NULL;
char      *translation = NULL;

static E_Gadget_Site_Orient gorient;
static E_Gadget_Site_Anchor ganchor;

//////////////////////////////// EET /////////////////////////////////

typedef struct {
        Eina_List   *configlist_eet;
} Note_List_Eet;


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
} My_Conf_Type;
   

static const char MY_CONF_FILE_ENTRY[] = "config";

static Eet_Data_Descriptor *_my_conf_descriptor;
static Eet_Data_Descriptor *_my_conf_sub_descriptor;

static void
_my_conf_descriptor_init(void)
{
    Eet_Data_Descriptor_Class eddc;
    EET_EINA_STREAM_DATA_DESCRIPTOR_CLASS_SET(&eddc, Note_List_Eet);
    _my_conf_descriptor = eet_data_descriptor_stream_new(&eddc);
   
    EET_EINA_STREAM_DATA_DESCRIPTOR_CLASS_SET(&eddc, My_Conf_Type);
    _my_conf_sub_descriptor = eet_data_descriptor_stream_new(&eddc);
   
    #define MY_CONF_ADD_BASIC(member, eet_type) \
        EET_DATA_DESCRIPTOR_ADD_BASIC             \
        (_my_conf_descriptor, Note_List_Eet, # member, member, eet_type)
		  
    #define MY_CONF_SUB_ADD_BASIC(member, eet_type) \
        EET_DATA_DESCRIPTOR_ADD_BASIC                 \
        (_my_conf_sub_descriptor, My_Conf_Type, # member, member, eet_type)
    
//     MY_CONF_SUB_ADD_BASIC(note_name, EET_T_STRING);
    MY_CONF_SUB_ADD_BASIC(id, EET_T_INT);
    MY_CONF_SUB_ADD_BASIC(font_size, EET_T_DOUBLE);
    MY_CONF_SUB_ADD_BASIC(switch_time, EET_T_DOUBLE);
    MY_CONF_SUB_ADD_BASIC(translation, EET_T_STRING);
    MY_CONF_SUB_ADD_BASIC(popup, EET_T_UCHAR);
    MY_CONF_SUB_ADD_BASIC(switcher, EET_T_UCHAR);
    MY_CONF_SUB_ADD_BASIC(online, EET_T_UCHAR);
    MY_CONF_SUB_ADD_BASIC(layout, EET_T_UCHAR);
	 MY_CONF_SUB_ADD_BASIC(r, EET_T_INT);
    MY_CONF_SUB_ADD_BASIC(g, EET_T_INT);
    MY_CONF_SUB_ADD_BASIC(b, EET_T_INT);
    MY_CONF_SUB_ADD_BASIC(a, EET_T_INT);

    // And add the sub descriptor as a linked list at 'subs' in the main struct
    EET_DATA_DESCRIPTOR_ADD_LIST
     (_my_conf_descriptor, Note_List_Eet, "configlist_eet", configlist_eet, _my_conf_sub_descriptor);

     
    #undef MY_CONF_ADD_BASIC     
    #undef MY_CONF_SUB_ADD_BASIC
}

//////////////////////////////// EET /////////////////////////////////




void
_read_eet()
{
    Eet_File *ef;
    
    Note_List_Eet *my_conf;
        
    eet_init();

   char buf[4096], buf2[512];

   snprintf(buf2, sizeof(buf2), "%s/tageslosung", efreet_config_home_get());
   ecore_file_mkpath(buf2);
   snprintf(buf, sizeof(buf), "%s/tageslosung_config.cfg", buf2);
	
    ef = eet_open(buf, EET_FILE_MODE_READ);
    if (!ef)
    {
//         printf("ERROR: could not open '%s' for read\n", home_file);
        return;
    }
    
    my_conf = eet_data_read(ef, _my_conf_descriptor, MY_CONF_FILE_ENTRY);
        
    configlist =  my_conf->configlist_eet;
//     dcolor_r = my_conf->dcolor_r;
//     dcolor_g = my_conf->dcolor_g;
//     dcolor_b = my_conf->dcolor_b;
//     dcolor_a = my_conf->dcolor_a;
//     tcolor_default = my_conf->tcolor_default;
  
    eet_close(ef);
    eet_shutdown();
}


void
_save_eet()
{
    Eet_File *ef;
    eet_init();
	 
   char buf[4096];
	 
   snprintf(buf, sizeof(buf), "%s/tageslosung/tageslosung_config.cfg", efreet_config_home_get());
   
	ef = eet_open(buf, EET_FILE_MODE_WRITE);
       
    if(!ef)
    {
        printf("ERROR\n");
//         fprintf(stderr, "ERROR: could not open '%s' for write\n", home_file);
//            return EINA_FALSE;   //TODO got elm_main -> END
    }else
    {

        Note_List_Eet *my_conf = calloc(1, sizeof(Note_List_Eet));

        if (!my_conf)
        {
            fprintf(stderr, "ERROR: could not calloc My_Conf_Type\n");
//                 return NULL;   //TODO got elm_main -> END
        }

		  my_conf->configlist_eet = configlist;
 
        eet_data_write(ef, _my_conf_descriptor, MY_CONF_FILE_ENTRY, my_conf, EINA_TRUE);
    }
    
    eet_close(ef);
    eet_shutdown();
	 
}
/*
static void
_my_conf_descriptor_shutdown(void)
{
    eet_data_descriptor_free(_my_conf_sub_descriptor);
    eet_data_descriptor_free(_my_conf_descriptor);
}*/

static void
update_anchor_orient(void *data, E_Gadget_Site_Orient orient, E_Gadget_Site_Anchor anchor, Evas_Object *obj)
{
// 	Evas_Object *ly = data;
	
	char buf[4096];
//    const char *s = "float";
   s = "float";
	
   if (anchor & E_GADGET_SITE_ANCHOR_LEFT)
     {
        if (anchor & E_GADGET_SITE_ANCHOR_TOP)
          {
             switch (orient)
               {
                case E_GADGET_SITE_ORIENT_HORIZONTAL:
                  s = "top_left";
                  break;
                case E_GADGET_SITE_ORIENT_VERTICAL:
                  s = "left_top";
                  break;
                case E_GADGET_SITE_ORIENT_NONE:
                  s = "left_top";
                  break;
               }
          }
        else if (anchor & E_GADGET_SITE_ANCHOR_BOTTOM)
          {
             switch (orient)
               {
                case E_GADGET_SITE_ORIENT_HORIZONTAL:
                  s = "bottom_left";
                  break;
                case E_GADGET_SITE_ORIENT_VERTICAL:
                  s = "left_bottom";
                  break;
                case E_GADGET_SITE_ORIENT_NONE:
                  s = "left_bottom";
                  break;
               }
          }
        else
		  {	
			   evas_object_size_hint_aspect_set(obj, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
				
				Evas_Object *edje_obj = elm_layout_edje_get(ly);
            snprintf(buf, sizeof(buf), "%s/themes/tageslosung.edj", PACKAGE_DATA_DIR);
				elm_layout_file_set(edje_obj, buf, "tageslosung2_small");
			   edje_object_signal_emit(edje_obj, "black", "");
	         edje_object_signal_emit(edje_obj, "text_white", "gadget");
            s = "left";
				orient_helper = s;
		  }
     }
   else if (anchor & E_GADGET_SITE_ANCHOR_RIGHT)
     {
        if (anchor & E_GADGET_SITE_ANCHOR_TOP)
          {
             switch (orient)
               {
                case E_GADGET_SITE_ORIENT_HORIZONTAL:
                  s = "top_right";
                  break;
                case E_GADGET_SITE_ORIENT_VERTICAL:
                  s = "right_top";
                  break;
                case E_GADGET_SITE_ORIENT_NONE:
                  s = "right_top";
                  break;
               }
          }
        else if (anchor & E_GADGET_SITE_ANCHOR_BOTTOM)
          {
             switch (orient)
               {
                case E_GADGET_SITE_ORIENT_HORIZONTAL:
                  s = "bottom_right";
                  break;
                case E_GADGET_SITE_ORIENT_VERTICAL:
                  s = "right_bottom";
                  break;
                case E_GADGET_SITE_ORIENT_NONE:
                  s = "right_bottom";
                  break;
               }
          }
        else
		  {
	         evas_object_size_hint_aspect_set(obj, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
				
// 				Evas_Object *edje_obj = elm_layout_edje_get(data);
            snprintf(buf, sizeof(buf), "%s/themes/tageslosung.edj", PACKAGE_DATA_DIR);
				elm_layout_file_set(ly, buf, "tageslosung2_small");
			   edje_object_signal_emit(ly, "white", "");
	         edje_object_signal_emit(ly, "text_white", "gadget");
				s = "right";
				orient_helper = s;
			}
     }
   else if (anchor & E_GADGET_SITE_ANCHOR_TOP)
     s = "top";
   else if (anchor & E_GADGET_SITE_ANCHOR_BOTTOM)
     s = "bottom";
   else
     {
        switch (orient)
          {
           case E_GADGET_SITE_ORIENT_HORIZONTAL:
             s = "horizontal";
             break;
           case E_GADGET_SITE_ORIENT_VERTICAL:
             s = "vertical";
             break;
           default: break;
          }
     }
   snprintf(buf, sizeof(buf), "e,state,orientation,%s", s);
	printf("ORIENTATION: %s\n", buf);
	
}


static 
Eina_Bool _gadget_exit(void *data, int type, void *event_data) 
{
	
	Eina_List *l;
	Config_Item *list_data;
	Ecore_Event_Signal_User *user = event_data;
	
	if ( user->number == 2) 
	{

   EINA_LIST_FOREACH(configlist, l, list_data)
   {
	   if(list_data->id == id_num)
		{
         configlist = eina_list_remove(configlist, list_data);
		}
   }
   printf("DEL ID\n");
	
	_save_eet();
		
	} 
		return EINA_TRUE;
}


static void
orient_change(void *data, Evas_Object *obj, void *event_info)
{
// 	Evas_Object *ly = data;
   gorient = (uintptr_t)event_info;
   update_anchor_orient(data, gorient, ganchor, obj);
}

static void
anchor_change(void *data, Evas_Object *obj, void *event_info)
{
// 	Evas_Object *ly = data;
   ganchor = (uintptr_t)event_info;
   update_anchor_orient(data, gorient, ganchor, obj);
}


static void
_mouse_in_online(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{ 
		edje_object_signal_emit(ly, "mouse_in_online_go", "e");
}

static void
_mouse_out_online(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
	   edje_object_signal_emit(ly, "mouse_out_online_go", "e");
}


void
open_bibelserver_config(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   char buf[PATH_MAX];
	char *vers = data;

   stringReplace("<Losungsvers>", "", vers);
	stringReplace("</Losungsvers>", "", vers);
	remove_space(vers);
	snprintf(buf, sizeof(buf), "http://www.bibleserver.com/text/%s/%s", ci_translation, vers);
	
   evas_object_smart_callback_call(win, "gadget_open_uri", buf);
	printf("ONLINE CONFIG: %s\n", buf);

}


static void
open_bibelserver(void *data, Evas_Object *obj, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   Evas_Object *win = data;
	char buf[PATH_MAX];
	char *losungsvers_new = losungsvers;
	char *lehrtextvers_new = lehrtextvers;
	
	if(ci_online == 0)
	{
		stringReplace("<Losungsvers>", "", losungsvers_new);
		stringReplace("</Losungsvers>", "", losungsvers_new);
		remove_space(losungsvers_new);
		
		stringReplace("<Lehrtextvers>", "", lehrtextvers_new);
		stringReplace("</Lehrtextvers>", "", lehrtextvers_new);
		remove_space(lehrtextvers_new);
      
		if(!strcmp(edje_object_part_state_get(obj, "lehrtext", NULL), "default"))
		   snprintf(buf, sizeof(buf), "http://www.bibleserver.com/text/%s/%s", ci_translation, lehrtextvers_new);
	   else
	      snprintf(buf, sizeof(buf), "http://www.bibleserver.com/text/%s/%s", ci_translation, losungsvers_new);
	
      evas_object_smart_callback_call(win, "gadget_open_uri", buf);
		printf("ONLINE: %s\n", buf);
	}
}

/*
static void
delete_popup_evas(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   if(popup)
     {
        evas_object_del(popup);
        popup = NULL;
        return;
     }
}*/



static void
delete_popup_edje(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   if(popup)
     {
        evas_object_del(popup);
        popup = NULL;
        return;
     }
}


static void
show_popup(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   Evas_Object *win = data;
	Evas_Object *box, *lbl;
   char buffer[PATH_MAX];
   char buffer1[PATH_MAX];
	
	if(ci_popup == 1)
		return;
	
   snprintf(buffer, sizeof(buffer), "%s<br>%s", losungstext, losungsvers);
   snprintf(buffer1, sizeof(buffer1), "%s<br>%s", lehrtext, lehrtextvers);
	
   popup = elm_win_add(win, "Popup",  ELM_WIN_POPUP_MENU);
   elm_win_alpha_set(popup, 1);
	
   box = elm_box_add(popup);
   elm_box_horizontal_set(box, EINA_FALSE);
   elm_win_resize_object_add(popup, box);
   evas_object_show(box);
 
   lbl = elm_label_add(box);
	elm_label_line_wrap_set(lbl, ELM_WRAP_WORD);
   elm_label_wrap_width_set(lbl, ELM_SCALE_SIZE(400));
   elm_object_text_set(lbl, buffer);
   elm_box_pack_end(box, lbl);
   evas_object_show(lbl);
	
	lbl = elm_label_add(box);
	elm_label_line_wrap_set(lbl, ELM_WRAP_WORD);
   elm_label_wrap_width_set(lbl, ELM_SCALE_SIZE(400));
   elm_object_text_set(lbl, buffer1);
   elm_box_pack_end(box, lbl);
   evas_object_show(lbl);

   evas_object_size_hint_align_set(box, 0.5, 0.5);
	
   evas_object_show(popup);
}


void
_set_text_wheel(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
	
	Evas_Object *edje_obj = elm_layout_edje_get(data);
	_set_text(edje_obj, NULL, NULL, NULL);
}

void
_set_text(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{

   if(strcmp(edje_object_part_state_get(data, "losungstext", NULL), "default"))
	{
	   printf("activ Losung\n");
	   edje_object_signal_emit(data, "passive_lehrtext", "");
   }
	else
   {
		printf("activ Lehrtext\n");
	   edje_object_signal_emit(data, "passive_losung", "");
   }
	printf("set text\n");
}


static Eina_Bool
_set_text_timer(void *data)
{
	_set_text(data, NULL, NULL, NULL);

   return ECORE_CALLBACK_RENEW;
}


static Eina_Bool
_day_change(void *data)
{
	_xml_parse(data);
	_set_text(data, NULL, NULL, NULL);

   return ECORE_CALLBACK_CANCEL;
}

static void
_get_date()
{
	time_t t;
	struct tm * ts;
	t = time(NULL);
	ts = localtime(&t);
// 	printf("%d\n",ts->tm_year+1900);
	snprintf(year, sizeof(year), "%d", ts->tm_year+1900);
	snprintf(nextyear, sizeof(nextyear), "%d", ts->tm_year+1900+1);
	
	snprintf(today, sizeof(today), "%02d-%02d-%02d", ts->tm_year + 1900, ts->tm_mon +1 , ts->tm_mday);
	
}

static void
_check_day(void *data)
{
    time_t t1, t2;
    struct tm date2;

    time( &t1); // aktuelles Datum in Sekunden 

    // Konvertiere Sekunden nach struct tm 
    date2 = *localtime( &t1);
    // Überschreibe Tag und Monat 
	 date2.tm_sec = 59;
	 date2.tm_min = 59;
    date2.tm_hour = 23;

    // Konvertiere wieder von struct tm in Sekunden zurück 
    t2 = mktime( &date2);
	printf("Sek. bis morgen: %f", difftime(t2, t1));
	
	daytimer = ecore_timer_add(difftime(t2, t1), _day_change, data);
	
}

void
delete_timer()
{
   if(timer)
	{
      ecore_timer_del(timer);
		timer = NULL;
		printf("DELT TIMER 1\n");
	}
}


void
change_timer(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
// 	Evas_Object *ly = data;
   if(timer)
	{
      ecore_timer_del(timer);
		timer = NULL;
		printf("DELT TIMER 2\n");
	}

	if(ci_switch != 1)
	{
	   timer = ecore_timer_add(ci_switch_time * 60, _set_text_timer, data);
		
		printf("TIMER 2\n");
		
		printf("DELT TIMER Time %1.0f \n", ci_switch_time);
	}
}


void stringReplace(char *search, char *replace, char *string)
{
   while(strstr(string, search) != NULL)
   {
	   char *tempString, *searchStart;
	   int len=0;
	   // Speicher reservieren
	   tempString = (char*) malloc(strlen(string)+1204 * sizeof(char));
	
	   searchStart = strstr(string, search);

		// temporaere Kopie anlegen
   	strcpy(tempString, string);

	   // ersten Abschnitt in String setzen
	   len = searchStart - string;
	   string[len] = '\0';

	   // zweiten Abschnitt anhaengen
	   strcat(string, replace);

	   // dritten Abschnitt anhaengen
	   len += strlen(search);
	   strcat(string, (char*)tempString+len);

	   // Speicher freigeben
	   free(tempString);
  }
	return;
}

void remove_space(char *src)
{
   char *dst;

    /* find position of first non-space character */
   for (dst=src; *src == ' '; src++) {;}

    /* nothing to do */
    if (dst==src) return;

    /* K&R style strcpy() */
    while ((*dst++ = *src++)) {;}

   return;
}

int
_xml_parse(void *data)
{
	#define BUF 512
//    char buf_time[255];
//    char info[255];
   char puffer[BUF];
   char buffer[PATH_MAX];
   int d = 0;
   int x = 0;
	char buf2[4096];
		
	Losungen *losungen_new;
	
	// get menu state
	Evas_Object *edje_obj = elm_layout_edje_get(data);
	

   snprintf(buf2, sizeof(buf2), "%s/tageslosung/Losungen Free %s.xml", efreet_config_home_get(), year);
	
   FILE *fp;
   // Datei oeffnen
   fp = fopen(buf2, "r");

   if(fp == NULL) 
   {
        edje_object_part_text_set(edje_obj, "losungstext", "Losungsdata not found. Please go to https://www.losungen.de/download/ and download the xml file and put it as ~/.config/tageslosung/losungen.xml in your home<br> please set the 'end of file' to unix");
        edje_object_part_text_set(edje_obj, "lehrtext", "Losungsdata not found. Please go to https://www.losungen.de/download/ and download the xml file and put it as ~/.config/tageslosung/losungen.xml in your home<br> please set the 'end of file' to unix");
		  
		  snprintf(buffer, sizeof(buffer), "<Losungstext>Losungsdata not found. Please go to https://www.losungen.de/download/ and download the xml file and put it as ~/.config/tageslosung/losungen.xml in your home<br> please set the 'end of file' to unix</Losungstext>");
		  
		  losungstext = strdup(buffer);
        
		  return 0;
   }

   while( fgets(puffer, BUF, fp) != NULL ) 
   {

       if(strstr(puffer, "Datum") != 0)
       {
         d = 1;
			x = 1;
			losungen_new = calloc(1, sizeof(Losungen));
       }
       if(d == 1 && x != 0)
       {
			switch(x) {
                case 1: date = strdup(puffer);
								stringReplace("<Datum>", "", date);
								stringReplace("</Datum>\n", "", date);
								stringReplace("T00:00:00", "", date);
								remove_space(date);
								losungen_new->date = eina_stringshare_add(date);
// 								printf("%s", date);
								x++;
                    break;
                case 4: losungstext = strdup(puffer);
								stringReplace("<Losungstext>", "", losungstext);
								stringReplace("</Losungstext>\n", "", losungstext);
								remove_space(losungstext);
								losungen_new->losungstext = eina_stringshare_add(losungstext);
								x++;
                    break;
                case 5: losungsvers = strdup(puffer);
								stringReplace("<Losungsvers>", "", losungsvers);
								stringReplace("</Losungsvers>\n", "", losungsvers);
								remove_space(losungsvers);
								losungen_new->losungsvers = eina_stringshare_add(losungsvers);
								x++;
                    break;
                case 6: lehrtext = strdup(puffer);
								stringReplace("<Lehrtext>", "", lehrtext);
								stringReplace("</Lehrtext>\n", "", lehrtext);
								remove_space(lehrtext);
								losungen_new->lehrtext = eina_stringshare_add(lehrtext);
								x++;
                    break;
                case 7: lehrtextvers = strdup(puffer);
								stringReplace("<Lehrtextvers>", "", lehrtextvers);
								stringReplace("</Lehrtextvers>\n", "", lehrtextvers);
								remove_space(lehrtextvers);
								losungen_new->lehrtextvers = eina_stringshare_add(lehrtextvers);
								
								losungen = eina_list_append(losungen, losungen_new);
								x = 0;
								d = 0;
                    break;
                 default: 
								x++;
                    break;
                    }
       }
   }

   if(eina_list_count(losungen) == 0)
   {
        edje_object_part_text_set(edje_obj, "losungstext", "Fehler beim auswerten der xml Datei"); 
        edje_object_part_text_set(edje_obj, "lehrtext", "Fehler beim auswerten der xml Datei");
   }else
	{
		
		Losungen *list_data;
		Eina_List *l;
      EINA_LIST_FOREACH(losungen, l, list_data)
      {
// 		printf("DATUM LISTE: '%s'\n", list_data->date);
            if(strcmp(list_data->date, today) == 0)
				{
					snprintf(buffer, sizeof(buffer), "<Losungstext>%s</Losungstext>", list_data->losungstext);
				   losungstext = strdup(buffer);
// 					strcpy(losungstext, buffer);
					edje_object_part_text_set(edje_obj, "losungstext", buffer);
					
					snprintf(buffer, sizeof(buffer), "<Losungsvers>%s</Losungsvers>", list_data->losungsvers);
					losungsvers = strdup(buffer);
// 					strcpy(losungsvers, buffer);
					edje_object_part_text_set(edje_obj, "losungsvers", buffer);
					
					snprintf(buffer, sizeof(buffer), "<Lehrtext>%s</Lehrtext>", list_data->lehrtext);
					lehrtext = strdup(buffer);
// 					strcpy(lehrtext, buffer);
					edje_object_part_text_set(edje_obj, "lehrtext", buffer);
					
					snprintf(buffer, sizeof(buffer), "<Lehrtextvers>%s</Lehrtextvers>", list_data->lehrtextvers);
					lehrtextvers = strdup(buffer);
// 					strcpy(lehrtextvers, buffer);
					edje_object_part_text_set(edje_obj, "lehrtextvers", buffer);
				}
        }

		
	}

	fclose(fp);

   return 1;
}


void
set_color(Evas_Object *ly)
{
	edje_object_color_class_set(ly, "colorclass", /* class name   */
                               ci_r, ci_g, ci_b, ci_a,  /* Object color */
                               255, 255, 255, 255,   /* Text outline */
                               39, 90, 187, 255);  /* Text shadow  */
	printf("SET COLOR: %i %i %i %i, %1.0f\n", ci_r,ci_g,ci_b,ci_a, ci_font_size);
	
   char buf1[PATH_MAX];
   char buf2[PATH_MAX];

	unsigned int rgba = createHEX(ci_r, ci_g, ci_b, ci_a);

   snprintf(buf1, sizeof(buf1), "DEFAULT='font=Sans:style=Regular color=#%06x font_size=%1.0f'",  rgba, ci_font_size-3);
   snprintf(buf2, sizeof(buf2), "DEFAULT='font=Sans:style=Regular color=#%06x font_size=%1.0f'",  rgba, ci_font_size);

	edje_object_part_text_style_user_push(ly,"losungstext", buf2);
	edje_object_part_text_style_user_push(ly,"lehrtext", buf2);
	
	edje_object_part_text_style_user_push(ly,"losungsvers", buf1);
	edje_object_part_text_style_user_push(ly,"lehrtextvers", buf1);
	
	
		printf("BUF STYLE: %s\n", buf2);
}


int elm_main(int argc, char *argv[])
{
   char buf[PATH_MAX];
//    char buf2[PATH_MAX];
//    int gadget = 0;
   char buf1[16];
	
	Config_Item *config;
	config = calloc(1, sizeof(Config_Item));
		
		
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
   if (getenv("E_GADGET_ID"))
     {
//         gadget = 1;
        snprintf(buf1, sizeof(buf1), "%s", getenv("E_GADGET_ID"));
        id_num = atoi(buf1);
     }

    _my_conf_descriptor_init();
   _read_eet();
   //new window
   win = elm_win_add(NULL, "tageslosung", ELM_WIN_BASIC);
   elm_win_title_set(win, "Tageslosung");
   elm_win_autodel_set(win, EINA_TRUE);
   elm_win_alpha_set(win, EINA_TRUE);
	
	

	

	evas_object_size_hint_aspect_set(win, EVAS_ASPECT_CONTROL_BOTH, 10, 1);
	
   // LAYOUT CREATE START// 
   ly = elm_layout_add(win);		  
   snprintf(buf, sizeof(buf), "%s/themes/tageslosung.edj", PACKAGE_DATA_DIR);
	evas_object_size_hint_weight_set(ly, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	

   elm_win_resize_object_add(win, ly);
   evas_object_show(ly);
    // LAYOUT CREATE END// 

   evas_object_data_set(win, "config", config);
// 	evas_object_resize(win, 300, 30);
   evas_object_show(win);
	elm_layout_file_set(ly, buf, "tageslosung2");
   edje_object_signal_callback_add(ly, "online", "online", open_bibelserver, win);
   edje_object_signal_callback_add(ly, "settings", "settings", _settings_2, win);
   edje_object_signal_callback_add(ly, "show_popup", "show_popup", show_popup, win);
   edje_object_signal_callback_add(ly, "delete_popup", "delete_popup", delete_popup_edje, win);
	edje_object_signal_callback_add(ly, "mouse_in_online_go", "mouse_in_online_go", _mouse_in_online, NULL);
   edje_object_signal_callback_add(ly, "mouse_out_online_go", "mouse_out_online_go", _mouse_out_online, NULL);
   edje_object_signal_callback_add(ly, "switch_wheel", "switch_wheel", _set_text_wheel, ly);
	
	Evas_Object *edje_obj = elm_layout_edje_get(ly);
	
	evas_object_smart_callback_add(win, "gadget_site_orient", orient_change, ly);
   evas_object_smart_callback_add(win, "gadget_site_anchor", anchor_change, ly);
   evas_object_smart_callback_add(win, "gadget_configure", _settings_1, edje_obj);
//    evas_object_smart_callback_add(win, "gadget_removed", _delete_id, NULL);
	ecore_event_handler_add(ECORE_EVENT_SIGNAL_USER, _gadget_exit, NULL);
		
	_get_date();
	
	if(eina_list_count(losungen) == 0)
	_xml_parse(ly);
	
	
	_check_day(ly);
	_config_load(ly);							// load config data from eet to tmp vars
	
// 				Evas_Object *edje_obj = elm_layout_edje_get(ly);
	set_color(edje_obj);
	
	_set_text(ly, NULL, NULL, NULL);
/*	
   if(ci_theme == 0)
   {
	   edje_object_signal_emit(ly, "white", "");
		snprintf(buf2, sizeof(buf2), "DEFAULT='font=Sans:style=Regular color=#ffffff font_size=%1.0f'", ci_font_size);
		edje_object_part_text_style_user_push(ly,"lehrtext", buf2);
		edje_object_part_text_style_user_push(ly,"losungstext", buf2);
// 		printf("1 %s\n", buf2);
	}else
	{
		edje_object_signal_emit(ly, "black", "");
		snprintf(buf2, sizeof(buf2), "DEFAULT='font=Sans:style=Regular color=#000000 font_size=%1.0f'", ci_font_size);
		edje_object_part_text_style_user_push(ly,"lehrtext", buf2);
		edje_object_part_text_style_user_push(ly,"losungstext", buf2);
// 		printf("1 %s\n", buf2);
	}*/

	if(!ci_switch_time || ci_switch_time == 0)
		timer = ecore_timer_add(5 * 60, _set_text_timer, ly);
	else
		timer = ecore_timer_add(ci_switch_time * 60, _set_text_timer, ly);
	
	_save_eet();
	
  //run app RUN!
  elm_run();

  //shutdown!   
   if(timer)
	{
      ecore_timer_del(timer);
		timer = NULL;
		printf("DELT TIMER 3\n");
	}
//         _my_conf_descriptor_shutdown();
  return 0;
}

ELM_MAIN();
