// ����ָ���������书���֡�
// ���������ɵ���"�����", ������7c���ֱ�ϳɡ���ȸ�����׻����������������������Ϊһ���Ե��ߣ���7�ɼ��ʶ��������ľ���
// �ľ�Ҫ��Ϊ��Ӧ������>=30���ľ�����һpfm��
// ��180��������Ϊ��
// sixiang-shengong.c �����񹦡� ���ƾŽ����У�����Ч�����������������۵İ�������չ�֡�����һ�츳����36����ʹ���ռ�pfm��

#include <ansi.h>
inherit FORCE;

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("sixiang-shengong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

string *parry_msg = ({
        "ֻ��$n����˫�ۣ�ȭ�ϰ׻�֮�����֣�Ӳ��$P���б��ˡ�\n",
        "$n�Թ�Ϊ�أ�����������������֮����$P������ȥ��\n",
        "$n������������������������ƾ���������ص�ˮй��ͨ��$Pһʱ�޷����֡�\n",
        "$n���˽ŵף�����������֮��ˣ���$P�����ʵ����룬���������޴ӡ�\n"
      });

string *dodge_msg = ({
        "ֻ��$n����˫�ۣ�ȭ�ϰ׻�֮�����֣�Ӳ��$P���б��ˡ�\n",
        "$n�Թ�Ϊ�أ�����������������֮����$P������ȥ��\n",
        "$n������������������������ƾ���������ص�ˮй��ͨ��$Pһʱ�޷����֡�\n",
        "$n���˽ŵף�����������֮��ˣ���$P�����ʵ����룬���������޴ӡ�\n"
});


mapping *action = ({
([      "action": "$Nʮָ�������󿪴�ϣ����Ƹ��ͣ��ϡ�"NOR + HIW "�׻���" NOR "����"
                  "��" NOR + HIB "������" NOR "����һ�壬��ʱһ���ֱ��$n",
        "force" : 440,
        "attack": 220,
        "parry" : 60,
        "dodge" : 60,
        "damage": 220,
        "weapon" : HIR "��������" NOR,
        "damage_type" : "����"
]),
([      "action": "$N��ָ���ƣ�һ��һ�ƣ���Ϊ��" HIG "������" NOR "����" HIW "�Ұ�"
                  "��" NOR "����һ��һ�أ���$n��������",
        "force" : 380,
        "attack": 220,
        "parry" : 220,
        "dodge" : 60,
        "damage": 220,
        "weapon" : HIG "��������" NOR,
        "damage_type" : "����"
]),
([      
        "action": "ֻ��$Nʮָ���ţ�����������裬����" HIW "�׻���" NOR "����"
                  "��" HIR "��ȸ��" NOR "���ľ����ںϣ�\n��ʱ�����ݺᣬ��"
                  "ɰ��ʯ������$n��ȥ",
        "force" : 380,
        "attack": 280,
        "parry" : 60,
        "dodge" : 220,
        "damage": 220,
        "weapon" : HIW "��������" NOR,
        "damage_type" : "����"
]),
([      
        "action": "ֻ��$N���ֲ�һ����˫����̫��֮�ͣ���$n����ʱ��\n����" HIG "������" NOR "����"
                  "��" HIB "������" NOR "���������������",
        "force" : 460,
        "attack": 220,
        "parry" : 185,
        "dodge" : 65,
        "damage": 200,
        "weapon" : HIB "��������" NOR,
        "damage_type" : "����"
]),
([      "action": "$Nʮָ������������ɫ������ָ��ɿ��������\n�ѡ�" HIG "������" NOR "��֮׼��"
                  "��" HIR "��ȸ��" NOR "��֮�죬��$n����������ȥ",
        "force" : 360,
        "attack": 220,
        "parry" : 230,
        "dodge" : 225,
        "damage": 180,
        "weapon" : HIR "��������" NOR,
        "damage_type" : "����"
]),
([      "action": "ֻ��$N�������ߣ��ԡ�" HIG "����" NOR "��֮�����壬\n��"
                  "��" HIR "��ȸ" NOR "��֮��������$n���Ϻݺ�ײȥ",
        "force" : 460,
        "attack": 120,
        "parry" : 110,
        "dodge" : 225,
        "damage": 210,
        "weapon" : HIR "��������" NOR,
        "damage_type" : "����"
]),
([      "action": "$N���ư��磬�������������Ұ׻���ǰ���䡢����ȸ֮��\n��"
                  "����֮�ͣ�Χ��$n�����ը",
        "force" : 560,
        "attack": 300,
        "parry" : 200,
        "dodge" : 300,
        "damage": 400,
        "weapon" : HIR "��������" NOR,
        "damage_type": "����"
])
});

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

string main_skill() { return "sixiang-shengong"; }

mapping sub_skills = ([
        "qinglong-po"  : 180,
        "baihu-jing"   : 180,
        "xuanwu-shi"   : 180,
        "zhuque-wu"    : 180,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if (me->query_skill("literate", 1) < 1800)
        {
                tell_object(me, "����������񹦼�����£��������о�һ��ѧ�ʿ��ܸ��а�"
                                "����\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 180)
        {
                tell_object(me, "�㷢���Լ�����ѧ�����д���ߣ������޷������ɹ���\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 200)
        {
                tell_object(me, "�㷢���Լ����ڹ����������������޷������ɹ���\n");
                return 0;
        }

        if ((int)me->query("max_neili") < 3500)
        {
                tell_object(me, "������Լ��������̣��޷��ϳ��������񹦡�\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ��\n");
                return 0;
        }

        tell_object(me, HIY "\n���Ǽ䣬�㽫�����������������������÷����Ժ��н����\n"
                            "�֣�����������ת���������������ְ׻���ǰ�����䣬��ͻ��ȸ\n"
                            "ǡ������֮�ͣ��������֡������������������񹦡�\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
	return usage == "unarmed" || usage == "parry" || usage == "dodge"|| usage == "force"|| usage == "throwing";
}

int double_attack()
{
	return 1;
}

int valid_force(string force) { return 1; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������񹦱�����֡�\n");

        if ((int)me->query("int") < 30)
                return notify_fail("�����������̫�ͣ��޷���������񹦡�\n");

        if ((int)me->query("dex") < 30)
                return notify_fail("����������������޷����������񹦡�\n");

        if ((int)me->query("con") < 30)
                return notify_fail("����������̫�ͣ��޷���������񹦡�\n");

        if ((int)me->query("str") < 30)
                return notify_fail("�����������������޷����������񹦡�\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("����ڹ���򲻹����޷����������񹦡�\n");

        if ((int)me->query("max_neili") < 3500)
                return notify_fail("�������̫�����޷����������񹦡�\n");
            
        if (me->query_skill("martial-cognize", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("�����ѧ�����д���ߣ������޷����������񹦡�\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷���������������񹦡�\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("��Ļ����Ṧˮƽ���ޣ��޷���������������񹦡�\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("��Ļ����м�ˮƽ���ޣ��޷���������������񹦡�\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷���������������񹦡�\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("sixiang-shengong", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������������񹦡�\n");
        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        object anqi;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("sixiang-shengong", 1) < 200 ||
            ! living(me) || (int)me->query("neili") < 250 ||
            me->query_skill_mapped("parry") != "sixiang-shengong" ||
            me->query_skill_mapped("dodge") != "sixiang-shengong" ||
//            ob->query_temp("weapon") ||
            (! objectp(anqi = me->query_temp("handing"))) ||
            anqi->query("id") != "qi jing"  || (anqi->query_amount() < 1))
                return;

        cost = damage / 2;

      anqi->add_amount(-1);

        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("sixiang-shengong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$N" HIW "һ�л���$n" HIW "�Ļ���������ֻ�������ھ�"
                                            "����ޱȣ���������$n" HIW "�԰׻�֮�Ƹ�����������\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIB "$N" HIB "һ�й�����$n" HIB "ŭ��һ��������"
                                            "������������Ӳ��$N" HIB "���ж�����δ�ˡ�\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$N" HIR "ԶԶ�������У���$n" HIR "������ȸ"
                                            "������������������Ʈ����\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "�������������������⣬�ѽ�$N" HIG "��"
                                            "�н�����ʽȫ��������\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIW "$n" HIW "Ĭ�������񹦣��԰׻�֮�Ʒ�����\n˭֪$N" HIW       
                                 "��������ޱȣ���̾һ����һ�о���ʵ�ش���$n" HIY
                                 "���ϡ�\n" NOR;
                        break;

                case 1:
                        result = HIB "$N" HIB "һ�й�����$n" HIB "ŭ��һ��������"
                                            "������������Ӳ��$N" HIB "���У�\n˭֪$N" HIB       
                                            "�������أ����о���ʵ�ش���$n" HIY "���ϡ�\n" NOR;
                        break;

               case 2:
                        result = HIR "$N" HIR "ңң�������У�$n" HIR "������ȸ����"
                                            "��������������\n������Ʈ������$N" HIR "��ʽ��Ȼһ��\n"
                                            "����$n" HIR "������š�\n" NOR;
                        break;

                default:
                        result = HIG "$N" HIG "�������������������⣬����$n" HIG "���н���·�߷���\n"
                                     "��$n" HIG "��ʽһ�䣬�������򣬽�������ȥ��\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon, weapon2, anqi;
        int i, ap, ap2, dpp, dpd, dpf, dpu, ap1, lvl;
        string type, msg;
        anqi = me->query_temp("handing");
        if ((me->query("neili") < 200)
           || me->query_skill_mapped("force") != "sixiang-shengong"
           || me->query_skill_mapped("unarmed") != "sixiang-shengong"
           || me->query_skill_mapped("throwing") != "sixiang-shengong"
           || (objectp(weapon = me->query_temp("weapon")))
           || (! objectp(anqi))
	   || (string)anqi->query("id") != "qi jing"
           || anqi->query_amount() < 1)
                return;

        ap = me->query_skill("force");
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");  
        dpu = victim->query_skill("unarmed");  
        ap1 = ap * 2;    
        me->add("neili", -20);
        me->interrupt_me();

        switch(random(4))
        {
           case 1: 
                if (ap1 > dpp || ap1 > dpd || ap1 > dpf || ap1 > dpu)
                {        
                 
                  me->add("neili", -20);
                  anqi->add_amount(-1);
                  victim->receive_wound("qi", ap * 4 + 300, me);
                  
                 message_vision(HIW "\n$N" HIW "��������������ͻ�"
                            HIW "����ȭֱȡ$n" HIW "��������ţ�\n" NOR, me, victim);

                }        
               break;

           case 2:
		message_vision(HIG "\n$N" HIG "�۹���·�������񹦻�����"
                            HIG "��ֱȡ$n" HIG "��ʽ�е�������\n" NOR, me, victim);
		
		if (! me->is_busy())
		{
			weapon2 = victim->query_temp("weapon");
			if ( ap1 >= dpp && weapon2 )
			{
				msg = HIG "$n" HIG "������ǰ�������ƣ�����"
					"��" + weapon2->name() + HIG "����"
					"������һ�������ֶ�����\n" NOR;
				weapon2->move(environment(me)); 
				anqi->add_amount(-1);
				me->add("neili", -20);   
				if ( ap1 > dpp ) 
				{
					msg +=  HIG "ֻ�������ſ�һҧ����" + weapon2->name() + HIG "����"
						"���У�����$n" HIG "�ݺ����£���ʱѪ���Ľ���\n" NOR;
					anqi->add_amount(-1);
					victim->receive_wound("qi", ap * 2 + 300, me);
				}
			} else
			{
				msg = HIY "$n" HIY "ֻ����������������������"
					"һʱ��ȴҲ����������\n" NOR;
				me->add("neili", -20);
				anqi->add_amount(-1);
				victim->start_busy(4 + random(5));
			}
		}else 
		if (ap1 > dpd)
		{
			msg = HIY "$n" HIY "��æ������������һʱҲ�ڲ����ַ�����\n" NOR;
			anqi->add_amount(-1);
			victim->start_busy(4 + random(5));
		}else
		{
			msg = HIG "\n$N" HIG "�۹���·�������񹦻�����"
				HIG "��ֱȡ$n" HIG "��ʽ�е�������\n��$n" HIG "����"
				HIG "�������������б�������������ңң�භ�������·硣\n" NOR;
			anqi->add_amount(-1);
			victim->start_busy(2);
		}
		message_combatd(msg, me, victim);
		break;          

            case 3:
                 msg = HIB "\n$N" HIB "�����˵���ٴ��һ������"
                       HIB "��������������֮�ƣ���$n" HIB "��ȥ��"
                       HIB "\n$n" HIB "�����޿ɱܣ�ֻ�ô߶��ھ���Ӳ��һ�У�\n" NOR;
                 message_combatd(msg, me, victim);

                   if ( ap1> dpu )
        
                  { msg = HIB + "����" + anqi->name() + HIB "��âһ����һ������"
                          HIB + "͸�����룬$n" HIB " ��ʱ��Ѫ��ӿ������ͨ�졣\n" NOR;
                    victim->receive_wound("qi", ap1 * 4, me);
                    }  else 
                   {  msg = HIB "$n" HIB "����˫�ۣ������Զԣ�����$N" HIB "֮��жȥ��\n" NOR;
                    }
            message_combatd(msg, me, victim);
             me->add("neili", -50);
            anqi->add_amount(-1);

                  if ( ap1 > dpp)
        
                  { msg = HIB + "ȴ����������������һ�ظ��͵ĳ徢"
                          HIB + "����������$n" HIB " �������̣���ͷһ��\n" NOR;
                    victim->receive_wound("qi", ap1 * 4, me);
                    }  else 
                   {  msg = HIB "$n" HIB "�����������˾�һ�ã�����$N" HIB "֮��������\n" NOR;
                    }
            message_combatd(msg, me, victim);
            me->add("neili", -50);
             anqi->add_amount(-1);

                 if ( ap1 > dpd)
        
                  { msg = HIB + "��Ȼ����������â���֣�$n" HIB "��æ�ٶ�����һ��"
                          HIB + "˭֪��âȴ���龢��$n" HIB "�����޴���й�������Ҵ������һ����Ѫ��\n" NOR;
                    victim->receive_wound("qi", ap1 * 4, me);
                    }  else 
                   {  msg = HIB "$n" HIB "������һ��������â��Ϊ���Ρ�\n" NOR;
                    }
            message_combatd(msg, me, victim);
            anqi->add_amount(-1);
            me->add("neili", -50);

            if ( ap1 * 3 / 2 > dpf )
        
                  { msg = HIB + "δ������������â��ʢ����ѹ��֮�ƣ�"
                          HIB + "$n" HIB "���������ֿ���������׵���ȥ���߿���Ѫ��\n" NOR;
                    victim->receive_wound("qi", ap1 * 4, me);
                    }  else 
                   {  msg = HIB "$n" HIB "�������̣���������â������ɣ�����δ���ˡ�\n" NOR;
                    }
            anqi->add_amount(-1);
            me->add("neili", -50);
            message_combatd(msg, me, victim);

               break;

          default :        
             if ( ! me->query_temp("sixiang-shengong/lian") && 
                  (ap1 > dpp || ap1 > dpd || ap1 > dpf || ap1 > dpu ) )
             {  
                 message_sort(HIY "\n$N" HIY "�������£�������������ȸ֮��" 
                             "��������죬��$n" HIY "������ȥ��һʱ����֮�ͱ仯��ǧ��\n" NOR, me, victim);
                me->add("neili", -50);
                me->set_temp("sixiang-shengong/lian", 1);
                for (i = 0; i < 10; i++)
                {
                    if (! me->is_fighting(victim))
                            break;
                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, anqi, i * 2);
                     anqi->add_amount(-1);

                }
                me->delete_temp("sixiang-shengong/lian");
                
             }
             break;                        
       }
}

int query_effect_parry(object attacker, object me)
{
        object anqi;
        int lvl;

        if  (! objectp(anqi = me->query_temp("handing")) || 
            anqi->query("id") != "qijing"|| (anqi->query_amount() < 1) )  
                return 0;

        lvl = me->query_skill("sixiang-shengong", 1);
        if (lvl < 200) return 50;
        if (lvl < 225) return 60;
        if (lvl < 250) return 70;
        if (lvl < 275) return 80;
        if (lvl < 325) return 90;
        if (lvl < 350) return 100;
        return 120;
}

int query_effect_dodge(object attacker, object me)
{
        object anqi;
        int lvl;

        if  (! objectp(anqi = me->query_temp("handing")) || 
            anqi->query("id") != "qijing"|| (anqi->query_amount() < 1) )  
                return 0;

        lvl = me->query_skill("sixiang-shengong", 1);
        if (lvl < 200) return 50;
        if (lvl < 225) return 60;
        if (lvl < 250) return 70;
        if (lvl < 275) return 80;
        if (lvl < 325) return 90;
        if (lvl < 350) return 100;
        return 120;
}

int difficult_level()
{
        return 500;
}

int practice_skill(object me)
{
        return notify_fail("������������ޣ��޷��򵥵�ͨ����ϰ������\n");
}

string perform_action_file(string action)
{
        return __DIR__"sixiang-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"sixiang-shengong/exert/" + action;
}
