// wangqing-jian.c
// by yuchang

#include <ansi.h>
inherit SKILL;

mapping *action = ({
        ([      "name":         "�����",
                "action":       "$Nʹ�����齣���е�"+HIY"���������"NOR+"$N�ѷ·������ں���һ����ɲ�Ǽ���ǲԲ���񷣬���޵�ֹ��Ҳû�и��顣",
                "dodge":        200,
                "parry" :       400,
                "force":        470,
        "damage" :  300,
                "damage_type":  "����"
        ]),
        ([      "name":         "���ƾ�",
             "action":       "$Nʹ�����齣���е�"+HIW"�����ƾ���"NOR+"��$N��ʱ������ǣ��ٵ���϶���˻�����",
                "dodge":        300,
                "parry" :       300,
                "force" :       300,
        "damage":   450,
                "damage_type":  "����"
        ]),
        ([      "name":         "������",
                "action":       "$N�ٽ���ü����ׯ������$w�������ڰ�գ�ңָ$n��ʹ�����齣���е�"+HIR"����������"NOR,
                "dodge":        430,
                "parry" :       300,
                "force":        470,
        "damage" :  500,
                "damage_type":  "����"
        ]),
        ([      "name":         "��˼��",
                "action":       "$Nʹ�����齣���е�"+HIB"����˼����"NOR+"����һЩ���������ơ����֡���������ס$n���Ծ���������������ʹ$n׹�������³���֮��",
                "dodge":        320,
                "parry" :       280,
                "force" :       280,
        "damage":   550,
                "damage_type":  "����"
        ]),
        ([      "name":         "��Ͼ�",
                "action":       "$Nʹ�����齣���е�"+HIC"����Ͼ���"NOR+"��ٿ��һ������������ȥ��һ���֣���ժ�±����$w�������ࡱ������һ��������",
                "dodge":        300,
                "parry" :       400,
                "force" :       400,
                "damage":       550,
                "damage_type":  "����"
        ]),
        ([      "name":         "������",
                "action":       "$Nֻ��һ�ɹ���ؾó��ĺ����������м���ȫ��ʹ�����齣���е�"+BLU"����������"NOR+"����Ϯ$n",
                "dodge":        400,
                "parry" :       430,
                "force" :       350,
                "damage":       500,
                "damage_type":  "����"
        ]),
        ([      "name":         "������",
                "action":       "$nֻ����һ��ǿ���ѹ��������ǵص�ӿѹ������������Ȼ�к����������齣���еġ���������",
                "dodge":        400,
                "parry" :       400,
                "force" :       400,
                "damage":       550,
                "damage_type":  "����"
        ]),
        ([      "name":         "�����",
                "action":       "$n��Ҫ�̳�����Ȼ���÷�ӿ�ƶ�������$Nһ���Զ����裬���˽�ȥ,   ����"+HIG"���������"NOR,
                "dodge":        400,
                "parry" :       400,
                "force" :       400,
                "damage":       400,
                "damage_type":  "����"
        ]),
});

int valid_learn(object me)
{
        return notify_fail("���齣��ֻ�ܿ��ж��������������!��\n");

}

int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry" || usage=="dodge";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        write("���齣����������\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

int effective_level() { return 25;}

string *dodge_msg = ({
       "$n��������Ծ��ƽ���ӳ�������һ�㣬���Ʒ��������һ�ۣ������˳�ȥ��\n",
       "$n��δ�أ�����ȴ�ص��ɶ������������ǣ�б�����䡣\n",
       "$nһ�㣬�ּ��س������ȥ�ƾ�����$n�ڽ�����ӳҫ�������ȸ�������ƿն�ȥ��\n",
       "������һ���ۼ䣬$nٿȻ�����ˣ�һ����ӹ����������͡�\n",
        "$nʩչ�ˡ��������顱�еġ���ӳ����������ɫ��������ʧ�ˡ�\n",   
       "����΢�磬��ɼ������������,$n������Ҷ����Ʈ��$N����������"+HIW"��������"NOR+"һ��\n",
});

string *parry_msg = ({
       "$n��"+MAG"��ʦ�̾���"NOR+"֮�ƣ�������$N֮��,����$N����һ�ִ��.\n",
      "$n����ɲ�Ǽ䣬��������һ����ľ������˲�佫���е�Ѩ��ȫ������.����"+HIM"��ľ�����NOR\n",
       "$n����"+CYN"��ˮ�ž���"NOR+"��$n��Χ������������ˮ����$N������ȫ����ˮǽ�ϣ����޷�͸��.\n",
        "$n����ңԶ�Ļ��ҡ�Σ���"+RED"�����Ӿ���"NOR+"֮�ƣ�������Ŀ,����һ��.\n",
        "$n��"+YEL"�����ھ���"NOR+"Ѹ�ٵ��ڵ��Ͼ򿪶�,$n������\n",
});

string *unarmed_parry_msg = ({
       "$nʹ��$v������ǰ������һ��ͭǽ���ڣ���ס��$N�Ĺ��ơ�\n",
        "$nһ�����е�$v����ס��ȫ��\n",
        "$n��$v������һ�̣�$v�����������պ�ֱ��$N��˫�ۡ�\n",
        "$n�ٽ�������һ�������ӽ���͸�����ƿ���$N��\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}


string perform_action_file(string action)
{
        return __DIR__"wangqing-jian/" + action;
}



