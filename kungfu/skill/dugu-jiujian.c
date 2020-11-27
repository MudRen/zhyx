#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *parry_msg = ({
        "ȴ��$n̤ǰһ������ʽбָ����ұۣ���Ҫʹ$P�������ˡ�\n",
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
([      "action" : "����$Nͦ�����ϣ�$wһ����һ�з·�̩ɽ�����ġ�" HIC "������"
                   "Ȫ" NOR "��ֱ��$n��$l",
        "force" : 290,
        "attack": 145,
        "dodge" : 95,
        "parry" : 105,
        "damage": 160,
        "damage_type" : "����"
]),
([      "action" : "$N������$n�ӳ���" CYN "Ȫ��ܽ��" NOR "������" MAG "����"
                   "�ϸ�" NOR "������" HIG "ʯ������" NOR "������" HIW "����"
                   "����" NOR "������" HIY "���ף��" NOR "����\nɽ����",
        "force" : 410,
        "attack": 135,
        "dodge" : 135,
        "parry" : 175,
        "damage": 270,
        "damage_type" : "����"
]),
([
        "action" : "$N������ת�������̳�ʮ�Ž�����Ȼ�ǻ�ɽ��" HIW "��Ůʮ�Ž�"
                   NOR "�������������ʮ�Ž�����һ�У��ַ�֮�죬\nֱ�Ƿ�����"
                   "˼",
        "force" : 310,
        "attack": 115,
        "dodge" : 75,
        "parry" : 105,
        "damage": 205,
        "damage_type" : "����"
]),
([      "action" : "$N���ƺ��������裬�������������������ɽ����Ϊһ������$n��"
                   "����ȥ",
        "force" : 280,
        "attack": 125,
        "dodge" : 55,
        "parry" : 125,
        "damage": 160,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ������ɭ�ϣ�����ǧ���������۶�������ǹ��ꪣ���ɳǧ"
                   "�������ɽ���ƻ���$n",
        "force" : 340,
        "attack": 160,
        "dodge" : 65,
        "parry" : 95,
        "damage": 220,
        "damage_type" : "����"
]),
([      "action" : "ȴ��$N���潣�ߣ����һ�գ��ұ�һ�䣬����Ҳ��ԽתԽ�Ӻ�����"
                   "������" HIY "̩ɽʮ����" NOR "��Ϊһ����\n��$n",
        "force" : 250,
        "attack": 135,
        "dodge" : 85,
        "parry" : 105,
        "damage": 210,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ�䣬ʹ����ɽ�ġ�" HIB "һ�������" NOR "��������$n"
                   "��$l����֪������;��ͻȻת�򣬴��$n\n����֮��",
        "force" : 240,
        "attack": 105,
        "dodge" : 125,
        "parry" : 175,
        "damage": 180,
        "damage_type" : "����"
]),
([      "action" : "$N����������һ�����ǡ�" CYN "������ɽ" NOR "��������$w����"
                   "ն�䣬ֱ����$n��$l",
        "force" : 345,
        "attack": 125,
        "dodge" : 115,
        "parry" : 145,
        "damage": 210,
        "damage_type" : "����"
]),
([      "action" : "$N����$wԽתԽ�죬ʹ�ľ�Ȼ�Ǻ�ɽ�ġ�" HIW "�ٱ�ǧ������ʮ"
                   "��ʽ" NOR "������ʽ�����ƾ���ӿ���Թ�\n�߲��ɵ�ĿΪ֮ѣ",
        "force" : 350,
        "attack": 145,
        "dodge" : 165,
        "parry" : 185,
        "damage": 250,
        "damage_type" : "����"
]),
([      "action" : "$N��Ц����������ׯ�ϣ�$w��ӣ����ڡ�" HIR "��Ħ��" NOR "��"
                   "Ϊһʽ������ش���$n",
        "force" : 330,
        "attack": 135,
        "dodge" : 95,
        "parry" : 125,
        "damage": 260,
        "damage_type" : "����"
]),
([      "action" : "$N����$w��ʹ��" CYN "̫����" NOR "�����⣬�������СС��"
                   "����ԲȦ�������޾�ԴԴ�����ز���$n",
        "force" : 230,
        "attack": 105,
        "dodge" : 285,
        "parry" : 375,
        "damage": 140,
        "damage_type" : "����"
]),
([      "action" : "$N�������أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n����"
                   HIR "��Ħ��" NOR "���Ľ����¶����",
        "force" : 330,
        "attack": 185,
        "dodge" : 135,
        "parry" : 155,
        "damage": 280,
        "damage_type" : "����"
]),
([      "action" : "ȴ��$NͻȻ�鲽������ʹ�������䵱��" HIG "���ѵ�ˮ" NOR
                   "����һ��",
        "force" : 180,
        "attack": 95,
        "dodge" : 285,
        "parry" : 375,
        "damage": 130,
        "damage_type" : "����"
]),
([      "action" : "$N�˽���磬��������з���$n��$l�����Ա�$n���أ���������"
                   "��" HIR "��ħ��" NOR "���ġ�" HIR "����ʽ" NOR "��",
        "force" : 270,
        "attack": 155,
        "dodge" : 135,
        "parry" : 165,
        "damage": 260,
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ�˽����һ�ֹ���ġ�" HIY "�����罣��" NOR "����"
                   "��Ȼ��$n�����Ҵ�����",
        "force" : 330,
        "attack": 145,
        "dodge" : 175,
        "parry" : 255,
        "damage": 220,
        "damage_type" : "����"
]),
([      "action" : "$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N����"
                   "����ʵ",
        "force" : 310,
        "attack": 165,
        "dodge" : 115,
        "parry" : 135,
        "damage": 270,
        "damage_type" : "����"
]),
([      "action" : "$N����������ת��$n�����������µ���$n�̳�һ������֪ʹ����"
                   "ʲô����",
        "force" : 330,
        "attack": 135,
        "dodge" : 175,
        "parry" : 215,
        "damage": 225,
        "damage_type" : "����"
]),
([      "action" : "$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��"
                   "֪����Ǻ�",
        "force" : 360,
        "attack": 160,
        "dodge" : 150,
        "parry" : 285,
        "damage": 210,
        "damage_type" : "����"
]),
([      "action" : "$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ�������"
                   "�ȵ�$n���ò���",
        "force" : 510,
        "attack": 225,
        "dodge" : 135,
        "parry" : 175,
        "damage": 190,
        "damage_type" : "����"
]),
([      "action" : "$N���ֺὣ����$n��$l���������������е�һ����������Ȼ���"
                   "$n���Կ��彣������",
        "force" : 334,
        "attack": 135,
        "dodge" : 155,
        "parry" : 185,
        "damage": 280,
        "damage_type" : "����"
]),
([      "action" : "$N�ٽ���ӣ�Ѹ���ޱȵص���$n��$l��ȴ���˿�������������ʲô"
                   "��ʽ",
        "force" : 380,
        "attack": 125,
        "dodge" : 145,
        "parry" : 215,
        "damage": 230,
        "damage_type" : "����"
]),
([      "action" : "$N����һ��ָ��$n���������$n���������ڣ��˵����������ף���"
                   "��˼��",
        "force" : 370,
        "attack": 135,
        "dodge" : 185,
        "parry" : 255,
        "damage": 238,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������"
                   "$n��$l",
        "force" : 390,
        "attack": 155,
        "dodge" : 185,
        "parry" : 275,
        "damage": 230,
        "damage_type" : "����"
]),
([
        "action" : "$N��$w����һ�ڣ�����$n�Լ���$wײ����������֮������������"
                   "�Ѳ�",
        "force" : 410,
        "attack": 155,
        "dodge" : 185,
        "parry" : 195,
        "damage": 280,
        "damage_type" : "����"
])
});

mapping *action2 = ({
([      "action" : HIW "����$N����$w" HIW "�ƿճ�����ƽƽһ������$n��������ʽ����",
        "force" : 450,
        "attack": 180,
        "dodge" : 100,
        "parry" : 100,
        "damage": 240,
        "damage_type" : "����"
]),
([      "action" : HIW "$N�����۽������赭д������̳�һ������֮����������ʽ",
        "force" : 500,
        "attack": 200,
        "dodge" : 120,
        "parry" : 120,
        "damage": 270,
        "damage_type" : "����"
]),
([      "action" : HIW "$N����Ʈ�ݣ���̬��Ȼ������������У�����$w" HIW "�����������������"
                   "�Ž��ѵ����շ�����ľ���",
        "force" : 550,
        "attack": 220,
        "dodge" : 140,
        "parry" :140,
        "damage": 300,
        "damage_type" : "����"
]),
});
int valid_enable(string usage)
{ 
        int lvl;
        object me = this_player();

        lvl = (int)this_player()->query_skill("dugu-jiujian", 1);

        if (lvl >= 30 )
        {

                return usage == "sword" || usage =="parry";
        }
        else
                return usage == "parry";
       
}

mapping query_action(object me, object weapon)
{
        if (me->query("can_learn/dugu-jiujian/nothing"))
               return action2[random(sizeof(action2))];

        else   return action[random(sizeof(action))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("dugu-jiujian", 1) < 120
           || ! (m_weapon = me->query_temp("weapon"))
           || ! living(me) 
           || m_weapon->query("skill_type") != "sword")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dugu-jiujian", 1);
         
        // ����
        if (me->query("can_learn/dugu-jiujian/nothing"))
        {           
             if (ap / 2 + random(ap) < dp)
             {
                        result = ([ "damage": -damage ]);

                        result += (["msg" : HIG "$n" HIG "������$N" HIG "�Ĺ��ƣ�"
                                    "����ӳ�һ����������$N" HIG "��\n" NOR]);
            
                        ob->start_busy(2);
             }
             
             return result;
             
        }

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(9))
                {
                case 0:
                        result += (["msg" : HIC "ȴ��$n" HIC "̤ǰһ������ʽбָ$P" HIC
                                            "�ұۣ���ʽѸ���ޱȣ�ʹ��$N" HIC "��������"
                                            "��\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "��$n" HIC "�Թ�Ϊ�أ��Խ�Ϊ�ˣ�������"
                                            "����$N" HIC "�͹����ػӳ���λ�����̩ɽ"
                                            "��" NOR + YEL "�����" NOR + HIC "��������"
                                            "\n" NOR]);
                        break;

                case 2:
                        result += (["msg" : HIC "$n" HIC "ͻȻһ������$N" HIC "����һ��"
                                            "ȴ�����������ţ�$N" HIC "��ʱ�����޴룬��"
                                            "�Ʋ�������ͣ��������\n" NOR]);
                        break;

                case 3:
                        result += (["msg" : HIC "����$n" HIC "�������ܣ��ٽ������ʹ��"
                                            "��" NOR + HIG "���両��" NOR + HIC "������"
                                            "$N" HIC "���󣬵����˴��С�\n" NOR]);
                        break;

                case 4:
                        result += (["msg" : HIC "ȴ��$n" HIC "ͻȻʹ��������ɷ罣����"
                                            NOR + CYN "���ڤڤ" NOR + HIC "����������"
                                            "��$N" HIC "һ�ʣ���ʱͻ���˹��ơ�\n" NOR]);
                        break;

                case 5:
                        result += (["msg" : HIC "$n" HIC "ͦ�����䣬��һ�С�" NOR + HIW
                                            "���Ƴ��" NOR + HIC "���ش�$N" HIC "����"
                                            "ʱ�ѽ����ƻ��⡣\n" NOR]);
                        break;

                case 6:
                        result += (["msg" : HIC "ֻ��$n" HIC "���˷���������Ʈ�磬һʽ" 
                                            "��" NOR + HIW "��������" NOR + HIC "������"
                                            "�޶�����ס�˽�����\n" NOR]);
                        break;

                case 7:
                        result += (["msg" : HIC "����$n" HIC "���˷�����ʹ����ɽ���С�"
                                            NOR + HIY "�������" NOR + HIC "����������"
                                            "�磬�ܿ���$N" HIC "���С�\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "����ͻ�䣬������������������"
                                            "��ز����ʹ��ɽ�����ġ�" NOR + HIY "������"
                                            "��" NOR + HIC "����ͼ��ʹ$N" HIC "���С�\n"
                                            NOR]);
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
                                 "���任���ֽ��У�Ȼ��$N" HIY "��Ҳ�������ٴι�"
                                 "����˿������$n" HIY "���Ի�\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if ((int)me->query("neili") < 1000)
		return;
	 if ( me->query("can_learn/dugu-jiujian/nothing") && damage_bonus > 150 )
        {
			    me->add("neili", -35);
                victim->receive_wound("qi", (damage_bonus - 120) / 3, me);
                return random(2) ? HIR "$Nһ�����г�����˲��"+HIW"���콣��"+HIR "����" + HIY "ҹ��" HIG "����" NOR + HIR"����$n"
					               HIR  "����͸�����...\n" NOR:
                                   
                                   HIR "��ʱֻ������һ����һ��"+HIY"����" + HIR "��$n"								  
                                   HIR "���Ͽ���������"+HIR"��Ѫ��ʱ��ӿ����...\n" NOR;
        }     
     
}

int valid_learn(object me)
{
        object ob;

        if( !(ob = me->query_temp("weapon"))
        ||   (string)ob->query("skill_type") != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

        if (me->query("int") < 39)
                return notify_fail("������ʲ��㣬�޷�������¾Ž��Ľ��⡣\n");

        if (me->query("can_learn/dugu-jiujian/nothing") &&
            me->query("con") < 36 && me->query("dex") < 36)
                return notify_fail("��������ǻ��������㣬�޷������¾Ž��Ľ��⡣\n");

        if (me->query("character") == "�ĺ�����")
                return notify_fail("��һ����ɱ�����ˣ�û��������¾Ž��ĵ��������塣\n");

        if (me->query("character") == "���ռ�թ")
                return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û��������¾Ž���\n");

        if (me->query("character") == "��������")
                return notify_fail("�����а�����ʲô���¾Ž������߰���ģ�û�а�����ơ�\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("��Ļ�����������̫ǳ���޷�������¾Ž���\n");

        if (me->query_skill("sword", 1) < me->query_skill("dugu-jiujian", 1))
                return notify_fail("��Ļ��������������ޣ��޷����������Ķ��¾Ž���\n");

        return 1;
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
        return 100;
}

int practice_skill(object me)
{
	      int level, cost;
        level = (int) me->query_skill("dugu-jiujian", 1);

        if ( level > 400 ) cost = level / 3 + random(level);
                     else  cost = level / 4 + random(level);
	
	if (me->query("family/family_name") != "��ɽ��")
	    return notify_fail("���¾Ž�ֻ��ͨ�����ܾ�ʽ�����������о���ߡ�\n");
	else
	 	{
	 		object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) || 
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < cost)
                return notify_fail("����������������¾Ž���\n");

        if ((int)me->query("neili") < cost)
                return notify_fail("����������������¾Ž���\n");

        me->receive_damage("qi", cost);
        me->add("neili", - cost);
        return 1;
	 	}
	 
}

string perform_action_file(string action)
{

        return __DIR__"dugu-jiujian/" + action;
}

void skill_improved(object me)
{
        int lvl, i;

        i = me->query("int") / 3;
        lvl = me->query_skill("dugu-jiujian", 1);

        if (lvl > 120
           && me->query("can_perform/dugu/qi") <= 100
           && ! me->query("can_learn/dugu-jiujian/nothing"))
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
           && me->query("can_perform/dugu/po") <= 100
           && ! me->query("can_learn/dugu-jiujian/nothing"))
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
}

int difficult_level()
{
        object me = this_object();
       
        if (me->query("can_learn/dugu-jiujian/nothing"))
               return 550;

        else   return 400;
}