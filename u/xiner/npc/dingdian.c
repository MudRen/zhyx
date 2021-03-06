inherit NPC;
#include <ansi.h>

mixed ask_wu();
mixed ask_ying();

void create()
{
        set_name("丁典", ({ "ding dian", "ding" }));
        set("long", 
                "这人满脸虬髯，头发长长的直垂至颈，衣衫破烂不堪，简直如同荒山中的野人。\n");
        set("gender", "男性");
        set("age", 35);

        set_skill("force", 300);
        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("shenzhaojing", 300);
        set_skill("feiyan-zoubi", 300);

        map_skill("force","shenzhaojing");
        map_skill("dodge","feiyan-zoubi");
        map_skill("unarmed","shenzhaojing");
        map_skill("parry","shenzhaojing");
        prepare_skill("unarmed","shenzhaojing");
        set("max_neili",5000);
        set("neili",5000);
        set("jiali",100);

        set("combat_exp", 800000);
        set("shen_type", 1);

        set("inquiry", ([
                "无影拳舞" : (: ask_wu :),
                "无影神拳" : (: ask_ying :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_object(object me, object obj)
{

        if ((string)obj->query("id")=="lu juhua") 
	{
		message("vision",me->name()+"给丁典一盆绿菊花。\n",environment(me),({me}));
		command("touch "+me->query("id"));
		command("say 这位"+RANK_D->query_respect(me)+"是霜华派来送信的吧。");
		command("say 我也没别的东西可以谢你。");
                command("say 只有一套『神照经』，你可以试着看能学会不！");
                me->set("can_learn/dingdian/shenzhaojing", 1);
                destruct(obj);
                return 1;
        }
        return 0;
}

int recognize_apprentice(object ob, string skill)
{
        if (! ob->query("can_learn/dingdian/shenzhaojing"))
        {
                command("say 我与你毫无瓜葛，你问这些干嘛！\n");
                return -1; 
        }

        if (skill != "shenzhaojing")
        {
                command("killair");
                command("say 这是什么，我可不会。");
                return -1;
        }

        if (ob->query_skill("shenzhaojing", 1) > 180)
        {
                command("say 好了，剩下的需要你自己领悟了。");
                return -1;
        }
        return 1;
}

mixed ask_wu()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shenzhaojing/wu"))
                return "能教的已经教完了，还来找我干嘛？";

        if (! me->query("can_learn/dingdian/shenzhaojing"))
                return "我与你毫无瓜葛，你问这些干嘛！";

        if (me->query_skill("shenzhaojing", 1) < 250)
                return "你对『神照经』的领悟有限这招恐怕不能理解！";

        message_vision(HIW "$n" HIW "一声暴喝，将神照功功力聚"
			"之于拳，携着雷霆万钧之势向连环$N" HIW "攻出。\n"
			"$N" HIW "大骇，硬接了这一招，只感内息翻腾"
			"，全身骨骼快要散架一般。突然目光一亮"
			"，似乎明白了什么。\n" NOR,
			me, this_object());

        command("hmm");
        tell_object(me, HIC "你学会了「无影拳舞」这一招。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 150000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 150000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 150000);
        if (me->can_improve_skill("shenzhaojing"))
                me->improve_skill("shenzhaojing", 150000);
        me->set("can_perform/shenzhaojing/wu", 1);
        return 1;
}

mixed ask_ying()
{
        object me;

        me = this_player();

        if (me->query("can_perform/shenzhaojing/ying"))
                return "能教的已经教完了，还来找我干嘛？";

        if (! me->query("can_learn/dingdian/shenzhaojing"))
                return "我与你毫无瓜葛，你问这些干嘛！";

        if (me->query_skill("shenzhaojing", 1) < 200)
                return "你对『神照经』的领悟有限这招恐怕不能理解！";

        message_vision(HIW "$n" HIW "倏然跃近，无声无影击出"
			"一拳，去势快极，拳影重重叠叠，直袭"
			"$N" HIW "而去。\n$N" HIW "大骇，硬"
			"接了这一招，只感内息翻腾，全身骨骼"
			"快要散架一般。突然目光一亮，似乎明"
			"白了什么。\n" NOR,
			me, this_object());

        command("hmm");
        tell_object(me, HIC "你学会了「无影神拳」这一招。\n" NOR);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 150000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 150000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 150000);
        if (me->can_improve_skill("shenzhaojing"))
                me->improve_skill("shenzhaojing", 150000);
        me->set("can_perform/shenzhaojing/ying", 1);
        return 1;
}