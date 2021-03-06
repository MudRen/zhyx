#include <ansi.h>
inherit ROOM;

int sos(int,int);
void fresh(object ob);

void create()
{
        set("short", "赌场");
        set("long", @LONG
这里是进行赌野球拳对决的房间，四周的赌房里传出来吆五喝
六的赌博声。这个赌场规模虽算不上很大，但赌的种类却很齐
全，服务也非常周到。这里的墙上挂着一块牌子(paizi)。
LONG);
        set("item_desc", ([
                "paizi" : WHT "\n\n        ※※※※※※※※※※※※※※※\n"
                              "        ※                          ※\n"
                              "        ※         " NOR + HIW "决战规则" NOR + WHT "         ※\n"
                              "        ※                          ※\n"
                              "        ※      野球拳共有『石头』  ※\n"
                              "        ※  『剪刀』『布』三种招式  ※\n"
                              "        ※  其中石头克制剪刀，剪刀  ※\n"
                              "        ※  克制布，布克制石头。    ※\n"
                              "        ※  玩家和决斗者每次各出一  ※\n"
                              "        ※  招，克制者取胜，被克制  ※\n"
                              "        ※  者输，否则算平局。      ※\n"
                              "        ※                          ※\n"
                              "        ※  " NOR + HIW "开战" NOR + WHT "：                  ※\n"
                              "        ※                          ※\n"
                              "        ※      " NOR + HIY "shi(石)" NOR + WHT "             ※\n"
                              "        ※ " NOR + HIY "box  jian(剪)" NOR + HIY "  数量 货币" NOR + WHT " ※\n"
                              "        ※      " NOR + HIY "bu(布)   " NOR + WHT "           ※\n"
                              "        ※                          ※\n"
                              "        ※※※※※※※※※※※※※※※\n\n\n" NOR,
        ]));
        set("exits", ([
                "north" : __DIR__"duchang",
        ]));
        set("objects", ([
                "/u/xiner/npc/xiami" : 1,
                "/u/xiner/npc/zhuang" : 1,
        ]));
        set("no_fight", 1);
        set("coor/x",-9);
	set("coor/y",-10);
	set("coor/z",0);
	setup();
}

void init()
{
        add_action("do_box", "box");
}

int do_box(string arg)
{
        int wager, skill, lpoint, tpoint;
        string wtype1, wtype2, status;
        object mtype, me;
        mapping lrn;

        int min, max;
        min = 10000;
        max = 500000;

        me = this_player();

        if (me->query_temp("casino/mark"))
                return notify_fail(CYN "庄家叫道：干嘛？干嘛？现在还没轮到你呢。\n" NOR);

        if (! arg || sscanf(arg, "%s %d %s", wtype1, wager, wtype2) != 3)
                return notify_fail(CYN "庄家讥笑道：哪里有你那样比试野球拳的？\n" NOR);

        mtype = present(wtype2 + "_money", me);

        if (! mtype)
		return notify_fail("你身上没有这种货币。\n");

        if (wager < 1)
		return notify_fail("你要压多少啊？\n");

        if ((int)mtype->query_amount() < wager)
                return notify_fail("你身上没有那么多" + mtype->query("name") + "。\n");

        if (wager > 50)
		return notify_fail(CYN "庄家叹道：小赌宜情！大赌伤身！\n" NOR);

        if (wager * (mtype->query("base_value")) < min
           || wager * (mtype->query("base_value")) > max)
        	return notify_fail("你的赌注应至少一两黄金，最多黄金五十两。\n");

        if ((wtype1 != "shi") && (wtype1 != "jian") && (wtype1 != "bu") )
                return notify_fail("你准备出『石头』『剪刀』还是『布』？\n");

        me->set_temp("gamb_t",(me->query_temp("gamb_t") +1));

        if (me->query_temp("gamb_t") > 50)
        {
                call_out("fresh", 600, me);
                me->set_temp("casino/mark", 1);
                return notify_fail(CYN "庄家叫道：这位" + RANK_D->query_respect(me) +
                                   CYN "，你赌了那么久，也该换人了吧？\n" NOR);
        }

        message_vision("\n小虾米喝道：准备好了吧！\n一！二！三！", me);

	switch(random(3))
	{
	case 1:	//npc出 石头
		message_vision(HIW "\n小虾米喝道：『石头』！\n" NOR, me);
		if (wtype1 == "shi")
			 status = "equal";
		else if (wtype1 == "jian")
			 status = "lose";
		else if (wtype1 == "bu")
			 status = "win";
		break;

	case 2:	//npc出 剪刀
		message_vision(HIW "\n小虾米喝道：『剪刀』！\n" NOR, me);
		if (wtype1 == "shi")
			 status = "win";
		else if (wtype1 == "jian")
			 status = "equal";
		else if (wtype1 == "bu")
			 status = "lose";
		break;

	default ://npc出 布
		message_vision(HIW "\n小虾米喝道：『布』！\n" NOR, me);
		if (wtype1 == "shi")
			 status = "lose";
		else if (wtype1 == "jian")
			 status = "win";
		else if (wtype1 == "bu")
			 status = "equal";
		break;
	}

        if ( status == "equal")
	{
        	message_vision(me->query("name") + "这局打平！系统收走一"+ mtype->query("base_unit") + mtype->query("name") + "。\n", me);
                mtype->set_amount((int)mtype->query_amount() - 1);
                mtype->move(me, 1);
        } else
        if ( status == "lose")
	{
        	message_vision(me->query("name") + "输了" + chinese_number(wager) +
                               mtype->query("base_unit") + mtype->query("name") +
                               "。\n", me);
                mtype->set_amount((int)mtype->query_amount() - wager);
                mtype->move(me, 1);
        } else
	{
       		message_vision(me->query("name") + "赢了" + chinese_number(wager) +
                               mtype->query("base_unit") + mtype->query("name") +
                               "。\n", me);
                mtype->set_amount((int)mtype->query_amount() + wager);
                mtype->move(me, 1);
		if (me->query_skill("yeqiu-quan") < 180 && random(9)==1)
		{
	        	message_vision("$N通过这局比试对野球拳法有所领悟！\n", me);
			me->improve_skill("yeqiu-quan", 10000);
		}
        }
        return 1;
}

void fresh(object ob)
{
	if (! objectp(ob)) return;
        ob->delete_temp("gamb_t");
        ob->delete_temp("casino/mark");
}

int sos(int lower, int upper)
{
        int x,y;
        x = 0;

        while (lower <= upper)
        {
                y = lower * lower;
                x += y;
                lower++;
        }
        return x;
}
