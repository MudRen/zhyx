// by yuchang
#include <ansi.h>

inherit NPC;
void create()
{
        set_name("������", ({ "ao cangtian", "ao", "cangtian"}));
        set("title", HIY "����ɽׯ��ʥ" NOR);
        set("long",
"�����쳤�ò���˧�������ŵ�һ��Բ����Ƥ����΢�е㷢�ڣ����ǹǼܴܺ����ϵ�������㣬
һ���۾���������ʱӺ�ݻ�������һ������֮�£�������Ȼ�𾴣����ұ��ӡ�\n");
        set("gender", "����");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen", -200000);
        set("per", 30);
        set("str", 35);
        set("int", 25);
        set("con", 25);
        set("dex", 30);


        set("max_qi", 20000);
        set("max_jing", 20000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 500);
        set("chat_chance_combat", 60);
        set("combat_exp", 5000000);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ren" :),
        }) );
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("hand", 500);
        set_skill("strike", 500);
        set_skill("staff", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("blade", 500);
        set_skill("pixie-jian", 500);
        set_skill("literate", 500);
        set_skill("taoism", 500);
        set_skill("buddhism", 500);

        set_skill("jiuyang-shengong", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("xuanming-zhang", 500);
        set_skill("jiuyin-baiguzhao", 500);
        set_skill("dugu-jiujian", 500);
        set_skill("liumai-shenjian", 500);
        set_skill("qianzhu-wandushou", 500);
        set_skill("ranmu-daofa", 500);
        set_skill("dagou-bang", 500);
        set_skill("shaolin-yishu", 500);
        set_skill("wudu-qishu", 500);
        set_skill("throwing", 500);
        set_skill("mantian-xing", 500);
        set_skill("idle-force", 500);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "six-finger");
        map_skill("sword", "dugu-jiujian");

        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("finger", "liumai-shenjian");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.cimu" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.six" :),
                (: perform_action, "finger.zhongheng" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        

        setup();
        carry_object("/d/ajszhuang/npc/obj/changjian")->wield();
        carry_object("/d/ajszhuang/npc/obj/female2-cloth")->wear();
}
void init()
{       
        object ob;
        ob = this_player();
        ::init();

        
        add_action("do_yun","yun");
        add_action("do_yun","exert");

        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}


int do_yun(string arg)
{
        object obj;

        obj=this_object();
        if (arg == "roar" )
        {
                message_vision(CYN "\n������ȵ����޳����ӣ���������ɲ��������\n" NOR,
                                   obj);
                return 1;
        }
        return 0;

}



int accept_ansuan(object who)
{
        return notify_fail("��Ҫ�þ����ý�����Ҫ�ó��汾�¡�\n");
}


void receive_wound(string type, int n)
{
        return;
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() )
        return;

         command("yi");
         command("say �ߣ�����һ���������ġ�");
         command("chat Ҫ��õ������ý�Ҳ���ԣ��������ȵô�Ӯ��!");
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
}
void die()
{
        object killer;
        int exp,userexp;
        
         if(objectp(killer=this_object()->query_last_damage_from()))
        {
                userexp=killer->query("combat_exp");
                exp=((int)killer->query("literate")*2)+random(1000)+10000+(userexp);


                if (!killer->query_temp("m_success/��ʥ"))
                {
                        killer->set_temp("m_success/��ʥ",1);
                        killer->add("combat_exp",exp);
                        killer->add("potential",20000);
                        message("channel:chat", HBMAG"��ת����"+killer->query("name")+"�ɹ���ɱ������ʥ!��������ɽׯ��һ��!\n"NOR,users());
                }
                
                tell_object(killer, HIM "\n��Ȼ�㷢�����Ѿ�������һ��İ���ķ���\n" NOR);
                killer->move("/d/ajszhuang/cjl2");
                message_vision("�����ȥ����ͻȻ���ֺ�������һ���ˡ�\n", this_object());
        }
        message_vision("$N����һ������ȥ��\n", this_object());
        destruct(this_object());
} 
