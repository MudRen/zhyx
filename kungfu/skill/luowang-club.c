// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// luowang-club.c ����������

#include <ansi.h> 
#include <combat.h>

inherit SKILL; 

mapping *action = ({ 
([      "action" :
       "$N���еĹ�����������һ��,������һ��[˳�����],�ǹ�βֱ ��$n��$l��ȥ",     
       "force"  : 350, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 230, 
       "damage_type": "����" 
]), 
([      "action" :"$N���ȵ�أ����ϰγ����࣬$w����ó�������Ӱ��
$n��ס�����д��һ��[ѩ���Ƕ�]��ֻ��������������������$n��$1��ȥ",     
       "force"  : 380, 
       "attack" : 200, 
       "dodge"  : -5, 
       "parry"  : -80, 
       "damage" : 250, 
       "damage_type": "����" 
]), 
([      "action" : "$N��$wһ�ܣ���ס��$n��ȥ·��$N���е�$wһ�񣬴��������ɽ�⣬
����������Ƭ��â�г��һ�����̣�ֱ��$n��$1��ȥ������һ�У۲��Ƽ��գ�",
       "force"  : 400, 
       "attack" : 200, 
       "dodge"  : -40, 
       "parry"  : -105, 
       "damage" : 280, 
       "damage_type": "����" 
]), 
([      "action" :       "$N���е�$wһ���Թ��е�ʽ���󿪴���,       
       $w����������Ӱ��$n��$1������ȥ",      
       "force"  : 420, 
       "attack" : 180, 
       "dodge"  : -15, 
       "parry"  : -80, 
       "damage" : 280, 
       "damage_type": "����" 
]), 
([      "action" : "$N�������һת,���:[������β],$w����������Ӱɨ��$n������", 
       "force"  : 420, 
       "attack" : 190, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 290, 
       "damage_type": "����"
]), 
([     "action" : "$N����һչ,��Ϊ[���Ӵ���]ʽ,���е�$w��������ش���$n�ĵ�$l",
       "force"  : 450,
       "attack" : 150,
       "dodge"  : -20,
       "parry"  : -120,
       "damage" : 310,
       "damage_type": "����"
]), 
([     "action" : "$N��������һ��,������ǹ���ַ�,һʽ[������ˮ],���е�$w��$n��$l��ȥ",
       "force"  : 520, 
       "force" : 460, 
       "attack" : 160, 
       "dodge"  : -40, 
       "parry"  : -100, 
       "damage" : 90, 
       "damage_type": "����" 
]), 
([      "action" : "$N���е�$w���˸����������ȶ�����$w���һ�������д��һ��
��������[������ɽ]��ֻ��$w��һ����Х��$n��$1��ȥ",
       "force"  : 490, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -75, 
       "damage" : 320, 
       "damage_type": "����" 
]), 
([      "action" : "$N��һ�ڣ�˫��˳���������£�����$wһ����һʽ��Ϭţ����],
       ���е�$w���糤�磬������$n��$1��ȥ",    
       "force"  : 500, 
       "attack" : 150, 
       "dodge"  : -30, 
       "parry"  : -110, 
       "damage" : 340, 
       "damage_type": "����" 
]), 
([      "action" : "$N���е�$w������ɨ��һ�Ѱ�$nȦס,�����ţ�$N��$w��$nһ���       
        ��Хһ��:[�޺�����],���Ҿ�ֱ��$n��$1��ȥ",           
       "dodge"  : -25, 
       "force"  : 500, 
       "attack" : 170, 
       "dodge"  : -70, 
       "parry"  : -55, 
       "damage" : 350, 
       "damage_type": "����" 
]), 
([      "action" : "$Nʹ��һ��[�����п�],���е�$w��ӯ����ػ�������$n��$1�����ȥ",
       "force" : 510, 
       "attack" : 185, 
       "dodge"  : -30, 
       "parry"  : -100, 
       "damage" : 410, 
       "damage_type": "����" 
]), 
([      "action" :        "$Nһ��������$w����һ������˳�Ƽ�ת��ͻȻ��ͣ��
        $n����ǰԾȥ�����г�Х�����չ�᡹���Һ�ɨ$n��$l",    
       "force"  : 510, 
       "attack" : 180, 
       "dodge"  : -50, 
       "parry"  : -110, 
       "damage" : 410, 
       "damage_type": "����" 
]), 
([       "action" : "$N˫Ŀ���Ⱪ��������ŭ���ɶ���һʽ[��ɨǧ��]����
       ��������Ӱ,$wֱ��$n��$l����$n������Ӧ��$w��Ȼ�����·��Ƶ���$nȫ��
       ������ȥ,�ٶȼ���$nֻ����ǰ���ǹ�Ӱ��������",     
       "force"  : 560, 
       "attack" : 170, 
       "dodge"  : -65, 
       "parry"  : -120, 
       "damage" : 500, 
       "damage_type": "����" 
]), 
}); 

string main_skill() { return "luowang-club"; } 

mapping sub_skills = ([ 
       "shunfeng-daqi"         : 120,        // 1 
       "xuehua-gaiding"        : 120,        // 2 
       "boyun-jianri"          : 120,        // 3
       "liuding-kaishan"       : 120,        // 4
       "wulong-baiwei"         : 120,        // 5
       "yanzi-chuanlin"        : 120,        // 6
       "jiaolong-chushui"      : 120,        // 7
       "dupi-huashan"          : 120,        // 8
       "xiniu-wangyue"         : 120,        // 9
       "luohan-bohu"           : 120,        // 10
       "tianma-xingkong"       : 120,        // 11
       "fenghuang-zhanchi"     : 120,        // 12
       "hengsao-qianjun"       : 120,        // 13
]); 

int get_ready(object me) 
{ 
       return 1; 
} 

int get_finish(object me) 
{ 
       if (me->query("str") < 25 || me->query_str() < 45) 
       { 
               tell_object(me, "��������ϣ��������弸����ȫ�����ˣ���������᲻��һ�㾢��\n"); 
               return 0; 
       } 

       if (me->query("con") < 25 || me->query_con() < 45) 
       { 
               tell_object(me, "��������ϣ��;�����ǰ������ð��̫��Ѩͻͻ������\n"); 
               return 0; 
       } 

       if ((int)me->query_skill("force") < 200) 
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
               tell_object(me, "��Խ����������İ����������򣬻���������һ�ξ��ܹ��ڻ��ͨ��\n"); 
               return 0; 
       } 

       tell_object(me, HIY "��һ���ǳɣ���������������ͷ��β������һ�䣬���ж���ͨ\n" 
                           "���˵Ľ�������������裬�ڻ��ͨ�˹����ľ�΢֮����\n" 
                           "��Ҳ���ǲ�ʹ����ô��ô�򵥡�\n" NOR); 
       return 1; 
} 

mapping query_sub_skills() 
{ 
       return sub_skills; 
} 

int valid_enable(string usage) { return usage=="club" ||  usage=="parry"; }   

int valid_learn(object me) 
{  
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "club")
                return notify_fail("�������޹���ôѧϰ����\n");
       if ((int)me->query("str") < 25 &&
           (int)me->query("con") < 25) 
               return notify_fail("���������ӹǻ���������������С������Բ�������\n"); 
       if ((int)me->query("int") < 20) 
               return notify_fail("���˰ɣ����������Բ��ã���ô������ء�\n"); 
       if ((int)me->query_skill("force") < 200) 
               return notify_fail("����ڹ���򲻹����޷�ѧϰ������������\n"); 
       if ((int)me->query_skill("hunyuan-yiqi") < 200) 
               return notify_fail("��Ļ�Ԫһ������򲻹����޷�ѧϰ������������\n");
       if((int)me->query_skill("zui-gun") < 200) 
               return notify_fail("��������򲻹����޷�ѧϰ������������\n"); 
       if ((int)me->query_skill("buddhism") < 200) 
               return notify_fail("��������ķ���򲻹����޷�ѧϰ������ϢϢ��ؽ�����������\n"); 
       if ((int)me->query("max_neili") < 2000) 
               return notify_fail("���������ô������ڻ��ͨ������������\n"); 

       if ((int)me->query_skill("club", 1) < 200) 
               return notify_fail("��Ļ���������򲻹����޷�ѧϰ������������\n"); 
       if ((int)me->query_skill("club", 1) < (int)me->query_skill("luowang-club", 1)) 
       return
   notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ľ�����������\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
       mapping a_action;
       int level;

       level = (int)me->query_skill("luowang-club", 1);
       a_action = action[random(sizeof(action))]; 
       a_action["dodge"] -= level / 10;
       a_action["parry"] -= level / 10;
       a_action["attack"] += level / 10;
       a_action["force"] += level / 10;
       a_action["damage"] += level / 10;
       if (me->query_temp("action_flag"))
                me->set_temp("action_msg","������");
       return a_action;
} 

int practice_skill(object me) 
{ 
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "club")
                return notify_fail("�������޹���ô������\n");
     if ((int)me->query("qi") < 150) 
               return notify_fail("�������̫���ˡ�\n"); 
       if ((int)me->query("neili") < 100) 
               return notify_fail("�������������������������\n"); 

       me->receive_damage("qi", 120); 
       me->add("neili", -50); 
       return 1; 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        if (random(10) >= 1)
       { 
               victim->receive_wound("qi", damage_bonus); 
               victim->receive_wound("jing", damage_bonus); 
               return HIR "����һ�����Ƶĺ���������$n�Ŀ��пȳ��˼�����Ѫ��\n" NOR; 
       } 
} 

string perform_action_file(string action) 
{ 
       return __DIR__"luowang-club/" + action; 
} 

void skill_improved(object me) 
{ 
       int i; 
       string *sub_skillnames; 

       sub_skillnames = keys(sub_skills); 
       for (i = 0; i < sizeof(sub_skillnames); i++) 
               me->delete_skill(sub_skillnames); 
} 
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;
    
        skill = me->query_skill("luowang-club", 1);
        if (skill > 120 && ! objectp(weapon = me->query_temp("weapon")))
        {
                enemy=me->query_enemy();
                if (! sizeof(enemy)) return;
                for (i=0;i<sizeof(enemy);i++)
                {
                        for (j=0;j<(skill/(60*sizeof(enemy)));j++)
                        if ((me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && enemy[i]->query("qi")>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        me->add_temp("str",skill/10);
                                        me->add_temp("dex",skill/10);
                                        COMBAT_D->do_attack(me, enemy[i], me->query_temp("weapon"), TYPE_REGULAR);
                                }
                        } else break;
                }
                me->delete_temp("str");
                me->delete_temp("dex");
        }
}


