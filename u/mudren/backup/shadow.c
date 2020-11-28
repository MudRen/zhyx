#include <ansi.h>
#define CHAMPION_FILE "/u/yuchang/backup/npc/shadow.o"
#define MINGREN_DIR "/u/yuchang/backup/"
inherit NPC;
void loadall(object me);
void create()
{
        string info,name,id,file;
        set_name( "ĩ������" , ({ "mori mingren" }) );

        info = read_file(CHAMPION_FILE);
/*
if (!info) set_name("hehe",({"hehe"}));
*/
        if( info && sscanf(info,"%s %s %s",file,id,name) == 3)
        {
                restore_object(file);
        set_name( name , ({ id }) );
        delete("env");
        set("attitude", "aggressive");
        reset_action();
        delete_temp("already_loaded");
        loadall(this_object());
        set("title", HIR "��������" NOR);
        }
        setup();        
                
}

void loadall(object me)
{
        int MAX = 3;
        string name,id, *created;
        int i,j;
        object thing, *inv;
        inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        destruct(inv[i]);
                }

        id = me->query("id");
        created = get_dir(MINGREN_DIR + "item/" + id[0..0] + "/" + id + "/");
        for(j=0; (j<sizeof(created) && j < (MAX+1) ); j++)
		{
	        thing = new( MINGREN_DIR + "item/" + id[0..0] + "/" + id +
        "/" + created[j]);
if (!thing) break;
                        if(thing->move(me)) 
                        {
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

