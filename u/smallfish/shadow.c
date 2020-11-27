#include <ansi.h>
#define CHAMPION_FILE "/u/smallfish/backup/npc/shadow.o"
#define MINGREN_DIR "/data/"
inherit NPC;
void loadall(object me);
void create()
{
        string info,name,id,file,nothing,title;
        set_name( "ĩ������" , ({ "mori mingren" }) );
       setup();

        info = read_file(CHAMPION_FILE);
        if( info && sscanf(info,"%s %s %s %s %s",file,id,name,title,nothing) == 5)
        {
                restore_object(file);
        set_name( name , ({ id }) );
	set("title", HIR "ĩ������ " NOR + query("title"));
        delete_temp("already_loaded");
	set("mingren",1);
        loadall(this_object());
        }
        setup();        
                
}

void loadall(object me)
{
        string name,id, *created;
        int i,j;
        object thing,*inv;
		string the_thing;
        inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        destruct(inv[i]);
                }

        id = me->query("id");
        created = get_dir(MINGREN_DIR + "item/" + id[0..0] + "/");
        for(j=0; j<sizeof(created); j++)
		{
	        if( sscanf(created[j],id + "-%s.c",the_thing) == 1)
			{
				if (! stringp(the_thing = me->query("can_summon/" + the_thing))) continue;
				call_other(the_thing, "???");
				thing = find_object(the_thing);
				thing->delete_temp("stab_by");
				thing->delete("no_get");
				thing->move(me);
				thing->wield();
				thing->wear();
			}

        }
        me->reset_action();
        me->set_temp("already_loaded",1);
}
void init()
{
        if(!query_temp("already_loaded"))
                loadall(this_object());
        return;
}

