#include <ansi.h>

inherit NPC;
//inherit F_UNIQUE;
inherit F_GUARDER;

void create()
{
        set_name("��Ѱ��", ({ "li xunhuan", "li", "xunhuan"}));
        set("long", "    һ�����Ű������������ӣ����ε�����\n" 
                    "����Ѫɫ���ƺ����ɫ���ȶ��԰ס�������\n"
                    "����һ��С�������������һ��ľ�ˡ���Χ\n"
                    "������һ�����·𶼿�������\n"); 
        set("nickname", HIR "С��̽��" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 34);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 40);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 100000);
        set("max_jing", 3000);
        set("max_neili", 60000);
        set("neili", 60000);
        set("jiali", 250);
        set("combat_exp", 50000000);

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "��Ѱ�������̾�˿�����\n" NOR,
                CYN "��Ѱ�������ص�������е�ľż��\n" NOR,
                CYN "��Ѱ�������˼�����\n" NOR,
                CYN "��Ѱ�������ȡ��ȡ���\n" NOR,
        }));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: perform_action, "hand.jiuzi" :),
                (: perform_action, "dodge.guiyuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("dodge", 700);
        set_skill("parry", 700);
        set_skill("unarmed", 700);
        set_skill("throwing", 700);
        set_skill("xiaoli-feidao", 700);
        set_skill("changquan", 700);
        set_skill("shexing-lifan", 700);
        set_skill("force", 700);
        set_skill("yijinjing", 700);
        set_skill("hand", 500);
        set_skill("jiuzi-zhenyan", 500);
        set_skill("literate", 250);
        set_skill("buddhism", 250);
        set_skill("lamaism", 250);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "changquan");
        map_skill("throwing", "xiaoli-feidao");
        map_skill("unarmed", "changquan");
        map_skill("hand", "jiuzi-zhenyan");

        prepare_skill("hand", "jiuzi-zhenyan");
        
        //set("env/immortal", 1);

        set_temp("apply/damage", 300);
	set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 300);
        set("apply/dodge", 400);

        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/renou");       
        set_temp("handing", carry_object(__DIR__"obj/feidao"));       
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
            query("jing") < 1000 ||
            query("neili") < 20000)
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
