// yinyun-ziqi.c ������
// �䵱�����ڹ�
// Created by Lonely

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyun-ziqi", 1);
        return lvl * lvl * 15 * 19 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("yinyun-ziqi", 1);
        int t = 1, j;

        for (j = 1; j < lvl / 10; j++) 
                t *= 2;
        if (t > 5000) t = 5000;
        if ( me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ�����������������������������񹦡�\n");

        if ( me->query("class") == "bonze" )
                return notify_fail("�����������������ϣ���Υ��������徻֮�⣬"
                                +RANK_D->query_respect(me)+"���޴˹������������\n");

        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if ((lvl > 10 && lvl < 100 && (int)me->query("shen") < t * 200)
                || ( lvl >=100 && (int)me->query("shen") < 10000))
                return notify_fail("�����������̫���ˡ�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"yinyun-ziqi/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "status_msg" : "ͷ�������������ɫ����",
                "start_my_msg" : "��ϥ������˫Ŀ���գ�������һ�������絤�������һ����Ϣ�������Ѩ��������������֮����\n",
                "start_other_msg" : "��ϥ����������˫�����ճ�ȭ����һ�ᣬͷ��ð����������\n",
                "halt_msg" : "΢һ��ü������Ϣѹ�ص������һ������վ��������\n",
                "end_my_msg" : "����Ϣ����������ʮ�����죬���ص��ֻ����ȫ��ů����ġ�\n",
                "end_other_msg" : "����һ������һ���½�վ�����������о���һ����\n"
        ]);
}


