// npc: /d/city/npc/ftb_killer.c
// Chu 2/10/99
// Rama 20/05/02 modified for hx

#include <ansi.h>
inherit NPC;

mixed setup_robber(int exp_level);
int set_random_name();
void start_checking(object target);
void start_job(object target);
void clear_dumudian();
void self_destruct();


nosave string *menpai_names1 = ({
    "��ɽ��",
    "������",
    "�䵱��",
    "������",
    "ؤ��",
});

nosave string *menpai_names2 = ({
    "��ɽ",
    "����",
    "�䵱",
    "����",
    "ؤ��",
});

nosave int random_id;

void create()
{
        set_random_name();
        set("gender", "����" );
        set("age", 29);
        set("str", 25);
        set("dex", 30);
        set("con", 25);
        set("int", 23);
        set("shen_type", -1);

        set("max_qi", 300);
        set("max_jing", 100);
        set("neili", 200);
        set("max_neili", 200);
        set("no_refresh", 1);

//        setup_robber();

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/xingxiu/obj/fire");
            remove_call_out("self_destruct");
            call_out("self_destruct", 1200);

}

int set_random_name()
{
    string my_name;

    random_id=random(5);
    my_name = menpai_names2[random_id] + "����";
    set_name(my_name, ({"dizi"}));
    set("long", "����������һ�������"+menpai_names1[random_id]+"���ӡ�\n");

    return random_id;
}

mixed setup_robber(int exp_level)
{
    int level, menpai, exp;

    menpai = random_id;

//    printf("exp_factor = %f.\n",exp_factor);

    exp = exp_level*(random(50)+130)/100;

    if (exp < 0 ) return;

    level = pow(10*exp, 0.333334);

//    level = level - 5;

    if (level < 20) level = 20;

    set("max_neili", level*12);
    set("neili", level*12);
    set("eff_jingli", level*10);
    set("max_jingli", level*10);
    set("jingli", level*10);
    set("max_qi", level*12);
    set("eff_qi", level*12);
    set("qi", level*12);
    set("max_jing", level*10);
    set("eff_jing", level*10);
    set("jing", level*10);
    set("jiali", level/2);

    set("combat_exp", exp);
    set_skill("force", level);
    set_skill("dodge", level);
    set_skill("parry", level);
    set_skill("sword", level);
    set_skill("blade", level);
    set_skill("strike", level);
    set_skill("cuff", level);
    set_skill("finger", level);
    set_skill("claw", level);
    set_skill("club", level);
    set_skill("kick", level);
    set_skill("staff", level);
    set_skill("whip", level);

    switch (menpai){
    // Huashan
    case 0:
        set_skill("huashan-sword", level);
        set_skill("feiyan-huixiang", level);
        set_skill("zixia-shengong", level);
        set_skill("huashan-quanfa", level);

        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "huashan-sword");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("sword", "huashan-sword");

        set("default_weapon", "/clone/weapon/gangjian");

        break;
    // xingxiu
    case 1:
        set_skill("force", level);
        set_skill("huagong-dafa", level);
        set_skill("dodge", level);
        set_skill("zhaixinggong", level);
        set_skill("parry", level);
        set_skill("staff", level);
        set_skill("tianshan-zhang", level);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
       set("default_weapon", "/clone/weapon/tiegun");
        break;
    // wudang
    case 2:
        set_skill("taiji-shengong", level);
        set_skill("taiji-jian", level);
        set_skill("tiyunzong", level);
        set_skill("taiji-quan", level);

        map_skill("force", "taiji-shengong");
        map_skill("parry", "taiji-jian");
        map_skill("cuff", "taiji-quan");
        map_skill("dodge", "tiyunzong");
        map_skill("sword", "taiji-jian");

        prepare_skill("cuff", "taiji-quan");
        set("default_weapon", "/clone/weapon/gangjian");
        break;
    // shaolin
    case 3:
        set_skill("damo-jian", level);
        set_skill("xiuluo-dao", level);
        set_skill("wuchang-zhang", level);
        set_skill("zui-gun", level);
        set_skill("shaolin-shenfa", level);
        set_skill("hunyuan-yiqi", level);
        set_skill("yizhi-chan", level);
        set_skill("banruo-zhang", level);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "damo-jian");
        map_skill("sword", "damo-jian");
        map_skill("blade", "xiuluo-dao");
        map_skill("club", "zui-gun");
        map_skill("staff", "wuchang-zhang");
        map_skill("finger", "yizhi-chan");
        map_skill("strike", "banruo-zhang");

        prepare_skill("finger", "yizhi-chan");
        prepare_skill("strike", "banruo-zhang");
        set("default_weapon", "/clone/weapon/gangjian");
        break;

    // gaibang
    case 4:
    default:
        set_skill("dagou-bang", level);
        set_skill("feiyan-zoubi", level);
        set_skill("huntian-qigong", level);
        set_skill("changquan", level);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("unarmed", "changquan");

        set("default_weapon", "/clone/weapon/gangdao");
        break;
    }
    if (random(2) > 0) carry_object(query("default_weapon"))->wield();

    return menpai;
}

void start_checking(object target)
{
    call_out("start_job", 15+random(10), target);
    return;
}


void self_destruct() {
    object me = this_object();

    clear_dumudian();
    message("vision", name(1)+"����ææ���뿪��.\n", environment(me), me);
    destruct(me);
}

void start_job(object target)
{
    object me = this_object();
    object target_obj, gang;

    gang = present("tong gang", environment(me));

    if (!gang) {
        // Tong gang is not here, just go
        self_destruct();
        return;
    }
    if ( !me->is_fighting() && !me->query_temp("disabled") )
    {
        // only check if I am not fighting
       if (present(target->query("id"), environment(me))) {
           // if the player still here, attack him
           message_vision(HIR"\n$N��$n�����ȵ���" + RANK_D->query_rude(target) + "���Ҳ�ʶ�ô�����\n\n"NOR, me, target);
           kill_ob(target);
       }
       else
       {
           target_obj = present("zhiri lama", environment(me));
           if (target_obj)
           {
//               EMOTE_D->do_emote(this_object(), vb, emote_arg, 0, 0);

               command("hehe "+target_obj->query("id"));
               kill_ob(target_obj);
           }
           else
           {
               if (gang->query_current_liquid() > 0)
               {
                    // set gang on fire.
                    command("say "+"���ӿ���ͺ¿�ǻ���ô������");
                    message_vision(HIR"$N�ӻ����ͳ�һ֧���ۣ���ȼ��ͭ���е����͡�\n"NOR, me);
                    gang->burn_out_gang();
               }
               self_destruct();
               return;
           }
       }
    }
    call_out("start_job", 15+random(10), target);
    return;
}

void clear_dumudian()
{
    object room1;

    if(!( room1 = find_object("/d/xueshan/dumudian")) )
         room1 = load_object("/d/xueshan/dumudian");
    room1->reset_to_normal();
    return;
}

void die()
{
    clear_dumudian();
    ::die();
}
