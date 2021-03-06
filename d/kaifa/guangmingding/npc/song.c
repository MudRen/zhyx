#include <ansi.h>
inherit NPC;
void create()
{
        set_name("宋远桥", ({ "song yuanqiao", "song", "yuanqiao" }));
        set("nickname", HIC "武当首侠" NOR);
        set("long", "他就是张三丰的大弟子、武当七侠之首的宋远桥。\n"
                    "身穿一件干干净净的灰色道袍。他身材瘦长，满\n"
                    "脸红光。恬淡冲和，沉默寡言。\n");
        set("gender", "男性");
        set("age", 61);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 31);
        set("int", 27);
        set("con", 32);
        set("dex", 30);
        
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 200);
        set("combat_exp", 2000000);
        set("score", 100000);

        set_skill("force", 260);
        set_skill("wudang-xinfa", 260);
        set_skill("taiji-shengong", 240);
        set_skill("dodge", 240);
        set_skill("tiyunzong", 240);
        set_skill("unarmed", 240);
        set_skill("taiji-quan", 220);
        set_skill("strike", 240);
        set_skill("wudang-zhang", 240);
        set_skill("zhenshan-zhang", 240);
        set_skill("hand", 240);
        set_skill("paiyun-shou", 240);
        set_skill("parry", 240);
        set_skill("sword", 260);
        set_skill("wudang-jian", 260);
        set_skill("shenmen-jian", 260);
        set_skill("taiji-jian", 240);
        set_skill("taoism", 240);
        set_skill("literate", 220);
        set_skill("martial-cognize", 240);
        set_skill("medical", 200);
        set_skill("wudang-yaoli", 200);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "zhenshan-zhang");
        map_skill("hand", "paiyun-shou");
        map_skill("medical", "wudang-yaoli");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.jia" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "sword.zhuan" :),
                (: perform_action, "unarmed.zhen" :),
                (: perform_action, "unarmed.zhan" :),
                (: perform_action, "unarmed.ji" :),
                (: perform_action, "unarmed.yin" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
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
//                say(CYN "玄慈大喝道：你这魔教爪牙，还不速来受死！\n" NOR);    
        set("anti",me);
                me->kill_ob(obj);
                  kill_ob(me);
                break;
        case 1:
 //               say(CYN "玄慈大叹：哎，又一个送死的来了！\n" NOR);
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
                shout(HIR "\n【光明顶之战】" HIW "宋远桥：哎！" HIC + query("anti")->name() + HIW "维护魔教，不自量力，白白送了性命！\n" NOR );

        }
}


void die()
{
        if (objectp(query("anti")))
        {
                
                query("anti")->set_temp("skybook/tulong/guangmingding/wudang",1);
  
    message_vision(HIY "\n宋远桥大叹一声：罢了罢了！随之带领门下弟子鱼贯离去！\n" NOR,
                                   this_object(),query("anti"));
if ( query("anti")->query_temp("skybook/tulong/guangmingding/shaolin") > 0  
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/emei") > 0
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/chengkun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/kunlun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/huashan") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/wudang") > 0  )
        {      
                shout(HIR "\n【光明顶之战】" HIW "明教弟子：" HIC + query("anti")->name() + HIW "在光明顶技压群雄，独力击退六大门派，救明教万千弟子于危难之中！\n" NOR );
                 query("anti")->delete_temp("skybook/tulong/guangmingding");
          query("anti")->set("skybook/tulong/winguangming",1);
                        query("anti")->move(__DIR__"to_ding");

        }
                 destruct(this_object());
        }

::die();
}


