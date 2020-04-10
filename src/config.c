#include "tageslosung.h"

Evas_Object *lbl1, *lbl1_1, *lbl2, *lbl2_1;



void
_config_load(void *data)
{
//    char buf[PATH_MAX];
   int found = 0;
// 	Evas_Object *edje_obj = elm_layout_edje_get(data);
	Eina_List *l;
	Config_Item *list_data;

   printf("LIST COUNT %i\n", eina_list_count(configlist));

   EINA_LIST_FOREACH(configlist, l, list_data)
   {
	   if(list_data->id == id_num)
		{				
		   ci_font_size = list_data->font_size;
		   ci_switch_time = list_data->switch_time;
			ci_translation = eina_stringshare_add(list_data->translation);
			ci_popup = list_data->popup;
			ci_switch = list_data->switcher;
			ci_online = list_data->online;
// 			ci_theme = list_data->theme;
			ci_layout = list_data->layout;
			ci_r = list_data->r;
			ci_g = list_data->g;
			ci_b = list_data->b;
			ci_a = list_data->a;
			found = 1;
         printf("FOUND = 1\n");
		}
   }

   if(found == 0)
	{
      printf("FOUND = 0");
      ci_font_size = 10.0;
		ci_switch_time = 20.0;
		ci_translation = eina_stringshare_add("LUT");
		ci_popup = 0;
		ci_switch = 0;
		ci_online = 0;
// 		ci_theme = 0;
		ci_layout = 0;
		ci_r = 255;
		ci_g = 255;
		ci_b = 255;
		ci_a = 255;
	}
}


static void
_config_save(void *data, Evas *e EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Eina_List *l;
	Config_Item *list_data;
	Config_Item *list_data1;
	list_data1 = calloc(1, sizeof(Config_Item));
	int found = 0;
	
	printf("SAVE\n");
		
	Evas_Object *tb = data;
   Evas_Object *check_popup = evas_object_data_get(tb, "check_popup");
   Evas_Object *check_online = evas_object_data_get(tb, "check_online");
   Evas_Object *check_switch = evas_object_data_get(tb, "check_switch");
   Evas_Object *check_layout = evas_object_data_get(tb, "check_layout");
//    Evas_Object *hoversel = evas_object_data_get(tb, "hoversel");
   Evas_Object *sl_switch_time = evas_object_data_get(tb, "sl_switch_time");
   Evas_Object *ly = evas_object_data_get(tb, "ly");
   Evas_Object *sl_font = evas_object_data_get(tb, "sl_font");
//    Evas_Object *tg_theme = evas_object_data_get(tb, "tg_theme");	
	
	if(ci_switch == 1)
		delete_timer();
		
	
   EINA_LIST_FOREACH(configlist, l, list_data)
   {
	   if(list_data->id == id_num)
		{
		   printf("ID LIST %i\n", list_data->id);
			list_data->font_size = elm_slider_value_get(sl_font);
			list_data->translation = eina_stringshare_add(ci_translation);
			list_data->switcher = elm_check_state_get(check_switch);
			list_data->popup = elm_check_state_get(check_popup);
			list_data->layout = elm_check_state_get(check_layout);
			list_data->online = elm_check_state_get(check_online);
			list_data->switch_time = elm_slider_value_get(sl_switch_time);
			list_data->r = ci_r;
			list_data->g = ci_g;
			list_data->b = ci_b;
			list_data->a = ci_a;
			found = 1;
			}
   }
		  
	if(found == 0)
	{
		list_data1->id = id_num;
		list_data1->popup = elm_check_state_get(check_popup);
		list_data1->online = elm_check_state_get(check_online);
		list_data1->switcher = elm_check_state_get(check_switch);
		list_data1->layout = elm_check_state_get(check_layout);
		list_data1->translation = eina_stringshare_add(ci_translation);
		list_data1->switch_time = elm_slider_value_get(sl_switch_time);
		list_data1->font_size = elm_slider_value_get(sl_font);
		list_data1->r = ci_r;
		list_data1->g = ci_g;
		list_data1->b = ci_b;
		list_data1->a = ci_a;

						
		configlist = eina_list_append(configlist, list_data1);
	}
	
   ci_popup = elm_check_state_get(check_popup);
	ci_switch = elm_check_state_get(check_switch);
	ci_online = elm_check_state_get(check_online);
	ci_layout = elm_check_state_get(check_layout);
	ci_switch_time = elm_slider_value_get(sl_switch_time);
	ci_font_size = elm_slider_value_get(sl_font);
// 	ci_theme = elm_check_state_get(tg_theme);
//    ci_translation = elm_object_text_get(hoversel);
					
	printf("INTERVALL SAVE: %1.0f\n", ci_switch_time);
   printf("FONT SIZE: %1.0f\n", ci_font_size);
	
	change_timer(ly, NULL, NULL);
	
	_save_eet();
}

void
_print_cal_info(Evas_Object *cal, Evas_Object *en)
{
   char info[1024];
   struct tm stm;

   elm_calendar_selected_time_get(cal, &stm);

		snprintf(info, sizeof(info), "%02d-%02d-%02d", stm.tm_year + 1900, stm.tm_mon + 1, stm.tm_mday);
		
		Eina_List *l;
		Losungen *list_data;
      EINA_LIST_FOREACH(losungen, l, list_data)
      {
            if(strcmp(list_data->date, info) == 0)
				{
						elm_object_text_set(lbl1, list_data->losungstext);
						elm_object_text_set(lbl1_1, list_data->losungsvers);
						elm_object_text_set(lbl2, list_data->lehrtext);
						elm_object_text_set(lbl2_1, list_data->lehrtextvers);
				}
        }	
}

static void
_print_cal_info_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   _print_cal_info(obj, data);
}


unsigned int createHEX(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + (a & 0xff);
}


static void
_colorselector_changed_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{	
	Evas_Object *tb = data;
   Evas_Object *ic = evas_object_data_get(tb, "ic");

   elm_colorselector_color_get(obj, &ci_r, &ci_g, &ci_b, &ci_a);
	
	evas_object_color_set(ic, ci_r, ci_g, ci_b, ci_a);
	
	set_color();
}

void
_sl_font_changed(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	ci_font_size = elm_slider_value_get(obj);
   set_color();
}


static void
_check_switch_changed(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	Evas_Object *sl = data;
   if(!elm_check_state_get(obj))
   {
	   elm_object_disabled_set(sl, EINA_FALSE);
   }else
	{		
	 elm_object_disabled_set(sl, EINA_TRUE);
	}
}

static void
_check_layout_changed(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	char buf1[4096];
	
	snprintf(buf1, sizeof(buf1), "%s/themes/tageslosung.edj", PACKAGE_DATA_DIR);
   
	if(elm_check_state_get(obj))
   {		
//       evas_object_size_hint_aspect_set(win, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
		elm_layout_file_set(ly, buf1, "tageslosung2_small");
		printf("check if\n");
   }else
	{		
//       evas_object_size_hint_aspect_set(win, EVAS_ASPECT_CONTROL_BOTH, 10, 1);
		elm_layout_file_set(ly, buf1, "tageslosung2");
		printf("check else\n");
	}
	
	set_color();
}

/*
static void
_check_bibelserver_changed(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	Evas_Object *hoversel = data;
   if(!elm_check_state_get(obj))
   {		
	   elm_object_disabled_set(hoversel, EINA_FALSE);
   }else
	{		
	 elm_object_disabled_set(hoversel, EINA_TRUE);
	}
}*/


static void
_hoversel_selected_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	ci_translation = eina_stringshare_add((char*)data);
	printf("HOVERSEL: %s\n", ci_translation);
}

static void
_popup_del(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_data EINA_UNUSED)
{
   evas_object_del(obj);
}


void
_settings_1(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	Evas_Object *win = obj;
	Evas_Object *ly = data;
	
	_settings(win, ly, NULL);
}


void
_settings_2(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *win = data;
	Evas_Object *ly = obj;
	
	_settings(win, ly, NULL);
}


static void
_config_show_general(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *tb = data;
	
   Evas_Object *popup_frame = evas_object_data_get(tb, "popup_frame");
	Evas_Object *advanced_frame = evas_object_data_get(tb, "advanced_frame");
	Evas_Object *general_frame = evas_object_data_get(tb, "general_frame");
	Evas_Object *calendar_frame = evas_object_data_get(tb, "calendar_frame");
	Evas_Object *data_frame = evas_object_data_get(tb, "data_frame");
	Evas_Object *help_frame = evas_object_data_get(tb, "help_frame");

//    evas_object_hide();
   evas_object_hide(popup_frame);
   evas_object_hide(calendar_frame);
   evas_object_hide(help_frame);
   evas_object_hide(advanced_frame);
   evas_object_hide(data_frame);
   evas_object_show(general_frame);
	printf("SHOW FEED\n");
}


static void
_config_show_popup(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *tb = data;
	
   Evas_Object *popup_frame = evas_object_data_get(tb, "popup_frame");
	Evas_Object *advanced_frame = evas_object_data_get(tb, "advanced_frame");
	Evas_Object *general_frame = evas_object_data_get(tb, "general_frame");
	Evas_Object *calendar_frame = evas_object_data_get(tb, "calendar_frame");
	Evas_Object *data_frame = evas_object_data_get(tb, "data_frame");
	Evas_Object *help_frame = evas_object_data_get(tb, "help_frame");
//    evas_object_hide();
   evas_object_hide(general_frame);
   evas_object_hide(calendar_frame);
   evas_object_hide(help_frame);
   evas_object_hide(advanced_frame);
   evas_object_hide(data_frame);
   evas_object_show(popup_frame);
	printf("SHOW POPUP\n");
}


static void
_config_show_advanced(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *tb = data;
	
   Evas_Object *popup_frame = evas_object_data_get(tb, "popup_frame");
	Evas_Object *advanced_frame = evas_object_data_get(tb, "advanced_frame");
	Evas_Object *general_frame = evas_object_data_get(tb, "general_frame");
	Evas_Object *calendar_frame = evas_object_data_get(tb, "calendar_frame");
	Evas_Object *data_frame = evas_object_data_get(tb, "data_frame");
	Evas_Object *help_frame = evas_object_data_get(tb, "help_frame");
//    evas_object_hide();
   evas_object_hide(general_frame);
   evas_object_hide(calendar_frame);
   evas_object_hide(help_frame);
   evas_object_hide(popup_frame);
   evas_object_hide(data_frame);
   evas_object_show(advanced_frame);
	printf("SHOW POPUP\n");
}


static void
_config_show_calendar(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *tb = data;
	
   Evas_Object *popup_frame = evas_object_data_get(tb, "popup_frame");
	Evas_Object *advanced_frame = evas_object_data_get(tb, "advanced_frame");
	Evas_Object *general_frame = evas_object_data_get(tb, "general_frame");
	Evas_Object *calendar_frame = evas_object_data_get(tb, "calendar_frame");
	Evas_Object *data_frame = evas_object_data_get(tb, "data_frame");
	Evas_Object *help_frame = evas_object_data_get(tb, "help_frame");
	
	
//    evas_object_hide();
   evas_object_hide(general_frame);
   evas_object_hide(popup_frame);
   evas_object_hide(help_frame);
   evas_object_hide(advanced_frame);
   evas_object_hide(data_frame);
   evas_object_show(calendar_frame);
	
	printf("SHOW ADVANCED\n");
}

static void
_config_show_data(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *tb = data;
	
   Evas_Object *popup_frame = evas_object_data_get(tb, "popup_frame");
	Evas_Object *advanced_frame = evas_object_data_get(tb, "advanced_frame");
	Evas_Object *general_frame = evas_object_data_get(tb, "general_frame");
	Evas_Object *calendar_frame = evas_object_data_get(tb, "calendar_frame");
	Evas_Object *data_frame = evas_object_data_get(tb, "data_frame");
	Evas_Object *help_frame = evas_object_data_get(tb, "help_frame");
	
	
//    evas_object_hide();
   evas_object_hide(general_frame);
   evas_object_hide(popup_frame);
   evas_object_hide(help_frame);
   evas_object_hide(advanced_frame);
   evas_object_hide(calendar_frame);
   evas_object_show(data_frame);
	
	printf("SHOW ADVANCED\n");
}


static void
_config_show_help(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *tb = data;
	
   Evas_Object *popup_frame = evas_object_data_get(tb, "popup_frame");
	Evas_Object *advanced_frame = evas_object_data_get(tb, "advanced_frame");
	Evas_Object *general_frame = evas_object_data_get(tb, "general_frame");
	Evas_Object *calendar_frame = evas_object_data_get(tb, "calendar_frame");
	Evas_Object *data_frame = evas_object_data_get(tb, "data_frame");
	Evas_Object *help_frame = evas_object_data_get(tb, "help_frame");
	
   evas_object_hide(general_frame);
   evas_object_hide(popup_frame);
   evas_object_hide(calendar_frame);
   evas_object_hide(advanced_frame);
   evas_object_hide(data_frame);
	evas_object_show(help_frame);
	
	printf("SHOW ADVANCED\n");
}
static void
completion_cb(void *data, const char *file, int status)
{
	
	Eina_List *completion_list = data;
   Evas_Object *year_data = eina_list_nth(completion_list, 0);
   Evas_Object *obj = eina_list_nth(completion_list, 1);
	
	if(status >= 200 && status <= 226)
	{
		elm_object_text_set(obj, "100%");
		
		//Unzip and rename
		Ecore_Exe *exe;
		char buf[4096];

		snprintf(buf, sizeof(buf), "cd /home/simon/.config/tageslosung && unzip /home/simon/.config/tageslosung/Losung_%s_XML.zip && sed -i 's/\r//g' 'Losungen Free %s.xml'", (char*)year_data, (char*)year_data);
// 		snprintf(buf, sizeof(buf), "cd /home/simon/.config/tageslosung && unzip /home/simon/.config/tageslosung/Losung_2018_XML.zip  && sed -i 's/\r//g' 'Losungen Free 2018.xml'");
		exe = ecore_exe_run(buf, NULL);
		if (exe > 0)
		{
			ecore_exe_free(exe);
		}
		
	}
	else
		elm_object_text_set(obj, "Error downloading file");
		
}
/*
static int
progress_cb(void *data, const char *file, long int dltotal, long int dlnow, long int ultotal, long int ulnow)
{
// 	Evas_Object *bt = data;
// 	elm_object_text_set(bt, "...");
}*/

static void
_download_data_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	char buf[512], cache_dir[4096], filename[512];

	
	
	elm_object_text_set(obj, "download");

	snprintf(cache_dir, sizeof(cache_dir), "%s/tageslosung/", efreet_config_home_get());
	snprintf(filename, sizeof(filename), "%s/tageslosung/Losung_%s_XML.zip", efreet_config_home_get(), (char*)data);

		ecore_file_recursive_rm(filename);
		
		if(!ecore_file_is_dir(cache_dir))
		{
			ecore_file_mkpath(cache_dir);
			printf("MKDIR: %s\n", cache_dir);
		}
		
// 		src_dest = "https://www.losungen.de/fileadmin/media-losungen/download/Losung_2019_XML.zip";
		
		snprintf(buf, sizeof(buf), "https://www.losungen.de/fileadmin/media-losungen/download/Losung_%s_XML.zip", (char*)data);
// 		snprintf(buf1, sizeof(buf1), "%s/tageslosung/Losung_%s_XML.zip", efreet_config_home_get(), data);
		Eina_List *completion_list = NULL;
		completion_list = eina_list_append(completion_list, data);
		completion_list = eina_list_append(completion_list, obj);
		
		ecore_file_download(buf, filename, completion_cb, NULL, completion_list, NULL);

}



void
_settings(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   printf("DAY: %i\n", current_day);
	char buf[PATH_MAX];
// 	double step;
	Evas_Object *popup_settings;
	
	// General frame Objects
	Evas_Object *general_frame;
	Evas_Object *tb_general;
	Evas_Object *check_online;
	Evas_Object *hoversel;
	Evas_Object *button;
	Evas_Object *button1;
	Evas_Object *check_switch;
	Evas_Object *sl_switch_time;
	Evas_Object *sl_font;
	
	// Popup frame Objects
	Evas_Object *popup_frame;
	Evas_Object *tb_popup;
	Evas_Object *check_popup;
	Evas_Object *check_layout;
	
	
	// Advanced frame Objects
	Evas_Object *tb_advanced;
	Evas_Object *advanced_frame;
	Evas_Object *cs;
	
	// Calendar frame Objects
	Evas_Object *tb_calendar;
	Evas_Object *calendar_frame;
	Evas_Object *boxh;
	Evas_Object *boxv;
	
	Evas_Object *cal;
	
	
	// Data Management frame Objects
	Evas_Object *tb_data;
	Evas_Object *data_frame;

	// Help frame Objects
	Evas_Object *help_frame;
	Evas_Object *tb_help;
	
	// Separator
	Evas_Object *o;
	
	// Lable
	Evas_Object *lbl;
		
	// List Objects
	Elm_Object_Item *list;
	Evas_Object *it;
	
	
	Evas_Object *ly = obj;
	Evas_Object *win = data;
	

	
   popup_settings = elm_win_add(win, "win", ELM_WIN_BASIC);
   elm_win_alpha_set(popup_settings, 1);
	
	tb = elm_table_add(popup_settings);
	evas_object_size_hint_weight_set(tb, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(tb, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(tb);
	
	lbl = elm_label_add(tb);
   evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(lbl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_style_set(lbl, "marker");
   elm_object_text_set(lbl, "<b>Tageslosung Configuration</b>");
   elm_table_pack(tb, lbl, 0, 0, 2, 1);
   evas_object_show(lbl);
	
	list = elm_list_add(tb);
	evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(list, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(tb, list, 0, 1, 1, 1);
	
   elm_list_select_mode_set(list, ELM_OBJECT_SELECT_MODE_ALWAYS);
	
   elm_scroller_content_min_limit(list, 1, 1);
	
   it = elm_list_item_append(list, "General", NULL, NULL,
                             _config_show_general, tb);
   elm_list_item_selected_set(it, 1);
	
   it = elm_list_item_append(list, "Popup", NULL, NULL,
                             _config_show_popup, tb);
	
   it = elm_list_item_append(list, "Advanced", NULL, NULL,
                             _config_show_advanced, tb);
	
   it = elm_list_item_append(list, "Calendar", NULL, NULL,
                             _config_show_calendar, tb);
	
   it = elm_list_item_append(list, "Data Management", NULL, NULL,
                             _config_show_data, tb);
	
	it = elm_list_item_append(list, "Help", NULL, NULL,
                             _config_show_help, tb);
   elm_list_go(list);
   evas_object_show(list);
	
	
/// FEED FRAME ///
	general_frame = elm_frame_add(popup_settings);
   elm_object_text_set(general_frame, "General");
	evas_object_size_hint_weight_set(general_frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(general_frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(tb, general_frame, 1, 1, 1, 1);
	
			tb_general = elm_table_add(general_frame);
			elm_table_padding_set(tb_general, 0, 2);
// 			evas_object_size_hint_weight_set(tb_general, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(tb_general, 0, EVAS_HINT_FILL);
			evas_object_show(tb_general);
			
			check_layout = elm_check_add(popup_settings);
			elm_object_text_set(check_layout, "Hide Text");
			elm_check_state_set(check_layout, ci_layout);
// 			elm_object_disabled_set(check_layout, EINA_TRUE);
			E_ALIGN(check_layout, 0.0, 0.0);
			E_WEIGHT(check_layout, EVAS_HINT_EXPAND, 0);
			elm_table_pack(tb_general, check_layout, 0, 0, 2, 1);
			evas_object_show(check_layout);
			evas_object_data_set(tb, "check_layout", check_layout);
			
			check_online = elm_check_add(popup_settings);
			elm_object_text_set(check_online, "Disable click to open on bibelserver.com");
			elm_check_state_set(check_online, ci_online);
			E_ALIGN(check_online, 0.0, 0.0);
			elm_table_pack(tb_general, check_online, 0, 1, 2, 1);
			evas_object_show(check_online);
			evas_object_data_set(tb, "check_online", check_online);
			
		   boxh = elm_box_add(popup_settings);
			elm_box_horizontal_set(boxh, EINA_TRUE);
			E_EXPAND(boxh);
			E_ALIGN(boxh, 0.0, 0.0);
			evas_object_show(boxh);
			
				lbl = elm_label_add(boxh);
				elm_object_text_set(lbl, "<custom align=left>Bibelübersetzung </custom>");
// 				E_ALIGN(lbl, 0.0, 0.5);
				elm_box_pack_end(boxh, lbl);
				evas_object_show(lbl);
				
				hoversel = elm_hoversel_add(boxh);
				elm_hoversel_auto_update_set(hoversel, EINA_TRUE);
				elm_hoversel_hover_parent_set(hoversel, popup_settings);
				if(!strcmp(ci_translation, "LUT"))
					elm_object_text_set(hoversel, "Luther 2017 Deutsch AT, NT");
				else if(!strcmp(ci_translation, "ELB"))
					elm_object_text_set(hoversel, "Elberfelder Bibel Deutsch AT, NT");
				else if(!strcmp(ci_translation, "HFA"))
					elm_object_text_set(hoversel, "Hoffnung für alle Deutsch AT, NT");
				else if(!strcmp(ci_translation, "SLT"))
					elm_object_text_set(hoversel, "Schlachter 2000 Deutsch AT, NT");
				else if(!strcmp(ci_translation, "NGÜ"))
					elm_object_text_set(hoversel, "Neue Genfer Übersetzung Deutsch Psalmen, NT");
				else if(!strcmp(ci_translation, "GNB"))
					elm_object_text_set(hoversel, "Gute Nachricht Bibel Deutsch AT, NT");
				else if(!strcmp(ci_translation, "EU"))
					elm_object_text_set(hoversel, "Einheitsübersetzung Deutsch AT, NT, Apokryphen");
				else if(!strcmp(ci_translation, "NLB"))
					elm_object_text_set(hoversel, "Neues Leben. Die Bibel Deutsch AT, NT");
				else if(!strcmp(ci_translation, "NeÜ"))
					elm_object_text_set(hoversel, "eue evangelistische Übersetzung Deutsch AT, NT");
				else if(!strcmp(ci_translation, "ESV"))
					elm_object_text_set(hoversel, "English Standard Version");
				else if(!strcmp(ci_translation, "NIV"))
					elm_object_text_set(hoversel, "New International Version");
				else if(!strcmp(ci_translation, "NIRV"))
					elm_object_text_set(hoversel, "New Int. Readers Version");
				else if(!strcmp(ci_translation, "KJV"))
					elm_object_text_set(hoversel, "King James Version");
				else if(!strcmp(ci_translation, "JSVS"))
					elm_object_text_set(hoversel, "King James V. with Strong's Dictionary");
				else if(!strcmp(ci_translation, "OT"))
					elm_object_text_set(hoversel, "Hebrew OT");
				else if(!strcmp(ci_translation, "LXX"))
					elm_object_text_set(hoversel, "Septuaginta");
				else
					elm_object_text_set(hoversel, "select");
					
			
				
				elm_hoversel_item_add(hoversel, "Luther 2017 Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "LUT");
				elm_hoversel_item_add(hoversel, "Elberfelder Bibel Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "ELB");
				elm_hoversel_item_add(hoversel, "Hoffnung für alle Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "HFA");
				elm_hoversel_item_add(hoversel, "Schlachter 2000 Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "SLT");
				elm_hoversel_item_add(hoversel, "Neue Genfer Übersetzung Deutsch Psalmen, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "NGÜ");
				elm_hoversel_item_add(hoversel, "Gute Nachricht Bibel Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "GNB");
				elm_hoversel_item_add(hoversel, "Einheitsübersetzung Deutsch AT, NT, Apokryphen", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "EU");
				elm_hoversel_item_add(hoversel, "Neues Leben. Die Bibel Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "NLB");
				elm_hoversel_item_add(hoversel, "Neue evangelistische Übersetzung Deutsch AT, NT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "NeÜ");
				elm_hoversel_item_add(hoversel, "English Standard Version", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "ESV");				
				elm_hoversel_item_add(hoversel, "New International Version", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "NIV");				
				elm_hoversel_item_add(hoversel, "New Int. Readers Version", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "NIRV");				
				elm_hoversel_item_add(hoversel, "King James Version", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "KJV");				
				elm_hoversel_item_add(hoversel, "King James V. with Strong's Dictionary", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "KJVS");				
				elm_hoversel_item_add(hoversel, "Hebrew OT", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "OT");				
				elm_hoversel_item_add(hoversel, "Septuaginta", NULL, ELM_ICON_NONE, _hoversel_selected_cb, "LXX");
				
// 				evas_object_smart_callback_add(hoversel, "clicked",
// 														_hoversel_clicked_cb, NULL);
// 				evas_object_smart_callback_add(hoversel, "clicked",
// 														_hoversel_selected_cb, NULL);
// 				evas_object_smart_callback_add(hoversel, "dismissed",
// 														_hoversel_dismissed_cb, NULL);
				
				
				elm_box_pack_end(boxh, hoversel);
				evas_object_show(hoversel);
				evas_object_data_set(tb, "hoversel", hoversel);
			
			elm_table_pack(tb_general, boxh, 1, 1, 2, 1);
			evas_object_show(boxh);
				
			o = elm_separator_add(popup_settings);
			elm_separator_horizontal_set(o, EINA_TRUE);
			elm_table_pack(tb_general, o, 0, 2, 2, 1);
			evas_object_show(o);
			
			check_switch = elm_check_add(popup_settings);
			elm_object_text_set(check_switch, "Disable Losung/Lehrtext switch or set ");
			elm_check_state_set(check_switch, ci_switch);
			E_ALIGN(check_switch, 0.0, 0.5);
			E_WEIGHT(check_switch, EVAS_HINT_EXPAND, 0);
			elm_table_pack(tb_general, check_switch, 0, 3, 2, 1);
			evas_object_data_set(tb, "check_switch", check_switch);
			evas_object_show(check_switch);
				
			sl_switch_time = elm_slider_add(popup_settings);
			E_ALIGN(sl_switch_time, 0.0, 0.5);
			elm_slider_unit_format_set(sl_switch_time, "%1.0f minutes");
			elm_slider_indicator_format_set(sl_switch_time, "%1.0f");
			elm_slider_span_size_set(sl_switch_time, 360);
			elm_slider_min_max_set(sl_switch_time, 1, 120);
			elm_object_text_set(sl_switch_time, "switch time ");
			elm_slider_value_set(sl_switch_time, ci_switch_time);
			elm_table_pack(tb_general, sl_switch_time, 0, 4, 2, 1);
			evas_object_data_set(tb, "sl_switch_time", sl_switch_time);
			evas_object_show(sl_switch_time);		
			
			o = elm_separator_add(popup_settings);
			elm_separator_horizontal_set(o, EINA_TRUE);
			elm_table_pack(tb_general, o, 0, 6, 2, 1);
			evas_object_show(o);
				
			sl_font = elm_slider_add(popup_settings);
			E_ALIGN(sl_font, 0.0, 0.5);
			elm_slider_unit_format_set(sl_font, "%1.0f px");
			elm_slider_indicator_format_set(sl_font, "%1.0f");
			elm_slider_value_set(sl_font, ci_font_size);
			elm_slider_span_size_set(sl_font, 360);
			elm_slider_min_max_set(sl_font, 8, 50);
			elm_object_text_set(sl_font, "Font Size    ");
			elm_slider_value_set(sl_font, ci_font_size);
			// 				step = _step_size_calculate(0, 9);
			// 				elm_slider_step_set(sl_font, 50.0);
			evas_object_data_set(tb, "sl_font", sl_font);
			elm_table_pack(tb_general, sl_font, 0, 5, 2, 1);
			evas_object_show(sl_font);

   elm_object_content_set(general_frame, tb_general);
	evas_object_data_set(tb, "general_frame", general_frame);
/// FEED FRAME END ///

/// POPUP FRAME ///
	popup_frame = elm_frame_add(popup_settings);
   elm_object_text_set(popup_frame, "Popup");
	evas_object_size_hint_weight_set(popup_frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(popup_frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(tb, popup_frame, 1, 1, 1, 1);
	
			tb_popup = elm_table_add(popup_settings);
			evas_object_size_hint_weight_set(tb_popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(tb_popup, EVAS_HINT_FILL, 0);
			evas_object_show(tb_popup);
			
			check_popup = elm_check_add(popup_settings);
			elm_object_text_set(check_popup, "Disable Popup");
			elm_check_state_set(check_popup, ci_popup);
			E_ALIGN(check_popup, 0.0, 0.0);
			E_WEIGHT(check_popup, EVAS_HINT_EXPAND, 0);
			elm_table_pack(tb_popup, check_popup, 0, 3, 1, 1);
			evas_object_show(check_popup);
			evas_object_data_set(tb, "check_popup", check_popup);

		
		elm_object_content_set(popup_frame, tb_popup);
		evas_object_data_set(tb, "popup_frame", popup_frame);
	/// POPUP FRAME END ///
		
	/// ADVANCED FRAME ///
	advanced_frame = elm_frame_add(popup_settings);
	elm_object_text_set(advanced_frame, "Color");
	evas_object_size_hint_weight_set(advanced_frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(advanced_frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_table_pack(tb, advanced_frame, 1, 1, 1, 1);
	
			tb_advanced = elm_table_add(popup_settings);
			evas_object_size_hint_weight_set(tb_advanced, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(tb_advanced, EVAS_HINT_FILL, 0);
			evas_object_show(tb_advanced);

			cs = elm_colorselector_add(popup_settings);
			evas_object_size_hint_weight_set(cs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(cs, EVAS_HINT_FILL, EVAS_HINT_FILL);
         
			evas_color_argb_premul(ci_a, &ci_r, &ci_g, &ci_b);
			elm_colorselector_color_set(cs, ci_r, ci_g, ci_b, ci_a);
				
			elm_colorselector_mode_set(cs, ELM_COLORSELECTOR_BOTH);
			elm_colorselector_palette_name_set(cs, "tageslosung");
			elm_colorselector_palette_color_add(cs, 253, 232, 82, 255);
			elm_colorselector_palette_color_add(cs, 255, 186, 0, 255);
			elm_colorselector_palette_color_add(cs, 223, 147, 37, 255);
			elm_colorselector_palette_color_add(cs, 238, 119, 99, 255);
			elm_colorselector_palette_color_add(cs, 164, 182, 166, 255);
			elm_colorselector_palette_color_add(cs, 146, 175, 29, 255);
			elm_colorselector_palette_color_add(cs, 41, 68, 59, 255);
			elm_colorselector_palette_color_add(cs, 0, 109, 128, 255);
			elm_colorselector_palette_color_add(cs, 11, 54, 71, 255);
			elm_colorselector_palette_color_add(cs, 41, 46, 68, 255);
			elm_colorselector_palette_color_add(cs, 116, 13, 14, 255);
			elm_colorselector_palette_color_add(cs, 101, 33, 44, 255);
			elm_colorselector_palette_color_add(cs, 132, 50, 118, 255);
			elm_colorselector_palette_color_add(cs, 68, 40, 55, 255);
			elm_colorselector_palette_color_add(cs, 63, 37, 60, 255);
			elm_colorselector_palette_color_add(cs, 115, 87, 63, 255);
			elm_colorselector_palette_color_add(cs, 66, 70, 73, 255);
			elm_colorselector_palette_color_add(cs, 255, 255, 255, 255);
			elm_colorselector_palette_color_add(cs, 0, 0, 0, 255);
			evas_object_data_set(tb, "cs", cs);
			elm_table_pack(tb_advanced, cs, 0, 0, 1, 1);
			evas_object_show(cs);

		
   elm_object_content_set(advanced_frame, tb_advanced);
	evas_object_data_set(tb, "advanced_frame", advanced_frame);
/// ADVANCED FRAME END ///
	
/// CALENDAR FRAME ///
	calendar_frame = elm_frame_add(popup_settings);
   elm_object_text_set(calendar_frame, "Calendar");
	evas_object_size_hint_weight_set(calendar_frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(calendar_frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(tb, calendar_frame, 1, 1, 1, 1);
	
			tb_calendar = elm_table_add(popup_settings);
			evas_object_show(tb_calendar);
			
			
	
		   boxh = elm_box_add(popup_settings);
			elm_box_horizontal_set(boxh, EINA_TRUE);
// 			E_EXPAND(boxh);
// 			E_WEIGHT(check, 0, 0);
			E_ALIGN(boxh, 0.0, 0.0);
			evas_object_show(boxh);
			
			
				cal = elm_calendar_add(boxh);
				elm_calendar_first_day_of_week_set(cal, ELM_DAY_MONDAY);
				evas_object_size_hint_weight_set(cal, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				elm_box_pack_end(boxh, cal);

// 				time_t the_time = (SEC_PER_YEAR * 41) + (SEC_PER_DAY * 9); // Set date to DEC 31, 2010 
// 				elm_calendar_selected_time_set(cal, gmtime(&the_time));
				elm_calendar_min_max_year_set(cal, atoi(year), atoi(nextyear));
			
				evas_object_show(cal);

				
						boxv = elm_box_add(boxh);
						elm_box_horizontal_set(boxv, EINA_FALSE);
						E_EXPAND(boxv);
						E_WEIGHT(boxv, 0, 0);
						E_ALIGN(boxv, 0.5, 0.5);
						evas_object_show(boxv);
				
						lbl1 = elm_label_add(boxv);
						elm_label_line_wrap_set(lbl1, ELM_WRAP_WORD);
						elm_label_wrap_width_set(lbl1, ELM_SCALE_SIZE(400));
						elm_object_text_set(lbl1, losungstext);
		// 				E_ALIGN(lbl, 0.0, 0.0);
						elm_box_pack_end(boxv, lbl1);
						evas_object_show(lbl1);
						
						lbl1_1 = elm_label_add(boxv);
						elm_object_text_set(lbl1_1, losungsvers);
		// 				E_ALIGN(lbl1_1, 0.0, 0.0);
						elm_box_pack_end(boxv, lbl1_1);
						evas_object_show(lbl1_1);
						
						o = elm_separator_add(boxv);
						elm_separator_horizontal_set(o, EINA_TRUE);
						elm_box_pack_end(boxv, o);
						evas_object_show(o);
						
						lbl2 = elm_label_add(boxv);
						elm_label_line_wrap_set(lbl2, ELM_WRAP_WORD);
						elm_label_wrap_width_set(lbl2, ELM_SCALE_SIZE(400));
						elm_object_text_set(lbl2, lehrtext);
		// 				E_ALIGN(lbl2, 0.0, 0.0);
						elm_box_pack_end(boxv, lbl2);
						evas_object_show(lbl2);
						
						lbl2_1 = elm_label_add(boxv);
						elm_object_text_set(lbl2_1, lehrtextvers);
		// 				E_ALIGN(lbl2_1, 0.0, 0.0);
						elm_box_pack_end(boxv, lbl2_1);
						evas_object_show(lbl2_1);
						
						elm_box_pack_end(boxh, boxv);
						evas_object_show(boxv);

				evas_object_smart_callback_add(cal, "changed", _print_cal_info_cb, lbl);
				
				evas_object_smart_callback_add(lbl1, "clicked", open_bibelserver_config, losungsvers);
				evas_object_smart_callback_add(lbl1_1, "clicked", open_bibelserver_config, losungsvers);
				evas_object_smart_callback_add(lbl2, "clicked", open_bibelserver_config, lehrtextvers);
				evas_object_smart_callback_add(lbl2_1, "clicked", open_bibelserver_config, lehrtextvers);
				
			
				elm_table_pack(tb_calendar, boxh, 0, 0, 1, 1);
			evas_object_show(boxh);

	
   elm_object_content_set(calendar_frame, tb_calendar );
	evas_object_data_set(tb, "calendar_frame", calendar_frame);
/// ADVANCED FRAME END ///
	
	
	
/// DATA FRAME ///
	data_frame = elm_frame_add(popup_settings);
   elm_object_text_set(data_frame, "Data Management");
	evas_object_size_hint_weight_set(data_frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(data_frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(tb, data_frame, 1, 1, 1, 1);
	
			tb_data = elm_table_add(popup_settings);
			evas_object_size_hint_weight_set(tb_data, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(tb_data, EVAS_HINT_FILL, EVAS_HINT_FILL);
			evas_object_show(tb_data);

			lbl = elm_label_add(popup_settings);
			elm_object_text_set(lbl, "Here you can download the tageslosung data from <br>Evangelische Brüder-Unität – Herrnhuter Brüdergemeinde www.losungen.de.");
// 			E_EXPAND(lbl);
// 			E_FILL(lbl);
			elm_table_pack(tb_data, lbl, 0, 0, 2, 1);
			evas_object_show(lbl);
			
// 			char year[512];
// 			time_t t;
// 			struct tm * ts;
// 			t = time(NULL);
// 			ts = localtime(&t);
// 			printf("%d\n",ts->tm_year+1900);
// 			snprintf(year, sizeof(year), "%d", ts->tm_year+1900);
			
			button = elm_button_add(popup_settings);
			snprintf(buf, sizeof(buf), "download %s", year);
			elm_object_text_set(button, buf);
			evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 0);
// 			elm_object_tooltip_text_set(button, "download losung data for year 2018");
			elm_table_pack(tb_data, button, 0, 1, 1, 1);
			evas_object_show(button);
			
			button1 = elm_button_add(popup_settings);
			snprintf(buf, sizeof(buf), "download %s", nextyear);
			elm_object_text_set(button1, buf);
			evas_object_size_hint_weight_set(button1, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(button1, EVAS_HINT_FILL, 0);
// 			elm_object_tooltip_text_set(button1, "download losung data for year 2019");
			elm_table_pack(tb_data, button1, 1, 1, 1, 1);
			evas_object_show(button1);
			
			evas_object_smart_callback_add(button, "clicked", _download_data_cb, (void*)year); 
			evas_object_smart_callback_add(button1, "clicked", _download_data_cb, (void*)nextyear); 
			

// 			https://www.losungen.de/fileadmin/media-losungen/download/Losung_2019_XML.zip
			
// 			lbl = elm_label_add(popup_settings);
// 			elm_object_text_set(lbl, "<custom align=left>- click on the cross, to open the shown text on bibelserver.com<br>"
// 											"- mouse over the text to show the popup<br>"
// 											"- mouse wheel on text to switch Tageslosung/Lehrtext<br>"
// 											"- right click for settings<br>"
// 											"- closing the settings panel will save the settings</custom>");
// 			E_FILL(lbl);
// 			E_EXPAND(lbl);
// 			evas_object_size_hint_align_set(lbl, 0.5, 0.5);
// 			elm_table_pack(tb_data, lbl, 0, 1, 1, 1);
// 			evas_object_show(lbl);
	
	
	
   elm_object_content_set(data_frame, tb_data );
	evas_object_data_set(tb, "data_frame", data_frame);	
		
/// DATA FRAME END///
	
	
/// HELP FRAME ///
	help_frame = elm_frame_add(popup_settings);
   elm_object_text_set(help_frame, "Help");
	evas_object_size_hint_weight_set(help_frame, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(help_frame, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_table_pack(tb, help_frame, 1, 1, 1, 1);
	
			tb_help = elm_table_add(popup_settings);
			evas_object_size_hint_weight_set(tb_help, 0, 0);
			evas_object_size_hint_align_set(tb_help, 0, 0);
			evas_object_show(tb_help);

			lbl = elm_label_add(popup_settings);
			elm_object_text_set(lbl, "Rechte der Texte:<br>Evangelische Brüder-Unität – Herrnhuter Brüdergemeinde<br>Weitere Informationen finden Sie auf www.losungen.de.");
			E_EXPAND(lbl);
			E_FILL(lbl);
			elm_table_pack(tb_help, lbl, 0, 0, 1, 1);
			evas_object_show(lbl);
			
			lbl = elm_label_add(popup_settings);
			elm_object_text_set(lbl, "<custom align=left>- click on the cross, to open the shown text on bibelserver.com<br>"
											"- mouse over the text to show the popup<br>"
											"- mouse wheel on text to switch Tageslosung/Lehrtext<br>"
											"- right click for settings<br>"
											"- closing the settings panel will save the settings</custom>");
			E_FILL(lbl);
			E_EXPAND(lbl);
			evas_object_size_hint_align_set(lbl, 0.5, 0.5);
			elm_table_pack(tb_help, lbl, 0, 1, 1, 1);
			evas_object_show(lbl);
	
	
	
   elm_object_content_set(help_frame, tb_help );
	evas_object_data_set(tb, "help_frame", help_frame);	
		
/// HELP FRAME END///
	
	evas_object_data_set(tb, "win", win);
   evas_object_data_set(tb, "ly", ly);
	
   elm_object_content_set(popup_settings, tb);
	_config_show_general(tb, NULL, NULL);
	
	evas_object_smart_callback_add(cs, "changed", _colorselector_changed_cb, tb);

	evas_object_event_callback_add(popup_settings, EVAS_CALLBACK_MOUSE_OUT, _config_save, tb);
	evas_object_event_callback_add(popup_settings, EVAS_CALLBACK_HIDE, _popup_del, NULL);
   evas_object_smart_callback_add(check_switch, "changed", _check_switch_changed, sl_switch_time);
   evas_object_smart_callback_add(check_layout, "changed", _check_layout_changed, tb);
	
	
   evas_object_smart_callback_add(sl_font, "changed", _sl_font_changed, tb);
	
   evas_object_show(popup_settings);
	
	
	
			if(ci_switch == 1)
		_check_switch_changed(sl_switch_time, check_switch, NULL);
}

