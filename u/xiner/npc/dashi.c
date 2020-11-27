//���Դ�ʦ(������ӡ�;�������)

#include <ansi.h>
inherit  NPC;

mixed ask_zhenyan();
mixed learn_skill();
mixed learn_skill2();

void create()
{
	set_name("���Դ�ʦ", ({ "zhenyan dashi", "dashi" }));
	set("title", "ɳ�Ż���");
//	set("nickname", HIR "�ٱ����߽�������ǰ" NOR);
	set("gender", "����");
	set("age", 80);
	set("long", @LONG
����ɮ��ü��ף�����ׯ����͸�����֮����������һ��������
���ϴ���˫Ŀ�뿪��գ������������˼��е��еĸ��ˡ�
LONG );
        set("gender", "����" );
        set("attitude", "friendly");

        set("max_neili", 10000);
        set("neili", 10000);
        set("max_jing", 10000);
        set("jing", 10000);
        set("max_qi", 8000);
        set("qi", 8000);
        set("jingli", 8000);
        set("max_jingli", 8000);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12500000);

	set_skill("force", 500);
	set_skill("yijinjing", 500);
        set_skill("dodge", 500);
        set_skill("shaolin-shenfa", 500);
        set_skill("hand", 500);
        set_skill("jiuzi-zhenyan", 500);
        set_skill("shou-yin", 500);
        set_skill("parry", 500);
        set_skill("jingang-buhuaiti", 500);
        set_skill("buddhism", 300);
        set_skill("lamaism", 300);
        set_skill("literate", 300);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand", "jiuzi-zhenyan");
        map_skill("parry", "jingang-buhuaiti");
	prepare_skill("strike", "jiuzi-zhenyan");

        set("jiali", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200); 

        set("inquiry", ([ 
//		"��������" : (: ask_zhenyan :), 
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({
			(: random_move :),
			CYN "���Դ�ʦ�����̾�˿�����\n" NOR,
				}));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
        carry_object("d/city/obj/jiasha")->wear(); 
}

void random_move()
{
	if (time() - query("born_time") > 800)
	{
		message_vision("$NƮȻ��ȥ��\n", this_object());
		destruct(this_object());
		return;
	}
        NPC_D->random_move(this_object());
}

void init()
{
    add_action("do_answer", "answer");
}

int accept_object(object me, object ob)
{
        if (ob->query("id") != "buchen sheli")
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        } else
        {
       	        destruct(ob);
       	        command("say ��лʩ������ʦ�ֵ�������");

		if(!me->query("can_learn/zhenyan/shou-yin") && me->query("reborn"))
		{
	                me->set("can_learn/zhenyan/shou-yin", 1);
			call_out("learn_skill",2);
                	return -1;
		} else
		{
        	        command("thank " + me->query("id"));
	                return -1;
		}
        }
}

mixed learn_skill()
{
	object me = this_player();
	command("buddhi " + me->query("id"));
	message_vision(WHT"���Դ�ʦ��$N˵������ʩ���������Ե������ƶɮ��һ�۷𷨣���\n"NOR, me);                
	write(HIG"���Դ�ʦ����˵������ʩ����֪��ν�������ԣ� \n"NOR
		"(����answer xxx ����)\n" NOR);
	me->set_temp("sun/zhenyan/ask1",1); //���˲���answer
	return 1;
}

mixed do_answer(string arg)
{
	object me = this_player();
	if ( !arg ) return command("say ��Ҫ�ش�ʲô?");
	if ( !me->query("can_learn/zhenyan/shou-yin") ) return 0;
	if (! me->query_temp("sun/zhenyan/ask1") ) return 0; //��û����!

	if ( arg == "�ٱ����߽�������ǰ")
	{
		write(HIG"���Դ�ʦ���������������Ÿ��֣������Զ���������ĵ��ұ��䡶�����ӡ�\n"
			"�ھ�ĵ���ƪ��ԭ��Ի�����ٱ����ߣ�������ǰ�С�������֮���������١���\n" NOR);
		call_out("learn_skill2",2);
		return 1;
	}
	command("sigh");
	command("say ʩ�������Ե��̫ǳ����ذɣ�");
	me->delete_temp("sun/zhenyan/ask1"); //���һ�ξͽ���
	return 1;
}

mixed learn_skill2()
{
        object me = this_player();
        int lv;

	me->delete_temp("sun/zhenyan/ask1");

	if (me->query("shou-yin"))
		return command("say �㲻���Ѿ�ѧ����ô��"); 

        if (!me->query("can_learn/zhenyan/shou-yin"))
		return command("say ʩ�������Ե��̫ǳ����ذɣ�"); 

        if (me->query_skill("shou-yin", 1))
		return command("say �Ҹý̵Ķ��Ѿ������ˣ�ʣ�µľͿ����ڼ���ϰ�ˣ�");

	if (me->query_skill("yinyang-shiertian", 1)||me->query_skill("paiyun-zhang", 1)
		||me->query_skill("lunhui-jian", 1)||me->query_skill("fengshen-tui", 1)
		||me->query_skill("fuyu-shengong", 1))
		return command("say �����Ѿ�ѧ���˸�����书������Ŵ���ӡ�Ѿ����ʺ���ѧϰ�ˣ�");		

	if (me->query("str") < 34)
		return command("say ��ı����������޷���ϰ��ӡ��\n");

        if (me->query_skill("hand", 1) < 200)
		return command("say ������ַ���Ϊ���㣬�޷����������ӡ��");

        if (me->query_skill("buddhism") < 100 || me->query_skill("lamaism") < 100)
		return command("say ��ϧʩ�����ҷ���Ե����������������Դ���ӡ��");

        command("nod");
        command("say ��Ȼ����ƶɮ�ͽ����Դ���ӡ�����㣬��ɿ����ˣ�");
        message_vision(HIC "$N" HIC "���������ԡ���ӡ����ͷ��β��$n" HIC "��ʾ��һ�飡\n" NOR,
                       this_object(), me);
        command("haha");
        tell_object(me, HIG "��ѧ���ˡ���ӡ����\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("buddhism"))
                me->improve_skill("buddhism", 1500000);
        if (me->can_improve_skill("lamaism"))
                me->improve_skill("lamaism", 1500000);
        command("say ����˶��پͿ���������ˣ�ʣ�µľͿ����Լ���ȥ��ϰ��");
        lv = me->query("int");
        if (lv <= 30)
               me->set_skill("shou-yin", lv);
        else
               me->set_skill("shou-yin", 30 + (lv - 30) * 2);
    	me->set("shou-yin",1);
        return 1;
       
}
