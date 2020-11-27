// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit FORCE;
int valid_force(string force) { return 1; } 

// ����Ӧ�ñ�̫����ǿЩ
int query_neili_improve(object me)  
{
        int lvl; 
        lvl = (int)me->query_skill("bahuang-gong", 1); 
        return lvl * lvl * 24 * 15 / 100 / 200; 
}

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bahuang-gong", 1);

        if (me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ���������������������İ˻�����Ψ�Ҷ��𹦡�\n");

        if (me->query("class") == "bonze")
                return notify_fail("�˻�����Ψ�Ҷ��𹦽����������ϣ���Υ��������徻֮�⣬" +
                                   RANK_D->query_respect(me) + "���޴˹������������\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{

        return notify_fail("�˻�����Ψ�Ҷ���ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"bahuang-gong/" + func;
}

int help(object me)
{
        write(WHT"\n���˻�����Ψ�Ҷ��𹦡�\n\n"CYN+
                 " �����˻�����Ψ�Ҷ��𹦣��书�����죬������������ν��ͳ��ѧ���ྶ\n"+
                 " �ڣ��뱱ڤ�񹦼�С���๦������ң�������ڹ�������Ȼ�˹�ÿ��������\n"+
                 " ����ɢ��һ�Σ���������֮Ѫ�����������ɻָ������������쳣��\n"+
                 " �����˻�����Ψ�Ҷ���Ϊ�����ڹ������˳��������˳������ศ���ȴ\n"+
                 " �ֻ�����ƣ������չ���ѧ����ɽ����������ɽ����������������Ტ��\n"+
                 " ������֮�����ӵ����쾡�¡�\n\n"+

              WHT" Ҫ�󣺻����ڹ���           "HIR"10"WHT" ��\n"NOR);

        return 1;
}
