// zhenwu-jian.c ���佣
// Created by Lonely for only one object in mud
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;
void create()
{
        set_name(HIW"���佣"NOR, ({"zhenwu jian", "sword", "jian"}));
        set_weight(15000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ�Ѻ������۵ĹŽ�,��������Ļ������ƺ�������Щ����,�����Ͼ�Ȼ���м���ȱ�ڡ�\n");
                set("value", 100000);
                set("material", "blacksteel");
                set("weapon_prop/dodge", -2);
                set("weapon_prop/parry", 3);
                set("unique", 1);
                set("rigidity", 300);
                set("replica_ob","/d/city/npc/obj/changjian");
                set("no_put",1);
                set("no_steal",1);    
                set("wield_neili", 300);
                set("wield_maxneili", 700);
                set("wield_str", 22);        
                set("wield_msg",HIW"$N[��]��һ�����һ�����佣,�����ж�ʱ�������ޱߵ�ɱ����\n"NOR);
                set("unwield_msg",HIW"$N�����еı������뽣�ʡ����ܵ�ɱ��Ҳ������ʧ�ˡ�\n"NOR);
        }
        init_sword(400,2);
        setup();
}       


