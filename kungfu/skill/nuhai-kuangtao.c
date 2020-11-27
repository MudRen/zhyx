// nuhai-kuangtao.c    ŭ������

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "yunv-xinfa" ||
               force == "jiuyang-shengong";

}


int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nuhai-kuangtao", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        if ( me->query("gender") == "����")
                return notify_fail("���޸����ԣ������ѵ���������ϰŭ�����Ρ�\n");

        if (me->query("gender") == "Ů��")
                return notify_fail("ŭ�������Ǹ����ڹ���������Ů����ѧ��\n");


        if ((int)me->query_skill("yunv-xinfa", 1) < 50)
                return notify_fail("�����Ů�ķ���򻹲�����\n");

        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("��Ļ���������򻹲�����\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("ŭ������ֻ����ѧ(learn)�����������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"nuhai-kuangtao/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short" : me->name()+"��ϥ���ڵ��ϣ����������з�����Х����Ϣ������",
"start_self"  : HIG"����ϥ����������ԴԴ���ϵ���תȫ����ʼ�˹����ˡ�\n"NOR,
"on_self"     : HIM"����������������󣬱̺���Х�������������ȣ����ƽ�����ת��\n"NOR,
"start_other" : HIG""+me->name()+"��ϥ���£�Ƭ�̼䣬��������������Х������������������\n"NOR,
"finish_self" : HIG"��е���Х���������ˣ��������棬������ȻȬ����վ��������\n"NOR,
"finish_other" :me->name()+"һ����Х����ͬ���캣��ϯ�����������ͦ�������ȴ�Ǿ�������\n",
"unfinish_self" :"��е������϶��������޷��������ˣ������ȥ���Ʊ��߻���ħ��ֻ���ݻ����ˡ�\n",
"unfinish_other":me->name()+"ҡ����������һ��鴤����������ʮ�����ء�\n",
"halt_self"   : "������һ������������߲���Х����ѹ��������վ��������\n",
"halt_other"  : me->name() +"����������վ�������������ƺ�������ת��\n",
        ]);
}

