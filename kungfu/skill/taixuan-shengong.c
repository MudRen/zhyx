// taixuan-shengong.c ̫����
// By haiyan

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
    "$n�����ĳ������絽������$N��������һ�ߡ�\n",
    "$n�ֱۻ�ת��ץס$N����һ�ƣ���$NԶԶ������\n",
    "$n������ţ���Ծ��������������ʮ�����⡣\n",
    "$Nֻ����ǰһ����ֻ����$n����һ�ϣ��Լ���������ȻĪ�����������ˡ�\n",
});

mapping *action = ({
([  "action":"$N����һ�ƣ�һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
    "force" : 220,
    "attack": 110,
    "parry" : 80,
    "dodge" : 75,
    "damage": 90,
    "lvl" : 0,
    "damage_type":  "����"
]),
([  "action":"$N����ת����ͣ��ͻȻһ�С�һ����Ϭ��ʹ��������$w����һ������������$n$l��",
    "force" : 230,
    "attack": 130,
    "parry" : 102,
    "dodge" : 95,
    "damage": 100,
    "lvl" : 30,
    "damage_type":  "����"
]),
([  "action":"$N�����������$n�۰���Ѹ���ޱȵ�һ����$nһ�ӵ��˳�ȥ",
    "force" : 250,
    "attack": 150,
    "parry" : 120,
    "dodge" : 115,
    "damage": 105,
    "lvl" : 50,
    "damage_type":  "����"
]),
([  "action":"$N����$w�󿪴��أ�ÿһ����$n��ȥ�������ƿ�ɽ��һ�㣬��һ���Ƶ��۵ġ�������⡹��",
    "force" : 260,
    "attack": 180,
    "parry" : 130,
    "dodge" : 105,
    "damage": 110,
    "lvl" : 80,
    "damage_type":  "����"
]),
([  "action":"$N���һ�����ſ�һ��������$n������ȥ",
    "force" : 280,
    "attack": 190,
    "parry" : 135,
    "dodge" : 120,
    "damage": 120,
    "lvl" : 100,
    "damage_type":  "����"
]),
([  "action":"$N����һԾ��ʹ�˸����˷��ȥ����ȴ��ת��֮�ʶ�׼$n$lбб�ӳ�һ����",
    "force" : 290,
    "attack": 210,
    "parry" : 155,
    "dodge" : 115,
    "damage": 130,
    "lvl" : 130,
    "damage_type":  "����"
]),
([  "action":"$N�����ϣ�˫���͵�����$n",
    "force" : 300,
    "attack": 220,
    "parry" : 140,
    "dodge" : 120,
    "damage": 150,
    "lvl" : 150,
    "damage_type":  "����"
]),
([  "action":"ֻ��$N�����أ�ʹ��һ�С������ƶˡ�������$w�������ó���㺮�ǣ�ֱ��$n��$l��",
    "force" : 330,
    "attack": 260,
    "parry" : 140,
    "dodge" : 120,
    "damage": 180,
    "lvl" : 180,
    "damage_type":  "����"
]),
([  "action":"$N����΢�࣬ͻȻ����һ�ţ�����$n����·���ŵ���;���͵�һ̧������$n����",
    "force" : 350,
    "attack": 220,
    "parry" : 150,
    "dodge" : 120,
    "damage": 210,
    "lvl" : 200,
    "damage_type":  "����"
]),
([  "action":"ֻ��$N���ʮ���佣��������ʮ������ʽ��罫$n�������С�",
    "force" : 360,
    "attack": 240,
    "parry" : 150,
    "dodge" : 110,
    "damage": 230,
    "lvl" : 230,
    "damage_type":  "����"
]),
([  "action":"$N����һԾ������$wһ�С����к�ء���׼$n��$lбб�̳�һ����",
    "force" : 350,
    "attack": 220,
    "parry" : 150,
    "dodge" : 120,
    "damage": 260,
    "lvl" : 250,
    "damage_type":  "����"
]),
([  "action":"$NͻȻ������һ�࣬��ס$n��·������������ӿ����",
    "force" : 380,
    "attack": 220,
    "parry" : 160,
    "dodge" : 125,
    "damage": 280,
    "lvl" : 280,
    "damage_type":  "����"
]),
([  "action":"$N�����һ����Х������$w�������ֱָ$n��$l��",
    "force" : 400,
    "attack": 250,
    "parry" : 140,
    "dodge" : 165,
    "damage": 320,
    "lvl" : 300,
    "damage_type":  "����"
]),
});

int valid_enable(string usage)
{
     object me;
     string verb;

     me = this_player();
     if (!me || !userp(me)) return usage == "force";

     verb = me->query("taixuan");

     if (verb == "force")    return usage == "force";
     if (verb == "sword")    return usage == "sword" || usage == "parry";
     if (verb == "dodge")    return usage == "dodge";
     if (verb == "unarmed")  return usage == "unarmed" || usage == "parry";
}

int valid_force(string force)  { return 1; }
int can_not_hubo() {return 1;}

int double_attack()  { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("taixuan-shengong", 1);
        return lvl * lvl * 15 * 22 / 100 / 200;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("taixuan-shengong", 1);
        for (i = sizeof(action); i > 0; i--)
             if (level > action[i-1]["lvl"])
                  return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level, mar;
        string verb;

        mar = (int)me->query_skill("martial-cognize", 1);

        if ((int)me->query_skill("literate", 1) > 200)
             return notify_fail("�㱥��ʫ�飬�޷�������ӵ�̫���񹦡�\n");

        if ( ! ultrap(me) )
             return notify_fail("�����ѧ���о�̫����ǳ��"
                                "һʱ֮���������̫���񹦡�\n");

        if (mar < 200)
             return notify_fail("�����̫���񹦹�����£���"
                                "�Լ�����ѧ����ȫȻ�޷����ס�\n");

        level = me->query_skill("taixuan-shengong", 1);

        if ((string)me->query("gender") == "����" && level > 49)
             return notify_fail("���޸����ԣ����������������������̫���񹦡�\n");

        if (mar < 500 && mar < level)
             return notify_fail("������Լ�����ѧ�������ޣ��������������̫���񹦡�\n");

        verb = me->query("taixuan");

        switch(verb)
        {
             case "force":
                  if ((int)me->query_skill("force", 1) < level)
                         return notify_fail("��Ի����ڹ�����⻹������"
                                            "�޷��������������̫���񹦡�\n");
                  break;
             case "sword":
                  if ((int)me->query_skill("sword", 1) < level)
                         return notify_fail("��Ի�����������⻹������"
                                            "�޷��������������̫���񹦡�\n");
                  break;
             case "dodge":
                  if ((int)me->query_skill("dodge", 1) < level)
                         return notify_fail("��Ի����Ṧ����⻹������"
                                            "�޷��������������̫���񹦡�\n");
                  break;
             case "unarmed":
                  if ((int)me->query_skill("unarmed", 1) < level)
                         return notify_fail("��Ի���ȭ�ŵ���⻹������"
                                            "�޷��������������̫���񹦡�\n");
                  break;
        }
        return 1;
}

mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp;

        if ((int)me->query_skill("taixuan-shengong", 1) < 100)
             return;

        if ((string)me->query("taixuan") != "dodge")   return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;

        dp = target->query_skill("force", 1) + target->query_skill("dodge", 1);
        ap = me->query_skill("dodge", 1) + me->query_skill("taixuan-shengong", 1);

        if (ap / 3 + random(ap) > dp)
        {
                me->add("neili", -30);
                msg = dodge_msg[random(sizeof(dodge_msg))];
                msg = replace_string(msg, "$N", "$N" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;
                result = ([ "damage": -damage,
                            "msg"   : msg ]);
                return result;
        }
}

int practice_skill(object me)
{
        return notify_fail("̫���񹦲�����޷��򵥵�ͨ����ϰ������\n");
}

string perform_action_file(string action)
{
        object me = this_player();

        if ((string)me->query("taixuan") == "sword")
             return __DIR__"taixuan-shengong/perform/sword/" + action;

        if ((string)me->query("taixuan") == "unarmed")
             return __DIR__"taixuan-shengong/perform/unarmed/" + action;
}

string exert_function_file(string action)
{
        object me = this_player();

        if ((string)me->query("taixuan") == "force")
             return __DIR__"taixuan-shengong/exert/" + action;
}

