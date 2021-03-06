#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "\n\n                修        罗        道" NOR);
        set("long", HIG "\n"
"阿修罗原是印度远古诸神之一，被视为恶神，属于凶猛好斗的\n"
"鬼神，经常与帝释天争斗不休。因有福报而没有德性有的说法\n"
"只是将他纳入鬼神中，或说是堕落的天人，而北传佛教将他列\n"
"为善道，南传佛教则归类入恶道中。福如天人，德非天人。你\n"
"可以在这里参悟(canwu)。\n\n" NOR);
set("exits", ([ 
            "out"   : "/d/special/taixu",            
        ]));
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}


int do_canwu()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("lunhui-jian", 1);     

        if (ob->query("can_perform/lunhui-jian/xiuluodao"))
        {
                write("你已经参悟透了修罗道。\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("你未修前世，无法参透修罗道。\n");
                return 1; 
        } */

        if (c_skill < 500)
        {
                write("你至少要五百级轮回剑，才能参透修罗道。\n");
                return 1; 
        }

        if (ob->query("jing") < 80)
        {
                write("你精力不能集中，现在无法参悟。\n",ob);
                return 1; 
        }
      
        if (random(15) != 1)
        {
        
                write("你趺坐静思良久，还是无法参透生死之道。\n", ob);              
                return 1;
        }
		
		if (random(4) == 1)
		{
        message_sort(HIW"\n$N" HIW"趺坐静思，猛然间一声长叹，诸"
                     "多凡尘旧事已涌上心头，$N" HIW "终于将「修罗道」"
                     "参悟出来，从此再无疑虑。\n", ob);       
    
          write(HIC "你学会了「修罗道」。\n" NOR);
          ob->set("can_perform/lunhui-jian/xiuluodao", 1);
		}
		else 
		{
		 message_sort(HIR"\n$N只觉得人生如梦，生死无意，气血翻涌，一头栽倒在地!\n", ob);    
		 ob->die();
		 return 1;
		}
		
        ob->receive_damage("jing", 75);
        ob->start_busy(2);
        return 1;
}