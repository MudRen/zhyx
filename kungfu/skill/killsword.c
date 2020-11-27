// killsword.c ��ɷ����
// by yuchang
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIW"
$N�����ݽ�����߽��������ˡ���ɷ�������ľ�ѧ�����ΰ�Ѩ���಻����\n"NOR+
YEL"$N�ٸ���������󽭱��ڣ������޾������Ű׻ܷ�������$N���һ����\n"NOR+
HIY"    �����������������\n"NOR,

        "force" : 250,
        "dodge" : 15,
        "damage": 100,
        "lvl" : 90,
        "set_name" : "���ΰ�Ѩ",
        "damage_type":  "����"
]),
([      "action" : HIB"
$N��Ŀ��Ц�������е�ɱ���������ģ��þ�ȫ��ʹ����ɷ����֮���վ���------\n\n"NOR+
HIC"�������������� ������ �� �� ��������������������������\n\n"NOR+
HIR"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"NOR+    
HIR"WWWWWWWWWWWWWWWWWWWP'dP'dWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWW'VWWWb &'''.o.. .dWWWWWWWWWWWWP~~''_{WWWWWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWb  '''''''w.     jWWWWWWWP'  ,.--''    .wWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWWbWWWWF'''''`    WWWWWWP' .-'          {WWWWWWWWWWWWWWWWWWW\n"NOR+
HIR"WWWWWWWWWWWWLLWP      jWWWWP'               .wwWWWWWWWWW WWWWWWWW\n"NOR+
HIR"WWWWW`W`W`WWWW'      jWWW'                 {WWWWWWWWWWP  `VWWWWWW\n"NOR+
HIR"WWWWWW, dWWWW'      jWWWW                 .wwWWP'.w.'WWP.WWWWWWWW\n"NOR+
HIR"WWWWWW' VWWWW        VWW'               _{WWWW( WWWW. P.WWWWWWWWW\n"NOR+
HIR"::::::':  :::         '                {  `:::::. '' ,.::::::::::\n"NOR+
HIR":::::,:::  ::                                `''''  .::::::::::::\n"NOR+
HIR"::::::::::                                       ..,:::::::::::::\n"NOR+
HIR":::::::::::   .                  ..:.      `:::::::::::::::::::::\n"NOR+
HIR":::::::::::: ::   .: ::::::::   :::::::.          `::::::::::::::\n"NOR+
HIR"::::::::::::::' .::::::::::::.    .::::::::::::::  ::::::::::::::\n"NOR+
HIR":::::::::::::'.:::::::::::::::::  ::::::::::::::'  ::::::::::::::\n"NOR+
HIR":::::::'.....:.. ::::::::'......:. :::::::::'....::.`::::::::::::\n"NOR+
HIR":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"NOR+
HIR":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"NOR,

        "force" : 300,
        "dodge" : 15,
        "damage": 600,
        "lvl" : 100,
        "skill_name" : "�л�����",
              "damage_type":  "����" 
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
me=this_player();
if(me->query_skill("force")<350)
return notify_fail("��Ļ����ڹ���Ϊ����ѧ��ɷ�������־�����\n");
if(me->query_skill("strike")<180)
return notify_fail("��Ļ����Ʒ�����ѧ��ɷ�������־�����\n");
return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("killsword", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/50)];
}

int practice_skill(object me)
{
        object weapon;


        if(this_player()->query_skill("king-of-dragon")<100)
        return notify_fail("�㻹Ҫ�ھ�����������������ǿ��\n");
        if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "sword") 
            return notify_fail("��ʹ�õ��������ԡ�\n"); 

        if ((int)me->query("qi") < 500)
        return notify_fail("���������������ɷ�������־�����\n");
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"killsword/" + action;
}



