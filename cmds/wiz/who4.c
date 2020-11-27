//����鿴kar  by xiner 

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        object *ob_list, *wiz_ob;
        mapping dbase;
        string line;
        int i;
        int delta;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());

        ob_list = users();
        wiz_ob = filter_array(ob_list, (: wizardp :));
        ob_list -= wiz_ob;

        wiz_ob  = sort_array(wiz_ob, "sort_wizard");
        ob_list = sort_array(ob_list, "sort_user");
        ob_list = wiz_ob + ob_list;

        str =WHT"����������������������������������������������������������������������\n"NOR
             HIG"���       ����| ����| ����| ��| ��ò| ��Ե| ����| ԪӤ| ����| ת�� \n"NOR
             WHT"����������������������������������������������������������������������\n"NOR;

        i = 0;
        foreach (ob in ob_list)
        {
                dbase = ob->query_entire_dbase();
                line = sprintf(NOR"%-10s  "
                               HIW"%2d |"
                               HIW"%4d |"
                               HIW"%4d |"
                               HIW"%4d |"
                               HIR"%4d |"
                               HIM"%4d |"
                               HIY"%4d |"
                               HIY"%4d |"
	                       HIY"%4d |"
                               HIY"%4d \n" NOR,
                               ob->name(1),
                               ob->query("str") - ob->query("gift/str/succeed") - ob->query("gift/sun"),
                               ob->query("int") - ob->query("gift/int/succeed") - ob->query("gift/water"),
                               ob->query("con") - ob->query("gift/con/succeed") - ob->query("gift/lighting"),
                               ob->query("dex") - ob->query("gift/dex/succeed") - ob->query("gift/feng"),
                               dbase["per"],
                               dbase["kar"],
                               dbase["breakup"],
                               dbase["animaout"],
                               dbase["death"],
                               dbase["reborn"],);

                str += line;

                if (i++ >= 200) break;
        }
        str += WHT"��������������������������������������������������������������������\n"NOR +
               sprintf("%s���� %d λʹ���������С�\n", LOCAL_MUD_NAME(), sizeof(ob_list));
        me->start_more(str);
        return 1;
}

int sort_wizard(object ob1, object ob2)
{
	return (int)SECURITY_D->get_wiz_level(ob2) -
               (int)SECURITY_D->get_wiz_level(ob1);
}

int sort_user(object ob1, object ob2)
{
        return ob2->query("mud_age") - ob1->query("mud_age");
}

int help(object me)
{
        write(@HELP
ָ���ʽ��who3

�����Ϣ��ѯ�б�3��
HELP );
        return 1;
}            
