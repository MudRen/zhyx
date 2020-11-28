// Inherit: quarry.c ����
// Create by Vin for Heros.cn

#include <ansi.h>
inherit NPC;

int is_quarry()
{
	return 1;
}

void setup()
{
        if (this_object()->query("aves"))
        {
                set("limbs", ({ "ͷ��", "����", "���", "�ҳ�",
                                "צ��", "β��" }));
                set("verbs", ({ "bite", "claw" }));
        } else
        {
                set("limbs", ({ "ͷ��", "����", "����", "����",
                                "ǰ��", "���", "β��" }));
                set("verbs", ({ "hoof", "bite", "claw" }));
        }
        set("race", "Ұ��");
        set("attitude", "aggressive");
        ::setup();
}

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()))
                return;

        // �Զ�����Ԧ�����ȼ����ߵ����
        if ((int)me->query_skill("training", 1) < 100
           && ! this_object()->query("no_auto_kill") && me->query("age") > 15)
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me);
        }

        remove_call_out("disappear");
        call_out("disappear", 20);
}

void disappear()
{
        object ob = this_object();

        // ���Ժ�����Ұ�޻��֮
        if (living(ob) && ob->query("owner")
            && ! ob->is_busy() && ! ob->is_fighting() )
        {
                message_vision(WHT "\nͻȻ$N" WHT "�͵�һ�ܣ�˲���"
                               "��ʧ����Ӱ���١�\n\n", ob);
                destruct(ob);
        }
}

void die(object killer)
{
        object me, item;
        object ob = this_object();
        int power, skill;
        string msg;

        if (ob->query("aves"))
                message_vision(HIR "\nֻ��$N" HIR "�����˼��£��Ӱ�"
                               "����׹�����������ˡ�\n\n" NOR, ob);
        else
                message_vision(HIR "\nֻ��$N" HIR "���˼��������ڵ�"
                               "�������˼��£����ˡ�\n\n" NOR, ob);

        if (objectp(me = killer)
           || objectp(me = query_last_damage_from()))
        {
                // ���Ϊ�Լ����������֮
                if (ob->query("owner") == me->query("id"))
                //   && me->query("combat_exp") <= 800000)
                {
                        //��������������
                        if ( me->query("changanjob/kind") == "hunt" )
                             me->set("changanjob/ok", 1);
                        // ���������趨�Ĳ��������轱��
                        power = ob->query("power");

                        if (power < 5)
                                power = 5;

                        if (power > 500)
                                power = 500;

                        GIFT_D->bonus(me, ([ "prompt" : "ͨ�������ȡ" + ob->name() +
                                                        HIG "�ľ���",
                                             "exp"    : random(100) + 400,
                                             "pot"    : random(100) + 300,
                                             "mar"    : random(50) + 50,
                                             "score"  : random(10) + 20, 
                                           "weiwang"  : random(10) + 20, ]), 1);
                }
                skill = me->query_skill("hunting", 1);

                // �����Ʒ
                if (ob->query("item1") && random(skill) > 10)
                {
                        item = new(ob->query("item1"));
                        item->move(me, 1);

                        msg = HIC "����ϸ��Ѱ" + ob->name() +
                              HIC "��ʬ�壬�����������һ" +
                              item->query("base_unit") +
                              item->name() + HIC;

                        // һ�����ʻ�ø߼���Ʒ
                        if (ob->query("item3") && random(skill) > 60
                           && random(5) > 3)
                        {
	                        item = new(ob->query("item3"));
        	                item->move(me, 1);

	                        msg += "��һ" + item->query("base_unit") +
                                       item->name() + HIC;
                        } else
                        if (ob->query("item2") && random(skill) > 30
                           && random(4) > 2)
                        {
	                        item = new(ob->query("item2"));
        	                item->move(me, 1);

	                        msg += "��һ" + item->query("base_unit") +
                                       item->name() + HIC;
                        }
                        msg += "��\n\n" NOR;
                        tell_object(me, msg);
                }
        }
        destruct(ob);
}