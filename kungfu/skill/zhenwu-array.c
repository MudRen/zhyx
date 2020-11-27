// ���佣�� zhenwu-array.c
// Modified by haiyan

#include <ansi.h>

#define MAX_ZHEN 8 
#define MIN_ZHEN 5 

inherit F_CLEAN_UP;
inherit F_SSERVER;

int valid_enable(string usage) { return usage=="array"; }

string *style = ({ 
HIM "$N�ֳ�$w��ǰ����һ���裬����$w��Ȼ����$n��\n"NOR,
HIM "$N�ŵ�һ��������$w�������Ѵ���$nС����\n"NOR, 
HIM "$N������ס$w������һ���׻�������ֱָ$nü�ģ�\n"NOR,
HIM "$N��ǰһ�ݣ����˰벽��ͻȻһ������������$w��$n���˹�ȥ��\n"NOR,
HIM "$N��$w�϶�Ϊһ���������ͦ�����$n������Ҫ����\n"NOR, 
HIM "$N������һ������������$w�������£�����$n���̣�\n"NOR, 
HIM "$N����һԾ������$w�������죬����$n����������\n"NOR, 
HIM "$N����$w���ӣ������������⣬����һת��Ѹ�ٴ���$n��\n"NOR
});

string *zhen = ({ 
HIC"\n���佣�󻺻�ת������$nΧ�ں��ģ�һ��ǿ�������ѹ��$n��\n\n"NOR, 
HIC"\n���佣��������ˣ�$n������󣬿�����˿��������ֻ�ý����Ż����������Գ��С�\n\n"NOR, 
HIC"\n$Nһ����Х�����佣��Ѹ����λ�����˲����������$n���ˡ�\n\n"NOR, 
HIC"\n���佣��Խ��ԽС���������಻�������ν������˳�һ��Ȧ��$n��\n\n"NOR 
});

int valid_learn(object me) 
{ 
        if ((int)me->query_skill("wudang-xinfa", 1) < 100)
                return notify_fail("����䵱�ķ���򲻹���������ᡸ���佣�󡹡�\n"); 

        if ((int)me->query_skill("taoism", 1) < 150) 
                return notify_fail("��ĵ�ѧ�ķ���Ϊ�������޷��������ġ����佣�󡹡�\n"); 

        if ((int)me->query_skill("sword", 1) < 100) 
                return notify_fail("��Ļ����������̫ǳ���ԡ����佣�󡹵ı仯������ᡣ\n"); 

        if ((int)me->query_skill("array", 1) < (int)me->query_skill("zhenwu-array", 1)) 
                return notify_fail("��Ļ�����ˮƽ���ޣ��޷���������ġ����佣�󡹡�\n"); 

        return 1;
} 

void remove_effect(object me);
void checking(int del_time,object me);

int practice_skill(object me) 
{
      return notify_fail("���佣��ֻ����ѧ(learn)����������������ȡ�\n"); 
}

int form_array(object me)
{
        int i; 
        object *member, weapon; 
        member = me->query_team();

        if( !pointerp(member=me->query_team()) || !me->is_team_leader())
                return notify_fail("ֻ�ж�������ſ���ָ������\n");

        if( me->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("�㻹û��׼�������佣��\n");

        if( sizeof(member) > MAX_ZHEN )
                return notify_fail("���佣�����ֻ���ɰ����䵱������ɡ�\n");

        if( sizeof(member) < MIN_ZHEN )
                return notify_fail("���佣������Ҫ�������䵱������ɡ�\n");

        if( me->query_skill("zhenwu-array",1) < sizeof(member)*20 ) 
                return notify_fail("������佣��ľ�Ҫ�仯��δ��ȫ����\n"); 

        for( i = 0; i < sizeof(member); i++ ) 
        { 
           if (!member[i]) 
                return notify_fail("��Ķ����������뿪����Ҫ������϶��顣\n");

           if (environment(member[i]) != environment(me)) 
                return notify_fail("������е�"+member[i]->name()+"��������ߡ�\n");

           if (member[i]->query("family/family_name") != "�䵱��") 
                return notify_fail("������е�"+member[i]->name()+"�����䵱�ɵ��ӡ�\n"); 

           if (member[i]->query_skill("zhenwu-array",1) < 80 ) 
                return notify_fail("������е�"+member[i]->name()+"���佣���󷨻�δ���š�\n");

           if (! objectp(weapon = member[i]->query_temp("weapon")) || 
                (string)weapon->query("skill_type") != "sword") 
                return notify_fail("������е�"+member[i]->name()+"û��װ������\n"); 

           if (member[i]->query_skill("sword",1) < 120 ) 
                return notify_fail("�������"+member[i]->name()+"�Ļ�����������̫�͡�\n");

           if (member[i]->query_skill_mapped("array") != "zhenwu-array") 
                return notify_fail("������е�"+member[i]->name()+"δ׼�������佣���󷨣�\n");
        } 

        if( me->is_busy())
               return notify_fail("������æ������ָ����������! \n");

        if( me->query_temp("alreading") )
               return notify_fail("��Ķ����Ѿ�����ˡ����佣�󡹣�\n");

        message_vision( HIY "$N" HIY "һ����Х������" + weapon->name() + 
                        HIY "һ���������ƶ����������˷��������վ����λ���ڳ���"
                        HIY "�����佣���󷨣�\n\n"
                        HIW "���˻ӽ���������佣�� ���� ���µ�һ��\n\n" NOR, me);

        me->set_temp("alreading",(int)me->query_skill("zhenwu-array", 1)/10+10);
        call_out("checking", 1, 1, me); 
        return 1;
}

void checking(int del_time,object me)
{
        string msg;
        int num, atac;
        int i, fighting;
        object *member, target, weapon;

        if (!me->query_temp("alreading")) return;

        target = me->query_temp("offensive_target");
        num = (int)me->query_temp("alreading");
        member = me->query_team(); 

        me->set_temp("alreading", me->query_temp("alreading")-del_time);
        if( wizardp(me) )  tell_object(me,sprintf("<����ʱ�仹ʣ%d��>\n",num));
        if( num <= 1 ) 
        {
             message_vision(HIW "$N" HIW "�ѽ��Լ������յ����佣��ȫ���仯"
                            HIW "������ϣ���ɢ�˽���\n\n"NOR, me);
             me->delete_temp("alreading");
             return;
        }

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character())
        {
            call_out("checking", 1, 1, me); 
            return;
        }

        for (i = 0; i < sizeof(member); i++ ) 
        {
            if (!member[i]) 
            {
                message_vision(HIW "����$n" HIW "���뿪�������佣����Ҫ������ϡ�\n\n" NOR, me, member[i]); 
                remove_effect(me);
                return;
            }

            if(member[i]->is_corpse())
            {
                if ( sizeof(member) < MIN_ZHEN )
                {
                    message_vision(HIW "����$N" HIW "û�ֵܵ�ס$n"
                                   HIW "������һ�������佣���������㣬�ٳ���������$n���ơ�\n\n"NOR, member[i], target);
                    remove_effect(me);
                    return;
                }
                else
                    message_vision(HIW "���˿���$N" HIW "����$n"
                                   HIW "���֣�ŭ������ʿ�����������¸ı����Σ���$n"
                                   HIW "����Χס��\n\n"NOR, member[i], target);
            }

            if (environment(member[i]) != environment(me)) 
            {
                message_vision(HIW "$n" HIW "��$N" HIW "��ս���£�˽�Ķ���Ϊ���Ա�����Ȼ�����ֳ���\n"
                               HIC "����$n�뿪�ֳ������佣��$N�����ˣ�\n\n" NOR, target, member[i]); 
                remove_effect(me);
                return;
            }

            weapon = member[i]->query_temp("weapon");
            if (!objectp(weapon) || (string)weapon->query("skill_type") != "sword")
            {
                message_vision(HIW "$N" HIW "��$n" HIW "�������֣�������񣬼���$n�������С�\n"
                               HIW "$n" HIW "����֮�£��������ˣ�����ƫ�������佣��λ��\n"
                               HIC "���佣��$N" HIC "�����ˣ���\n\n" NOR, target, member[i]); 
                remove_effect(me);
                return;
            }
            atac += (member[i]->query_skill("force",1) +
                     member[i]->query_skill("sword",1)) / 2;
            member[i]->kill_ob(target); 
        }

        atac = atac / sizeof(member);
        if( wizardp(me) )  tell_object(me,sprintf("<���ӹ�����%d��>\n",atac));
        fighting = random(sizeof(member)); 
        if (living(member[fighting]))
        {
           if (random(10) > 6)
           {
              msg = zhen[random(sizeof(zhen))]; 
              message_vision(msg, me, target);
           }

           if (random(8) > 5)
           {
               if (target->query("family/family_name") != "�䵱��") 
                   message_vision(HIY "$N" HIY "������$n"
                                  HIY "�ȵ������󵨿�ͽ�����䵱�ɽ��������е������������������\n"
                                  NOR, member[fighting], target);
           else
                   message_vision(HIY "$N" HIY "��$n"
                                  HIY "�ȵ������������䵱��Ҫ�����Ż������������������\n"
                                  NOR, member[fighting], target);
           }

           weapon = member[fighting]->query_temp("weapon");
           msg = style[random(sizeof(style))]; 
           msg = replace_string(msg,"$w",weapon->name()); 
           if (objectp(weapon) && (string)weapon->query("skill_type") == "sword")
           {
               if (!member[fighting]->is_busy())
               {
                   message_combatd(msg, member[fighting], target); 
                   member[fighting]->add_temp("apply/attack", atac);
                   member[fighting]->add_temp("apply/damage", atac);
                   COMBAT_D->do_attack(member[fighting], target, weapon, 0);
                   member[fighting]->add_temp("apply/attack", -atac);
                   member[fighting]->add_temp("apply/damage", -atac);
                   member[fighting]->start_busy(2);
               }
           }
        }
        call_out("checking", 1, 1, me);
        return;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("alreading");
        me->start_busy(1);
}

