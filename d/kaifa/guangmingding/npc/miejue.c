inherit NPC;

#include <ansi.h>

void create()
{
        set_name("���ʦ̫", ({ "miejue shitai", "miejue", "shitai", "mie", "jue"}));
        set("long", "���Ƕ����ɵĵ��������ӣ����ζ����������ˡ�\n");
        set("gender", "Ů��");
        set("age", 62);
        set("title",HIM"������������"NOR);
        set("attitude", "peaceful");
        set("class", "bonze");



        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 1200);
        set("max_jingli", 1200);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 50000);

        set_skill("force", 260);
        set_skill("emei-xinfa", 260);
        set_skill("emei-jiuyang", 200);
        set_skill("linji-zhuang", 260);
        set_skill("dodge", 240);
        set_skill("zhutian-bu", 240);
        set_skill("finger", 240);
        set_skill("tiangang-zhi", 240);
        set_skill("hand", 240);
        set_skill("jieshou-jiushi", 240);
        set_skill("strike", 260);
        set_skill("jinding-zhang", 260);
        set_skill("piaoxue-zhang", 260);
        set_skill("sixiang-zhang", 260);
        set_skill("sword", 260);
        set_skill("huifeng-jian", 260);
        set_skill("emei-jian", 260);
        set_skill("yitian-jian", 260);
        set_skill("blade", 240);
        set_skill("yanxing-dao", 240);
        set_skill("parry", 260);
        set_skill("martial-cognize", 200);
        set_skill("literate", 200);
        set_skill("mahayana", 200);
        set_skill("buddhism", 200);

        map_skill("force", "linji-zhuang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "jinding-zhang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "yitian-jian");

        prepare_skill("strike", "jinding-zhang");
        prepare_skill("hand", "jieshou-jiushi");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
                (: perform_action, "sword.jue" :),
                (: perform_action, "finger.ling" :),
                (: perform_action, "strike.bashi" :),
                (: perform_action, "hand.jie" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/city/obj/cloth")->wear();
}void init()
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
                shout(HIR "\n��������֮ս��" HIW "���ʦ̫������" HIC + query("anti")->name() + HIW "ά��ħ�̣������������װ�����������\n" NOR );

        }
}


void die()
{
        if (objectp(query("anti")))
        {
                
                query("anti")->set_temp("skybook/tulong/guangmingding/emei",1);
        message_vision(HIY "\n���ʦ̫��̾һ�������˰��ˣ���֮�������µ��������ȥ��\n" NOR,
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





