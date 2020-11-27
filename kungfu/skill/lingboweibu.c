// by Lonely

#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
        "ֻ��$nʩչ�貨΢���������ϣ�է��է�������޳��򣬽�ֹ���ڡ�\n",
        "ֻ��$nʩչ�貨΢����������ӯ���·�����֮���£���֪���ľ͵�������֮�⡣\n",
        "$n����ӰƮƮ��������֮��ѩ��ʩչ�������貨΢����$N��$n���½Ƕ�մ������\n",
        "����$nʩչ�貨΢������һת����һб�����Ѿ��Ƶ���$N�����ᡣ\n",
        "����$nʩչ�貨΢����ֻ�����赭д������̤��һ����������رܿ���$N�Ĺ��ơ�\n",
        "ֻ��$n��Ӱ�������һת����Ѹ����Ʈ������ʩչ�������貨΢����\n",
        "$Nֻ������ǰһ����ͷ�Է��裬ֻ�������涼��$n����Ӱ��\n",
        "$n��������̤��һ����ʩչ�貨΢����������������$Nǣ��������ת��\n",
});

int valid_enable(string usage) 
{ 
        return usage == "dodge"; 
}

int practice_level(){ return 101; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 500)
                return notify_fail("���������Ϊ�������޷���ϰ����Ĳ�����\n");
                
        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹����޷���ϰ����Ĳ�����\n");
                
        if (me->query_skill("dodge", 1) <= me->query_skill("lingboweibu", 1))
                return notify_fail("��Ļ����������޷���������ļ��ɡ�\n");
                
        if ((int)me->query("dex") < 21 || (string)me->query("family/family_name") != "��ң��") 
               return notify_fail("�������������貨΢����С��Ū�����ȡ�\n"); 
        
        if ((int)me->query("int") < 25) 
               return notify_fail("������������ѧ�貨΢����ǿѧ��û���õġ�\n"); 
               
        return 1;
}

string query_dodge_msg(string limb,object me)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 40)
                return notify_fail("�������̫���ˣ��������貨΢����\n");
                
        if ((int)me->query("neili") < 50)
                return notify_fail("�������̫���ˣ��������貨΢����\n");
                
        me->add("neili", -30);          
        me->receive_damage("qi", 20);        
        return 1;
}

string perform_action_file(string action)
{
      return __DIR__"lingboweibu/" + action;
}

int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("lingboweibu", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}

// �о����Ѷȵ��趨
int difficult_level()
{
        return 500;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("lingboweibu", 1) < 50 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) * 2 / 3 +
             me->query_skill("lingboweibu", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "ʩչ�貨΢���������ϣ�է��է�������޳���"
                                            "��ֹ���ڣ�\n$N" +
                                            HIC "ֻ������ǰһ����ͷ�Է��裬ֻ�������涼��$n����Ӱ������ȫ��������\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "ʩչ�貨΢����������ӯ���·�����֮����"
                                            "��֪���ľ͵�������֮�⣬����$N" HIC "�Ĺ��ơ�\n" NOR]);
                        break;

                default:
                        if (! ob->is_busy())
                                ob->start_busy(random(3));
                        result += (["msg" : HIC "$n" HIC "��������̤��һ����ʩչ�貨΢��"
                                            HIC "��������������$N"
                                            HIC "ǣ��������ת�������泩��\n" NOR]);
                        
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "ʩչ�貨΢���������ϣ�է��է�������޳���"
                                 "���޳���\nȻ��$N" +
                                 HIY "��Ҳ�������ֻ���ֱ�룬��Ϯ$n"
                                 HIY "��\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "ʩչ�貨΢����������ӯ���·�����֮���£�"
                                 "����$N" HIY "����ȴ�Ǳ仯�޷�������ѭ����\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "��������̤��һ����ʩչ�貨΢����"
                                 HIY "��������������$N"
                                 HIY "���̱仯���࣬�����п��ٽ���$n"
                                 HIY "��\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

void skill_improved(object me)
{
        if (me->query_skill("lingboweibu",1) == 80 && ! me->query("lbwb") 
        &&  me->query_skill("literate", 1) > 80)
        {
                tell_object(me, HIY "$Nһ������������ֻ���������泩����֪���������������ۡ�\n" NOR);
                me->add("max_neili", random(30)+20);
                me->add("lbwb",1);
        }
        if (me->query_skill("lingboweibu", 1) == 120 && me->query("lbwb") == 1 
        &&  me->query_skill("literate", 1) > 100)
        {
                tell_object(me, HIM "$N��ʮ�������꣬�պ�����һ����Ȧ���ص�ԭ�أ��������\n" NOR);
                me->add("max_neili", random(30)+20);
                me->add("lbwb", 1);
        }
        if (me->query_skill("lingboweibu", 1) == 160 && me->query("lbwb") == 2 
        &&  me->query_skill("literate", 1) > 120)
        {
                tell_object(me, CYN "$NԽ��Խ�죬��Ϣ���Ų�����ס��ת������Ȼ�Լ��������Ѿ�������ߣ�\n" NOR);
                me->add("max_neili", random(30)+20);
                me->add("lbwb", 1);
        }
        if (me->query_skill("lingboweibu", 1) == 200 && me->query("lbwb") == 3 
        &&  me->query_skill("literate", 1) > 140)
        {
                message_vision(RED "$N������죬����̤�����Ų���Բ��ֻ��������ˬ��ȫ����������\n" NOR, me);
                me->add("max_neili", random(30)+20);
                me->add("lbwb", 1);
        }
}

