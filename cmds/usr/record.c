// record.c

#include <ansi.h>

inherit F_CLEAN_UP;

/** ������ݱ�ǣ����WIZ������ͳһ�淶����¼���ڻ��ң�
 * birthgift ������������¼
 * festival ��ҽ��������¼
 * gift �Ե���¼
 * job �ɿ��˻������¼����ɺ�ɾ����
 * map ��ͼ���ݼ�¼
 * mark �����򹤵����ݼ�¼(�Ƽ�֧������job���ݺͽ���״̬��Ǽ�¼�ڴ�)
 * mirror_* ���������¼
 * over_quest ��������|ת���������ؼ�¼(�Ƽ���Ҫ����quest���ݼ�¼�ڴ�)
 * quest* ���������¼
 * rumor �����¼���¼
 * skybook ����������������¼
 * state ���״̬���ݼ�¼(�Ƽ�������״̬ͳ�����ݼ�¼�ڴ�)
 * static ��Ȼ�����Ƽ�¼
 * story ���¼�¼
 * tattoo �����¼
 */

int main(object me, string arg)
{
    object ob;
    mapping my;
    string line;

    if (!arg)
        ob = me;
    else if (wizardp(me) && SECURITY_D->valid_grant(me, "(wizard)"))
    {
        ob = present(arg, environment(me));
        if (!ob || !ob->is_character())
            ob = find_player(arg);
        if (!ob || !ob->is_character())
            ob = find_living(arg);
        if (!ob || !ob->is_character())
            return notify_fail("��Ҫ�쿴˭��״̬��\n");
    }
    else
        return notify_fail("ֻ�������ܲ쿴���˵�״̬��\n");

    my = ob->query_entire_dbase();

    if (playerp(ob) && (!stringp(my["born"])))
        return notify_fail("��û�г����ţ��쿴ʲô��\n");

    if (!mapp(my["mark"]))
    {
        my["mark"] = ([]);
    }
    if (!mapp(my["state"]))
    {
        my["state"] = ([]);
    }
    if (!mapp(my["over_quest"]))
    {
        my["over_quest"] = ([]);
    }
    if (!my["state"]["quest"])
    {
        my["state"]["quest"] = my["quest_count"];
    }
    if (!my["state"]["mirror"])
    {
        my["state"]["mirror"] = my["mirror_count"];
    }

    line = (ob == me ? "��" : ob->name()) + "����Ϸ��¼���£�\n";
    line += HIC "��" HIY "----------------------------------------------------------------" HIC "��\n" NOR;
    // line += sprintf(HIW " ����������ȡ������%d ��\n", sizeof(my["birthgift"]));
    // line += sprintf(HIW " ����������������%d ��\n", my["state"]["pray"]);
    // line += "\n";
    line += sprintf(HIW " %-30s%-20s\n", "����������" + my["mark"]["job_smith"] + " ��", "���������" + my["mark"]["job_copy"] + " ��");
    if (my["gender"] == "Ů��")
    {
        line += sprintf(HIW " %-30s%-20s\n", "�÷������" + my["mark"]["job_sew"] + " ��", "���˴�����" + my["mark"]["job_cook"] + " ��");
    }
    line += sprintf(HIW " %-30s%-20s\n", "ĥҩ������" + my["mark"]["job_peiyao"] + " ��", "�ֻ�������" + my["mark"]["job_zhonghua"] + " ��");
    line += sprintf(HIW " �����򹤴�����%d ��\n", my["mark"]["guofu_job"]);
    line += sprintf(HIW " %-30s%-20s\n", "��ʯ������" + my["mark"]["job_mine1"] + " ��", "��ʯ�ͻ�������" + my["mark"]["job_transit1"] + " ��");
    line += sprintf(HIW " %-30s%-20s\n", "�ɿ������" + my["mark"]["job_mine2"] + " ��", "�ɿ��ͻ�������" + my["mark"]["job_transit2"] + " ��");
    line += "\n";
    line += sprintf(HIW " ʦ��������ɴ�����%d ��\n", my["state"]["quest"]);
    line += sprintf(HIW " ����������ɴ�����%d ��\n", my["state"]["mirror"]);
    line += sprintf(HIW " ������ս���ܴ�����%d �Σ���ʤ��%d ��\n", my["state"]["challenge"], my["state"]["challenge_win"]);
    line += sprintf(HIW " ���˴����μӴ�����%d �Σ���ʤ��%d ��\n", my["state"]["pk"], my["state"]["pk_win"]);
    // line += sprintf(HIW " ֧�߽���������%d ��\n", my["state"]["puzzle"]);
    line += "\n";
    line += sprintf(HIW " ���������%d ��\n", my["state"]["fish"]);
    line += sprintf(HIW " ���Դ�����%d ��\n", my["state"]["hunt"]);
    line += sprintf(HIW " ��ҽ������%d ��\n", my["state"]["zhenjiu"]);
    line += sprintf(HIW " ����������%d ��\n", my["over_quest"]["liandan_quest"]);
    line += "\n";
    line += sprintf(HIW " ͵�Դ�����%d ��\n", my["thief"]);
    line += sprintf(HIW " ˯��������%d ��\n", my["state"]["sleep"]);
    line += sprintf(HIW " �ƶ����룺%d ��\n", my["state"]["go"] * 5);
    line += "\n";
    if(me->query("family/family_name") == "ؤ��")
    {
        line += sprintf(HIW " ���ֳɹ�������%d ��\n", my["state"]["beg"]);
    }
    line += HIC "��" HIY "----------------------------------------------------------------" HIC "��\n" NOR;
    write(line);
    debug("����������Ϸ��¼�����С���");

    return 1;
}

int help(object me)
{
    write(@HELP
ָ���ʽ: time

���ָ���¼�������Ϸ���ݣ������Լ��ĳɾͰɡ�

HELP
    );
    return 1;
}
