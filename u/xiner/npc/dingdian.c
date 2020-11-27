inherit NPC;
#include <ansi.h>

mixed ask_wu();
mixed ask_ying();

void create()
{
        set_name("����", ({ "ding dian", "ding" }));
        set("long", 
                "����������ף�ͷ��������ֱ���������������ò�������ֱ��ͬ��ɽ�е�Ұ�ˡ�\n");
        set("gender", "����");
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
                "��Ӱȭ��" : (: ask_wu :),
                "��Ӱ��ȭ" : (: ask_ying :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_object(object me, object obj)
{

        if ((string)obj->query("id")=="lu juhua") 
	{
		message("vision",me->name()+"������һ���̾ջ���\n",environment(me),({me}));
		command("touch "+me->query("id"));
		command("say ��λ"+RANK_D->query_respect(me)+"��˪���������ŵİɡ�");
		command("say ��Ҳû��Ķ�������л�㡣");
                command("say ֻ��һ�ס����վ�������������ſ���ѧ�᲻��");
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
                command("say ��������޹ϸ�������Щ���\n");
                return -1; 
        }

        if (skill != "shenzhaojing")
        {
                command("killair");
                command("say ����ʲô���ҿɲ��ᡣ");
                return -1;
        }

        if (ob->query_skill("shenzhaojing", 1) > 180)
        {
                command("say ���ˣ�ʣ�µ���Ҫ���Լ������ˡ�");
                return -1;
        }
        return 1;
}

mixed ask_wu()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shenzhaojing/wu"))
                return "�̵ܽ��Ѿ������ˣ��������Ҹ��";

        if (! me->query("can_learn/dingdian/shenzhaojing"))
                return "��������޹ϸ�������Щ���";

        if (me->query_skill("shenzhaojing", 1) < 250)
                return "��ԡ����վ����������������п��²�����⣡";

        message_vision(HIW "$n" HIW "һ�����ȣ������չ�������"
			"֮��ȭ��Я���������֮��������$N" HIW "������\n"
			"$N" HIW "�󺧣�Ӳ������һ�У�ֻ����Ϣ����"
			"��ȫ�������Ҫɢ��һ�㡣ͻȻĿ��һ��"
			"���ƺ�������ʲô��\n" NOR,
			me, this_object());

        command("hmm");
        tell_object(me, HIC "��ѧ���ˡ���Ӱȭ�衹��һ�С�\n" NOR);
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
                return "�̵ܽ��Ѿ������ˣ��������Ҹ��";

        if (! me->query("can_learn/dingdian/shenzhaojing"))
                return "��������޹ϸ�������Щ���";

        if (me->query_skill("shenzhaojing", 1) < 200)
                return "��ԡ����վ����������������п��²�����⣡";

        message_vision(HIW "$n" HIW "ٿȻԾ����������Ӱ����"
			"һȭ��ȥ�ƿ켫��ȭӰ���ص�����ֱϮ"
			"$N" HIW "��ȥ��\n$N" HIW "�󺧣�Ӳ"
			"������һ�У�ֻ����Ϣ���ڣ�ȫ�����"
			"��Ҫɢ��һ�㡣ͻȻĿ��һ�����ƺ���"
			"����ʲô��\n" NOR,
			me, this_object());

        command("hmm");
        tell_object(me, HIC "��ѧ���ˡ���Ӱ��ȭ����һ�С�\n" NOR);
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