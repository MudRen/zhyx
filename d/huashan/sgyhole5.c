// Room: /d/huashan/sgyhole.c

inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
这是一个毫不起眼的山洞，但是里面的石壁上却画满了五
岳剑派所有已经失传的精妙绝招。花岗岩石壁(wall)上很多小
人，全是用利器刻制，想见当初运力之人内力十分深厚。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "south"   : __DIR__"sgyhole4",

        ]));
        set("item_desc", ([ 
            "wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L
TEXT
        ]));

        setup();
}
void init()
{
        add_action("do_mianbi", "mianbi");
}

int do_mianbi()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("wuyue-shenjian", 1);

		if (ob->query("family/family_name") != "华山派"
		&& ob->query("family/family_name") != "嵩山派"
		&& ob->query("family/family_name") != "衡山派")
		{
			write("你非五岳剑派中人哪里能领悟其中精妙的招式。\n", ob);
                return 1; 
		}

		if (!ob->query("can_perform/huashan-jian/xian"))
		{
			write("你没有领悟到华山剑法的绝招：夺命连环三仙剑，没有办法领悟五岳神剑。\n", ob);
            return 1; 
		}			   

		if (!ob->query("can_perform/wushen-jian/shen"))
		{
			write("你没有领悟到衡山五神剑的绝招：五神朝元势，没有办法领悟五岳神剑。\n", ob);
            return 1; 
		}			   

		if (!ob->query("can_perform/poyang-jian/long"))
		{
			write("你没有领悟到嵩山破阳冷光剑的绝招：天外玉龙，没有办法领悟五岳神剑。\n", ob);
            return 1; 
		}  
		

		if (ob->query_skill("martial-cognize", 1) < 300)
		{
			write("你觉得五岳神剑极其深奥，依照自己的武学修养难以理解。\n", ob);
            return 1; 
		}               

        if ((int)ob->query("max_neili") < 5000)
		{
			write("你的内力修为不够，没有办法练五岳神剑。\n", ob);
            return 1; 
		}               

        if ((int)ob->query_skill("sword", 1) < 300)
		{
			write("你的基本剑法太差，没有办法练五岳神剑。\n", ob);
            return 1; 
		}  

        if (! ob->can_improve_skill("wuyue-shenjian"))
        {
                write("你的实战经验不足，无法领悟石壁内容。\n");
                return 1; 
        }

        if (ob->query("jing") < 50)
        {
                write("你精力不能集中，现在无法领悟石壁内容。\n");
                return 1; 
        }

        if (c_skill > 300)
        {
                write("你觉得石壁内容太肤浅了。\n");
                return 1;
        }

        if (ob->is_busy()) 
              { 
                     write("你目前正忙呢，现在无法领悟石壁内容。\n"); 
                      return 1;  
              } 

        message_vision("$N面对着石壁趺坐静思，良久，对「五岳神剑」"
                        "似有所悟。\n", ob);
        ob->improve_skill("wuyue-shenjian", ob->query("int"));
        ob->receive_damage("jing", 45);
        ob->start_busy(random(2));
        return 1;
}
