#include <weapon.h> 
#include <ansi.h>
inherit SWORD; 

void create()
{
        set_name(HIR"�����ý�"NOR, ({ "jueshi haojian", "jueshi", "sword", "jian" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("long", HIR"����һ���ĳ������ı�����ȫ��ͨ�졣�˽�����"
                           "����ɽׯ��\n��ɽׯ��������ʦ��ʱ�������ɣ����ƽ���֮����\n"NOR);
                set("wield_msg", HIW"ɲ�Ǽ�һ����׳ɽ�ӵĺں�"
                             "������ʼ��������������������ǰ��\n"NOR);
                set("unwield_msg", HIW"����$N" HIW"��$n" HIW"����һָ��"
                                 "��ƥ���������𣬽�$n" HIW"����ʵʵ�ع���������\n"NOR);
                set("unit", "��");
                set("value", 10000);
                set("material", "steel"); 
                set("no_sell", 1);      
               
        }
        init_sword(140);
        setup();
}

int query_autoload()
{
       return 1;
}
