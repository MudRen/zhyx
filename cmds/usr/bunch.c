// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// bunch.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int sort_bunch(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

int sort_hatred(string id1, string id2, mapping hatred);
int sort_member(string id1, string id2);
int show_bunch_info(object me, string arg);
int show_bunch_area(object me, string arg);
int show_bunch_member(object me, string arg);
int show_bunch_hatred(object me, string arg);
int show_bunch_all(object me, string arg);
int expell_bunch_member(object me, string arg);
int dismiss_bunch(object me, string arg);

int main(object me, string arg)
{
        object *obs;
        string fname;
        string *args;

        if (! arg) arg = "info";
        args = explode(arg, " ");
        if (sizeof(args) > 1)
                arg = implode(args[1..<1], " ");
        else
                arg = 0;

        switch (args[0])
        {
        case "info":
                // ��ʾͬ�˵���Ϣ
                return show_bunch_info(me, arg);

        case "member":
                return show_bunch_member(me, arg);

        case "dismiss":
                return dismiss_bunch(me, arg);

        case "top":
                return "/cmds/usr/top"->main(me, "bunch");

        case "area":
                return show_bunch_area(me, arg);
                
        case "hatred":
                // ��ʾͬ�˵ĳ���
                return show_bunch_hatred(me, arg);                
                
        case "all":
                return show_bunch_all(me, arg);

        case "out":
                if (! stringp(fname = me->query("bunch/bunch_name")))
                        return notify_fail("�����ڻ�û�м����κΰ����ء�\n");

                if (me->query_temp("pending/out_bunch"))
                {
                        // ͬ�˵������½�
                        BUNCH_D->add_bunch_fame(fname, -BUNCH_D->query_bunch_fame(fname) / 10);
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                "��˵" + me->name(1) + "(" + me->query("id") +
                                ")���޷��ˣ��Ѿ����롺" + fname + "����ȥ��");
                        me->delete_temp("pending/out_bunch");

                        // ������û���ͬ���е���Ϣ
                        UPDATE_D->clear_user_data(me->query("id"), "bunch");
                        return 1;
                }

                write("�������Ҫ��������������������ή��" + fname + "��������\n"
                      YEL "�����ȷ���ˣ���������һ�� bunch out ���\n" NOR);
                me->set_temp("pending/out_bunch", 1);
                return 1;
        }

        write("��Ч�Ĳ�����\n");
        return 1;
}

// ������ҺͲ���ѡ��ͬ�˵�����
mixed select_bunch(object me, string arg)
{
        string fam;
        object ob;

        if (! wizardp(me))
                // only wizard can show every league's list
                fam = 0;
        else
        if (stringp(arg) && arg != "")
        {
                if (! arrayp(BUNCH_D->query("member/" + fam)))
                        fam = 0;
                else
                        fam = arg;

                if (! stringp(fam) && objectp(ob = UPDATE_D->global_find_player(arg)))
                {
                        // û�� arg ���ͬ�ˣ��鿴�Ƿ��и����
                        fam = ob->query("bunch/bunch_name");
                        UPDATE_D->global_destruct_player(ob);
                        if (! stringp(fam))
                                return notify_fail("��������û�м����κΰ��ɡ�\n");
                }

                if (! stringp(fam))
                        return notify_fail("û�������ң����ܲ�����ص�ͬ�ˡ�\n");
        }

        if (! fam)
        {
                // select my league
                if (! stringp(fam = me->query("bunch/bunch_name")))
                        return notify_fail("�����ڻ�û�м����κΰ����ء�\n");
        }

        return fam;
}


// ��ʾͬ�˵ĳ���
int show_bunch_hatred(object me, string arg)
{
        mapping hatred;
        string fam;
        string *ids;
        mixed *data;
        string msg;
        string st;
        int count;
        int i;

        if (! stringp(fam = select_bunch(me, arg)))
                return 0;

        hatred = BUNCH_D->query_bunch_hatred(fam);
        if (! mapp(hatred) || ! sizeof(hatred))
        {
                write(fam + "����û��ʲô���ˡ�\n");
                return 1;
        }

        ids = keys(hatred) - ({ 0 });
        ids = sort_array(ids, (: sort_hatred :), hatred);

        count = 0;
        msg = WHT "Ŀǰ" + fam + "�ڽ����ϵĳ�ж���\n" NOR
              HIY "��������������������������������\n" NOR;
        for (i = 0; i < sizeof(ids) && count < 30; i++)
        {
                data = hatred[ids[i]];
                if (! arrayp(data) || sizeof(data) < 2 ||
                    ! stringp(data[0]) || ! intp(data[1]))
                        continue;

                st = sprintf("%s(%s%s%s)", data[0], YEL, ids[i], NOR);
                msg += sprintf("%2d. %-34s  %s%-9d%s\n",
                               ++count, st, HIR, data[1], NOR);
        }

        msg += HIY "��������������������������������\n" NOR;
        if (i < sizeof(ids))
                msg += WHT "�����ϵĵ���̫�࣬���Ծ�����\n" NOR;
        else
                msg += WHT "Ŀǰһ����" + chinese_number(i) +
                       "�ˡ�\n" NOR;
        write(msg);
        return 1;
}

// ��ʾĳһ��ͬ���е���Ա
int show_bunch_member(object me, string arg)
{
        string *member;
        string id;
        object user;
        string msg;
        int n;

        if (! arg)
        {
                if (! stringp(arg = me->query("bunch/bunch_name")))
                        return notify_fail("�����ڻ�û�м����κ�һ�������ء�\n");
        }

        if (! arrayp(member = BUNCH_D->query_members(arg)))
        {
                write("���ڽ�����û��(" + arg + ")������ɡ�\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(arg + "�����˶�ϡ�䡣\n");

        if (! wizardp(me))
        {
                if (me->query("jing") < 50)
                        return notify_fail("�����ھ��񲻼ã��޷�������Щ��Ϣ��\n");

                if (me->is_busy())
                        return notify_fail("��������æ��û��ʱ�������Щ��Ϣ��\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        msg = "";
        n = 0;
        foreach (id in member)
        {
                user = UPDATE_D->global_find_player(id);
                if (! objectp(user))
                        continue;

                n++;
                msg += user->short(1) + "\n";
                UPDATE_D->global_destruct_player(user);
        }

        if (msg == "")
                return notify_fail(arg + "�����˶�ϡ�䡣\n");

        write(arg + "Ŀǰ������" + chinese_number(n) + "�ˣ�\n" + msg);
        return 1;
}

// ��ʾĳһ��ͬ���е���Ա
int show_bunch_all(object me, string arg)
{
        mapping fame;
        string *fam;
        string id, bunch;
        object user;
        string msg;
        int n, npc, area, player;

        if (! mapp(fame = BUNCH_D->query_bunch_fame()))
        {
                write("���ڽ�����û���κ������İ��ɡ�\n");
                return 1;
        }
        
        fam = keys(fame) - ({ 0 });

        if (sizeof(fam) < 1)
                return notify_fail("Ŀǰ������û��ʲô�����İ��ɡ�\n");

        if (! wizardp(me))
        {
                if (me->query("jing") < 50)
                        return notify_fail("�����ھ��񲻼ã��޷�������Щ��Ϣ��\n");

                if (me->is_busy())
                        return notify_fail("��������æ��û��ʱ�������Щ��Ϣ��\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        fam = sort_array(fam, (: sort_bunch :), fame);
                
        msg = sprintf(WHT "%-12s%-20s%-10s%-10s%-10s%-12s\n" NOR,
                      "�������", "������", "�����", "�ΣУ���", "������", "���ʲ�(�ƽ�)");
        msg += HIY "��������������������������������������������������������������������������\n" NOR;
        
        n = 0;
        foreach (bunch in fam)
        {
                id = BUNCH_D->query(bunch + "/bangzhu");
                npc = sizeof(BUNCH_D->query_npcs(bunch));
                area = sizeof(BUNCH_D->query_areas(bunch));
                player = sizeof(BUNCH_D->query_members(bunch));
                
                user = UPDATE_D->global_find_player(id);
                if (! objectp(user))
                        continue;

                n++;
                msg += sprintf(WHT "%-12s%-20s%-10s%-10s%-10s%-12s\n" NOR,
                               bunch, user->query("name") + "(" + user->query("id") + ")",
                               player + " ��", npc + " ��", area + " ��",
                               BUNCH_D->query(bunch + "/money") / 10000 + " ��");         
               
                UPDATE_D->global_destruct_player(user);
        }

        if (n < 1)
                return notify_fail("����û���κΰ�����Ϣ��\n");

        msg += "\nĿǰ��̶����" + HIM + chinese_number(n) + NOR + "�����ɡ�\n";
        msg += HIY "��������������������������������������������������������������������������\n" NOR;

        write(msg);
        return 1;
}

// ��ʾͬ���е���Ϣ
int show_bunch_info(object me, string arg)
{
        string fam;
        object  ob;
        string  msg;
        string *member;
        string  id;
        int i;

        if (! stringp(fam = select_bunch(me, arg)))
                return 0;

        if (! arrayp(member = BUNCH_D->query_members(fam)))
        {
                write("���ڽ�����û��(" + fam + ")������ɡ�\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(fam + "����û��һ��������ҡ�\n");

        msg = WHT "\n" + fam + "�İ�������б�\n" NOR;
        msg += HIY "��������������������������������������������������������������������������\n" NOR;
        member = sort_array(member, (: sort_member :));
        foreach (id in member)
        {
                msg += sprintf(WHT "%-10s  ", id);
                if (objectp(ob = find_player(id)))
                        msg += sprintf(HIY "����   "        
                                       NOR WHT "ְλ��" HIM "%-10s "                                                                      
                                       NOR WHT "������" HIW "%-8d "
                                       NOR WHT "������" HIY "%-8d "
                                       NOR WHT "�ȼ���" HIR "%-2d\n" NOR,
                                       ob->query("bunch/title"),
                                       ob->query("score"),
                                       ob->query("weiwang"),
                                       ob->query("level"));                                       
                else
                {       ob = UPDATE_D->global_find_player(id);
                        msg += sprintf(HIR "����   "
                                       NOR WHT "ְλ��" HIM "%-10s "                                                                      
                                       NOR WHT "������" HIW "%-8d "
                                       NOR WHT "������" HIY "%-8d "
                                       NOR WHT "�ȼ���" HIR "%-2d\n" NOR,
                                       ob->query("bunch/title"),
                                       ob->query("score"),
                                       ob->query("weiwang"),
                                       ob->query("level"));                             
                        UPDATE_D->global_destruct_player(ob);
                }
        }

        msg += HIY "\n��������������������������������������������������������������������������\n" NOR;
        msg += WHT "\n" + fam + "�İ��ɰ����б�\n" NOR;
        msg += HIY "��������������������������������������������������������������������������\n" NOR;
        
        if (arrayp(member = BUNCH_D->query_npcs(fam)))
        {
                i = 0;
                foreach (id in member)
                {
                        i++;
                        ob = get_object(id); 
                        msg += sprintf("%-24.22s%s", ob->query("name") + "(" + ob->query("id") + ")",
                                       (i%3 == 0 && i > 2  ? "\n" : ""));
                }
        } else 
                msg += "���κΰ��ɣΣУ�\n";
        
        msg += HIY "\n\n��������������������������������������������������������������������������\n" NOR;
        msg += WHT "\n" + fam + "�İ��ɵ����б�\n" NOR;
        msg += HIY "��������������������������������������������������������������������������\n" NOR;             
 
        if (arrayp(member = BUNCH_D->query_areas(fam)))
        {
                i = 0;
                foreach (id in member)
                {
                        i++;
                        ob = get_object(id); 
                        msg += sprintf("%-24.22s%s", ob->short(),
                                       (i%3 == 0 && i > 2  ? "\n" : ""));
                }
        } else        
                msg += "���κΰ��ɵ���\n";

        msg += HIY "\n\n��������������������������������������������������������������������������\n" NOR;
        msg += WHT "\n" + fam + "�ϸ������뵥��\n" NOR;
        msg += HIY "��������������������������������������������������������������������������\n" NOR;
        i = (int)BUNCH_D->query(fam + "/last_area_money");
        if (! intp(i))   i = 0;
        msg += "�������룺" + MONEY_D->money_str(i) + "\n\n";
        i = (int)BUNCH_D->query(fam + "/last_npc_money");
        if (! intp(i))   i = 0;
        msg += "�������룺" + MONEY_D->money_str(i) + "\n\n";
        i = (int)BUNCH_D->query(fam + "/last_bangzhu_money");
        if (! intp(i))   i = 0;
        msg += "�������ã�" + MONEY_D->money_str(i) + "\n\n";
        msg += HIY "��������������������������������������������������������������������������\n" NOR;
                	                                            
        msg += sprintf("����%s�ڽ����Ͼ��� %s%d%s ��������\n%s���� %s%s%s ���ʽ�\n",
                       fam, HIY, BUNCH_D->query_bunch_fame(fam), NOR,
                       fam, HIY, MONEY_D->money_str(BUNCH_D->query(fam + "/money")), NOR);
        write(msg);

        return 1;
}

int show_bunch_area(object me, string arg)
{
        string fam;
        string *member;
        string id;
        object area, npc;
        string msg;
        int n;

        if (! stringp(fam = select_bunch(me, arg)))
                return 0;

        if (! arrayp(member = BUNCH_D->query_areas(fam)))
        {
                write("���ڰ���" + fam + "û���κε��̡�\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(fam + "����û���κε��̡�\n");

        if (! wizardp(me))
        {
                if (me->query("jing") < 50)
                        return notify_fail("�����ھ��񲻼ã��޷�������Щ��Ϣ��\n");

                if (me->is_busy())
                        return notify_fail("��������æ��û��ʱ�������Щ��Ϣ��\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        msg = sprintf(HIC "\n%-16s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR,
                      "��������", "פ�أΣУ�", "�ʽ��", "������",
                      "�ʲ����ƽ�", "�������루������", "�ҳ϶�");
                      
        msg += HIY "������������������������������������������������������������������������������������������\n" NOR;
                
        n = 0;
        foreach (id in member)
        {
                area = get_object(id);
                if (! objectp(area))
                        continue;
                
                // npc = get_object(area->query("bunch/npc_file"));
                
                n++;
                msg += sprintf(HIC "%-16s%-20s%-8s%-8s%-14s%-18s%-8s\n" NOR, 
                               area->short(), area->query("bunch/npc_name") + "(" + area->query("bunch/npc_id") + ")",
                               area->query("area/ziyuan") ? area->query("bunch/jizhi") + "%" : "----", 
                               area->query("area/ziyuan") ? area->query("bunch/kaifa") + "%" : "----", 
                               area->query("bunch/money") / 10000 + " ��", 
                               area->query("bunch/last_money") / 100 + " ��",
                               area->query("bunch/zhongcheng") + "%");
        }

        if (n < 1)
                return notify_fail(arg + "����û���κε��̡�\n");

        msg += "\nĿǰ" + HIM + fam + NOR + "����" + HIM + chinese_number(n) + NOR + "�����̡�\n";
        msg += HIY "������������������������������������������������������������������������������������������\n" NOR;
        // me->start_more(msg);
        write(msg);
        return 1;
}
        
// ��ʾĳһ��ͬ���е���Ա
int dismiss_bunch(object me, string arg)
{
        string *member;
        string id;
        object user;
        string msg;
        int n;

        if (wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("���Ȩ�޲���������ǿ�н�ɢ���ɡ�\n");

        if (! arg)
                return notify_fail("��Ҫ��ɢ�ĸ����ɣ�\n");

        if (! arrayp(member = BUNCH_D->query_members(arg)))
        {
                write("���ڽ�����û��(" + arg + ")������ɡ�\n");
                return 1;
        }

        write("��ǿ�н�ɢ��" + arg + "��\n");
        BUNCH_D->dismiss_league(arg);
        return 1;
}

int expell_bunch_member(object me, string arg)
{
        string fname;
        object ob;
        
        if (! stringp(fname = me->query("bunch/bunch_name")))
        {
                write("�����ڻ�û�м����κΰ����ء�\n");
                return 1;
        }
        
        if (me->query("bunch/level") != 9)
        {
                write("ֻ�а�������Ȩ������ĳ�˳���ᣡ\n");
                return 1;
        }
        
        if (arg == me->query("id"))
        {
                write("�����Լ����㻹�����ɢ��İ��ɣ�\n");
                return 1;
        }
           
        if (! objectp(ob = find_player(arg)))
        {
                ob = UPDATE_D->global_find_player(arg);

                if (! objectp(ob))
                { 
                        write("û�������ҡ�\n");
                        return 1;
                } 
        
                if (ob->query("bunch/bunch_name") != fname)
                {
                        UPDATE_D->global_destruct_player(ob);                                                      
                        write("��������İ������ˣ�����Ȩ��������\n");    
                        return 1;                   
                        
                }
                UPDATE_D->global_destruct_player(ob);
                
        }
        
        BUNCH_D->add_bunch_fame(fname, -BUNCH_D->query_bunch_fame(fname) / 20);
       
        if (objectp(ob))
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + ob->query("name") + "(" + arg + ")" +
                        "�����ɡ�" + fname + "���������ˡ�");

        UPDATE_D->clear_user_data(arg, "bunch");
        
        return 1;
}

// �����еĳ�޶�������
int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return 1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return -1;

        return d2[1] - d1[1];
}

// ��ͬ���е����н����Ա����
int sort_member(string id1, string id2)
{
        object ob1, ob2;

        ob1 = find_player(id1);
        ob2 = find_player(id2);
        if (! objectp(ob1) && ! objectp(ob2))
                return strcmp(id2, id1);

        if (objectp(ob1) && objectp(ob2))
                return ob2->query("combat_exp") - ob1->query("combat_exp");

        if (objectp(ob1))
                return -1;

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: bunch info [���] | hatred [���] | member [��������] | top | area

�鿴Ŀǰ�����ڰ��ɵĸ�����Ϣ�����У�

info   ���鿴�����е������Ա״̬��������
hatred ���鿴���ɵĳ�޶���
member ���鿴ĳ�����ɵĳ�Ա��
top    ���鿴���ɵ�����������
area   : �鿴���ɵĵ�����Ϣ��
all    : �鿴���еİ�����Ϣ��

��ʦ���Բ鿴�������ɵ���Ϣ��ֻ��Ҫ�����������ϰ��ɵ����ֻ�
�ǰ����е���ҡ�������ʦ����ʹ�� bunch dismiss  ����ǿ�н�ɢ
һ�����ɡ�

see also: league (����ͬ��)
HELP );
        return 1;
}

