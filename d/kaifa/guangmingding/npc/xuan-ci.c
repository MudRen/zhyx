// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("���ȴ�ʦ", ({
                "xuanci dashi",
                "xuanci",
                "dashi",
        }));
        set("long",
                "����һλ�����ü����ɮ����һϮ��˿������ġ�\n"
                "������������ͣ���ȴ�����⣬Ŀ�̴�Ц���Ե��������㡣\n"
        );

        set("title", HIY"�����·���"NOR);
        set("gender", "����");

        set("age", 70);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 1400);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 50);
        set("combat_exp", 1450000);
        set("score", 500000);

        set_skill("force", 170);
        set_skill("hunyuan-yiqi", 170);
        set_skill("dodge", 160);
        set_skill("shaolin-shenfa", 160);
        set_skill("finger", 170);
        set_skill("strike", 170);
        set_skill("hand", 160);
        set_skill("claw", 160);
        set_skill("parry", 160);
        set_skill("nianhua-zhi", 170);
        set_skill("sanhua-zhang", 170);
        set_skill("fengyun-shou", 160);
        set_skill("longzhua-gong", 160);
        set_skill("buddhism", 160);
        set_skill("literate", 160);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
void init()
{       
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("killing");
                call_out("killing", 1, ob);
        }
}

void killing(object ob)
{       
        object me;
        object obj=this_object();

        me = this_player();
        if (! ob || environment(ob) != environment())
                return;
                switch(random(2))
        {
        case 0:
//                say(CYN "���ȴ�ȵ�������ħ��צ������������������\n" NOR);    
        set("anti",me);
                me->kill_ob(obj);
                  kill_ob(me);
                break;
        case 1:
 //               say(CYN "���ȴ�̾��������һ�����������ˣ�\n" NOR);
                set("anti",me);
                  kill_ob(me);
                me->kill_ob(obj);
                break;
        }
}


void killed_enemy()
{
        if (objectp(query("anti")))
        {
                shout(HIR "\n��������֮ս��" HIW "���ȴ�ʦ������" HIC + query("anti")->name() + HIW "ά��ħ�̣������������װ�����������\n" NOR );

        }
}


void die()
{
        if (objectp(query("anti")))
        {
        query("anti")->set_temp("skybook/tulong/guangmingding/shaolin",1);      
           message_vision( HIY "\n���ȴ�̾һ�������˰��ˣ���֮�������µ��������ȥ��\n" NOR,
                                   this_object(),query("anti"));                 
        if ( query("anti")->query_temp("skybook/tulong/guangmingding/shaolin") > 0  
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/emei") > 0
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/chengkun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/kunlun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/huashan") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/wudang") > 0  )
        {      
                shout(HIR "\n��������֮ս��" HIW "���̵��ӣ�" HIC + query("anti")->name() + HIW "�ڹ�������ѹȺ�ۣ����������������ɣ���������ǧ������Σ��֮�У�\n" NOR );
                query("anti")->delete_temp("skybook/tulong/guangmingding");
                query("anti")->set("skybook/tulong/winguangming",1);
                        query("anti")->move(__DIR__"to_ding");
        }
                 destruct(this_object());
        }
          
::die();
}


