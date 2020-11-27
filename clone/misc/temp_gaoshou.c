#include <ansi.h>
inherit NPC;
inherit F_AUTOLOAD;

#define GAOSHOU_DIR "/data/leitai/"

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = query("id");
	if (! stringp(id)) return 0;
	return sprintf(GAOSHOU_DIR "npc/%s", id);
}

int save()
{
	string file;

	if (stringp(file = this_object()->query_save_file()))
	{
		assure_file(file+ __SAVE_EXTENSION__);
		return save_object(file);
	}

	return 0;
}

int restore()
{
	string file;

	if (stringp(file = this_object()->query_save_file()))
		return restore_object(file);
	return 0;
}

void create()
{
        string id,name;
        ::create();
        id = BIWU_D->get_new_id();
        set_name( "ĩ�ո���" , ({ id }) );
        setup();
        restore();
}

void delete_status()
{
        object ob;
        mapping my;

        ob = this_object();
        my = ob->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["max_jingli"] * 2;
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"] * 2;
        my["food"]   = ob->max_food_capacity();
        my["water"]  = ob->max_water_capacity();

	 if (ob->is_ghost()) ob->reincarnate();
	 ob->clear_condition();

        ob->delete("can_summon");
        ob->delete("carry_ob");
        ob->delete("LastReadNews");
        ob->delete("balance");
        ob->delete("board_last_read");
        ob->delete("brothers");
        ob->delete("comeworld");
        ob->delete("env");
        ob->delete("jiebai");
        ob->delete("last_examine");
        ob->delete("last_read_news");
        ob->delete("last_save");
        ob->delete("party");
        ob->delete("postover");
        ob->delete("private_room");
        ob->delete("purename");
        ob->delete("surname");
        ob->delete("registered");
        ob->delete("startroom");
        ob->clean_up_autoload();
        ob->set("jiali",ob->query_skill("force") / 2);
        ob->improve_craze(ob->query_max_craze());
        ob->set("jianu",ob->query_max_craze() / 100);
        ob->save();
        return;
}