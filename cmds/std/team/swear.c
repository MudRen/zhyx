// team command: swear

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;
        object env;
        object tob;
        string msg;

        string pure_name;

        // �������ĺϷ���
        t = me->query_team();
        if (! arrayp(t))
                return notify_fail("�����ڲ����ڶ����а���\n");

        if (! me->is_team_leader())
                return notify_fail("ֻ�ж����������ܷ��������ȱ��졣\n");

        if (! arg)
                return notify_fail("����ǰ�����һ�����ְɣ�\n");

        t -= ({ 0 });

        if (sizeof(t) < 1)
                return notify_fail("���������������û�б��ˣ���ʲô�壿\n");

        if (me->query_temp("pending/team_doing") &&
            me->query_temp("pending/team_doing") != "swear")
                return notify_fail("�㻹�ǵ�Ŀǰ�����е������������˵�ɡ�\n");

        // �ж�����ĺϷ���
        if (arg == "cancel")
        {
                if (arrayp(t = me->query_temp("pending/team_swear/member")))
                {
                        me->delete_temp("pending/team_swear");
                        write("��ȡ���ʹ�ҽ������ͷ��\n");
                        t -= ({ 0 });
                        message("vision", YEL + me->name(1) +
                                "ȡ���˴��һͬ����ĳ��顣\n", t, me);
                } else
                        write("�����ڲ�û�г����ҽ��尡��\n");

                me->delete_temp("pending/team_doing");
                return 1;
        }

        if (mapp(me->query_temp("pending/team_swear")))
        {
                write("���������ҽ����أ����ǵȴ�һ�Ӧ�ɡ�\n");
                return 1;
        }

        if (me->query("weiwang") < 1000)
        {
                write("���ڽ������޼���֮����Ҳ��������ţ�\n");
                return 1;
        } else
        if (me->query("weiwang") < 10000)
        {
                write("������������������һ�����۰���ڣ������Ժ���˵�ɡ�\n");
                return 1;
        } else
        if (me->query("weiwang") < 20000)
        {
                write("�������ڽ�����Ҳ������Щ��ͷ�ˣ���ϧ���ǲ�����\n");
                return 1;
        } else
        if (me->query("weiwang") < 50000)
        {
                write("����Ŭ��Ŭ�������Լ�����������"
                      "��������˵�����Ҳ��Զ�ˡ�\n");
                return 1;
        }

        // �ж����ֵĺϷ���
        pure_name = arg;
        if (strlen(pure_name) > 16)
                return notify_fail("���������̫���ˡ�\n");

        if (strlen(pure_name) < 4)
                return notify_fail("���������̫���ˡ�\n");

        if (! is_chinese(pure_name))
                return notify_fail("���������������֡�\n");

        if (stringp(msg = LEAGUE_D->valid_new_league(pure_name)))
                return notify_fail(msg);

        if (strlen(pure_name) != strlen(arg))
                arg += NOR;

        // �ж϶����������˵ĺϷ���
        env = environment(me);
        foreach (tob in t)
        {
                if (environment(tob) != env)
                        return notify_fail("����������е��˻�û�е����ء�\n");

                if (! living(tob))
                        return notify_fail("����������л����˻��Բ����ء�\n");

                if (! playerp(tob))
                        return notify_fail("������壬ֻ��" + tob->name(1) + "����Ӧ��\n");

                if (tob->is_fighting())
                        return notify_fail("�����������������æ�Ŵ���ء�\n");

                if (mapp(tob->query("league")))
                        return notify_fail("����������������Ѿ�������ͬ���ˡ�\n");
        }

        me->set_temp("pending/team_swear/member", t);

        message_vision("$N��������������������ֵ���"
                       "Ͷ��ϣ�����Ϊ�β���ݣ�����" +
                       "��" + arg + "������\n", me);
        me->set_temp("pending/team_swear/name", pure_name);
        me->set_temp("pending/team_swear/accept", ({ me }));
        me->set_temp("pending/team_doing", "swear");

        foreach (tob in t)
        {
                if (tob == me)
                        continue;

                tell_object(tob, HIG + me->name(1) + "(" +
                            me->query("id") + ")���ô��һ"
                            "ͬ���壬������" + arg + "����"
                            "���Ƿ�ͬ��(right/refuse)��\n" + NOR);
        	tob->set_temp("pending/answer/" + me->query("id") + "/right",
                              bind((: call_other, __FILE__, "do_right", tob, me :), tob));
        	tob->set_temp("pending/answer/" + me->query("id") + "/refuse",
        	              bind((: call_other, __FILE__, "do_refuse", tob, me :), tob));
        }

        return 1;
}

int do_right(object me, object ob)
{
        object *t;
        object *r;
        string msg;
        object tob;
        int base;
        string league_name;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

        t = ob->query_temp("pending/team_swear/member");
        if (! arrayp(t))
		return notify_fail("�˼������Ѿ�����������ˡ�\n");

        if (member_array(me, t) == -1)
                return notify_fail("�������Ѿ������˼ҵĽ��忼�Ƿ�Χ֮���ˡ�\n");

        switch (random(8))
        {
        case 0:
                msg = "$N���ͷ�����˿���ң�֣�ص�������û���������ͬ�⣡��\n";
                break;
        case 1:
                msg = "$N��ϲ�����ƴ�Ц�������������⣡������������\n";
                break;
        case 2:
                msg = "$N������Ц�������������ܺã��ܺã����ǲ�������\n";
                break;
        case 3:
                msg = "$Nֻ������ӯ�������������ã��������߽��������Ǻεȵ����磿��\n";
                break;
        case 4:
                msg = "$N��ͷ��ף����һָ����ң����������º��ܣ������ڴˣ���ϲ������\n";
                break;
        case 5:
                msg = "$Nһ����̾��������$l���Լ��ǣ����������ж���֮Ը����\n";
                break;
        case 6:
                msg = "$N�����ķ��������ٷ���������$l֮���ҽ������죡��\n";
                break;
        case 7:
                msg = "$N�ȵ��������н���֮�£���������߯�����ˣ��˾������\n";
                break;
        default:
                msg = "$N��������������ԣ������������������ʣ���\n";
                break;
        }
        msg = replace_string(msg, "$l", ob->name(1));
        message_vision(msg, me, ob);

        r = ob->query_temp("pending/team_swear/accept");
        if (! arrayp(r) || sizeof(r) < 1)
                r = ({ me });
        else
                r += ({ me });

        if (sizeof(t) == sizeof(r) && ! sizeof(t - r) && ! sizeof(r - t))
        {
                string fail = 0;

                // ȫ��ͬ�⣬����Ƿ��ܹ���ɵ�������ͬʱ����
                // �����������
                base = 10000;
                foreach (tob in t)
                {
                        if (! objectp(tob) || environment(tob) != environment(me))
                        {
                                fail = "��Ȼ��Ҷ�ͬ��"
                                       "�ˣ���ϧ�������˲��ڣ�$N";
                                       "������ֻ�����ա�\n";
                                break;
                        }

                        if (! living(tob) || tob->is_fighting())
                        {
                                fail = "��Ȼ��Ҷ�ͬ��"
                                       "�ˣ���ϧ��������û���ʹ�"
                                       "��һͬ���壬$N������ֻ�����ա�\n";
                                break;
                        }

                        if (mapp(tob->query("league")))
                        {
                                fail = "��Ȼ��Ҷ�ͬ��"
                                       "�ˣ���ϧ" + tob->name() +
                                       "�Ѿ������˱��ͬ���ˣ�$N������ֻ�����ա�\n";
                                break;
                        }

                        base += tob->query("weiwang");
                }

                // ʧ���ˣ��޷�����
                if (stringp(fail))
                {
                        ob->delete_temp("pending/team_swear");
                        message_vision(fail, ob);
                        return 1;
                }

                // ��ɽ���
                league_name = ob->query_temp("pending/team_swear/name");
                LEAGUE_D->create_league(league_name, base, t);
                switch (random(3))
                {
                case 0:
                        msg = "��˵" + implode(t->name(1), "��") + "��� ��" HIG +
                              league_name + HIM"�����ݺὭ����";
                        break;
                case 1:
                        msg = "����" + implode(t->name(1), "��") + "���վ��壬" +
                              "����� ��" HIG + league_name +  HIM"�� ���𶯽�����";
                        break;
                default:
                        msg = "��˵" + implode(t->name(1), "��") + "��Ͷ��ϣ�" +
                              "������ˣ����� ��" HIG + league_name + HIM "����";
                        break;
                }

                msg = sort_string(msg, 64, strlen("���������š�ĳ�ˣ�"))[0..<2];
                CHANNEL_D->do_channel(this_object(), "rumor", msg);
                ob->delete_temp("pending/team_swear");
        } else
                ob->set_temp("pending/team_swear/accept", r);

        return 1;
}

int do_refuse(object me, object ob)
{
        object *t;
        string msg;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

        t = ob->query_temp("pending/team_swear/member");
        if (! arrayp(t))
		return notify_fail("�˼������Ѿ�����������ˡ�\n");

        if (member_array(me, t) == -1)
                return notify_fail("�������Ѿ������˼ҵĽ��忼�Ƿ�Χ֮���ˡ�\n");

        ob->delete_temp("pending/team_swear");
        message_vision("$Nҡ��ҡͷ����$n���������ǵ������Ҳ��ܣ�������û����Ȥ����\n",
                       me, ob);
        t -= ({ 0 });
        message("vision", YEL + me->name(1) + "�ܾ���" + ob->name(1) +
                "�Ľ������顣\n" NOR, t, me);
        return 1;
}