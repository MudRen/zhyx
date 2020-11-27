#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
#define TONGZHI "/clone/lonely/book/tongzhi"

void create()
{
        set_name("С˫��", ({ "xiner's shuanger" }));
        set("long", "����һ��ʮ���������Ů,��Լʮ��������͡�\nһ��ѩ�׵�����,ü����С,Ц���绨,��Ц�����ؿ����㡣\n"); 
        set("title", HIW "ܰ����Ѿ��" NOR);
	set("nickname", HIM "������˫" NOR);
	set("gender", "Ů��");
	set("age", 15);
	set("attitude", "peaceful");
	set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 35);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 25000);
	set("jiali",10);
        set("neili", 25000);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: perform_action, "hand.jiuzi" :),
                (: perform_action, "unarmed.zhi" :),
                (: perform_action, "unarmed.zhua" :),
                (: perform_action, "unarmed.zhang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        set_skill("force", 550);
        set_skill("jiuyin-shengong", 500);
        set_skill("dodge", 550);
        set_skill("zhuangzi-wu", 550);
        set_skill("parry", 500);
        set_skill("unarmed", 550);
        set_skill("hand", 550);
        set_skill("jiuzi-zhenyan", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("literate", 200);
        set_skill("buddhism", 260);
        set_skill("lamaism", 260);
        set_skill("count", 100);

        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "jiuzi-zhenyan");
        map_skill("unarmed", "jiuyin-shengong");
		
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 500);

        prepare_skill("hand", "jiuzi-zhenyan");
        prepare_skill("unarmed", "jiuyin-shengong");

        setup();

	carry_object("/d/city/npc/cloth/feature")->wear(); 

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
	if (time() - query("born_time") > 300)
	{
		message_vision("$N����һЦ��ƮȻ��ȥ��\n", this_object());
	//	CHANNEL_D->do_channel( this_object(), "chat", "���������´������棡\n");
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

	if (ob->query_temp("tzs"))
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "����"
                               "���Ѿ�����֪ͨ���������\n" NOR,
                               this_object(), ob);
                return -1;
        }

	if (ob->query("reborn"))
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "����"
                               "�㲻���Ѿ�ת������ô��\n" NOR,
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

/*	if (me->query("shen") < 0)
	{
		tell_object(me, HIC "\n˫��˵�������������䲻����Ķ��֣����ն���Ϊ���ֳ�����\n" NOR);
		return;
	}
*/

        ob = find_object(TONGZHI);
        if (! ob) ob = load_object(TONGZHI);

        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (!environment(ob))
	{
        	command("say �ðɣ�����ı��»������������ݡ�ת��֪ͨ�顱�͸����ˣ�");
	        command("say ���������ϲ�Ҫ����Ŷ����Ȼ������");
		ob->move(me);
		me->set_temp("tzs",1);
		::lost();
        }else
	{
		if (objectp(owner))
			tell_object(me, HIC "\n�ҸողŸ�"HIR + owner->query("name") + HIC "Ū��һ��֪ͨ�飬��Ȼ������ɣ���\n\n" NOR);
		else
		        tell_object(me, HIC "\n˫��˵�������㹦�򲻴���ƷҲ�����ԡ���ϧ֪ͨ�����ڻ�ûŪ�ã��㻹�õ�һ�������\n\n" NOR);
        	::lost();
	}
}

void unconcious()
{
        say( HIC"˫���ӻ����ó�һ�����������������������������\n"NOR);
        say( HIC"Ƭ��֮�䣬˫���ָֻ��˾���\n"NOR);
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