
inherit SKILL;
#include <ansi.h>

mapping zhaoshi = ([
        "dodge" : ({ -50,-10,10,20,30,50,60,30,20,-30,}),
        "damage"        : ({ 150,100,90,70,50,30,40,80,70,130,}),
        "parry" : ({ -25,-50,-80,-20,-20,-25,-50,-80,-20,-20,}),
        "force" : ({  130,100,80,70,60,60,70,80,100,120, }),
        "attack"        : ({  130,100,80,70,60,60,70,80,100,120, }),
        "damage_type"   : ({ "����","����","����","����","����","��Ѩ","������","����","����","����"}),
        "limbs" : ({    "����","���","����","���","���","���","����",
                                "����","�Ҽ�","����","�ҽ�","�ұ�","�ҽ�","����",
                                "����","�����","С��","��","����", }),
        "action"        : ({ 
                "$Nʹһ��"+BLINK""+HIW"��ӭ����������"NOR"������$w��������$n���ţ���ɤ��ǰ��",
                "$N���㾫�񣬶���$w��һ��"+BLINK""+HIG"������Ѱ�ߡ�"NOR"����$n$l",
                "$Nһ���粽��ʹһ��"+BLINK""+HIC"����ɽ��ˮ��"NOR"������$w�������ٴ���$n��$l",
                "$Nһ��ǹ�ѣ�ž����һ������"+BLINK""+HIM"�����ǹ����"NOR"���������ң�����ʵʵ����$nȫ��Ҫ��",
                "ֻ��$Nһ��б�磬ʹ��"+BLINK""+HIR"���ٻ������ơ�"NOR"������$w����һ�����������¶��ϼ���$n$l",
                "ֻ��$N����һ��������$w�����벻���ĽǶȴ���$n��$l��\n��һ��"+BLINK""+HIB"�����߳�����"NOR"�������磬�����ޱ�",
                "$Nʹ��"+BLINK""+MAG"������Ͷ���ơ�"NOR"������б�ɣ��Ӳ���ͻ��һǹ������$n$l",
                "$N�������ߣ����Ǻ���һ��ת����æ��ʹ��һ��"+BLINK""+RED"������ǹ��"NOR"��$wһͦ����$n$l",
                "$N���һ��������$w΢�һ�С�������ӿ������ʱǹӰ���ǽ��\n�����ת�ֵ���Ю�����֮�Ʒ���$n",
                "$N����һ��������ǹӰ�Ƚ�����������ס������һ�С����귭�ơ���\nֻ����âһ����$w�����������$n",
                "$Nʹ�����������ơ����ߵ���âһ������������ӥ�������������֮�ƣ�����Ʈ��Ĵ���$n",
                "$N$wָ�أ����ΰ�����ʹ��һ�С�ԡ���ˡ�����ǰ��ȥ��\nֻ��һ����â�ӹ�����ǹ�������ƵĻ����ռ䣬����$n",
                "$N΢һ������ʹ���������ԭ����������𻨣�ֻ�����������\n$n������һƬ���֮��",
                "$N���һ����$w������һ����â��ֻ����������\n$Nǹ��һ�������С����Ʊ��ա��ݿ����࣬����$n",
                "$N$wһ����ǹӰ���죬$n��ʱ���������С���ϼ���졹��һƬ���֮��",
                "$N$wһ������$n���´���������һƬ���������С�������Ӫ���Ƶ�$n�������ˣ��޴����",
                        }),
 
]);

 
int valid_learn(object me)
{
return notify_fail("����ֻ��ѧϰ�ˡ�\n");
}

int valid_enable(string usage)
{
//return usage=="spear" || usage=="parry";
return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
int *force,*attack,*dodge,*parry,*damage;
string *action,*damage_type;

force = zhaoshi["force"];
attack = zhaoshi["attack"];
dodge = zhaoshi["dodge"];
parry = zhaoshi["parry"];
damage = zhaoshi["damage"];
action = zhaoshi["action"];
damage_type = zhaoshi["damage_type"];

return  ([      
        "action"        :       action[random(sizeof(action))],
        "attack"        :       attack[random(sizeof(attack))],
        "dodge" :       dodge[random(sizeof(dodge))],
        "damage"        :       damage[random(sizeof(damage))],
        "parry" :       parry[random(sizeof(parry))],
        "force" :       force[random(sizeof(force))],
        "damage_type"   :       damage_type[random(sizeof(damage_type))],
        ]);
}

int practice_skill(object me)
{
string msg,*msgs;
if( (int)me->query("sen") < 30)
        return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");
if( (int)me->query("kee") < 30 )
        return notify_fail("����������������Ϣһ�������ɡ�\n");
if( (int)me->query("force") < 10 )
        return notify_fail("������������ˡ�\n");
msgs=zhaoshi["action"];
msg=msgs[random(sizeof(msgs))];
msg=replace_string(msg,"$n","ǹ��");
msg=replace_string(msg,"$w","���г�ǹ");
msg=replace_string(msg,"$l","����");
message_vision(msg+"\n",me);
me->receive_damage("kee", 30);
me->add("force", -10);
return 1;
}

string perform_action_file(string func)
{
return CLASS_D("star") + "/shengdou/"+func;
}

