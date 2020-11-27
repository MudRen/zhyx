inherit NPC;
#include <ansi.h>

void create()
{
        set_name("����", ({ "cheng kun", "cheng" }) );
        set("title", "������ͽ");
        set("nickname", HIR "������" NOR);
        set("gender", "����");
        set("shen_type", 0);
        set("age", 65);
        set("long", "�˳ơ������֡�������\n");
        set("attitude", "peaceful");
        set("str", 36);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("max_qi", 5200);
        set("max_jing", 2600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 80);

        set("combat_exp", 2400000);

        set_skill("unarmed", 240);
        set_skill("cuff", 240);
        set_skill("strike", 240);
        set_skill("sword", 260);
        set_skill("force", 260);
        set_skill("parry", 240);
        set_skill("dodge", 240);
        set_skill("hand", 240);
        set_skill("literate", 220);
        set_skill("damo-jian", 260);
        set_skill("hunyuan-yiqi", 260);
        set_skill("qishang-quan", 240);
        set_skill("pili-shou", 240);
        set_skill("shaolin-shenfa", 240);
        set_skill("martial-cognize", 200);

        map_skill("sword", "damo-jian");
        map_skill("parry", "qishang-quan");
        map_skill("force", "hunyuan-yiqi");
        map_skill("cuff", "qishang-quan");
        map_skill("hand", "pili-shou");
        map_skill("dodge", "shaolin-shenfa");

        prepare_skill("cuff", "qishang-quan");

        set_temp("apply/attack", 220);
        set_temp("apply/dodge", 220);
        set_temp("apply/parry", 200);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.shang" :),
        }));             

        setup();
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
                shout(HIR "\n��������֮ս��" HIW "����������" HIC + query("anti")->name() + HIW "ά��ħ�̣������������װ�����������\n" NOR );

        }
}


void die()
{
        if (objectp(query("anti")))
        {
                
                query("anti")->set_temp("skybook/tulong/guangmingding/chengkun",1);
 
     message_vision(HIR "\n���񼲵ĳ������ڵõ�Ӧ�е��³���\n" NOR,
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

