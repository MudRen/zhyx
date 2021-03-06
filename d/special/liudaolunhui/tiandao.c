#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "\n\n                天        极        道" NOR);
        set("long", HIW "\n"
"茫茫云海，渺无边际。四周金光散布，祥云朵朵，远处有凤凰\n"
"盘绕，麒麟逐戏。耳边传来阵阵梵音，令你茫然不知所措。天\n"
"道众生遍及欲界、色界及无色界三界。欲界有六欲天，色界有\n"
"四禅十八天，无色界四天，共有二十八天。你可以在这里参悟\n"
"(canwu)。\n\n" NOR);
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

        if (ob->query("can_perform/lunhui-jian/tiandao"))
        {
                write("你已经参悟透了天极道。\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("你未修前世，无法参透天极道。\n");
                return 1; 
        }
 */
        if (c_skill < 700)
        {
                write("你至少要七百级轮回剑，才能参透天极道。\n");
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
		
		if (random(5) == 1)
		{
        message_sort(HIW"\n$N" HIW"趺坐静思，猛然间一声长叹，诸"
                     "多凡尘旧事已涌上心头，$N" HIW "终于将「天极道」"
                     "参悟出来，从此再无疑虑。\n", ob);       
    
          write(HIC "你学会了「天极道」。\n" NOR);
          ob->set("can_perform/lunhui-jian/tiandao", 1);
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