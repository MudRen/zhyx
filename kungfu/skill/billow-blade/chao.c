#include <ansi.h>
#include <combat.h>

#define SHA "��" HIR "��һ�߹۳���" NOR "��"

inherit F_SSERVER;
inherit SKILL;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);
 
        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SHA "��\n");

        if (me->query_skill("force") < 400)
              return notify_fail("����ڹ���Ϊ����������ʩչ" SHA "��\n");

        if (me->query_skill("billow-blade", 1) < 300)
                return notify_fail("��Ĳ��˵�����Ϊ����������ʩչ" SHA "��\n");

        if (me->query_skill_mapped("blade") != "billow-blade")
                return notify_fail("��û�м������˵���������ʩչ" SHA "��\n");

        if (me->query("neili") < 1000)
                return notify_fail("�����������������ʩչ" SHA "��\n");
                
        if(me->query_temp("no_sha"))
                return notify_fail("����Ϣδ�ȣ��޷�ʹ��" SHA "��\n");   

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

                    message_vision(HIR"$NХ�����������Ƴ��죬�����𴦣�ʩչ�����˵������� �� һ �� �� �� ������\n"NOR, me);

        ap = me->query_skill("blade") + me->query_dex() * 5;
        dp = target->query_skill("force") + target->query_con() * 5;

                damage = ap / 3 + random(ap/3);

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           YEL "��������������������������������������������������������������
      ����"HIC"��"NOR+YEL"����"HIC"һ"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"ӿ"NOR+YEL"����
��������������������������������������������������������������
"HIW"$N�ó���㵶�ˣ�����ˮ����ӣ�����һ�����ߣ�է��է�֣�΢΢���
ԶԶ��ȥ��"HIW"��Ӱ������������Ծ׷���������������ų�һ�ߣ��˷����˶�������\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           YEL "��������������������������������������������������������������
      ����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"ӿ"NOR+YEL"����
��������������������������������������������������������������
"HIW"ǰ��δƽ���ڶ��㵶��������"HIW"������������к���������ʽ����壬���ȶ�������\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           YEL "��������������������������������������������������������������
      ����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"ӿ"NOR+YEL"����
��������������������������������������������������������������
"HIW"���ص����༤����������ӿ��������ɽ�����ѣ�"HIW"��������ľ��ˣ��ݿ����࣡��\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           YEL "��������������������������������������������������������������
      ����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"ӿ"NOR+YEL"����
��������������������������������������������������������������
"HIW"���˽���������������ܾ���ʨͻأ���𣬶����ɸ�ˮ����������������ˮ��������\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           YEL "��������������������������������������������������������������
      ����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"��"NOR+YEL"����"HIC"ӿ"NOR+YEL"����
��������������������������������������������������������������
"HIW"���˹�������������ɽ������ѩ����ҡ����̣����˺�Х������������Ծ������η��ף����ò�Ϣ����\n"
                                           NOR);
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap/3);
                me->add("neili", -500);
                me->start_busy(3+random(3));
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "����ĵ�����ӿ��������͸$n"HIR"�����壬ֻ��������ϸ��ĵ��ۣ�
$n"HIR"������ͻȻ��¶��Ī���Ŀ־壬���еľ����ѱ��֧�����飬
$n"HIR"��ǰ�񱼣��·�Ҫץסʲô��ȴ���������޾��ĺڰ���ֻ�����������Ĳҽ��ڲ��֮��ص�����\n"
                                           NOR);
        } else
        {
                me->add("neili", -800);
                me->start_busy(3+random(4));
                msg = CYN "$n" CYN "��$P" CYN "������ӿ���������׵�"
                       "������æ������Ų������������\n" NOR;
        }
        message_combatd(msg, me, target);
        
        me->set_temp("no_sha",1);
        call_out("sha_ok", 3+random(4), me);   

        return 1;
}

void sha_ok(object me) {
  if (!me) return;
  me->delete_temp("no_sha");
}


