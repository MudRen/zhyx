// qiangdao.c ǿ��
inherit NPC;
#include <ansi.h>
void move();

void create()
{
        set_name(HIW "ǿ��" NOR, ({ "qiang dao", "dao",}));
        set("gender", "����");
        set("age", 28);
        set("long", "����һ��ר�����Ӫ����ǿ����\n");
        
        set("combat_exp",1000);
        set("attitude", "peaceful");
        
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        
         set("str",30);
         set("per",18);
         set("food",400);
         set("water",400);

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        add_money("silver",10);
}

void init()
{
        remove_call_out("leave");
        call_out("leave",300);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(HIC "ǿ�����·�ߵ��Ӳݣ������ˡ�\n" NOR,this_object());
                }
        else call_out("leave",10);
}

void die()
{
        object me = this_object()->query_temp("last_damage_from");
        object corpse, money;      
        int kar, exp, pot;
        kar = random(30);
        exp = kar + random(500);
        pot = 200 + random(50);

        message_vision(HIR "\nǿ�����ڵ��ϣ������˼��¾����ˡ�\n" NOR,me);
        if (me->query("kill_qiangdao") == 1 && this_object()->query_temp("owner/id") == me->query("id")) {
                message_vision(HIW "$N�������ˣ�\n"
                + chinese_number(exp) + "��ʵս���飬\n"
                + chinese_number(pot) + "��Ǳ�ܣ�\n"
                + chinese_number(10) + "��������\n" NOR, me);
                me->add("combat_exp", exp);
                me->add("potential", pot);
                me->add("weiwang", 10);
                me->delete("quest3");
                me->delete("kill_qiangdao");
                }
        else {
                message_vision(HIC "\n����$N"HIC"ɱ����Ŀ�꣬�����˱������������ڵ��۾��飺\n"
                + chinese_number(200) + "��ʵս���飬\n"
                + chinese_number(100) + "��Ǳ�ܣ�\n"
                + chinese_number(1000) + "��������Ϊ��л��\n" NOR, me);
                me->add("combat_exp", -200);
                me->add("potential", -100);
                me->add("weiwang",-1000);
                }

        corpse = new("/clone/misc/corpse");
        corpse->set("name",HIW "ǿ����ʬ��" NOR);
        corpse->set("long","����һ�������޶�����ǿ����\nȻ�������Ѿ����ˣ�ʣ��һ�߳�ª��ʬ�塣\n");
        corpse->move(environment(this_object()));
        corpse->set_max_encumbrance(1000);        
        money = new("/clone/money/gold");
        money->move(corpse);
        me->add("MKS", 1);

        destruct(this_object());
}

