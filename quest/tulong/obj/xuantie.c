#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        string tmp;
        int no;
        set_name(CYN "������" NOR,({"xuantie jian","xuantie","jian"}));
        set_weight(140000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�ؽ��޷棬���ɲ�������������������������������޷棬׾���ޱȡ�Ȼ�����ѽ������Ƹ������޼᲻�ݡ�������������ƾ���������¡�\n");
                set("material", "steel");
                set("no_drop", "��˱���������������󰡡�\n");
                set("no_give", "���ˣ�������ĳ�����\n");
                set("no_put", "��ϧ���ɡ�\n"); 
                set("no_sell", "������������������������ǲ��ǿ�����ˣ�\n");   
                set("wield_msg", CYN "$N�����ӱ���γ�����������ؼ��ʱһƬ����������������������\n" NOR);
                set("unwield_msg", CYN "$N��ɫ���أ������������뱳��Ĳ����У���ʱ�����������\n" NOR);
       }
// modified by chacha
       init_sword(70);
       setup();
// following 2 lines was added by chacha
       sscanf(file_name(),"%s#%d",tmp,no);
       if(no>0) destruct(this_object()); 
}

void init()
{
        add_action("do_get","get");
// modified by chacha
        set("weapon_prop/damage",this_player()->query("max_neili")/2);
}

int do_get(string arg)
{
        object me,ob;
        me=this_player();
        ob=this_object(); 

    if( !arg ) return notify_fail("��Ҫ����ʲ�ᶫ����\n");
        if (arg=="xuantie jian" || arg=="xuantie" || arg=="jian" ) 
         {
       if (me->query("str") < 31)
        return notify_fail("��������㣬�ò�����������\n");
        else
        write("��һ�Ѿ�����������\n");
        ob->move(me);
        return 1;
         }
}

void owner_is_killed()
{
       destruct(this_object());
}

