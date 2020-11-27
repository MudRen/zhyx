#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

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
        set("int", 35);
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
                (: perform_action, "dodge.guiyuan" :),
                (: exert_function, "powerup" :),
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
        set_skill("literate", 250);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "changquan");
        map_skill("throwing", "xiaoli-feidao");
        map_skill("unarmed", "changquan");
        
        //set("env/immortal", 1); 

        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/renou");       
        set_temp("handing", carry_object(__DIR__"obj/feidao"));       
}

