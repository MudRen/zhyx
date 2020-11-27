// employ.c
// Create by Rcwiz for HERO.CD

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
	object ob;
	string old_status, new_status;
	int my_level, ob_level, level;

        mapping job = ([
                       "���ֵ�ʦ"  :  "teacher.c",
                       "��Ҵ���"  :  "assistant.c",
                       "��ҳά��"  :  "webmaster.c",
                       "��Ϸ����"  :  "presell.c",
        ]);

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

	if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
		return notify_fail("ָ���ʽ��employ <ʹ����> <ְλ>\n");

	if (new_status != "���ֵ�ʦ" &&
            new_status != "��Ҵ���" &&
            new_status != "��ҳά��" &&
            new_status != "��Ϸ����" &&
            new_status != "ȡ����Ӷ" )
		return notify_fail("û������ְλ��\n");

	if (! objectp(ob = present(arg, environment(me))) ||
	    ! playerp(ob))
		return notify_fail("��ֻ�ܸı�ʹ���ߵ�ְλ��\n");

	if (ob->query("viremploy/job") == new_status)
		return notify_fail("������Ѿ����θ�ְλ��\n");

        if (new_status == "ȡ����Ӷ")
        {
                  if (! mapp(ob->query("viremploy")))
                           return notify_fail("�����û�е����κ�ְλ��\n");

                  CHANNEL_D->do_channel(this_object(), "rumor", 
                             ob->name() + "(" + ob->query("id") + ")������"
                             "��ְλ��" + ob->query("viremploy/job") + " ��ȡ���ˣ�\n");

                  ob->delete("viremploy");
                  "/cmds/adm/grant"->main(me, ob->query("id") + " -d home");
                  ob->delete("can_send_msg");
                  
               	  ob->save();

                  return 1;
        }
        
        CHANNEL_D->do_channel(this_object(), "rumor", 
                             ob->name() + "(" + ob->query("id") + ")������Ϊ" + HIG +
                             new_status + NOR + "��\n");

        ob->set("viremploy/job", new_status);
        ob->set("viremploy/workroom", job[new_status]);
        ob->set("can_send_msg",1);
        tell_object(ob, HIC "�����ʹ��msgָ�����������Ϣ���\\n " NOR);
        "/cmds/adm/grant"->main(me, ob->query("id") + " home");

	ob->save();

	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : promote <ĳ��> (Ȩ�޵ȼ�)

��������Ȩ�޵ȼ�, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
һ�� admin ������Ȩ�����κεȼ�, �� arch ֻ�������� arch��
HELP );
    return 1;
}
