// hanbing-zhenqi.c ��������
// updated by kasumi

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return force == "songshan-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("hanbing-zhenqi", 1);
          return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query("character") == "��������")
                return notify_fail("�����а��룺�����¹������䣬ѧ��������"
                                   "�书������\n");

        if (me->query("gender") == "����"
           && (int)me->query_skill("hanbing-zhenqi", 1) > 19)
                return notify_fail("���޸����ԣ��������������Զ�������������\n");

        if (me->query("con") < 34)
                return notify_fail("��������ǲ������޷���������������\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򲻹������Զ�������������\n");

        if (me->query("max_neili") < 1000)
                return notify_fail("��Ŀǰ��������Ϊ���������Զ�������������\n");

        if (me->query_skill("force", 1) < me->query_skill("hanbing-zhenqi", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ��������ĺ���������\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	if (me->query_skill("wuyue-shenjian", 1))
	{
       if (me->query_temp("weapon") && me->query_temp("freezing"))  
       {       
		victim->receive_wound("qi", damage_bonus + random(50), me);
		return HIR "ֻ��������Ϊ" HIW "��������" HIR "�����������껮��" +victim->name()+ HIW "��Ѫ�ɽ���\n" NOR;                
       }
	}
	else 
	{
		if (me->query_temp("weapon") && me->query_temp("freezing") && random(3) == 1)  
       {       
		victim->receive_wound("qi", damage_bonus + random(100), me);
		return HIR "ֻ��������Ϊ" HIW "��������" HIR "�����������껮��" +victim->name()+ HIW "��Ѫ�ɽ���\n" NOR;
		}
	}
   
   if ( !me->query_temp("weapon") && me->query_temp("freezing"))  
   {
        mixed result;
        int lvl  = me->query_skill("hanbing-zhenqi", 1);
        int flvl = me->query("jiali")+30;

        result = ::hit_ob(me, victim, damage_bonus, factor);

        if (intp(result) && result > 0)
        {
                if (me->query("neili") < 200 || lvl < 250)                
                       return;
            
                if (flvl*2 + random(lvl) > victim->query_skill("force",1))
                {
				         
                        victim->affect_by("freezing",
                               ([ "level"    : flvl * 3,
                                  "id"       : me->query("id"),
                                  "duration" : lvl / 60 + random(lvl / 40) ]));

                        

                        return random(2) ? ([ "damage" : result,
                                              "msg"    : HIW "$n" HIW "����$N" HIW "һ�У���"
                                                         "ʱֻ�е�����Ϯ�壬˵�����Ķ�������"
                                                         "��\n" NOR ]):

                                           ([ "damage" : result,
                                              "msg"    : HIW "ֻ��$n" HIW "ȫ��һ������Ƥ��"
                                                         "�ϣ���������$N" HIW "�����ھ��ĸ�"
                                                         "�š�\n" NOR ]);
                }
        }
        return result;
	}
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int n;

		n=(int)(me->query_skill("hanbing-zhenqi", 1)/100);

        if ((int)me->query_skill("hanbing-zhenqi", 1) < 160
           || ! living(me))
                return;

		if (ob->query_skill_mapped("force") == "jiuyang-shengong")
			n=(int) n/2;
                
        
        ap = ob->query_skill("force",1);
        dp = me->query_skill("hanbing-zhenqi",1);
        if (ap / 2 + random(ap) < dp)
        {             
             result = ([ "damage" : -damage/2 ]);
             result += ([ "msg" : HIM "$N" HIM "ֻ�о�һ��ǿ���ĺ���ֱ��ȫ��ȫ��ѪҺ�ƺ�Ҫ�����̣�������ʽ��ý�Ӳ������\n" NOR ]);
			 ob->start_busy(n);
	         return result;
        }
}



string exert_function_file(string func)
{
        return __DIR__"hanbing-zhenqi/" + func;
}

