// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// dugu-jiujian.c ���¾Ž�

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *parry_msg = ({ 
        "ȴ��$n̤ǰһ������ʽбָ����ұۣ���Ҫʹ$P������ˡ�\n", 
        "$n�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����������$P�͹����ػӳ���λ�����̩ɽ���������������\n", 
        "$n����ͻ�䣬�����������������ڽ�ز����ʹ��ɽ�����ġ�������������ͼ��ʹ$P���С�\n", 
        "$nͻȻһ������$P��$l����һ��ȴ�����������ţ�$P�����޴룬���Ʋ�������ͣ��������\n" 
        "$n�������ܣ��ٽ������ʹ�������両�ࡹ����$P��$l���뵲������С�\n", 
        "$nͻȻʹ��������ɷ罣���ġ����ڤڤ������������$Pһ�ʣ���ͼͻ��$P�Ĺ��ơ�\n" 
        "$nͦ��һ�����ǡ����Ƴ�ᶡ��ش�$P��$l����ͼ��$P�Ĺ��ƻ��⡣\n", 
        "ֻ��$n���˷���������Ʈ�磬һʽ�����������������޶�����ס��$P��\n������\n", 
        "$n���˷�����ʹ����ɽ���С�������롹��ɭɭ�����������ܣ��ܿ���$P������\n", 
}); 

mapping *action = ({
([      "action": HIW "����$Nͦ����ϣ�$w" + HIW "һ����һ�з·�̩ɽ�����ġ�������Ȫ��ֱ��$n��$l" NOR,
        "attack": 70,
        "dodge" : 60,
        "parry" : 70,
        "damage": 120,
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action": YEL "$N������$n�ӳ���Ȫ��ܽ�ء����������ϸǡ�����ʯ�����������������������������ף�ڡ���ɽ����" NOR,
        "attack": 71,
        "parry" : 72,
        "dodge" : 60,
        "damage": 120,
        "lvl" : 10,
        "damage_type" : "����"
]),
([
        "action": GRN "$N������ת�������̳�ʮ�Ž�����Ȼ�ǻ�ɽ����Ůʮ�Ž�����\n���������ʮ�Ž�����һ�У��ַ�֮�죬ֱ�Ƿ�����˼" NOR,
        "attack": 72,
        "dodge" : 64,
        "parry" : 78,
        "damage": 150,
        "lvl" : 20,
        "damage_type" : "����"
]),
([      "action": BLU "$N���ƺ��������裬�������������������ɽ����Ϊһ������$n������ȥ" NOR,
        "parry" : 73,
        "attack": 73,
        "dodge" : 65,
        "damage": 125,
        "lvl" : 30,
        "damage_type" : "����"
]),
([      "action": HIR "$N����ͻ������ɭ�ϣ�����ǧ�������۶�������ǹ��ꪣ���ɳǧ�������ɽ���ƻ���$n��$l" NOR,
        "parry" : 74,
        "attack": 74,
        "dodge" : 68,
        "damage": 130,
        "lvl" : 40,
        "damage_type" : "����"
]),
([      "action": CYN "ȴ��$N���潣�ߣ����һ�գ��ұ�һ�䣬����Ҳ��ԽתԽ�Ӻ�����������̩ɽʮ���̡�Ϊһ������$n" NOR,
        "attack": 75,
        "parry" : 75,
        "dodge" : 60,
        "damage": 120,
        "lvl" : 50,
        "damage_type" : "����"
]),
([      "action": HIY "$N����ͻ�䣬ʹ����ɽ�ġ�һ������㡹������$n��$l" + HIY "��\n��֪������;��ͻȻת�򣬴��$n����֮��" NOR,
        "attack": 76,
        "parry" : 76,
        "dodge" : 64,
        "damage": 120,
        "lvl" : 60,
        "damage_type" : "����"
]),
([      "action": MAG "$N����������һ�����ǡ�������ɽ��������$w" + MAG "����ն�䣬ֱ����$n��$l" NOR,
        "attack": 77,
        "dodge" : 67,
        "parry" : 77,
        "damage": 140,
        "lvl" : 70,
        "damage_type" : "����"
]),
([      "action": HIB "$N����$w" + HIB "ԽתԽ�죬ʹ�ľ�Ȼ�Ǻ�ɽ�ġ��ٱ�ǧ������ʮ��ʽ����\n��ʽ�����ƾ���ӿ���Թ��߲��ɵ�ĿΪ֮ѣ" NOR,
        "attack": 78,
        "dodge" : 60,
        "parry" : 78,
        "damage": 140,
        "lvl" : 80,
        "damage_type" : "����"
]),
([      "action": HIM "$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N��������ʵ" NOR,
        "attack": 79,
        "dodge" : 65,
        "parry" : 79,
        "damage": 160,
        "lvl" : 90,
        "damage_type" : "����"
]),
([      "action": HIC "$N��������ת��$n����������µ���$n�̳�һ������֪ʹ����ʲô����" NOR,
        "attack": 80,
        "parry" : 80,
        "dodge" : 65,
        "damage": 160,
        "lvl" : 100,
        "damage_type" : "����"
]),
([      "action": HIW "$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��֪����Ǻ�" NOR,
        "attack": 81,
        "parry" : 81,
        "dodge" : 66,
        "damage": 170,
        "lvl" : 110,
        "damage_type" : "����"
]),
([      "action": RED "$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ��������ȵ�$n���ò���" NOR,
        "attack": 82,
        "dodge" : 71,
        "parry" : 82,
        "damage": 175,
        "lvl" : 120,
        "damage_type" : "����"
]),
([      "action": YEL "$N���ֺὣ����$n��$l���������������е�һ����������Ȼ���$n���Կ��彣������" NOR,
        "attack": 83,
        "dodge" : 70,
        "parry" : 83,
        "damage": 180,
        "lvl" : 130,
        "damage_type" : "����"
]),
([      "action": HIR "$N�ٽ���ӣ�Ѹ���ޱȵص���$n��$l��ȴ���˿�������������ʲô��ʽ" NOR,
        "attack": 84,
        "parry" : 84,
        "dodge" : 60,
        "damage": 170,
        "lvl" : 140,
        "damage_type" : "����"
]),
([      "action": HIM "$N����һ��ָ��$n���������$n���������ڣ��˵����������ף�����˼��" NOR,
        "attack": 85,
        "parry" : 85,
        "dodge" : 64,
        "damage": 180,
        "lvl" : 150,
        "damage_type" : "����"
]),
([      "action": CYN "$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������$n��$l" NOR,
        "attack": 86,
        "dodge" : 60,
        "parry" : 86,
        "damage": 180,
        "lvl" : 160,
        "damage_type" : "����"
]),
([
        "action": RED "$N��$w"+ RED "����һ�ڣ�����$n�Լ���$w"+ RED "ײ����������֮����ʵ�����Ѳ�" NOR,
        "attack": 90,
        "dodge" : 70,
        "parry" : 90,
        "damage": 200,
        "lvl" : 170,
        "damage_type" : "����"
])
});

mapping *action2 = ({ 
([      "action" : HIW "����$N����$w�ƿճ�����ƽƽһ������$n��������ʽ����" NOR, 
        "force" : 300,
        "attack": 120, 
        "dodge" : 120, 
        "parry" : 120, 
        "damage": 180, 
        "damage_type" : "����" 
]), 
([      "action" : HIW "$N�����۽������赭д������̳�һ������֮����������ʽ" NOR,
        "force" : 300, 
        "attack": 130, 
        "dodge" : 130, 
        "parry" : 130, 
        "damage": 190, 
        "damage_type" : "����" 
]), 
([      "action" : HIW "$N��Ʈ�ݣ���̬��Ȼ������������У�����$w�����������������" 
                       "�Ž��ѵ����շ�����ľ���" NOR, 
        "force" : 300,
        "attack": 140, 
        "dodge" : 140, 
        "parry" : 140, 
        "damage": 200, 
        "damage_type" : "����" 
]), 
}); 

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me) 
{ 
        object ob; 
        
        if( !(ob = me->query_temp("weapon")) 
        ||   (string)ob->query("skill_type") != "sword" ) 
                return notify_fail("���������һ�ѽ�������������\n"); 
        
        if (me->query("int") < 34) 
                return notify_fail("������ʲ��㣬�޷������¾Ž��Ľ��⡣\n"); 
        
        // if (me->query("dugu-jiujian/nothing") && 
        if (
            me->query("con") < 26) 
                return notify_fail("��������ǲ��㣬�޷������¾Ž��Ľ��⡣\n"); 
            
        if (me->query("character") == "�ĺ�����") 
                return notify_fail("��һ����ɱ�����ˣ�û�������¾Ž��ĵ��������塣\n"); 
        
        if (me->query("character") == "���ռ�թ") 
                return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û�������¾Ž���\n"); 
        
        if (me->query("character") == "��������") 
                return notify_fail("�����а�����ʲô���¾Ž������߰���ģ�û�а�����ơ�\n"); 
        
        if (me->query_skill("sword", 1) < 100) 
                return notify_fail("��Ļ�����������̫ǳ���޷������¾Ž���\n"); 
        
        if (me->query_skill("sword", 1) < me->query_skill("dugu-jiujian", 1)) 
        return notify_fail("��Ļ��������������ޣ��޷���������Ķ��¾Ž���\n"); 
        
        return 1; 
} 

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("dugu-jiujian", 1);
        
        if (me->query("dugu-jiujian/nothing")) 
                return action2[random(sizeof(action2))];       
                  
        if (objectp(weapon) && (string)weapon->query("id") == "xuantie jian")
        {
                if (me->query_str() >= 60 && me->query_int() >= 36 
                &&  random(level) > 120 
                &&  me->query_skill("force") > 150 && me->query("neili") > 400)
                {
                        me->add("neili", -100);
                        return ([
                                "action": HIR "$N��ɫ�����ϣ��������������ؽ���ͻȻԾ������һ��"
                                          "Ԧ����Ϊһ��������$n��̶�ȥ" NOR,
                                "damage": 400,
                                "attack": 100,
                                "dodge" : 80,
                                "parry" : 80,
                                "damage_type" : "����"
                        ]);
                }
        }
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        return notify_fail("���¾Ž�ֻ��ͨ����"+RED+"�ܾ�ʽ"+NOR+"����������\n");
}

string perform_action_file(string action)
{
        return __DIR__"dugu-jiujian/" + action;
}

int query_effect_parry(object attacker, object me) 
{ 
        object weapon; 
        int lvl; 
        
        if (! objectp(weapon = me->query_temp("weapon")) || 
            (string)weapon->query("skill_type") != "sword") 
                return 0; 
        
        lvl = me->query_skill("dugu-jiujian", 1); 
        if (lvl < 90)  return 0; 
        if (lvl < 100) return 50; 
        if (lvl < 125) return 55; 
        if (lvl < 150) return 60; 
        if (lvl < 175) return 65; 
        if (lvl < 200) return 70; 
        if (lvl < 225) return 75; 
        if (lvl < 250) return 80; 
        if (lvl < 275) return 90; 
        if (lvl < 325) return 100; 
        if (lvl < 350) return 110; 
        return 120; 
} 

void skill_improved(object me) 
{ 
        int lvl, i; 
        
        i = me->query("int") / 3; 
        lvl = me->query_skill("dugu-jiujian", 1); 
        
        if (lvl > 120 
        &&  me->query("can_perform/dugu/qi") <= 100) 
        { 
                if (me->add("can_perform/dugu/qi", random(i)) < 100) 
                { 
                        tell_object(me, HIC "��Զ��¾Ž���" HIW "����ʽ" 
                                        HIC "�������µ�����\n" NOR); 
                } else 
                { 
                        tell_object(me, HIC "��ͨ���˶��¾Ž���" HIW "��" 
                                        "��ʽ" HIC "���İ��ء�\n" NOR); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                } 
        } 
        
        if (lvl > 150 
        &&  me->query("can_perform/dugu/po") <= 100) 
        { 
                if (me->add("can_perform/dugu/po", random(i)) < 100) 
                { 
                        tell_object(me, HIC "��Զ��¾Ž���" HIR "����ʽ" 
                                        HIC "�������µ�����\n" NOR); 
                } else 
                { 
                        tell_object(me, HIC "��ͨ���˶��¾Ž���" HIR "��" 
                                        "��ʽ" HIC "���İ��ء�\n" NOR); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                } 
        } 
        
        if (lvl > 200 
        &&  me->query("can_perform/dugu/yi") <= 100) 
        { 
                if (me->add("can_perform/dugu/yi", random(i)) < 100) 
                { 
                        tell_object(me, HIC "��Զ��¾Ž���" HIR "����" 
                                        HIC "�������µ�����\n" NOR); 
                } else 
                { 
                        tell_object(me, HIC "��ͨ���˶��¾Ž���" HIR "��" 
                                        "��" HIC "���İ��ء�\n" NOR); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                } 
        }         
} 
        
int difficult_level() 
{ 
        object me = this_object(); 
        
        if (me->query("dugu-jiujian/nothing")) 
                return 300; 
        
        else   return 200; 
} 
  
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mixed result; 
        int ap, dp, mp; 
        object m_weapon; 
        
        if ((int) me->query_skill("dugu-jiujian", 1) < 120 
        ||  ! (m_weapon = me->query_temp("weapon")) 
        ||  ! living(me) 
        ||  m_weapon->query("skill_type") != "sword") 
                return; 
        
        mp = ob->query_skill("count", 1); 
        ap = ob->query_skill("parry") + mp; 
        dp = me->query_skill("parry", 1) / 2 + 
        me->query_skill("dugu-jiujian", 1); 
          
        // ���� 
        if (me->query("dugu-jiujian/nothing")) 
        { 
                if (me->query_skill("sword") * 2 / 3 + random(me->query_skill("sword")) 
                >   ob->query_skill("parry")) 
                { 
                        result = ([ "damage": -damage ]); 
        
                        result += (["msg" : HIG "$n" HIG "�����$N" HIG "�Ĺ��ƣ�" 
                                            "����ӳ�һ����������$N" HIG "��\n" NOR]); 
        
                        if (! ob->is_busy())
                        ob->start_busy(1 + random(2)); 
                } 
              
                return result;                   
        } 
        
        if (ap / 2 + random(ap) < dp) 
        { 
                result = ([ "damage": -damage ]); 

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "ͻȻ�ٽ�һ�̣������������£�"
                                            "ȴĪ�������ͻ����$N�Ĺ��ƣ����$N���ϡ�\n"
                                            "$nһת���ƣ�����ԴԴ��������$N�������ƣ�\n" NOR]);
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "�ٽ��������������ش���$N��������"
                                            "$N��������������һ������������\n" NOR]);
                        COMBAT_D->do_attack(me, ob, me->query_temp("weapon")); 
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "�ὣ�ش̣��������$N��������"
                                            "$N���ò��������أ�����һ�μ����˳�����\n" NOR]);
                        break;
                case 3: 
                        result += (["msg" : HIC "ȴ��$n" HIC "̤ǰһ������ʽбָ$P" HIC 
                                            "�ұۣ���ʽѸ���ޱȣ�ʹ��$N" HIC "�������" 
                                            "��\n" NOR]); 
                        break; 
                case 4: 
                        result += (["msg" : HIC "$n" HIC "ͻȻһ������$N" HIC "����һ��" 
                                            "ȴ�����������ţ�$N" HIC "��ʱ�����޴룬��" 
                                            "�Ʋ�������ͣ��������\n" NOR]); 
                        break; 
                default: 
                        result += (["msg" : HIC "$n" HIC "�ۼ����޿ɱܣ�ֻ���ὣ�Ҵ�һͨ��"
                                            "��Ȼ�������ϵؽ�$N�Ĺ�����ȥ��\n" NOR]);
                        break;
                }       

                return result; 
        } else 
        if (mp >= 100) 
        { 
                switch (random(3)) 
                { 
                case 0: 
                        result = HIY "$n" HIY "һ�����е�" + m_weapon->name() + 
                                 HIY "���й�ֱ��һ��ͦ��������$N" HIY "���и���" 
                                 "����Ϯ$n" HIY "��\n" NOR; 
                        break; 
        
                case 1: 
                        result = HIY "$n" HIY "����" + m_weapon->name() + "����" 
                                 "��" HIY "��ָ��$N" HIY "�����е�����������$N" 
                                 HIY "����һ�䣬�������̲���Ϊ������\n" NOR; 
                        break; 
        
                default: 
                        result = HIY "$n" HIY "����" + m_weapon->name() + HIY 
                                 "���任���ֽ��У�Ȼ��$N" HIY "��Ҳ�����ٴι�" 
                                 "����˿������$n" HIY "���Ի�\n"  NOR; 
                        break; 
                } 
                COMBAT_D->set_bhinfo(result); 
        } 
} 
            
mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        mixed result;
        int lvl; 
        object weapon, weapon2; 
        int i, ap, dpp, dpd, dpf; 
        string type, msg, msg1; 
        
        lvl = me->query_skill("dugu-jiujian", 1); 
        
        if (me->query("neili") < 300 
        ||  me->query_skill_mapped("sword") != "dugu-jiujian" 
        ||  ! objectp(weapon = me->query_temp("weapon")) 
        ||  weapon->query("skill_type") != "sword" 
        ||  ! me->query("dugu-jiujian/nothing")) 
                return 0; 
          
        ap = me->query_skill("sword"); 
        dpp = victim->query_skill("parry"); 
        dpd = victim->query_skill("dodge"); 
        dpf = victim->query_skill("force"); 
        
        switch(random(3)) 
        { 
        case 1: 
                if (ap * 3 / 4 + random(ap) > dpp) 
                { 
                        me->add("neili", -100); 
                        result = ([ "damage" : (damage_bonus - 30) / 2 ]); 
                     
                        msg1 = random(2) ? HIR "$N" HIR "һ��������������ɣ�" + weapon->name() + HIR 
                                           "ʱ���������գ�ʱ��������ƣ�ȴ��֪����ͨ��" 
                                           "һ��֮�о��̲������������\n" NOR: 
                                           HIR "$N" HIR "����" + weapon->name() + HIR "��" 
                                           "�������۾�һ�㣬һ������ӳ�����ֱ����$n" HIR  
                                           "С��������ƽ��������λ������ȴ�����ǡ���ô���\n" NOR; 
                        result += ([ "msg" : msg ]);
                        return result;
                } 
                break; 
        
        case 2:        
                message_vision(HIC "\n$N" HIC "����������е�" + weapon->name() + 
                               HIC "�����дӳ��䲻��ķ�λֱָ$n" HIC "��ʽ�е�" 
                               "������\n" NOR, me, victim); 
        
                if (! me->is_busy()) 
                { 
                        weapon = me->query_temp("weapon"); 
                        weapon2 = victim->query_temp("weapon"); 
                        if (weapon2) type = weapon2->query("skill_type"); 
        
        
                        if (ap * 3 / 4 + random(ap) >= dpf && weapon2 
                        &&  type != "pin") 
                        { 
                                msg = HIW "$n" HIW "������ǰ�ۻ����ң�����" 
                                      "��" + weapon2->name() + HIW "һʱ��" 
                                      "Ȼ����ס�����ֶ�����\n" NOR; 
                                weapon2->move(environment(me));       
                                me->add("neili", -100);                  
                        } else 
                        { 
                                msg = HIY "$n" HIY "�Եÿ�϶��Ϣ��һʱ��ȴ" 
                                      "Ҳ����������\n" NOR; 
                                me->add("neili", -40); 
                        } 
                }else  
                if (ap * 4 / 5 + random(ap) > dpd) 
                { 
                        msg = HIY "$n" HIY "��æ�ֵ���һʱ�䲻����æ���ң�" 
                              "��Ͼ������\n" NOR; 
        
                        me->start_busy(1); 
                        victim->start_busy(1 + random(lvl / 30)); 
                } 
                else 
                { 
                        msg = HIC "$N" HIC "������������е�" + weapon->name() + 
                              HIC "����$n" HIC "������$n" HIC "���ص��쳣���ܣ�$N" 
                              HIC "һʱ��Ȼ�޷��ҵ�������\n" NOR; 
                        me->start_busy(1 + random(2)); 
                        victim->start_busy(1); 
                } 
                message_combatd(msg, me, victim); 
                break; 
        
        default : 
                if (ap * 2 / 3 + random(ap) > dpd &&  
                    ! me->is_busy() && 
                    ! me->query_temp("dugu-jiujian/lian")) 
                { 
                        weapon = me->query_temp("weapon"); 
                        message_sort(HIY "\n$N" HIY "�زؽ��⣬����" + weapon->name() + HIY  
                                     "��������������ٶ�֮�죬��λ֮׼�����Ƕ��¾Ž��Ѵﵽ" 
                                     "�շ�����ľ��硣\n" NOR, 
                                     me, victim); 
        
                        me->add("neili", -270); 
           
                        me->set_temp("dugu-jiujian/lian", 1); 
                        for (i = 0; i < 3; i++) 
                        { 
                                if (! me->is_fighting(victim)) 
                                        break; 
                  
                                if (! victim->is_busy() && random(2) == 1) 
                                        victim->start_busy(1); 
        
                                COMBAT_D->do_attack(me, victim, weapon, 0); 
                        } 
                        me->delete_temp("dugu-jiujian/lian"); 
            
                } 
                break;                         
        } 
} 
