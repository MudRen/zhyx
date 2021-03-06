#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "\n\n                地        狱        道" NOR);
        set("long", HIR "\n"
"极寒极冷，受尽各种折磨，毫无喜乐之所。若与人间比较，第\n"
"一狱以人间三千七百五十年为一年，在此须受困一万年，相当\n"
"于人间一百三十五亿年。而到了第十八地狱，便以亿亿亿年为\n"
"单位，如此长期的受刑可谓是名符其实的万劫不复。你可以在\n"
"这里参悟(canwu)。\n\n" NOR);

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

        if (ob->query("can_perform/lunhui-jian/diyudao"))
        {
                write("你已经参悟透了地狱道。\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("你未修前世，无法参透地狱道。\n");
                return 1; 
        } */

        if (c_skill < 300)
        {
                write("你至少要三百级轮回剑，才能参透地狱道。\n");
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
		
		if (random(3) == 1)
		{
        message_sort(HIW"\n$N" HIW"趺坐静思，猛然间一声长叹，诸"
                     "多凡尘旧事已涌上心头，$N" HIW "终于将「地狱道」"
                     "参悟出来，从此再无疑虑。\n", ob);       
    
          write(HIC "你学会了「地狱道」。\n" NOR);
          ob->set("can_perform/lunhui-jian/diyudao", 1);
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