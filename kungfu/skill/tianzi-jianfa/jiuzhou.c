//�࣬�죬�������,��,��,ԥ,��
/* ��Ц̸���¡�����[Wzw]��С¥һҹ������
��Ц̸���¡���Ϣͨ�棺����̶����ɫ��Ȥζ����(help funquest)����������(help mirror)
С�����˽�����
��Ц̸���¡�����[Wzw]����ҹ��������
��Ц̸���¡�����[Wzw]������������ŪӰ
��Ц̸���¡�����[Wzw]�����������紺ˮ */


#include <ansi.h>
#include <combat.h>

#define JIUZHOU "��" HIW "���ݳ���" NOR "��"

inherit F_SSERVER;

string final1(object me, object target, int damage, object weapon, int lvl);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage, object weapon, int lvl);
string final4(object me, object target, int damage, object weapon, int lvl);


int perform(object me, object target)
{
        int damage;
        string msg, sub_msg;
        int ap, dp;
        object weapon;       
        int lvl;

        if (userp(me) && ! me->query("can_perform/tianzi-jianfa/jiuzhou"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIUZHOU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JIUZHOU "��\n");   
        if (me->query_skill_mapped("sword") != "tianzi-jianfa")
                return notify_fail("��û�м������ӽ���������ʩչ" JIUZHOU "��\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("��������Ϊ����������ʩչ" JIUZHOU "��\n");

        lvl = (int)me->query_skill("tianzi-jianfa", 1);
        if (lvl < 340)
                return notify_fail("�����ӽ�����򲻹�������ʩչ" JIUZHOU "��\n");
   

        if ((int)me->query("neili") < 850)
                return notify_fail("��������������������ʩչ" JIUZHOU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_sort(HIY "\n$N" HIY "ͻ�Ե���̬֮�������ߺ���\n"NOR
                     HIR" ������֮�£�Ī�����������ӽ��������ݳ�������\n"NOR
                     HIW "     ��������" HIW "����ƺ�����ǧ��������ͬ$N�Ľ��о���Ϯ��$n"
                          HIW "��\n" NOR, me, target);

       ap = lvl + me->query_skill("sword", 1);
       

        // ��һ�У��ж϶Է�����
        dp = target->query_int() * 2 + target->query_skill("dodge", 1) 
             + target->query_skill("parry", 1);

        message_sort(HIG "\n$N" HIG "�ߺ�����һ�У�����ȡ���ݣ�"
                     "һ��ֱ��$n���š�\n" NOR, me, target);
        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                 msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                           (: final2, me, target, damage :));
              
        } else
        {
                msg = HIC "$n" HIC "����˫�ۣ������Զԣ�����$N" HIC "֮��жȥ��\n" NOR;
        }
        message_sort(msg, me, target);

        // �ڶ��У��ж϶Է�����
        dp = target->query_str() * 2 + target->query_skill("unarmed", 1) + 
             target->query_skill("parry", 1);
        message_sort(HIM "\n$N" HIM "�ߺ����ڶ��У�����ȡ���ݣ�"
                     "����ͻ�䣬�Ĺ�$n" HIM "˫�ۡ�\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 95 + random(10),
                                          HIR "$n" HIR "����$N" HIR "���з�ǳ֮������"
                                          "�������мܣ���Ȼ�䣬�����͡���һ����" + weapon->name() +
                                          HIR "�Ѵ���$n" HIR "��˫�ۣ���Ѫ����ӿ����\n" NOR, me , target);
        } else
        {
                msg = HIC "$n" HIC "���Ҵ��⣬�����Զԣ�����$N���л�ȥ��\n" NOR;
        }
        message_sort(msg, me, target);

        // �����У��ж϶Է�����
        dp = target->query_con() * 2 + target->query_skill("force", 1) + 
             target->query_skill("parry", 1);

        message_sort(HIC "\n����ʹ�ϣ������ŵ���������ȡ��������������$N" HIC "��"
                    "��˼����ֱȡ$n���\n" NOR, me,target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                         (: final1, me, target, damage, weapon, lvl :));
        } else
        {
                msg = HIC "$n" HIC "���˵��Ӳ�����ֵ�ס$N" HIC "���С�\n" NOR;
        }
        message_sort(msg, me, target);

        // �����У��ж϶Է���
        dp = target->query_dex() * 2 + target->query_skill("dodge", 1) + 
             target->query_skill("parry", 1);

        message_sort(HIW "\n$n��δ�ع�����������$N��ʹ�������У�����ȡ���ݣ�"
                     HIW "��������$n���̡�\n" NOR, me,target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          (: final3, me, target, damage, weapon, lvl :));
        } else
        {
                msg = HIC "$n" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ����Ŷ��$N" HIC "���С�\n" NOR;
        }
        message_sort(msg, me, target);


        // �����У��ж϶Է���ѧ����������ʶ��
        ap += ( me->query_skill("martial-cognize",1) + me->query_skill("literate", 1) ) / 2;
        dp = target->query_skill("martial-cognize",1) + target->query_skill("literate", 1) + 
             target->query_skill("parry", 1);

        message_sort(HIB "\n$Nʹ�����һ�У�������ԥ�����ݲ�ȡ��"
                     HIB "����" + weapon->name() + "ˢˢˢ�����彣��"
                     "��Ѹ�ײ����ڶ�֮�ƹ���$nȫ��ҪѨ��\n" NOR, me,target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          (: final4, me, target, damage, weapon, lvl :));
        } else
        {
                msg = HIC "$n" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ����Ŷ��$N" HIC "���С�\n" NOR;
        }
        message_sort(msg, me, target);



        me->start_busy(2 + random(3));
        me->add("neili", -800 - random(800));
        return 1;
}

string final1(object me, object target, int damage, object weapon, int lvl)
{
        target->add("neili", -(lvl + random(lvl)));

        return  HIR "$n" HIR "ȴ��$N" HIR "�������ƻֺ룬�������������ֵ�������������"
                "���������ˣ�$n" HIR "�ƺ�һ�������˼������پ���Ϣ��ɢ��" + weapon->name() + HIR 
                "������Ⱦ����Ѫ��\n" NOR;
}

string final2(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "����һ��������$N" HIY "�⼸�������ޱȣ���ʽ�仯Ī�⣬"
                "������ȴ��Ȼ����������ԥ�䣬$n" HIY "ȴ�����У��ٸо������ã���"
                "��������\n" NOR;
}

string final3(object me, object target, int damage, object weapon, int lvl)
{
   
        target->start_busy(4 + random(lvl / 40));
  
        return  HIY "$N" HIY  "�������ޱȣ�����" + weapon->name() + HIY "ʱ������������ʱ��"
                "�������裬���Ǽ�$n" HIY "�ѱ������ˣ�$N" HIY "��Ȼ������" + weapon->name() + HIY "һ"
                "ת�����ƶ�Ȼ�ӿ죬��$n" HIY "����Χס������һ˿��϶��\n" NOR;

}

string final4(object me, object target, int damage, object weapon, int lvl)
{
   
         
        return  HIY "$N" HIY  "�������ޱȣ�����" + weapon->name() + HIY "ʱ������������ʱ��"
                "�������裬���Ǽ�$n" HIY "�ѱ������ˣ�$N" HIY "��Ȼ������" + weapon->name() + HIY "һ"
                "ת�����ƶ�Ȼ�ӿ죬��$n" HIY "����Χס������һ˿��϶��\n" NOR;

}
