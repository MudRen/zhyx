// dragon-strike.c ����ʮ���� 
// by Lonely 

#include <ansi.h> 
#include <combat.h>

inherit SKILL; 

string main_skill() { return "yinyang-shiertian"; }

mapping *action = ({ 
([      "action" : "$N˫��ƽƽ�ᵽ��ǰ����ɫ���صĻ���ʩ���������лڡ�����$n��$l", 
        "force"  : 440, 
        "attack" : 100, 
        "dodge"  : 90, 
        "parry"  : 90, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
([      "action" : "$NͻȻ���η���˫�ƾӸ�����һ�С��������졹����$n��$l",     
        "force"  : 480, 
        "attack" : 100, 
        "dodge"  : 91, 
        "parry"  : 91, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
([      "action" : "$N����һ�С����������Ѹ���ޱȵ�����$n��$l", 
        "force"  : 470, 
        "attack" : 100, 
        "dodge"  : 92, 
        "parry"  : 92, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
([      "action" : "$N˫��ʩ��һ�С��轥��½�����������ŷ�������$n��$l", 
        "force"  : 460, 
        "attack" : 100, 
        "dodge"  : 93, 
        "parry"  : 93, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$N���ƾ۳�ȭ״������һ�С�Ǳ�����á���������$n��$l", 
        "force"  : 480, 
        "attack" : 100, 
        "dodge"  : 94, 
        "parry"  : 94, 
        "damage" : 90, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʩ��һ�С�����󴨡������Ʋ�������������$n��$l", 
        "force"  : 450, 
        "attack" : 100, 
        "dodge"  : 95, 
        "parry"  : 95, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʹ����ͻ�������������ƴӲ����ܵĽǶ���$n��$l�Ƴ�", 
        "force"  : 450, 
        "attack" : 100, 
        "dodge"  : 96, 
        "parry"  : 96, 
        "damage" : 90, 
        "damage_type": "����" 
]), 
([      "action" : "$N���һ����˫��ʹ�����𾪰��������һ�а����$n", 
        "force"  : 490, 
        "attack" : 100, 
        "dodge"  : 97, 
        "parry"  : 97, 
        "damage" : 120, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʹ������Ծ��Ԩ������$n��$l��������", 
        "force"  : 460, 
        "attack" : 100, 
        "dodge"  : 98, 
        "parry"  : 98, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$N���λ�����˫��ʹһ�С�˫��ȡˮ��һǰһ����$n��$l", 
        "force"  : 460, 
        "attack" : 100, 
        "dodge"  : 99, 
        "parry"  : 99, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʹ������Ծ��Ԩ�������η���˫�Ʋ���һ����$n��$l����",     
        "force"  : 450, 
        "attack" : 105, 
        "dodge"  : 100, 
        "parry"  : 100, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$N˫������ʹ����ʱ����������$n��������", 
        "force"  : 470, 
        "attack" : 100, 
        "dodge"  : 101, 
        "parry"  : 101, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʹ�������Ʋ��꡹�����Ʒ�ס$n����·������бб������$l",     
        "force"  : 460, 
        "attack" : 100, 
        "dodge"  : 102, 
        "parry"  : 102, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʹ�����������ڡ���˫�������������$n��$l", 
        "force"  : 490, 
        "attack" : 105, 
        "dodge"  : 103, 
        "parry"  : 103, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
([      "action" : "$N����һת��ͻȻ�۵�$n��ǰ��һ�С���ս��Ұ������$n��$l",     
        "force"  : 480, 
        "attack" : 110, 
        "dodge"  : 104, 
        "parry"  : 105, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$N�Ż��󿪣�һ�С���˪��������$n��$l��ȥ", 
        "force"  : 460, 
        "attack" : 100, 
        "dodge"  : 105, 
        "parry"  : 100, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$Nʹ��������ެ����˫���������ϻ���$n��$l", 
        "force"  : 480, 
        "attack" : 110, 
        "dodge"  : 106, 
        "parry"  : 100, 
        "damage" : 110, 
        "damage_type": "����" 
]), 
([      "action" : "$N���ƻ��أ�����ʹһ�С�������β�����»ζ��Ż���$n��$l",     
        "force"  : 520, 
        "attack" : 120, 
        "dodge"  : 120, 
        "parry"  : 120, 
        "damage" : 100, 
        "damage_type": "����" 
]), 
}); 

// string main_skill() { return "dragon-strike"; } 

mapping sub_skills = ([ 
       "kanglong-youhui"  : 80,        // 1 
       "feilong-zaitian"  : 80,        // 2 
       "jianlong-zaitian" : 80,        // 3 
       "hongjian-yulu"    : 80,        // 4 
       "qianlong-wuyong"  : 80,        // 5 
       "lishe-dachuan"    : 80,        // 6 
       "turu-qilai"       : 80,        // 7 
       "zhenjing-baili"   : 80,        // 8 
       "huoyue-zaiyuan"   : 80,        // 9 
       "shuanglong-qushui": 80,        // 10 
       "yuyue-yuyuan"     : 80,        // 11 
       "shicheng-liulong" : 80,        // 12 
       "miyun-buyu"       : 80,        // 13 
       "sunze-youfu"      : 80,        // 14 
       "longzhan-yuye"    : 80,        // 15 
       "lvshuang-bingzhi" : 80,        // 16 
       "diyang-chufan"    : 80,        // 17 
       "shenlong-baiwei"  : 80,        // 18 
]); 

int get_ready(object me) 
{ 
       return 1; 
} 

int get_finish(object me) 
{ 
       if (me->query("str") < 31 || me->query_str() < 45) 
       { 
               tell_object(me, "��������ϣ��ֱ�������������̧��������\n"); 
               return 0; 
       } 

       if (me->query("con") < 24 || me->query_con() < 37) 
       { 
               tell_object(me, "��������ϣ��;�����ǰ������ð��̫��Ѩͻͻ������\n"); 
               return 0; 
       } 

       if ((int)me->query_skill("force") < 150) 
       { 
               tell_object(me, "��������ϣ��������ѣ��Լ����ڹ�ˮƽ�������д���ߡ�\n"); 
               return 0; 
       } 

       if ((int)me->query("max_neili") < 1500) 
       { 
               tell_object(me, "��������ϣ������᲻��������������Ӧ�ü�������������\n"); 
               return 0; 
       } 

       if (random(10) < 5) 
       { 
               tell_object(me, "���ʮ���Ƶİ����������򣬻���������һ�ξ��ܹ��ڻ��ͨ��\n"); 
               return 0; 
       } 

       tell_object(me, HIY "��һ���ǳɣ���ʮ���ƴ�ͷ��β������һ�䣬���ж���ͨ\n" 
                           "���˽���ʮ���Ƶİ���裬�ڻ��ͨ���Ʒ��ľ�΢֮����\n" 
                           "��Ҳ�ǲ�ʹ����ô��ô�򵥡�\n" NOR); 
       return 1; 
} 

mapping query_sub_skills() 
{ 
       return sub_skills; 
} 

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }   

int valid_learn(object me) 
{ 
       if ((int)me->query("str") < 31) 
               return notify_fail("���������ӹǻ�������ʮ���ƣ�С��Ū���˸첲��\n"); 

       if ((int)me->query("con") < 24) 
               return notify_fail("���˰ɣ���������ǲ��ã���ǿѧ�ˡ�\n"); 

       if ((int)me->query_skill("force") < 150) 
               return notify_fail("����ڹ���򲻹����޷�ѧϰ����ʮ���ơ�\n"); 

       if ((int)me->query("max_neili") < 1500) 
               return notify_fail("���������ô������ڻ��ͨ����ʮ���ƣ�\n"); 

       if ((int)me->query_skill("strike", 1) < 30) 
               return notify_fail("��Ļ����Ʒ���򲻹����޷�ѧϰ����ʮ���ơ�\n"); 

       if ((int)me->query_skill("strike", 1) < (int)me->query_skill("dragon-strike", 1)) 
               return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ���ʮ���ơ�\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
       mapping a_action;
       int level, tmp;

       level = (int)me->query_skill("dragon-strike", 1);
       if (me->query_temp("xlz/hanglong"))
       {
                tmp = 4 + random(15);
                me->delete_temp("xlz/hanglong");
                return ([
                        "action": HIY "\n$N�е��������У�������΢�������ƻ��˸�ԲȦ��ƽ�Ƴ�ȥ�����ǽ���ʮ�����еġ������лڡ���\n" +
                                  "���Ƴ�ȥ�������赭д����һ��������ɲʱ֮������" + chinese_number(tmp) + "���ᾢ��һ��ǿ��һ����\n" +
                                  "���ص�����ֱ���޼᲻�ݣ���ǿ���ƣ�" NOR,
                        "dodge" : 140,
                        "parry" : 140,
                        "attack": 200,
                        "force" : 500 + 40 * tmp,
                        "damage": 100 + 20 * tmp,
                        "damage_type": random(2)?"����":"����" 
                ]);
        }
        
        return action[random(sizeof(action))]; 
} 

// int double_attack() { return 1; } 

int practice_skill(object me) 
{ 
        int cost; 

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("������ʮ���Ʊ�����֡�\n"); 

        if ((int)me->query("qi") < 110) 
                return notify_fail("�������̫���ˡ�\n"); 

        // cost = me->query_skill("dragon-strike", 1) / 5 + 90; 
        if ((int)me->query("neili") < 110) 
                return notify_fail("�����������������ʮ���ơ�\n"); 

        me->receive_damage("qi", 100); 
        me->add("neili", -100); 
        return 1; 
} 

mixed hit_ob(object me, object victim, int damage) 
{
        mixed result;
        string msg;
        int lvl; 
        
        lvl = me->query_skill("dragon-strike", 1); 
        
        if (damage < 100 || lvl < 150) return;
        
        result = ([ "damage" : damage ]);
        
        if (random(10) < 2)
                result += ([ "msg" : HIY "$N" HIY "һ�Ƽȳ���������ǰ������һ�С������лڡ���" 
                                     "������ǰ�ƣ�˫����������һ����ɽ������ѹ��������\n"
                                     HIR "$n" HIR "�������������Ե�����������ʱ�����ش����۵�һ�����³�һ����Ѫ��\n" 
                                     NOR ]);
        else
        {    
                msg = random(2) ? HIR "$n" HIR "һ���ҽУ���ǰ���������꡹������" 
                                  "�죬������Ѫ���硣\n" NOR :
                                  HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������" 
                                  "�߹Ƕ��۵�������\n" NOR;
                result += ([ "msg" : msg ]);
        }
                
        return result;
} 

string perform_action_file(string action) 
{ 
        object me = this_player();
        
        if (! me->query("family/family_name") || me->query("family/family_name") != "ؤ��")
                return 0;
                
        return __DIR__"dragon-strike/" + action; 
} 

void skill_improved(object me) 
{ 
        int i; 
        string *sub_skillnames; 

        sub_skillnames = keys(sub_skills); 
        for (i = 0; i < sizeof(sub_skillnames); i++) 
               me->delete_skill(sub_skillnames); 
} 

/*
// Let parry skill take its special effort. 
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("dragon-strike", 1)) < 100 ||
            ! living(me) || objectp(me->query_temp("weapon")))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) * 2 / 3 +
             me->query_skill("dragon-strike", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "��������һ�С�������β�������ֻ���һ�ơ�\n"
                                    "$N" HIC "�����������׺ݣ�����Ӳ�ӣ�����ܿ���\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIC "ֻ��$n" HIC "����Բ��������ֱ�ƣ�ʹ�С����������������ǰ��\n"
                                    "��һ�д��Ƿ�����ȴ����˫��֮�䲼��һ����ڡ�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "���²��ҵ�����˫�Ʒ��裬���Լ�ȫ������������֮�¡�\n"
                                    "��һ�ص���������Ԩͣ���ţ�ֱ�ް��������\n" NOR]);
                        break;
                }
                return result;
        } 
}
*/

int query_effect_parry(object attacker, object me) 
{
        int lvl;
        if (objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("dragon-strike", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

// ���ܵ�ʽ��� 
string query_description()  
{
        return 
        "����ʮ��������ֱǰ�������������������������񽣣���Ȼ"
        "�ۺ������������������о��롣���ڽ���ʮ���Ƶ�"
        "��λ�����������飬�����������������µĹ���λ�ġ�"
        "��Ȼѧϰ����Ҫ�Һ��߹�������ʮ��������ؤ��ר���书��"
        "�������ɵ����ﲻ��ѧϰ��ؤ��ѧϰ��������������ӻ�"
        "Ů���ܹ��õó������Ľл��������߹��ԣ����������Ϳ���"
        "�������ˡ��м����ط�����ѧϰ���ա����������û�� 31"
        " ������������� 24 ���������ǣ���ʡʡ���ɲ��������ˡ�"
        "����ʮ����Ҫ�Ƚ�ʮ����ѧ�뵽 80 ����Ȼ��ͨ��������"
        "�ɽ���ʮ���ơ�";
}

