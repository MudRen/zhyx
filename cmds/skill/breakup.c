// breakup.c

#include <ansi.h>

inherit F_CLEAN_UP;

int breaking(object me);
int halt_breaking(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	int exercise_cost;
	object where;

	seteuid(getuid());
	where = environment(me);
	
	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ����ɣ�\n");

        if (me->query("breakup"))
                return notify_fail("���Ѿ���ͨ���ζ������ˣ��ƺ�û�б�Ҫ����һ�Ρ�\n");

        if (! where->query("no_fight"))
                return notify_fail("�������ͨ�ζ���������̫��ȫ�ɣ�\n");

        if (! where->query("sleep_room"))
                return notify_fail("�����һ���ܹ���Ϣ�ĵط��չ����С�\n");

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");

        if (me->query("potential") - me->query("learned_points") < 100)
                return notify_fail("���Ǳ�ܲ�����û���չ������Դ�ͨ�ζ�������\n");

	if ((int)me->query("qi") * 100 / me->query("max_qi") < 90)
		return notify_fail("�����ڵ���̫���ˣ��޷����ıչء�\n");

	if ((int)me->query("jing") * 100 / me->query("max_jing") < 90)
		return notify_fail("�����ڵľ�̫���ˣ��޷����ıչء�\n");

        if ((int)me->query_skill("force") < 450)
                return notify_fail("������Լ����ڹ�������ޣ�������"
				   "Ҫ�ȶ������ڹ����С�\n");

        if ((int)me->query("max_neili") < 5500)
                return notify_fail("������������в��㣬����Ŀǰ������"
				   "��ͨ�ζ�������\n");

	if ((int)me->query("neili") * 100 / me->query("max_neili") < 90)
		return notify_fail("�����ڵ�����̫���ˣ��޷����ıչء�\n");
       
	if ( me->query_skill("martial-cognize",1) < 300 )
		return notify_fail("�����ѧ�����������޷��չء�\n");

        if (! ultrap(me))
                return notify_fail("�㻹û�е�����ʦ�ľ��磬���Ǻú�ѧϰ�����ɡ�\n");

	message_vision("$N��ϥ���£���ʼڤ���˹����չ����С�\n", me);
        me->set("startroom", base_name(where));
        me->set("doing", "breakup");
        CLOSE_D->user_closed(me);
	me->start_busy(bind((: call_other, __FILE__, "breaking" :), me),
                       bind((: call_other, __FILE__, "halt_breaking" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)��ʼ�չ����У���ͼ��ͨ�ζ�������",
                              ultrap(me) ? "����ʦ" : "",
			      me->name(1), me->query("id")));

	return 1;
}

int continue_breaking(object me)
{
	me->start_busy(bind((:call_other, __FILE__, "breaking" :), me),
                       bind((:call_other, __FILE__, "halt_breaking" :), me));
        CLOSE_D->user_closed(me);
	tell_object(me, HIR "\n������չ������Դ�ͨ�ζ�����...\n" NOR);
        return 1;
}

private void stop_breaking(object me)
{
        CLOSE_D->user_opened(me);
	if (! interactive(me))
	{
		me->force_me("chat* sigh");
		call_out("user_quit", 0, me);
	}
}

int breaking(object me)
{
        string msg;

        if (me->query("potential") <= me->query("learned_points"))
        {
                tell_object(me, "���Ǳ�ܺľ��ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                CLOSE_D->user_opened(me);
        	CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�չؽ������ƺ�û��̫��Ľ�չ��",
		                      me->name(1), me->query("id")));
		if (! interactive(me))
		{
			me->force_me("chat* sigh");
			call_out("user_quit", 0, me);
		}

                return 0;
        }

        me->add("learned_points", 1);

        if (random(10))
                return 1;

        if (random(40000) < me->query("con"))
        {
                message_vision(HIW "ֻ��$N" HIW "ͷ�ϰ������ڡ�����"
                               "��ͬ���������У������Ѿ����������۶���"
                               "������Ԫ��������á����˽���Ľ�Ҫ��ͷ��\n" NOR, me);
                tell_object(me, HIR "����������ڵ���ԴԴ����������"
                            "������Ѩ�����������ѵ�����������������\n" NOR);
                message_vision(HIC "ͻȻ$N" HIC "���һ����һ����������"
                               "��Ȼɢ�����������ܿ�����ʱ������ȡ�\n" NOR, me);
                tell_object(me, HIG "���ʱ���û���һ�����ɣ�һ������֮����Ȼ"
                            "��������һƬ����������û��˿�����ͣ���̩֮����\n" NOR);
                me->set("breakup", 1);
        	CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�����չؿ��ޣ����ڴ�ͨ"
                                              "���ζ����������ӵ������ϵ���ѧ���硣",
		                      me->name(1), me->query("id")));
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 250000);
                CHAR_D->setup_char(me);
                stop_breaking(me);
                return 0;
        }

        switch (random(5))
        {
        case 0:
                msg = "��ĬĬ��ת������������Щ�о���\n";
                break;

        case 1:
                msg = "�㽫�����˳�������Ϲ��������衢͸ʮ����¥���鲼��������Ȼ���ջص��\n";
                break;

        case 2:
                msg = "�㽫�����˾���Ѩ������֫���࣬Ȼ���ֻ��յ��\n";
                break;

        case 3:
                msg = "���ڵ����в��ϻ���������ֻ���û������ȡ�\n";
                break;

        default:
                msg = "�㻺���������ɣ���������ˮ¶����Ϊ���á�\n";
                break;
        }

        tell_object(me, msg);
        return 1;
}

int halt_breaking(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "����ֹ�˱չء�\n");
        message_vision(HIY "$N" HIY "����̾��һ�����������������ۡ�\n\n" NOR, me);
        me->add("potential", (me->query("learned_points") - me->query("potential")) / 2);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "�չ���;ͻȻ������");
	return 1;
}

private void user_quit(object me)
{
	if (! me || interactive(me))
		return;

	me->force_me("quit");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : breakup

�չ������Դ�ͨ�ζ���������Ҫ�ǳ������������ڹ����ײ���������
���һ�����Ǳ�ܡ�һ����ͨ���ζ���������ͬʱ��չ��������������
���������ޡ�

HELP );
        return 1;
}