#include <ansi.h>
#include <weapon.h> 
inherit WHIP; 
void create()
{
        set_name( RED "������" NOR, ({ "huhualing" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 0);
                set("material", "leather");
                set("rigidity", 70);
                set("long", "һ������֮�ϣ����˸�ϵ��һ˫��ɫ��С�塣���꣬���׵۰������ԣ�Ψ�ַ�ȸ�л���\n���ڹ�԰�еĻ�ľ�ϣ�ϵ���������壬ֻҪȸ��һ�仨�ϣ�����֮�����𣬶���͢��\n�Ļ���ʹ�ߣ��㼴�������񡣵�ʱ�������ˣ���������Ϊ�������塯������ʫ�ˣ�\nҲ���С�ʮ����峣������֮�䡣������֮���Ͱ��£�һ��һ�����գ����干��\n��һ����������������\n");
                set("wield_msg", "$N�ӻ���ȡ��һ��$n���������У�������Խ���š�\n");
                set("unwield_msg", "$N�����е�$n���뻳�С�\n");
        }
    init_whip(20);
}  
mixed hit_ob(object me, object victim)
{
       if ((int)me->query_cps()+(int)me->query_int()+random((int)me->query_kar()) > (int)victim->query_cps()+random((int)victim->query_int())+random((int)victim->query_kar()))
        {
                victim->start_busy(3);
                return HIY "�����嶣�����죬��������֮����������$n�ĳ����������ν�����\n" NOR;
        }
        else
        {
                me->start_busy(4);
                return HIB "�����嶣�����죬��������֮������$n����������Ϊ������\n" NOR;
        }
}      
