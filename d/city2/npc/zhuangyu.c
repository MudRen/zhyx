// zhuangyu.c

inherit NPC;

#include <ansi.h>

int ask_weiwang();

void create()
{
	set_name("ׯ�ʳ�", ({ "zhuang yuncheng", "zhuang","yuncheng" }) );
	set("gender", "����" );
	set("age", 40);
	set("int", 28);
	set("long",
		"���Ǹ�����ʫ�飬ȴ���޲���֮����������\n"
             +"��༭����ʷ���ԡ�������֮�ٸ淢��ȫ�Ҵ��뾩�С�\n" );

	set("attitude", "peaceful");
	set_skill("literate", 100);
	set("noget", "ׯ�ʳ�̾�����Ҳ����ˣ����߰ɡ������ҵ����Ҽ����˰���\n");
	set("chat_chance", 5);
	set("chat_msg", ({
	        "ׯ�ʳ�˵����ֻ���ҵ������ģ������м��˽�Ҷ��������\n"
	        "˭�������Ĺ��εļһﾹȻ��ȥ�淢���ҡ���...\n",
	        "ׯ�ʳ�˵����˭Ҫ����֮��ץ��ׯ���ͺ��ˡ�\n",
	        "ׯ�ʳ�ͻȻ˵��: ������������Ҫ�������ߴ��кô�����\n",
	        "ׯ�ʳ�̾�˿�����˵������֪�������鷿�����ܣ�ֻ��ϧ�ҳ���ȥ����\n",
	        "ׯ�ʳ�˵����˭Ҫ�����ң���һ������֪���Ķ���������\n",
	}));
        set("inquiry", ([
		"����" : "���ݵ��鷿���б�����",
		"�鷿" : "�鷿���Ƿ�������ѧ�ʡ�",
		"��" :  "�ƶ��Ƿ���ʱ�����з���ġ�",
		"����" :  "�ƶ��Ƿ���ʱ�����з���ġ�",
		"����" :  "������һ�£�������һ�¾����ˡ�",
		"����" :  "�ǿɲ������������������ѧ�ʵġ�",
		"��֮��" :  "�����͵�ׯ��ȥ�кô���",
                "����" :  (: ask_weiwang :),
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob; 
	int i;

        if (! query("startroom") ||
            find_object(query("startroom")) != environment())
                return;

	ob = this_player();
	if (interactive(ob) && ! is_fighting())
        {
	        say("ׯ�ʳǹ���Ц�������������������ˣ���λ" +
                    RANK_D->query_respect(ob) + "�������ı���\n"
                    "�ɲ��ٰ����㲻��ϸ���ң�\n");
        }

	i = ob->query("weiwang");
        if (i < 20)
	{
	        i += 10;
                ob->set("weiwang",i);
	        message_vision(HIC "$N" HIC "�Ľ�����������ˣ�\n" NOR,
                               this_player());
	}
	command("tell " + ob->query("id") +
                " �����ڵĽ��������� " + i + "��");
}

int accept_object(object me, object ob)
{
	if (! present(ob, me))
                return notify_fail("��û�����������");

	if ((string)ob->query("id") != "book ming")
                return 0;

        message_vision("ׯ�ʳǴ��˿�������˵��ׯ���ھ��Ƕ����ߡ�\n", me);
        destruct(ob);
        return 1;
}
