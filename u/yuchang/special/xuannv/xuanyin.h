
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
        set_name(HIG "��������ɴ" NOR, ({ "xuanyin" }));
        set_weight(15000);        
        set("special", 1);
        set("unit", "��");        
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");   
        set("point", 560);
        set("no_sell", 1 ); 
        set("value",1000000); 
        set("no_steal", 1);      
        set("material", "tian jing");
        set("wear_msg", HIG "����ɴ��ճ�����ϼ�����䣬������񳯷�����$N��\n"
                            "ɲʱ����$N�϶�Ϊһ��\n" NOR);
        set("remove_msg", HIC "$N" HIC "һ����̾����������ɴ�����ڣ���ʱ��ʧ�����Ρ�\n" NOR);
        if (! check_clone()) return;
        restore();
        set("armor_prop/dodge", 100);
        set("armor_prop/parry", 100);
        set("armor_prop/armor", 200);
        setup();
}

string long() { return query("long") + item_long(); }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "����һ̾������" HIC "����ɴ" HIR "����"
                                            "���죬$N" HIR "ֻ����ͷһ����ࡣ��һ�о�Ȼ����ȥ��\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "ֻ��$n" HIM "����" HIC "����ɴ" HIM "һ������"
                                            "��������" HIM "$N" HIM "��ֻ��ͷ��Ŀѣ����Ȼһ�д��ڿմ���\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "һ�д���$n" HIW "���پ���������������һ����ԭ����"
                                            "��" HIC "����ɴ" HIW "�û������Ļ���\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "����" HIC "����ɴ" HIY "һ��ϼ��������$N" HIY "��һ"
                                            "�б�ϼ�����ε�ס���˲���$n" HIY "�ֺ���\n" NOR]);
                        break;
                }
                return result;
        }
}


void init()
{
    add_action("do_canwu", "canwu");  
    add_action("do_linghui", "linghui");      
}

int do_canwu( string arg )
{
   object me;
   int s_skill, t_skill;

   me = this_player();

   if ( ! arg || arg != "xuanyin")
      return notify_fail("��Ҫ����ʲô?\n");

   if ( ! me->query("special_skill/queen") )
      return notify_fail("���������ɴ�����˰��죬"
                         "������ͨ���ƺ����Դ�����ᵽ�κ�������\n");


   s_skill = (int)me->query_skill("sword", 1);
   t_skill = (int)me->query_skill("xuannv-jian", 1);

        if (s_skill < t_skill)
        {
                message_vision("$N�Ի����������˽�̫�ͣ���"
                               "����������ɴ�ϵ����ݡ�\n", me);
                return 1; 
        }

        if (me->query("jing")< 90)
        {
                message_vision("$N̫���ˣ������޷���������ɴ�ϵ����ݡ�\n",me);
                return 1; 
        }

        if (t_skill >= 180)
        {
                message_vision("$N��������ɴ�ϵ�����̫��ǳ�ˡ�"
                               "����(linghui ����)��\n", me);
                return 1;
        }

        message_vision("$N��ϸ��������ɴ�����ص��ܼ�������Ů"
                       "������������\n", me);
        me->improve_skill("xuannv-jian", 1 + random(me->query("int")));
        me->receive_damage("jing", 75);
    return 1;
}

int do_linghui( string arg )
{
    object me = this_player();
    

    if ( ! me->query("special_skill/queen") )
        return 0;    
  
    if (me->is_busy())
          return notify_fail("��������æ���ء�\n");

    if (me->is_fighting())
          return notify_fail("�㻹���ȴ������˵�ɣ�\n");

    if ( ! arg || ( arg != "΢�������" && arg != "�����һ���") )
          return notify_fail("��Ҫ���ʲô���У���ʽΪ(linghui ����)��\n");

    if ( arg == "΢�������" 
        && me->query("can_perform/xuannv-jian/qingfu"))
          return notify_fail("�����㲻���Ѿ�������\n");
  
    if ( arg == "�����һ���" 
        && me->query("can_perform/xuannv-jian/taohua"))
          return notify_fail("�����㲻���Ѿ�������\n");

    if ((int)me->query("jing") < 100)
          return notify_fail("��ľ����޷����У��޷������У�\n");
 
    me->receive_damage("jing", 90);

    me->start_busy(2 + random(4));

    if (random(10) == 1 && arg == "΢�������" )
    {
        me->add("xuannv-jian/qingfu/count", 1);

        if (me->query("xuannv-jian/qingfu/count") >= 10)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ��΢������桹��\n" NOR);

            me->set("can_perform/xuannv-jian/qingfu", 1);
            me->delete("xuannv-jian/qingfu/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("xuannv-jian"))
                    me->improve_skill("xuannv-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);
            return 1;
        }

        write(HIC "��ԡ�΢������桹���������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }

    if (random(15) == 1 && arg == "�����һ���")
    {
        me->add("xuannv-jian/taohua/count", 1);

        if (me->query("xuannv-jian/taohua/count") >= 20)
        {
            write(HIM "��Ȼ�䣬�����л�Ȼ��ͨ���������ǡ�\n" NOR);
            write(HIC "������ͨ���˾�ѧ�������һ��졹��\n" NOR);

            me->set("can_perform/xuannv-jian/taohua", 1);
            me->delete("xuannv-jian/taohua/count");

            if (me->can_improve_skill("sword"))
                    me->improve_skill("sword", 1500000);
            if (me->can_improve_skill("xuannv-jian"))
                    me->improve_skill("xuannv-jian", 1500000);
            if (me->can_improve_skill("martial-cognize"))
                    me->improve_skill("martial-cognize", 1500000);

            return 1;
        }

        write(HIC "��ԡ������һ��졹���������µ���ʶ������������಻��֮����\n" NOR);
        me->start_busy(2 + random(4));
        return 1;   
    }
        return notify_fail("����ͼ������ɴ������йء�" + arg + "�������ݣ�\n"
                           "�������ûʲôЧ������������������\n");

}
void owner_is_killed()
{
        destruct(this_object());
} 
