#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
#define SHELI "/u/xiner/obj/sheli"

void create()
{
        set_name("������", ({ "xu ziling", "xu", "ziling"}));
        set("long", "һ�����εİ������ꡣ\n"); 
        set("title", HIY "����˫��" NOR);
        set("gender", "����");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 30);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 25000);
	set("jiali",150);
        set("neili", 25000);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 500);
        set_skill("hand", 500);
        set_skill("parry", 500);
        set_skill("unarmed", 500);
        set_skill("shou-yin", 500);
        set_skill("zhuangzi-wu", 500);
        set_skill("force", 500);
        set_skill("changsheng-jue", 500);
        set_skill("blade", 500);
        set_skill("badao-daofa", 500);
        set_skill("literate", 200);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "badao-daofa");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "shou-yin");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");
		
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);
        set_temp("apply/armor", 600);

        prepare_skill("hand", "shou-yin");

        setup();

        carry_object("/d/zhuanshi/sky/npc/obj/cloth1")->wear();
        carry_object("/d/zhuanshi/sky/npc/obj/hands")->wear();

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({(: random_move :)}));
                set("born_time", time());
                keep_heart_beat();
        }
}

void random_move()
{
	if (time() - query("born_time") > 600)
	{
		message_vision("$NƮȻ��ȥ��\n", this_object());
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�е������ȱ�"
                               "���Ҵ�����ܾ��������ġ�\n" NOR,
                               this_object(), ob);
                return -1;
        }       

        if (query("qi") < 10000 ||
            query("jing") < 10000 ||
            query("neili") < 10000)
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "��������"
                               "��̫���ˣ�����Ъ�����˵�ɡ�\n" NOR,
                               this_object(), ob);
                return -1;
        }
  

        message_vision(HIW "$N" HIW "��ϲ�����úúã�����������������"
                       "���Ȼ��Ȼ���\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "���˿�$n" CYN "���ٺ�Ц�������ˮ"
                       "ƽ̫���ˣ�Ҫ�ú��������ú�������\n" NOR,
                       this_object(), ob);
        ::win();
}


void lost()
{
        object me;
        object ob;
	object owner;

        if (! objectp(me = query_competitor()))
                return;

	if (me->query("shen") < 0)
	{
		tell_object(me, HIC "\n������˵�������������䲻����Ķ��֣����ն���Ϊ���ֳ�����\n" NOR);
		return;
	}

	if (me->query_skill("yinyang-shiertian", 1)||me->query_skill("paiyun-zhang", 1)
		||me->query_skill("lunhui-jian", 1)||me->query_skill("fengshen-tui", 1)
		||me->query_skill("fuyu-shengong", 1))
	{
		tell_object(me, HIC "\n������˵�����������书���С�Ӳ��Ƕ��֣�\n" NOR);
		return;
	}

        ob = find_object(SHELI);
        if (! ob) ob = load_object(SHELI);

        if (!environment(ob))
	{
	        ob->move(this_object());
        	command("say ��������Ӿ�ת������ɣ�������ҵ����Դ�ʦ������һ��������");
	        command("say ����һ�ж�Ҫ������Ե���֣�");
	        command("give sheli to " + me->query("id"));
		::lost();
        }
        tell_object(me, HIC "\n������˵�������㹦�򲻴���ƷҲ�����ԡ���ϧ�������Ѿ������������ˡ���\n\n" NOR);
        ::lost();
}

void unconcious()
{
        say( HIC"������˵�����������û��ô���ס���˵��ʹӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬�������ָֻ��˾��񣬡��ٺ١���Ц��������\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
	remove_all_enemy(1);
}

void die()
{
        unconcious();
}