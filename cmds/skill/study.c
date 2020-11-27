// study.c

#include <skill.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object where = environment(me);
	object ob;
	string zhao_name, book_name;
        string sname;
        string *args;
        mapping needs;
        string *need_sk;
        mixed need_lvl;
	int my_skill, cost, times, i;
        int t = time();

	if (! arg)
		return notify_fail("��Ҫ��ʲô��\n");

        if (where->query("pigging"))
                return notify_fail("�㻹��ר�Ĺ����ɣ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (t == me->query_temp("time/study"))
                return notify_fail("��ողŶ����飨�����Ҫ�������飬����ָ������Ĵ�������\n");

	if (me->is_fighting())
		return notify_fail("���޷���ս����ר�������ж���֪��\n");

	if (! arg || (i = sizeof(args = explode(arg, " "))) < 1)
                return notify_fail("ָ���ʽ��study|du <�鼮> <����>\n");

        i--;
        if (i >= 1 && sscanf(args[i], "%d", times) && times)
                i--;
        else
                times = 1;
        if (args[i] == "with" && i >= 1)
                i--;
        book_name = implode(args[0..i], " ");

	if (times < 1 || times > 100)
		return notify_fail("�����������һ�Σ����Ҳ"
                                   "���ܳ���һ�ٴΡ�\n");

	if (! objectp(ob = present(book_name, me)) &&
           ! objectp(ob = present(book_name, where)) )
		return notify_fail("û�Ȿ��ɶ�����\n");

	if (! mapp(ob->query("skill")))
		return notify_fail("���޷�����������ѧ���κζ�����\n");

	if (!me->query_skill("literate", 1))
		return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

        if (environment(me)->query("no_fight") &&
            (me->query("doing") != "scheme" || this_player(1)))
                return notify_fail("���޷�������ط����Ķ��顣\n");

	message("vision", me->name() + "��ר�ĵ��ж�" + ob->name() +
		"��\n", environment(me), me);
	if ((int)me->query("combat_exp") < ob->query("skill/exp_required"))
	{
		write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
		return 1;
	}

	cost = (ob->query("skill/jing_cost") * 20 +
                ob->query("skill/difficulty") -
                me->query_int()) / 20;
	if (cost < 10) cost = 10;

        if (mapp(needs = ob->query("skill/need")))
        {
                foreach (need_sk in keys(needs))
                {
                        // check all skills
                        need_lvl = needs[need_sk];
                        if (functionp(need_lvl))
                                need_lvl = evaluate(need_lvl);
                        else
                        if (! intp(need_lvl))
                                need_lvl = 0;

                        if (me->query_skill(need_sk, 1) < need_lvl)
                                // not reach the line
                                return notify_fail("���ж���һ��������������ͨ��" +
                                                   to_chinese(need_sk) +
                                                   "�Ļ������������������ĺ��塣\n");
                        // check next skill
                }
        }

        sname = ob->query("skill/name");
	notify_fail("����Ŀǰ����������û�а취ѧ������ܡ�\n");
	if (! SKILL_D(sname)->valid_learn(me))
                return 0;

        if (! XUE_CMD->can_learn(me, sname))
                return 0;

	if (me->query_skill(sname, 1) > ob->query("skill/max_skill"))
		return notify_fail("���ж���һ��������Ƿ���"
                                   "������˵�Ķ�����Զ�̫ǳ"
                                   "�ˣ�û��ѧ���κζ�����\n");

	if (me->query_skill(sname, 1) < ob->query("skill/min_skill"))
		return notify_fail("���ж���һ���������ȴ����"
                                   "������ż��ܵ����⻹̫ǳ"
                                   "����������ջ�\n");

	if (! me->query_skill(sname, 1))
                me->set_skill(sname, 0);

	my_skill = me->query_skill(sname, 1);
	if (! me->can_improve_skill(sname))
        {
		return notify_fail("Ҳ����ȱ��ʵս���飬���" +
                                   ob->name() + "������˵��"
                                   "���������޷���ᡣ\n");
	}

        me->set_temp("time/study", t);
	for (i = 0; i < times; i++)
	{
        	if ((int)me->query("jing") > cost)
                        me->receive_damage("jing", cost );
                else
                if (me->query("env/auto_regenerate") &&
                    SKILL_D("force/regenerate")->exert(me, me))
                {
                        // try to regenerate & learn again
                        write("����þ������һЩ���������顣\n");
                        i--;
                        continue;
                } else
                {
                        me->set("jing", 0);
                        break;
                }

		me->improve_skill(sname, (int) me->query_skill("literate", 1) / 10 + 1);
	}
        if (! i)
        {
                write("������̫���ˣ����һ��Ҳû�п���ȥ��\n");
                return 1;
        }

	if (zhao_name = SKILL_D(sname)->query_skill_name(my_skill))
	        write(sprintf("���ж���" + chinese_number(i) +
                      "���й�%s�ļ��ɣ��ԡ�%s����һ���ƺ���Щ�ĵá�\n",
		      to_chinese(sname), zhao_name));
	else
	        write(sprintf("���ж���"+chinese_number(i) +
                      "���й�%s�ļ��ɣ��ƺ��е��ĵá�\n",
                      to_chinese(sname)));

        if (i < times)
                write("�������Ѿ�����ƣ�룬�޷������ж���֪��\n");

	return 1;
}

int help(object me)
{
        write( @HELP
ָ���ʽ: study|du <��Ʒ����> [����]
          study|du <��Ʒ����> with [����]

���ָ��ʹ�����ͨ���Ķ����Ż�������Ʒ��ѧĳЩ����, ��ǰ��
��: �㲻���Ǹ�����ä���������㲻���ڲ���ս���ĵط����顣

see also : learn
HELP );
        return 1;
}