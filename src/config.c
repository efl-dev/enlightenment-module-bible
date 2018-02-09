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
		
	Evas_Object *mainbox = data;
   Evas_Object *check_popup = evas_object_data_get(mainbox, "check_popup");
   Evas_Object *check_online = evas_object_data_get(mainbox, "check_online");
   Evas_Object *check_switch = evas_object_data_get(mainbox, "check_switch");
   Evas_Object *check_layout = evas_object_data_get(mainbox, "check_layout");
//    Evas_Object *hoversel = evas_object_data_get(mainbox, "hoversel");
   Evas_Object *sl_switch_time = evas_object_data_get(mainbox, "sl_switch_time");
   Evas_Object *ly = evas_object_data_get(mainbox, "ly");
   Evas_Object *sl_font = evas_object_data_get(mainbox, "sl_font");
//    Evas_Object *tg_theme = evas_object_data_get(mainbox, "tg_theme");	
	
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
	Evas_Object *mainbox = data;
   Evas_Object *ic = evas_object_data_get(mainbox, "ic");
   Evas_Object *ly = evas_object_data_get(mainbox, "ly");

   elm_colorselector_color_get(obj, &ci_r, &ci_g, &ci_b, &ci_a);
	
	evas_object_color_set(ic, ci_r, ci_g, ci_b, ci_a);
	
	set_color(ly);
}

static void
_sl_font_changed_value(void *data EINA_UNUSED, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	ci_font_size = elm_slider_value_get(obj);
}


void
_sl_font_changed(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
	Evas_Object *mainbox = data;
//    Evas_Object *win = evas_object_data_get(mainbox, "win");
   Evas_Object *ly = evas_object_data_get(mainbox, "ly");	
	char buf[PATH_MAX];
	
   set_color(ly);
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
_check_layout_changed(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
	Evas_Object *mainbox = data;
   Evas_Object *win = evas_object_data_get(mainbox, "win");
   Evas_Object *ly = evas_object_data_get(mainbox, "ly");
// 	Evas_Object *edje_obj = elm_layout_edje_get(ly);
	char buf[4096];
	char buf1[4096];
	
	snprintf(buf1, sizeof(buf1), "%s/themes/tageslosung.edj", PACKAGE_DATA_DIR);
   
	if(elm_check_state_get(obj))
   {		
      evas_object_size_hint_aspect_set(win, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
		elm_layout_file_set(ly, buf1, "tageslosung2_small");
		printf("check if\n");
   }else
	{		
      evas_object_size_hint_aspect_set(win, EVAS_ASPECT_CONTROL_BOTH, 10, 1);
		elm_layout_file_set(ly, buf1, "tageslosung2");
		printf("check else\n");
	}
	
	set_color(ly);
}


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
}


static void
_hoversel_selected_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
//    char buf[PATH_MAX];
	ci_translation = eina_stringshare_add((char*)data);
	printf("HOVERSEL: %s\n", ci_translation);
}

static void
_popup_focus_out(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_data EINA_UNUSED)
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
_settings_2(void *data, Evas_Object *obj, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
	Evas_Object *win = data;
	Evas_Object *ly = obj;
	
	_settings(win, ly, NULL);
}



void
_settings(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{	
	Evas_Object *popup, *lbl, *fr, *fr2, *fr3, *sl_switch_time, *sl_font, *cal, *boxv, *cs;
   Evas_Object *o, *mainbox, *box_settings, *box_usage, *box_copyright, *check_switch;
   Evas_Object *check_online, *check_popup, *check_layout, *fr1, *boxh, *hoversel, *box_history;
	
// 	Evas_Object *tg_theme;
	Evas_Object *ic;
	Evas_Object *ly = obj;
	Evas_Object *win = data;
   char buf[PATH_MAX];

		  
   popup = elm_win_add(win, "win", ELM_WIN_BASIC);
   elm_win_alpha_set(popup, 1);
	
   mainbox = elm_box_add(popup);
	
	
   elm_box_horizontal_set(mainbox, EINA_FALSE);
   E_EXPAND(mainbox);
   E_ALIGN(mainbox, 0.0, 0.0);
   evas_object_show(mainbox);
	
	
   fr = elm_frame_add(mainbox);
   elm_object_text_set(fr, "Tageslosung Settings");
   E_EXPAND(fr);
   E_ALIGN(fr, 0.5, 0.5);
   E_FILL(fr);
   evas_object_show(fr);

   box_settings = elm_box_add(fr);
   elm_box_horizontal_set(box_settings, EINA_FALSE);
   E_EXPAND(box_settings);
   evas_object_show(box_settings);
	
	
   ic = elm_icon_add(box_settings);
	snprintf(buf, sizeof(buf), "%s/images/module_icon1.png", PACKAGE_DATA_DIR);
	elm_image_file_set(ic, buf, NULL);
   evas_object_size_hint_weight_set(ic, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(ic, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_min_set(ic, 56, 56);
	evas_object_color_set(ic, ci_r, ci_g, ci_b, ci_a);
	elm_box_pack_end(box_settings, ic);

   evas_object_data_set(mainbox, "ic", ic);
   evas_object_show(ic);
/*
   tg_theme = elm_check_add(box_settings);
   elm_object_style_set(tg_theme, "toggle");
   elm_object_text_set(tg_theme, gettext("Theme: "));
	elm_check_state_set(tg_theme, ci_theme);
   elm_object_part_text_set(tg_theme, "on", gettext("Black"));
   elm_object_part_text_set(tg_theme, "off", gettext("White"));
   elm_box_pack_end(box_settings, tg_theme);
   evas_object_show(tg_theme);
	evas_object_data_set(mainbox, "tg_theme", tg_theme);
	
	
	o = elm_separator_add(box_settings);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_settings, o);
   evas_object_show(o);
	
	*/
	
	cs = elm_colorselector_add(box_settings);
   evas_object_size_hint_weight_set(cs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(cs, EVAS_HINT_FILL, EVAS_HINT_FILL);
    
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
   elm_box_pack_end(box_settings, cs);
   evas_object_show(cs);
	evas_object_data_set(mainbox, "cs", cs);
	
	
	o = elm_separator_add(box_settings);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_settings, o);
   evas_object_show(o);
	
	check_layout = elm_check_add(box_settings);
	elm_object_text_set(check_layout, "Hide Text");
   elm_check_state_set(check_layout, ci_layout);
   E_ALIGN(check_layout, 0.0, 0.0);
 	E_WEIGHT(check_layout, EVAS_HINT_EXPAND, 0);
//    evas_object_smart_callback_add(check_layout, "changed", _check_changed, inst);
	elm_box_pack_end(box_settings, check_layout);
	evas_object_show(check_layout);
   evas_object_data_set(mainbox, "check_layout", check_layout);
	
	

	o = elm_separator_add(box_settings);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_settings, o);
   evas_object_show(o);
	
	
// 		   boxh = elm_box_add(box_settings);
// 			elm_box_horizontal_set(boxh, EINA_TRUE);
// 			E_EXPAND(boxh);/*
// 			E_WEIGHT(check, 0, 0);*/
// 			E_ALIGN(boxh, 0.0, 0.0);
// 			evas_object_show(boxh);
			
				check_switch = elm_check_add(box_settings);
				elm_object_text_set(check_switch, "Disable Losung/Lehrtext switch or set ");
			   elm_check_state_set(check_switch, ci_switch);
				E_ALIGN(check_switch, 0.0, 0.5);
				E_WEIGHT(check_switch, EVAS_HINT_EXPAND, 0);
				elm_box_pack_end(box_settings, check_switch);
				evas_object_show(check_switch);
			   evas_object_data_set(mainbox, "check_switch", check_switch);
				
				sl_switch_time = elm_slider_add(box_settings);
				E_ALIGN(sl_switch_time, 0.0, 0.5);
				elm_slider_unit_format_set(sl_switch_time, "%1.0f minutes");
				elm_slider_indicator_format_set(sl_switch_time, "%1.0f");
				elm_slider_span_size_set(sl_switch_time, 360);
				elm_slider_min_max_set(sl_switch_time, 1, 120);
				elm_object_text_set(sl_switch_time, "switch time ");
				elm_slider_value_set(sl_switch_time, ci_switch_time);
// 				step = _step_size_calculate(0, 9);
// 				elm_slider_step_set(sl, step);
// 				evas_object_size_hint_align_set(sl, EVAS_HINT_FILL, EVAS_HINT_FILL);
// 				evas_object_size_hint_weight_set(sl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				
				
				elm_box_pack_end(box_settings, sl_switch_time);
				evas_object_show(sl_switch_time);
				evas_object_data_set(mainbox, "sl_switch_time", sl_switch_time);
			
// 			elm_box_pack_end(box_settings, boxh);
// 			evas_object_show(boxh);

	o = elm_separator_add(box_settings);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_settings, o);
   evas_object_show(o);
	
///////
   sl_font = elm_slider_add(box_settings);
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
   elm_box_pack_end(box_settings, sl_font);
   evas_object_show(sl_font);
	evas_object_data_set(mainbox, "sl_font", sl_font);
				
				
	o = elm_separator_add(box_settings);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_settings, o);
   evas_object_show(o);
////	

	check_popup = elm_check_add(box_settings);
	elm_object_text_set(check_popup, "Disable Popup");
   elm_check_state_set(check_popup, ci_popup);
   E_ALIGN(check_popup, 0.0, 0.0);
 	E_WEIGHT(check_popup, EVAS_HINT_EXPAND, 0);
//    evas_object_smart_callback_add(check_popup, "changed", _check_changed, inst);
	elm_box_pack_end(box_settings, check_popup);
	evas_object_show(check_popup);
   evas_object_data_set(mainbox, "check_popup", check_popup);
	
	

   o = elm_separator_add(box_settings);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_settings, o);
   evas_object_show(o);

   check_online = elm_check_add(box_settings);
   elm_object_text_set(check_online, "Disable click to open on bibelserver.com");
	
	elm_check_state_set(check_online, ci_online);
   E_ALIGN(check_online, 0.0, 0.0);
//    E_WEIGHT(check, EVAS_HINT_EXPAND, 0);
   elm_box_pack_end(box_settings, check_online);
   evas_object_show(check_online);
   evas_object_data_set(mainbox, "check_online", check_online);

// 	o = elm_separator_add(box);
//    elm_separator_horizontal_set(o, EINA_TRUE);
//    elm_box_pack_end(box, o);
//    evas_object_show(o);

	
		   boxh = elm_box_add(box_settings);
			elm_box_horizontal_set(boxh, EINA_TRUE);
			E_EXPAND(boxh);/*
			E_WEIGHT(check, 0, 0);*/
			E_ALIGN(boxh, 0.0, 0.0);
			evas_object_show(boxh);
			
				lbl = elm_label_add(boxh);
				elm_object_text_set(lbl, "<custom align=left>Bibelübersetzung<br>auf bibelserver.com</custom>");
// 				E_ALIGN(lbl, 0.0, 0.5);
				elm_box_pack_end(boxh, lbl);
				evas_object_show(lbl);
				
				hoversel = elm_hoversel_add(boxh);
				elm_hoversel_auto_update_set(hoversel, EINA_TRUE);
				elm_hoversel_hover_parent_set(hoversel, popup);
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
				evas_object_data_set(mainbox, "hoversel", hoversel);
			
			elm_box_pack_end(box_settings, boxh);
			evas_object_show(boxh);

			




   elm_object_content_set(fr, box_settings);
   elm_box_pack_end(mainbox, fr);

	////////////////////////////////////////////////////////7
   fr1 = elm_frame_add(mainbox);
   elm_object_text_set(fr1, "History");
   E_EXPAND(fr1);
   E_FILL(fr1);
   evas_object_show(fr1);
   elm_box_pack_end(mainbox, fr1);
	
   box_history = elm_box_add(fr1);
   elm_box_horizontal_set(box_history, EINA_FALSE);
   E_EXPAND(box_history);
   evas_object_show(box_history);
	
	o = elm_separator_add(box_history);
   elm_separator_horizontal_set(o, EINA_TRUE);
   elm_box_pack_end(box_history, o);
   evas_object_show(o);
	

	
	
		   boxh = elm_box_add(box_history);
			elm_box_horizontal_set(boxh, EINA_TRUE);
// 			E_EXPAND(boxh);
// 			E_WEIGHT(check, 0, 0);
			E_ALIGN(boxh, 0.0, 0.0);
			evas_object_show(boxh);
			
			
				cal = elm_calendar_add(boxh);
				elm_calendar_first_day_of_week_set(cal, ELM_DAY_MONDAY);
				evas_object_size_hint_weight_set(cal, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				elm_box_pack_end(boxh, cal);

// 				time_t the_time = (SEC_PER_YEAR * 41) + (SEC_PER_DAY * 9); /* Set date to DEC 31, 2010 */
// 				elm_calendar_selected_time_set(cal, gmtime(&the_time));
				elm_calendar_min_max_year_set(cal, 2018, 2018);
			
				evas_object_show(cal);

				
						boxv = elm_box_add(boxh);
						elm_box_horizontal_set(boxv, EINA_FALSE);
						E_EXPAND(boxv);
						E_WEIGHT(boxv, 0, 0);
						E_ALIGN(boxv, 0.5, 0.5);
// 						evas_object_size_hint_max_set()
						
// 						evas_object_size_hint_aspect_set(boxv, EVAS_ASPECT_CONTROL_BOTH, 1,1);
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
				
			
			elm_box_pack_end(box_history, boxh);
			evas_object_show(boxh);
	
	
			
   elm_object_content_set(fr1, box_history);
   elm_box_pack_end(mainbox, fr1);
	
	////////////////////////////////////////////////////////7
   fr2 = elm_frame_add(mainbox);
   elm_object_text_set(fr2, "Usage");
   E_EXPAND(fr2);
   E_FILL(fr2);
//    evas_object_size_hint_align_set(fr2, 0.5, 0.5);
   evas_object_show(fr2);
   elm_box_pack_end(mainbox, fr2);
	
   box_usage = elm_box_add(fr2);
   elm_box_horizontal_set(box_usage, EINA_FALSE);
   E_EXPAND(box_usage);
   E_FILL(box_usage);
   evas_object_show(box_usage);
	
	
   lbl = elm_label_add(box_usage);
   elm_object_text_set(lbl, "<custom align=left>- click on the cross, to open the shown text on bibelserver.com<br>"
									"- click on text to open the popup<br>"
									"- mouse wheel on text to switch Tageslosung/Lehrtext<br>"
									"- alt+right click for settings<br>"
									"- closing the settings panel will save the settings</custom>");
   E_FILL(lbl);
   E_EXPAND(lbl);
   evas_object_size_hint_align_set(lbl, 0.5, 0.5);
   elm_box_pack_end(box_usage, lbl);
   evas_object_show(lbl);	
	

			
   elm_object_content_set(fr2, box_usage);
   elm_box_pack_end(mainbox, fr2);
	
	
	
	
/////////////////
	////////////////////////////////////////////////////////7
   fr3 = elm_frame_add(mainbox);
   elm_object_text_set(fr3, "Copyright");
   E_EXPAND(fr3);
   E_FILL(fr3);
//    evas_object_size_hint_align_set(fr3, 0.5, 0.5);
   evas_object_show(fr3);
   elm_box_pack_end(mainbox, fr3);
	
   box_copyright = elm_box_add(fr3);
   elm_box_horizontal_set(box_usage, EINA_FALSE);
   E_EXPAND(box_copyright);
   evas_object_show(box_copyright);
	
	
   lbl = elm_label_add(box_copyright);
   
   elm_object_text_set(lbl, "Rechte der Texte:<br>Evangelische Brüder-Unität – Herrnhuter Brüdergemeinde<br>Weitere Informationen finden Sie auf www.losungen.de.");
//    E_ALIGN(lbl, 0.0, 0.0);
   E_EXPAND(lbl);
   E_FILL(lbl);
   elm_box_pack_end(box_copyright, lbl);
   evas_object_show(lbl);	
	
   elm_object_content_set(fr3, box_copyright);
   elm_box_pack_end(mainbox, fr3);
	
	if(ci_switch == 1)
		_check_switch_changed(sl_switch_time, check_switch, NULL);
	
	if(ci_online == 1)
		_check_bibelserver_changed(hoversel, check_online, NULL);
	
	printf("orient_helper:%s\n", orient_helper);
	
	if(orient_helper != NULL)
	{
	   if(strcmp(orient_helper, "right") == 0) 
	   {
	      elm_object_disabled_set(sl_switch_time, EINA_TRUE);
	      elm_object_disabled_set(check_switch, EINA_TRUE);
	      elm_object_disabled_set(check_online, EINA_TRUE);
		   elm_object_disabled_set(sl_font, EINA_TRUE);
	   }
	}
	
   evas_object_smart_callback_add(check_online, "changed", _check_bibelserver_changed, hoversel);
   evas_object_smart_callback_add(check_switch, "changed", _check_switch_changed, sl_switch_time);
   evas_object_smart_callback_add(check_layout, "changed", _check_layout_changed, mainbox);
   evas_object_smart_callback_add(sl_font, "changed", _sl_font_changed, mainbox);
   evas_object_smart_callback_add(sl_font, "changed", _sl_font_changed_value, ly);
//    evas_object_smart_callback_add(tg_theme, "changed", _tg_changed_cb, ic);
//    evas_object_smart_callback_add(tg_theme, "changed", _config_save, mainbox);
//    evas_object_smart_callback_add(tg_theme, "changed", _sl_font_changed, ly);
	evas_object_smart_callback_add(cs, "changed", _colorselector_changed_cb, mainbox);
	
   evas_object_data_set(mainbox, "win", win);
   evas_object_data_set(mainbox, "ly", ly);
	
   elm_object_content_set(popup, mainbox);
	
	evas_object_event_callback_add(popup, EVAS_CALLBACK_MOUSE_OUT, _config_save, mainbox);
	evas_object_event_callback_add(popup, EVAS_CALLBACK_FOCUS_OUT, _popup_focus_out, NULL);
   evas_object_show(popup);
}

