#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_XIAO;
inherit F_UNIQUE;

void create()
{
        set_name(HIG"����"NOR,({ "yu xiao", "xiao" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 7000000);
                set("unique", 1);
                set("rigidity", 300);
                set("no_put", 1);
                set("no_steal", 1);
                set("replica_ob","/clone/weapon/zhuxiao");
                set("material", "steel");
                set("shape", "flute");
                set("long", 
                        "һ�����������ͨ�徧Ө���̣������ڴ�������ߣ������Ѫ����Ȼ����\n"
                        "������������ǧ��Ĺ��\n");
                set("wield_msg", 
                    HIG "$N��������һ֧����������ŵ�������������������˼���������㼴ƽ\n"
                        "����$N�漴�͵���������Ц�����ټ��ģ��������ڳճ�ЦЦ����\n"NOR);
                set("unwield_msg", CYN "$N��$n�嵽���ᡣ\n" NOR);
                set("unequip_msg", CYN "$N��$n�嵽���ᡣ\n" NOR);
        }

        setup();
}

void init()
{
        add_action("play_xiao", "play");
}

