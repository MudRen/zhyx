// team command: bunch

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;
        object env;
        object tob;
        string msg;
        object bei;

        string pure_name;

        if (! objectp(bei = present("bei chou", environment(me))))
                return notify_fail("�������ɱ����ڱ���������С�\n");
                
        // �������ĺϷ���
        t = me->query_team();
        if (! arrayp(t))
                return notify_fail("�����ڲ����ڶ����а���\n");

        if (! me->is_team_leader())
                return notify_fail("ֻ�ж����������ܷ��������ȱ��졣\n");

        if (! arg)
                return notify_fail("����ǰ�����һ�����ְɣ�\n");

        t -= ({ 0 });

        if (sizeof(t) < 5)
                return notify_fail("���������������û�ж����ˣ�����ʲô���ɣ�\n");

        if (me->query_temp("pending/team_doing") &&
            me->query_temp("pending/team_doing") != "bunch")
                return notify_fail("�㻹�ǵ�Ŀǰ�����е������������˵�ɡ�\n");

        // �ж�����ĺϷ���
        if (arg == "cancel")
        {
                if (arrayp(t = me->query_temp("pending/team_bunch/member")))
                {
                        me->delete_temp("pending/team_bunch");
                        write("��ȡ���ʹ�Ҵ������ɵ���ͷ��\n");
                        t -= ({ 0 });
                        message("vision", YEL + me->name(1) +
                                "ȡ���˴��һͬ�������ɵĳ��顣\n", t, me);
                } else
                        write("�����ڲ�û�г����Ҵ������ɰ���\n");

                me->delete_temp("pending/team_doing");
                return 1;
        }

        if (mapp(me->query_temp("pending/team_bunch")))
        {
                write("���������Ҵ��������أ����ǵȴ�һ�Ӧ�ɡ�\n");
                return 1;
        }

        if (me->query("balance") < 200000000)
        {
                write("����������Ҫ�ܶ�Ǯ�ģ��������е�������ɲ�������\n");
                return 1;
        }
        
        if (me->query("weiwang") < 10000)
        {
                write("���ڽ������޼���֮����Ҳ��������ţ�\n");
                return 1;
        } else
        if (me->query("weiwang") < 50000)
        {
                write("������������������һ�����۰���ڣ������Ժ���˵�ɡ�\n");
                return 1;
        } else
        if (me->query("weiwang") < 80000)
        {
                write("�������ڽ�����Ҳ������Щ��ͷ�ˣ���ϧ���ǲ�����\n");
                return 1;
        } else
        if (me->query("weiwang") < 100000)
        {
                write("����Ŭ��Ŭ�������Լ�����������"
                      "���������ɵ�����Ҳ��Զ�ˡ�\n");
                return 1;
        }

        // �ж����ֵĺϷ���
        pure_name = arg;
        if (strlen(pure_name) > 10)
                return notify_fail("���������̫���ˡ�\n");

        if (strlen(pure_name) < 4)
                return notify_fail("���������̫���ˡ�\n");

        if (! is_chinese(pure_name))
                return notify_fail("���������������֡�\n");

        if (stringp(msg = BUNCH_D->valid_new_bunch(pure_name)))
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

                if (mapp(tob->query("league")) || mapp(tob->query("bunch")))
                        return notify_fail("����������������Ѿ���������֯�ˡ�\n");
                        
                if (tob->query("weiwang") < 10000)
                        return notify_fail("��������������˵Ľ������������������������������һ�����۰���ڡ�\n");
        }

        me->set_temp("pending/team_bunch/member", t);

        message_vision("$N��������������������ֵ���"
                       "Ͷ��ϣ�����Ϊ�β��������ɣ�����" +
                       "��" + arg + "������\n", me);
        me->set_temp("pending/team_bunch/name", pure_name);
        me->set_temp("pending/team_bunch/accept", ({ me }));
        me->set_temp("pending/team_doing", "bunch");
        foreach (tob in t)
        {
                if (tob == me)
                        continue;

                tell_object(tob, YEL + me->name(1) + "(" +
                            me->query("id") + ")���ô��һ"
                            "ͬ�������ɣ�������" + arg + "����"
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
        string bunch_name;

	if (! ob || environment(ob) != environment(me))
		return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

	if (! living(ob))
		return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

        t = ob->query_temp("pending/team_bunch/member");
        if (! arrayp(t))
		return notify_fail("�˼������Ѿ������㴴�������ˡ�\n");

        if (member_array(me, t) == -1)
                return notify_fail("�������Ѿ������˼ҵĴ������ɿ��Ƿ�Χ֮���ˡ�\n");

        switch (random(8))
        {
        case 0:
                msg = "$N���ͷ�����˿���ң�֣�ص�������û���������ͬ�⣡��\n";
                break;
        case 1:
                msg = "$N��ϲ�����ƴ�Ц�������������⣡������������\n";
                break;
        case 2:
                msg = "$N������Ц�������������ܺã��ܺã����ǲ�����\n";
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

        r = ob->query_temp("pending/team_bunch/accept");
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
                                       "��һͬ�������ɣ�$N������ֻ�����ա�\n";
                                break;
                        }

                        if (mapp(tob->query("league")) || mapp(tob->query("bunch")))
                        {
                                fail = "��Ȼ��Ҷ�ͬ��"
                                       "�ˣ���ϧ" + tob->name() +
                                       "�Ѿ������˱����֯�ˣ�$N������ֻ�����ա�\n";
                                break;
                        }

                        base += tob->query("weiwang");
                }

                // ʧ���ˣ��޷�����
                if (stringp(fail))
                {
                        ob->delete_temp("pending/team_bunch");
                        message_vision(fail, ob);
                        return 1;
                }

                // ��ɽ���
                bunch_name = ob->query_temp("pending/team_bunch/name");
                BUNCH_D->create_bunch(bunch_name, base, t);
                ob->add("balance", -200000000);
                switch (random(3))
                {
                case 0:
                        msg = "��˵" + implode(t->name(1), "��") + "������" +
                              bunch_name + "�����ݺὭ����";
                        break;
                case 1:
                        msg = "����" + implode(t->name(1), "��") + "�������ɣ�" +
                              "����ˡ�" + bunch_name + "�����𶯽�����";
                        break;
                default:
                        msg = "��˵" + implode(t->name(1), "��") + "��Ͷ��ϣ�" +
                              "�������ɣ�������" + bunch_name + "����";
                        break;
                }

                msg = sort_string(msg, 100, strlen("���л����ɡ�ĳ�ˣ�"))[0..<2];
                CHANNEL_D->do_channel(this_object(), "rumor", msg);
                ob->delete_temp("pending/team_bunch");
        } else
                ob->set_temp("pending/team_bunch/accept", r);

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

        t = ob->query_temp("pending/team_bunch/member");
        if (! arrayp(t))
		return notify_fail("�˼������Ѿ������㴴�������ˡ�\n");

        if (member_array(me, t) == -1)
                return notify_fail("�������Ѿ������˼ҵĴ������ɿ��Ƿ�Χ֮���ˡ�\n");

        ob->delete_temp("pending/team_bunch");
        message_vision("$Nҡ��ҡͷ����$n���������ǵ������Ҳ��ܣ�������û����Ȥ����\n",
                       me, ob);
        t -= ({ 0 });
        message("vision", YEL + me->name(1) + "�ܾ���" + ob->name(1) +
                "�Ĵ����������顣\n" NOR, t, me);
        return 1;
}
