#include <ansi.h>
inherit NPC;

object room = 0;

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();

void create()
{
	set_name( "СϺ��", ({ "xiao xiami", "xiami" }) );
	set("long", "���������ǽ�ӹȺ�����������λСϺ�ס�\n");
	set("attitude", "friendly");
	set("title", HIR "�޵�" NOR);
	set("nickname", HIG "Ұ��ȭ" NOR);
        set("force_factor", 30);
        set("max_kee", 3000);
        set("max_sen", 3000);
        set("eff_gin", 3000);
        set("eff_kee", 3000);
        set("eff_sen", 3000);
        set("kee", 3000);
        set("sen", 3000);
        set("max_force", 3000);
        set("force", 3000);
        set("max_mana", 3000);
        set("mana", 3000);
	set("age", 18);
	set_temp("apply/damage",600);
        set("gender", "����" );
	set("str", 40);
	set("cor", 35);
	set("cps", 30);
	set("per",10);
	set("max_force",5000);
	set("force_factor",40);
	set("combat_exp", 13000000);

	set_skill("force", 500);
	set_skill("yijinjing", 500);
        set_skill("dodge", 500);
        set_skill("feiyan-zoubi", 500);
        set_skill("unarmed", 500);
        set_skill("yeqiu-quan", 500);
        set_skill("parry", 500);
        set_skill("jingang-buhuaiti", 500);
        set_skill("literate", 300);

        map_skill("force", "yijinjing");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "yeqiu-quan");
        map_skill("parry", "jingang-buhuaiti");
	prepare_skill("unarmed", "yeqiu-quan");

        set("inquiry", ([ 
                "Ұ��ȭ"   : "Ұ��ȭ����ʮ��Ҳ�������޵У�",
		"ʯͷ" : (: ask_skill1 :), 
		"����" : (: ask_skill2 :), 
		"��" : (: ask_skill3 :), 
		"��˫����" : (: ask_skill4 :), 
        ]));

	setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/shitou"))
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "�㻹����Ұ��ȭ�أ�������ʲô�ң�";

        if (me->query_skill("yeqiu-quan", 1) < 250)
                return "���Ұ��ȭ����ҲҪ����������ѧ�����У�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "һ�ۣ����ֹ���һȭ��$N" HIY
                     "������ƽƽ���������棬��֪�������ֵ���һ˲��ŷ���$n" HIY
                     "ȭͷ�Ѿ�������ȭͷ������һ��ʯͷ��һ����ʯ��$N" HIY "��ʱ��Ҳ�ѳֲ�ס����"
                     "��һȭ���ý�����ת����Ȧ���ò����ײ�ͣ��������\n\n" NOR,
                     me, this_object()); 

        command("say ���ˣ����Լ���ȥ��ϰ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�ʯͷ����\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/shitou", 1);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/jiandao"))
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "�㻹����Ұ��ȭ�أ�������ʲô�ң�";

        if (me->query_skill("yeqiu-quan", 1) < 250)
                return "���Ұ��ȭ����ҲҪ����������ѧ�����У�";

        message_sort(HIY "\n$n" HIY "ʳָ��ָһ�֣����ֹ���һ�С�$N" HIY
                     "������ƽƽ���������棬��֪�������ֵ���һ˲��ŷ���$n" HIY
                     "�������ľ�Ȼ�Ѿ��������������$N" HIY "ʱ����һ�����ٱ�"
                     "��һ�л��У��·��������������ں����Ķ���\n\n" NOR,
                     me, this_object()); 

        command("say ���ˣ����Լ���ȥ��ϰ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ���������\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/jiandao", 1);
        return 1;
}
mixed ask_skill3()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/bu"))
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "�㻹����Ұ��ȭ�أ�������ʲô�ң�";

        if (me->query_skill("yeqiu-quan", 1) < 250)
                return "���Ұ��ȭ����ҲҪ����������ѧ�����У�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "һ�ۣ����ֹ���һ�ơ�$N" HIY
                     "������ƽƽ���������棬��֪�������ֵ���һ˲��ŷ���$n" HIY
                     "��һ�ƾ�Ȼ�������һ�㣬$N" HIY "�������ˣ���Ȼ��"
                     "��һ�ƻ�����ͷת�򣬺ò����ײŻع�������\n\n" NOR,
                     me, this_object()); 

        command("say ���ˣ����Լ���ȥ��ϰ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/bu", 1);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/luan"))
                return "��һ���Ҳ����Ѿ��̹������𣿻�����ʲô��";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "�㻹����Ұ��ȭ�أ�������ʲô�ң�";

        if (me->query_skill("yeqiu-quan", 1) < 500)
                return "ֻ��Ұ��ȭ����ʮ��Բ���Ժ����ѧ�����У�";

        message_sort(HIY "\n$n" HIY "���׿�������$N" HIY "һ�ۣ���û���κζ�����$N" HIY
                     "ȴ��ʱ���ã�����¾�Ȼû���κ��书�ܹ��еù����ڵ�СϺ��"
                     "$N" HIY "����һ��ʱ�������ڻع���������Ц�������������ˣ���\n\n" NOR,
                     me, this_object()); 

        command("say ���ˣ����Լ���ȥ��ϰ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ���˫���衹��\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/luan", 1);
        return 1;
}