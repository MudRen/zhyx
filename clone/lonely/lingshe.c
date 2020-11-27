// lingshe.c ������
// by jeeny

#include <weapon.h>
#include <ansi.h>

inherit F_OBSAVE;
inherit STAFF;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIW "������" NOR, ({ "lingshe zhang", "staff", "lingshe" }));
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", @LONG
����һ������ë���Ȼ�ı��ȣ���������ŷ������ƾ����Ⱥͺ��߹���ս
���ٻغϡ���ͷ���Ÿ������Ц����ͷ����Ŀ�����������������ݣ���ι
�綾���趯ʱ��������˼��ɵ����������������ǲ����������������ߣ�
���������������ѷ���
LONG );
                set("unit", "��");
                set("value", 800000);
                set("no_sell", 1);
                set("du", 3) ;
                set("material", "steel");
                set("wield_msg", (: do_wield :));
                set("unwield_msg", (: do_unwield :));
                set("stable", 80);
        }
        init_staff(180);
        setup();
        restore();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if (me->query("shen") < -10000)
                return HIW "$Nһ����Х��ȡ��$n" HIW "��һʱ�䣬����ϮϮ��\n" NOR;
        else
        if (me->query("shen") <= 0)
                return HIC "$Nһ���֣���Ȼ��$n" HIW "�������С�\n" NOR;
        else
        if (me->query("shen") > 10000)
                return HIB "$N�߶����µ�����һ��$n" HIB "��\n" NOR;
        else
                return HIB "$Nһ����Ц����ৡ���һ��������$n" HIB "��\n" NOR;
}

string do_unwield()
{
        object me;

        me = this_player();
//        remove_call_out("check_npc");
        if (me->query("shen") <= 0)
                return HIC "$Nһ���֣������������ȡ�\n" NOR;
        else
        if (me->query("shen") > 10000)
                return HIG "$N��$n" HIG "�����������Ļ��������顱������ͣ��\n" NOR;
        else
                return HIG "$Nһɹ����$n" HIG "������䡣\n" NOR;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->is_good() || victim->is_bad())
                return - damage_bonus / 2;

        if (me->is_not_bad() || victim->is_not_good())
                return 0;

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa" ||
            me->query_skill("lingshe-zhangfa", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                        victim->start_busy(me->query_skill("staff") / 10 + 2);
                return HIB "$N��ǰһ�������е�" NOR+HIW "������" NOR+HIB "�����벻����"
                       "�Ƕ���$n��ȥ���ȷ������籩������ҡ�$n���һ\n"
                       "������֪��εֵ���ֻ���������ˡ�\n" NOR;

        case 1:
                n = me->query_skill("staff");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n = victim->query("eff_jing");
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIB "$Nһ�����������е������Ȼ���һ���׹⣬��ৡ���ɨ��$n��\n" NOR:
                                   HIB "$NͻȻ�����ȵ�����ʲô�������ɣ�����������������������"
                                   HIB "����һ����$n��ʱ������ǰ������ǧ�����ߴܶ���\n" NOR;
        }

        // double effect
        return damage_bonus;
}

/*
void start_borrowing()
{
        remove_call_out("return_to_feng");
        call_out("return_to_feng", 7200 + random(600));
}

void return_to_feng()
{
        object me;

        me = environment();
        if (! objectp(me))
                return;

        while (objectp(environment(me)) && ! playerp(me))
                me = environment(me);
 
        if (playerp(me))
        {
                if (me->is_fighting())
                {
                        call_out("return_to_feng", 1);
                        return;
                }

                message_vision("��Ȼһ��ŷ�����ҵĵ������˹���������$N��æ�к���������ʦү��"
                               "���������û������ȣ������ڲ�����ô����\n"
                               "$N���������ˣ����ˣ�����û�ȥ�ɡ���\n"
                               "$N���Ƚ���ŷ�����ҵ��Ӵ��ߡ�\n", me);
        } else
        {
                message("vision", "��Ȼһ��ŷ�����ҵ������˹��������������ȣ�̾�˿�����ҡҡ"
                                  "ͷ���ˡ�\n", me);
        }

        destruct(this_object());
}
*/