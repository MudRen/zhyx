// closed.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      100

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	int exercise_cost;
	object where;

	seteuid(getuid());
	where = environment(me);
	
	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ����ɣ�\n");

        if (! ultrap(me))
                return notify_fail("�㻹û�е�����ʦ�ľ��磬���Ǻú�ѧϰ�����ɡ�\n");

        if (wizardp(me))
                return notify_fail("��ʦ��ʲô�أ�\n");

        if (! where->query("no_fight"))
                return notify_fail("������չأ���̫��ȫ�ɣ�\n");

        if (! where->query("sleep_room"))
                return notify_fail("�����һ���ܹ���Ϣ�ĵط��չء�\n");

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

        if (me->query("potential") - me->query("learned_points") < 10000)
                return notify_fail("���Ǳ�ܲ�����û���չ����С�\n");

	if ((int)me->query("qi") * 100 / me->query("max_qi") < 90)
		return notify_fail("�����ڵ���̫���ˣ��޷����ıչء�\n");

	if ((int)me->query("jing") * 100 / me->query("max_jing") < 90)
		return notify_fail("�����ڵľ�̫���ˣ��޷����ıչء�\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("������������в��㣬����Ŀǰ������"
				   "���г�ʱ��ıչ�������\n");

	if ((int)me->query("neili") * 100 / me->query("max_neili") < 90)
		return notify_fail("�����ڵ�����̫���ˣ��޷����ıչء�\n");

	message_vision("$N��ϥ���£���ʼڤ���˹����չ����С�\n", me);
        me->set("startroom", base_name(where));
	me->set("doing", "closed");
        CLOSE_D->user_closed(me, "closed");
	me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("����ʦ%s(%s)��ʼ�չ����С�",
			      me->name(1), me->query("id")));

	return 1;
}

int continue_closing(object me)
{
	me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
	tell_object(me, HIR "\n������չ�...\n" NOR);
        return 1;
}

int filter_skill(string sk, object me)
{
        if (me->query_skill(sk, 1) < 500 || ! me->can_improve_skill(sk))
                return 0;

        if (SKILL_D(sk)->type() != "martial")
                return 0;

        if (SKILL_D(sk)->valid_enable("force"))
                return 1;

        if (SKILL_D(sk)->valid_enable("parry") ||
            SKILL_D(sk)->valid_enable("dodge"))
                return 0;

        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        int pot;
        int r;
        int exp_inc;
        string *ks;

        pot = me->query("potential");
        if (pot <= me->query("learned_points"))
        {
                tell_object(me, "���Ǳ�ܺľ��ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                CLOSE_D->user_opened(me);
        	CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�չع���Բ����",
		                      me->name(1), me->query("id")));
		if (! interactive(me))
		{
			me->force_me("chat* haha");
			call_out("user_quit", 0, me);
		}

                return 0;
        }

        t = me->query_temp("last_closing");
        tn = time();
        if (tn - t < 0)
        {
                me->set_temp("last_closing", tn);
                return 1;
        }

        if (tn - t < PERIOD)
                return 1;

        me->set_temp("last_closing", tn);
        if (me->add("learned_points", PERIOD_POT / 2 + random(PERIOD_POT)) > pot)
                me->set("learned_points", pot);

        if (random(10) == 0)
                tell_object(me, "�չ�������...\n");

        if ((random(100) < 12) && me->can_improve_neili())
        {
                tell_object(me, HIR "����ڹ��������򣬸е����������ˣ�\n" NOR);
                me->improve_neili(1);
        }

        if ((random(100) < 12) && me->can_improve_jingli())
        {
                tell_object(me, HIM "�����ͨ�������򣬸е����������ˣ�\n" NOR);
                me->improve_jingli(1);
        }

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize")) / 500;
        exp_inc = exp_inc * (100 + me->query("int")) / 100;
        me->add("combat_exp", exp_inc);

        ks = filter_array(keys(me->query_skills()), (: filter_skill :), me);
        if (r = sizeof(ks))
        {
                r = random(r);
                tell_object(me, HIY "���" + to_chinese(ks[r]) + "��������\n" NOR);
                me->improve_skill(ks[r], 15000 + random(3000));
        }

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "����ֹ�˱չء�\n");
        message_vision(HIY "$N" HIY "���һ��������������һ��������ʱ"
                       "�����������Ĳ���\n\n" NOR, me);
        me->add("potential", (me->query("learned_points") - me->query("potential")) / 2);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "�չ���;ͻȻ������");
	return 1;
}

private void user_quit(object me)
{
	if (! objectp(me) || interactive(me))
		return;

	me->force_me("quit");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : closed

�չ����У�ֻ���㵽�˴���ʦ�ľ����Ժ���ܹ��չ����С�Ҫ�������
һ����ȫ���ҿ�����Ϣ�ĵط����ܱչأ��չ�ǰ��Ҫ��һ���Ǳ�ܣ���
�ؿ�ʼ�Ժ���������Ժ����ɫ����Ȼ�������У�ֱ�������ֹ�չ�
(halt)����Ǳ�ܺľ����ڼ�����ҵľ��顢���ܡ���������������

HELP );
        return 1;
}